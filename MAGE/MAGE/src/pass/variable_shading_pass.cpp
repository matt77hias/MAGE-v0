//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\variable_shading_pass.hpp"
#include "rendering\renderer.hpp"
#include "rendering\rendering_state_cache.hpp"
#include "resource\resource_factory.hpp"
#include "math\view_frustum.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_VARIABLE_SHADING_PASS_VS_SCENE_BUFFER           0
#define MAGE_VARIABLE_SHADING_PASS_VS_MODEL_BUFFER           1
#define MAGE_VARIABLE_SHADING_PASS_PS_SCENE_BUFFER           0
#define MAGE_VARIABLE_SHADING_PASS_PS_MODEL_BUFFER           1
#define MAGE_VARIABLE_SHADING_PASS_PS_DIRECTIONAL_LIGHTS_SRV 0
#define MAGE_VARIABLE_SHADING_PASS_PS_OMNI_LIGHTS_SRV        1
#define MAGE_VARIABLE_SHADING_PASS_PS_SPOT_LIGHTS_SRV        2
#define MAGE_VARIABLE_SHADING_PASS_PS_DIFFUSE_SRV            3
#define MAGE_VARIABLE_SHADING_PASS_PS_SPECULAR_SRV           4
#define MAGE_VARIABLE_SHADING_PASS_PS_NORMAL_SRV             5
#define MAGE_VARIABLE_SHADING_PASS_PS_SAMPLER                0

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	VariableShadingPass::VariableShadingPass()
		: m_device_context(GetImmediateDeviceContext()),
		m_vs(CreateTransformVS()),
		m_ps{ CreateEmissivePS(), CreatePS(BRDFType::Unknown), CreateTSNMPS(BRDFType::Unknown) },
		m_bound_ps(PSIndex::Count), m_brdf(BRDFType::Unknown),
		m_model_buffer(), m_scene_buffer(),
		m_directional_lights_buffer(3), 
		m_omni_lights_buffer(32), 
		m_spot_lights_buffer(32) {}

	VariableShadingPass::VariableShadingPass(VariableShadingPass &&render_pass) = default;

	VariableShadingPass::~VariableShadingPass() = default;

	void VariableShadingPass::UpdatePSs(BRDFType brdf) {
		if (m_brdf != brdf) {
			m_brdf = brdf;
			m_ps[static_cast< size_t >(PSIndex::BRDF)]      = CreatePS(brdf);
			m_ps[static_cast< size_t >(PSIndex::BRDF_TSNM)] = CreateTSNMPS(brdf);
		}
	}

	void VariableShadingPass::BindPS(PSIndex index) noexcept {
		if (m_bound_ps != index) {
			m_ps[static_cast< size_t >(index)]->BindShader(m_device_context);
			m_bound_ps = index;
		}
	}

	void VariableShadingPass::BindPS(const Material *material) noexcept {
		
		if (!material->InteractsWithLight()) {
			BindPS(PSIndex::Emissive);
			return;
		}

		if (material->GetNormalSRV()) {
			BindPS(PSIndex::BRDF_TSNM);
		}
		else {
			BindPS(PSIndex::BRDF);
		}
	}

	void XM_CALLCONV VariableShadingPass::BindComponents(
		FXMMATRIX object_to_world, FXMMATRIX view_to_object,
		const Material *material) {

		ModelBuffer buffer;
		buffer.m_object_to_world                  = XMMatrixTranspose(object_to_world);
		buffer.m_object_to_view_inverse_transpose = view_to_object;
		buffer.m_Kd                               = material->GetDiffuseReflectivity();
		buffer.m_dissolve                         = material->GetDissolve();
		buffer.m_Ks                               = material->GetSpecularReflectivity();
		buffer.m_Ns                               = material->GetSpecularExponent();
		buffer.m_extra_parameters.x               = material->GetExtraParameter(0);
		buffer.m_extra_parameters.y               = material->GetExtraParameter(1);
		buffer.m_extra_parameters.z               = material->GetExtraParameter(2);
		buffer.m_extra_parameters.w               = material->GetExtraParameter(3);
		
		// Update the model buffer.
		m_model_buffer.UpdateData(m_device_context, buffer);
		// Bind the model buffer.
		VS::BindConstantBuffer(m_device_context, 
			MAGE_VARIABLE_SHADING_PASS_VS_MODEL_BUFFER, m_model_buffer.Get());
		PS::BindConstantBuffer(m_device_context, 
			MAGE_VARIABLE_SHADING_PASS_PS_MODEL_BUFFER, m_model_buffer.Get());

		// Bind the diffuse SRV.
		PS::BindSRV(m_device_context, 
			MAGE_VARIABLE_SHADING_PASS_PS_DIFFUSE_SRV, material->GetDiffuseReflectivitySRV());
		// Bind the specular SRV.
		PS::BindSRV(m_device_context, 
			MAGE_VARIABLE_SHADING_PASS_PS_SPECULAR_SRV, material->GetSpecularReflectivitySRV());
		// Bind the normal SRV.
		PS::BindSRV(m_device_context, 
			MAGE_VARIABLE_SHADING_PASS_PS_NORMAL_SRV, material->GetNormalSRV());
	}

	void VariableShadingPass::Render(const PassBuffer *scene, const CameraNode *node) {
		Assert(scene);
		Assert(node);

		// Reset the bound pixel shader index.
		m_bound_ps = PSIndex::Count;
		// Update the pixel shaders.
		UpdatePSs(node->GetSettings()->GetBRDF());

		// Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// Bind the rasterization state.
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// Bind the depth-stencil state.
		RenderingStateCache::Get()->BindDepthDefaultDepthStencilState(m_device_context);
		// Bind the blend state.
		RenderingStateCache::Get()->BindOpaqueBlendState(m_device_context);
		// Bind the sampler.
		PS::BindSampler(m_device_context, MAGE_VARIABLE_SHADING_PASS_PS_SAMPLER,
			RenderingStateCache::Get()->GetLinearWrapSamplerState());

		// Obtain node components.
		const TransformNode * const transform = node->GetTransform();
		const Camera        * const camera    = node->GetCamera();
		const XMMATRIX world_to_view          = transform->GetWorldToViewMatrix();
		const XMMATRIX view_to_world          = transform->GetViewToWorldMatrix();
		const XMMATRIX view_to_projection     = camera->GetViewToProjectionMatrix();
		const XMMATRIX world_to_projection    = world_to_view * view_to_projection;

		ProcessLights(scene->m_directional_lights, world_to_view);
		ProcessLights(scene->m_omni_lights, world_to_projection, world_to_view);
		ProcessLights(scene->m_spot_lights, world_to_projection, world_to_view);
		ProcessScene(scene, world_to_view, view_to_projection);
		ProcessModels(scene->m_opaque_models, world_to_projection, view_to_world);
		// Bind the blend state.
		if (Renderer::Get()->HasMSAA()) {
			RenderingStateCache::Get()->BindAlphaToCoverageBlendState(m_device_context);
		}
		else {
			RenderingStateCache::Get()->BindAlphaBlendState(m_device_context);
		}
		ProcessModels(scene->m_transparent_models, world_to_projection, view_to_world);
	}

	void XM_CALLCONV VariableShadingPass::ProcessScene(
		const PassBuffer *scene, 
		FXMMATRIX world_to_view, FXMMATRIX view_to_projection) {

		SceneBuffer scene_buffer;
		scene_buffer.m_world_to_view              = XMMatrixTranspose(world_to_view);
		scene_buffer.m_view_to_projection         = XMMatrixTranspose(view_to_projection);

		scene_buffer.m_Ia                         = scene->m_ambient_light;
		scene_buffer.m_nb_directional_lights      = static_cast< uint32_t >(m_directional_lights_buffer.size());
		scene_buffer.m_nb_omni_lights             = static_cast< uint32_t >(m_omni_lights_buffer.size());
		scene_buffer.m_nb_spot_lights             = static_cast< uint32_t >(m_spot_lights_buffer.size());

		scene_buffer.m_fog_color                  = scene->m_fog->GetIntensity();
		scene_buffer.m_fog_distance_falloff_start = scene->m_fog->GetStartDistanceFalloff();
		scene_buffer.m_fog_distance_falloff_range = scene->m_fog->GetRangeDistanceFalloff();

		// Update the scene buffer.
		m_scene_buffer.UpdateData(m_device_context, scene_buffer);
		// Bind the scene buffer.
		VS::BindConstantBuffer(m_device_context, 
			MAGE_VARIABLE_SHADING_PASS_VS_SCENE_BUFFER, m_scene_buffer.Get());
		PS::BindConstantBuffer(m_device_context, 
			MAGE_VARIABLE_SHADING_PASS_PS_SCENE_BUFFER, m_scene_buffer.Get());
	}

	void XM_CALLCONV VariableShadingPass::ProcessLights(
		const vector< const DirectionalLightNode * > &lights, 
		FXMMATRIX world_to_view) {
		
		vector< DirectionalLightBuffer > buffer;
		buffer.reserve(lights.size());
		
		for (const auto node : lights) {
			const TransformNode    * const transform = node->GetTransform();
			const DirectionalLight * const light     = node->GetLight();

			// Transform to view space.
			const XMVECTOR d = XMVector3TransformNormal(transform->GetWorldForward(), world_to_view);

			// Create a directional light buffer.
			DirectionalLightBuffer light_buffer;
			XMStoreFloat3(&light_buffer.m_d, d);
			light_buffer.m_I = light->GetIntensity();

			// Add directional light buffer to directional light buffers.
			buffer.push_back(std::move(light_buffer));
		}

		// Update the directional lights buffer.
		m_directional_lights_buffer.UpdateData(m_device_context, buffer);
		// Bind the directional lights buffer.
		PS::BindSRV(m_device_context, 
			MAGE_VARIABLE_SHADING_PASS_PS_DIRECTIONAL_LIGHTS_SRV,
			m_directional_lights_buffer.Get());
	}
	
	void XM_CALLCONV VariableShadingPass::ProcessLights(
		const vector< const OmniLightNode * > &lights,
		FXMMATRIX world_to_projection, FXMMATRIX world_to_view) {
		
		vector< OmniLightBuffer > buffer;
		buffer.reserve(lights.size());

		for (const auto node : lights) {
			const TransformNode * const transform = node->GetTransform();
			const OmniLight     * const light     = node->GetLight();
			const XMMATRIX object_to_world        = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection   = object_to_world * world_to_projection;

			// Cull the light against the view frustum.
			if (ViewFrustum::Cull(object_to_projection, light->GetBS())) {
				continue;
			}

			// Transform to view space.
			const XMVECTOR p = XMVector3TransformCoord(transform->GetWorldEye(), world_to_view);
			
			// Create an omni light buffer.
			OmniLightBuffer light_buffer;
			XMStoreFloat3(&light_buffer.m_p, p);
			light_buffer.m_I                      = light->GetIntensity();
			light_buffer.m_distance_falloff_end   = light->GetEndDistanceFalloff();
			light_buffer.m_distance_falloff_range = light->GetRangeDistanceFalloff();

			// Add omni light buffer to omni light buffers.
			buffer.push_back(std::move(light_buffer));
		}

		// Update the omni lights buffer.
		m_omni_lights_buffer.UpdateData(m_device_context, buffer);
		// Bind the omni lights buffer.
		PS::BindSRV(m_device_context,
			MAGE_VARIABLE_SHADING_PASS_PS_OMNI_LIGHTS_SRV,
			m_omni_lights_buffer.Get());
	}
	
	void XM_CALLCONV VariableShadingPass::ProcessLights(
		const vector< const SpotLightNode * > &lights,
		FXMMATRIX world_to_projection, FXMMATRIX world_to_view) {
		
		vector< SpotLightBuffer > buffer;
		buffer.reserve(lights.size());
		
		for (const auto node : lights) {
			const TransformNode  * const transform = node->GetTransform();
			const SpotLight      * const light     = node->GetLight();
			const XMMATRIX object_to_world         = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection    = object_to_world * world_to_projection;

			// Cull the light against the view frustum.
			if (ViewFrustum::Cull(object_to_projection, light->GetAABB())) {
				continue;
			}

			// Transform to view space.
			const XMVECTOR p = XMVector3TransformCoord( transform->GetWorldEye(),     world_to_view);
			const XMVECTOR d = XMVector3TransformNormal(transform->GetWorldForward(), world_to_view);

			// Create a spotlight buffer.
			SpotLightBuffer light_buffer;
			XMStoreFloat3(&light_buffer.m_p, p);
			XMStoreFloat3(&light_buffer.m_d, d);
			light_buffer.m_I                      = light->GetIntensity();
			light_buffer.m_exponent_property      = light->GetExponentProperty();
			light_buffer.m_distance_falloff_end   = light->GetEndDistanceFalloff();
			light_buffer.m_distance_falloff_range = light->GetRangeDistanceFalloff();
			light_buffer.m_cos_umbra              = light->GetEndAngularCutoff();
			light_buffer.m_cos_range              = light->GetRangeAngularCutoff();

			// Add spotlight buffer to spotlight buffers.
			buffer.push_back(std::move(light_buffer));
		}
		
		// Update the spotlights buffer.
		m_spot_lights_buffer.UpdateData(m_device_context, buffer);
		// Bind the spotlights buffer.
		PS::BindSRV(m_device_context,
			MAGE_VARIABLE_SHADING_PASS_PS_SPOT_LIGHTS_SRV,
			m_spot_lights_buffer.Get());
	}

	void XM_CALLCONV VariableShadingPass::ProcessModels(
		const vector< const ModelNode * > &models,
		FXMMATRIX world_to_projection, FXMMATRIX view_to_world) {

		for (const auto node : models) {
			const TransformNode * const transform = node->GetTransform();
			const Model         * const model     = node->GetModel();
			const XMMATRIX object_to_world        = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection   = object_to_world * world_to_projection;

			// Cull the model against the view frustum.
			if (ViewFrustum::Cull(object_to_projection, model->GetAABB())) {
				continue;
			}

			const XMMATRIX world_to_object        = transform->GetWorldToObjectMatrix();
			const XMMATRIX view_to_object         = view_to_world * world_to_object;
			const Material * const material       = model->GetMaterial();

			// Bind the components.
			BindComponents(object_to_world, view_to_object, material);
			// Bind the pixel shader.
			BindPS(material);

			// Bind the model.
			model->BindMesh(m_device_context);
			// Draw the model.
			model->Draw(m_device_context);
		}
	}
}