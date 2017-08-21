//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\basic_render_pass.hpp"
#include "rendering\rendering_state_cache.hpp"
#include "resource\resource_factory.hpp"
#include "math\view_frustum.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	BasicRenderPass::BasicRenderPass()
		: m_scene(nullptr), m_vs(), m_ps{},
		m_bound_ps(Count), m_render_mode(RenderMode::Default), m_brdf(BRDFType::Unknown),
		m_model_buffer(), m_scene_buffer(), m_directional_lights_buffer(3),
		m_omni_lights_buffer(32), m_spot_lights_buffer(32), 
		m_uv(CreateReferenceTexture()), m_box(CreateLineCube()) {

		InitializeShaders();
	}

	BasicRenderPass::BasicRenderPass(BasicRenderPass &&render_pass) = default;
	
	BasicRenderPass::~BasicRenderPass() = default;

	inline bool Cull(FXMMATRIX object_to_projection, const AABB &aabb) noexcept {
		const ViewFrustum view_frustum(object_to_projection);
		return !view_frustum.Overlaps(aabb);
	}

	inline bool Cull(FXMMATRIX object_to_projection, const BS &bs) noexcept {
		const ViewFrustum view_frustum(object_to_projection);
		return !view_frustum.Overlaps(bs);
	}

	size_t BasicRenderPass::ProcessDirectionalLights(FXMMATRIX world_to_view) {
		
		vector< DirectionalLightBuffer > buffer;
		buffer.reserve(m_scene->m_directional_lights.size());
		
		for (const auto node : m_scene->m_directional_lights) {
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

		m_directional_lights_buffer.UpdateData(buffer);
		BindDirectionalLightsBuffer();

		return buffer.size();
	}
	
	size_t BasicRenderPass::ProcessOmniLights(FXMMATRIX world_to_projection, FXMMATRIX world_to_view) {
		
		vector< OmniLightBuffer > buffer;
		buffer.reserve(m_scene->m_omni_lights.size());

		for (const auto node : m_scene->m_omni_lights) {
			const TransformNode * const transform = node->GetTransform();
			const OmniLight     * const light     = node->GetLight();
			const XMMATRIX object_to_world        = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection   = object_to_world * world_to_projection;

			// Cull the light against the view frustum.
			if (Cull(object_to_projection, light->GetBS())) {
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

		m_omni_lights_buffer.UpdateData(buffer);
		BindOmniLightsBuffer();

		return buffer.size();
	}
	
	size_t BasicRenderPass::ProcessSpotLights(FXMMATRIX world_to_projection, FXMMATRIX world_to_view) {
		
		vector< SpotLightBuffer > buffer;
		buffer.reserve(m_scene->m_spot_lights.size());
		
		for (const auto node : m_scene->m_spot_lights) {
			const TransformNode  * const transform = node->GetTransform();
			const SpotLight      * const light     = node->GetLight();
			const XMMATRIX object_to_world         = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection    = object_to_world * world_to_projection;

			// Cull the light against the view frustum.
			if (Cull(object_to_projection, light->GetAABB())) {
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
		
		m_spot_lights_buffer.UpdateData(buffer);
		BindSpotLightsBuffer();

		return buffer.size();
	}

	void BasicRenderPass::ProcessConstant(FXMMATRIX world_to_projection,
		FXMMATRIX world_to_view, FXMMATRIX view_to_projection, bool lighting = true) {

		SceneBuffer scene_buffer;
		scene_buffer.m_world_to_view      = XMMatrixTranspose(world_to_view);
		scene_buffer.m_view_to_projection = XMMatrixTranspose(view_to_projection);

		if (lighting) {
			const size_t nb_directional_lights        = ProcessDirectionalLights(world_to_view);
			const size_t nb_omni_lights               = ProcessOmniLights(world_to_projection, world_to_view);
			const size_t nb_spot_lights               = ProcessSpotLights(world_to_projection, world_to_view);
			
			scene_buffer.m_Ia                         = m_scene->m_ambient_light;
			scene_buffer.m_nb_directional_lights      = static_cast< uint32_t >(nb_directional_lights);
			scene_buffer.m_nb_omni_lights             = static_cast< uint32_t >(nb_omni_lights);
			scene_buffer.m_nb_spot_lights             = static_cast< uint32_t >(nb_spot_lights);

			scene_buffer.m_fog_color                  = m_scene->m_fog->GetIntensity();
			scene_buffer.m_fog_distance_falloff_start = m_scene->m_fog->GetStartDistanceFalloff();
			scene_buffer.m_fog_distance_falloff_range = m_scene->m_fog->GetRangeDistanceFalloff();
		}

		m_scene_buffer.UpdateData(scene_buffer);
		BindSceneBuffer();
	}

	void BasicRenderPass::ProcessNonConstant(FXMMATRIX object_to_world, FXMMATRIX view_to_object,
		const Material *material) {

		ModelBuffer buffer;
		buffer.m_object_to_world = XMMatrixTranspose(object_to_world);
		buffer.m_object_to_view_inverse_transpose = view_to_object;
		buffer.m_Kd                               = material->GetDiffuseReflectivity();
		buffer.m_dissolve                         = material->GetDissolve();
		buffer.m_Ks                               = material->GetSpecularReflectivity();
		buffer.m_Ns                               = material->GetSpecularExponent();
		buffer.m_extra_parameters.x               = material->GetExtraParameter(0);
		buffer.m_extra_parameters.y               = material->GetExtraParameter(1);
		buffer.m_extra_parameters.z               = material->GetExtraParameter(2);
		buffer.m_extra_parameters.w               = material->GetExtraParameter(3);
		
		m_model_buffer.UpdateData(buffer);
		BindModelBuffer();

		BindPixelShader(material);
		PS::BindSRV(3, material->GetDiffuseReflectivitySRV());
		PS::BindSRV(4, material->GetSpecularReflectivitySRV());
		PS::BindSRV(5, material->GetNormalSRV());
	}

	void BasicRenderPass::ProcessModels(const vector< const ModelNode * > &models,
		FXMMATRIX world_to_projection, FXMMATRIX view_to_world) {

		for (const auto node : models) {
			const TransformNode * const transform = node->GetTransform();
			const Model         * const model     = node->GetModel();
			const XMMATRIX object_to_world        = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection   = object_to_world * world_to_projection;

			// Cull the model against the view frustum.
			if (Cull(object_to_projection, model->GetAABB())) {
				continue;
			}

			const XMMATRIX world_to_object        = transform->GetWorldToObjectMatrix();
			const XMMATRIX view_to_object         = view_to_world * world_to_object;
			const Material * const material       = model->GetMaterial();

			ProcessNonConstant(object_to_world, view_to_object, material);

			// Bind model.
			model->BindMesh();
			// Draw model.
			model->Draw();
		}
	}

	void BasicRenderPass::ProcessModels(const vector< const ModelNode * > &models,
		FXMMATRIX world_to_projection, FXMMATRIX view_to_world, const Material *material) {

		for (const auto node : models) {
			const TransformNode * const transform = node->GetTransform();
			const Model         * const model     = node->GetModel();
			const XMMATRIX object_to_world        = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection   = object_to_world * world_to_projection;

			// Cull the model against the view frustum.
			if (Cull(object_to_projection, model->GetAABB())) {
				continue;
			}

			const XMMATRIX world_to_object        = transform->GetWorldToObjectMatrix();
			const XMMATRIX view_to_object         = view_to_world * world_to_object;

			ProcessNonConstant(object_to_world, view_to_object, material);

			// Bind model.
			model->BindMesh();
			// Draw model.
			model->Draw();
		}
	}

	void BasicRenderPass::ProcessModelAABBs(const vector< const ModelNode * > &models,
		FXMMATRIX world_to_projection, FXMMATRIX view_to_world, const Material *material) {

		for (const auto node : models) {
			const TransformNode * const transform = node->GetTransform();
			const Model         * const model     = node->GetModel();
			const XMMATRIX object_to_world        = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection   = object_to_world * world_to_projection;
			const AABB &aabb                      = model->GetAABB();

			// Cull the model against the view frustum.
			if (Cull(object_to_projection, aabb)) {
				continue;
			}

			Transform box_transform;
			box_transform.SetScale(aabb.Diagonal());
			box_transform.SetTranslation(aabb.Centroid());

			const XMMATRIX world_to_object        = transform->GetWorldToObjectMatrix();
			const XMMATRIX box_to_world           = box_transform.GetObjectToParentMatrix() * object_to_world;
			const XMMATRIX world_to_box           = world_to_object * box_transform.GetParentToObjectMatrix();
			const XMMATRIX view_to_box            = view_to_world * world_to_box;

			ProcessNonConstant(box_to_world, view_to_box, material);

			// Bind model.
			m_box->BindMesh();
			// Draw model.
			m_box->Draw();
		}
	}

	void BasicRenderPass::ProcessOmniLightAABBs(
		FXMMATRIX world_to_projection, FXMMATRIX view_to_world, const Material *material) {

		for (const auto node : m_scene->m_omni_lights) {
			const TransformNode * const transform = node->GetTransform();
			const OmniLight     * const light     = node->GetLight();
			const XMMATRIX object_to_world        = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection   = object_to_world * world_to_projection;
			const AABB &aabb                      = light->GetAABB();

			// Cull the model against the view frustum.
			if (Cull(object_to_projection, light->GetBS())) {
				continue;
			}

			Transform box_transform;
			box_transform.SetScale(aabb.Diagonal());
			box_transform.SetTranslation(aabb.Centroid());

			const XMMATRIX world_to_object        = transform->GetWorldToObjectMatrix();
			const XMMATRIX box_to_world           = box_transform.GetObjectToParentMatrix() * object_to_world;
			const XMMATRIX world_to_box           = world_to_object * box_transform.GetParentToObjectMatrix();
			const XMMATRIX view_to_box            = view_to_world * world_to_box;

			ProcessNonConstant(box_to_world, view_to_box, material);

			// Bind model.
			m_box->BindMesh();
			// Draw model.
			m_box->Draw();
		}
	}

	void BasicRenderPass::ProcessSpotLightAABBs(
		FXMMATRIX world_to_projection, FXMMATRIX view_to_world, const Material *material) {

		for (const auto node : m_scene->m_spot_lights) {
			const TransformNode * const transform = node->GetTransform();
			const SpotLight     * const light     = node->GetLight();
			const XMMATRIX object_to_world        = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection   = object_to_world * world_to_projection;
			const AABB &aabb                      = light->GetAABB();

			// Cull the model against the view frustum.
			if (Cull(object_to_projection, aabb)) {
				continue;
			}

			Transform box_transform;
			box_transform.SetScale(aabb.Diagonal());
			box_transform.SetTranslation(aabb.Centroid());

			const XMMATRIX world_to_object        = transform->GetWorldToObjectMatrix();
			const XMMATRIX box_to_world           = box_transform.GetObjectToParentMatrix() * object_to_world;
			const XMMATRIX world_to_box           = world_to_object * box_transform.GetParentToObjectMatrix();
			const XMMATRIX view_to_box            = view_to_world * world_to_box;

			ProcessNonConstant(box_to_world, view_to_box, material);

			// Bind model.
			m_box->BindMesh();
			// Draw model.
			m_box->Draw();
		}
	}

	void BasicRenderPass::InitializeShaders() {
		m_brdf                           = BRDFType::Unknown;
		m_vs                             = CreateTransformVS();
		m_ps[Default_Emissive]           = CreateEmissivePS();
		m_ps[Default_BRDF]               = CreatePS(m_brdf);
		m_ps[Default_BRDFTSNM]           = CreateTSNMPS(m_brdf);
		m_ps[DiffuseReflectivity]        = CreateDiffuseReflectivityPS();
		m_ps[DiffuseReflectivityTexture] = CreateDiffuseReflectivityTexturePS();
		m_ps[ShadingNormal]              = CreateShadingNormalPS();
		m_ps[TSNMShadingNormal]          = CreateShadingNormalTSNMPS();
		m_ps[Distance]                   = CreateDistancePS();
		m_bound_ps                       = Count;
	}

	void BasicRenderPass::UpdatePixelShaders(BRDFType brdf) {
		if (m_brdf != brdf) {
			m_brdf                 = brdf;
			m_ps[Default_BRDF]     = CreatePS(brdf);
			m_ps[Default_BRDFTSNM] = CreateTSNMPS(brdf);
			m_bound_ps             = Count;
		}
	}

	void BasicRenderPass::BindPixelShader(PSIndex index) noexcept {
		if (m_bound_ps != index) {
			m_ps[index]->BindShader();
			m_bound_ps = index;
		}
	}
		
	void BasicRenderPass::BindPixelShader(const Material *material) noexcept {
		switch (m_render_mode) {
		case RenderMode::Default: {
			if (!material->InteractsWithLight()) {
				BindPixelShader(Default_Emissive);
				return;
			}

			if (material->GetNormalSRV()) {
				BindPixelShader(Default_BRDFTSNM);
			}
			else {
				BindPixelShader(Default_BRDF);
			}

			break;
		}
		case RenderMode::Solid: {
			BindPixelShader(Default_BRDF);
			break;
		}
		case RenderMode::DiffuseTexture:
		case RenderMode::UVTexture: {
			BindPixelShader(DiffuseReflectivityTexture);
			break;
		}
		case RenderMode::ShadingNormal: {
			BindPixelShader(ShadingNormal);
			break;
		}
		case RenderMode::TSNMShadingNormal: {
			if (material->GetNormalSRV()) {
				BindPixelShader(TSNMShadingNormal);
			}
			else {
				BindPixelShader(ShadingNormal);
			}
			break;
		}
		case RenderMode::Distance: {
			BindPixelShader(Distance);
			break;
		}
		default: {
			BindPixelShader(DiffuseReflectivity);
		}
		}
	}

	void BasicRenderPass::Render(const PassBuffer *buffer) {
		m_scene = buffer;
		m_bound_ps = Count;
		
		for (const auto node : m_scene->m_cameras) {
			const CameraSettings *settings = node->GetSettings();

			switch (settings->GetRenderMode()) {
			
			case RenderMode::Default: {
				RenderDefault(node);
				break;
			}
			case RenderMode::Solid: {
				RenderSolid(node);
				break;
			}
			case RenderMode::DiffuseTexture: {
				RenderDiffuseTexture(node);
				break;
			}
			case RenderMode::UVTexture: {
				RenderUVTexture(node);
				break;
			}
			case RenderMode::ShadingNormal: {
				RenderShadingNormal(node);
				break;
			}
			case RenderMode::TSNMShadingNormal: {
				RenderTSNMShadingNormal(node);
				break;
			}
			case RenderMode::Distance: {
				RenderDistance(node);
				break;
			}
			default: {
				break;
			}
			}

			if (settings->HasRenderLayer(RenderLayer::Wireframe)) {
				RenderWireframe(node);
			}
			if (settings->HasRenderLayer(RenderLayer::AABB)) {
				RenderAABB(node);
			}
		}
	}

	void BasicRenderPass::RenderDefault(const CameraNode *node) {
		m_render_mode = RenderMode::Default;
		UpdatePixelShaders(node->GetSettings()->GetBRDF());
		
		m_vs->BindShader();
		RenderingStateCache::Get()->BindDepthDefaultDepthStencilState();
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState();
		RenderingStateCache::Get()->BindOpaqueBlendState();
		PS::BindSampler(0, RenderingStateCache::Get()->GetLinearWrapSamplerState());
		node->GetViewport().BindViewport();

		const TransformNode * const transform = node->GetTransform();
		const Camera        * const camera    = node->GetCamera();
		const XMMATRIX world_to_view          = transform->GetWorldToViewMatrix();
		const XMMATRIX view_to_world          = transform->GetViewToWorldMatrix();
		const XMMATRIX view_to_projection     = camera->GetViewToProjectionMatrix();
		const XMMATRIX world_to_projection    = world_to_view * view_to_projection;

		ProcessConstant(world_to_projection, world_to_view, view_to_projection, true);
		ProcessModels(m_scene->m_opaque_models, world_to_projection, view_to_world);
		RenderingStateCache::Get()->BindAlphaBlendState();
		ProcessModels(m_scene->m_transparent_models, world_to_projection, view_to_world);
	}

	void BasicRenderPass::RenderSolid(const CameraNode *node) {
		m_render_mode = RenderMode::Solid;
		
		m_vs->BindShader();
		RenderingStateCache::Get()->BindDepthDefaultDepthStencilState();
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState();
		RenderingStateCache::Get()->BindOpaqueBlendState();
		PS::BindSampler(0, RenderingStateCache::Get()->GetLinearWrapSamplerState());
		node->GetViewport().BindViewport();

		const TransformNode * const transform = node->GetTransform();
		const Camera        * const camera    = node->GetCamera();
		const XMMATRIX world_to_view          = transform->GetWorldToViewMatrix();
		const XMMATRIX view_to_world          = transform->GetViewToWorldMatrix();
		const XMMATRIX view_to_projection     = camera->GetViewToProjectionMatrix();
		const XMMATRIX world_to_projection    = world_to_view * view_to_projection;

		Material material;
		material.SetDiffuseReflectivity(RGBSpectrum(1.0f));

		ProcessConstant(world_to_projection, world_to_view, view_to_projection, true);
		ProcessModels(m_scene->m_opaque_models, world_to_projection, view_to_world, &material);
		ProcessModels(m_scene->m_transparent_models, world_to_projection, view_to_world, &material);
	}

	void BasicRenderPass::RenderDiffuseTexture(const CameraNode *node) {
		m_render_mode = RenderMode::DiffuseTexture;
		
		m_vs->BindShader();
		RenderingStateCache::Get()->BindDepthDefaultDepthStencilState();
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState();
		RenderingStateCache::Get()->BindOpaqueBlendState();
		PS::BindSampler(0, RenderingStateCache::Get()->GetLinearWrapSamplerState());
		node->GetViewport().BindViewport();
		
		const TransformNode * const transform = node->GetTransform();
		const Camera        * const camera    = node->GetCamera();
		const XMMATRIX world_to_view          = transform->GetWorldToViewMatrix();
		const XMMATRIX view_to_world          = transform->GetViewToWorldMatrix();
		const XMMATRIX view_to_projection     = camera->GetViewToProjectionMatrix();
		const XMMATRIX world_to_projection    = world_to_view * view_to_projection;

		ProcessConstant(world_to_projection, world_to_view, view_to_projection, false);
		ProcessModels(m_scene->m_opaque_models, world_to_projection, view_to_world);
		RenderingStateCache::Get()->BindAlphaBlendState();
		ProcessModels(m_scene->m_transparent_models, world_to_projection, view_to_world);
	}

	void BasicRenderPass::RenderUVTexture(const CameraNode *node) {
		m_render_mode = RenderMode::UVTexture;
		
		m_vs->BindShader();
		RenderingStateCache::Get()->BindDepthDefaultDepthStencilState();
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState();
		RenderingStateCache::Get()->BindOpaqueBlendState();
		PS::BindSampler(0, RenderingStateCache::Get()->GetLinearWrapSamplerState());
		node->GetViewport().BindViewport();

		const TransformNode * const transform = node->GetTransform();
		const Camera        * const camera    = node->GetCamera();
		const XMMATRIX world_to_view          = transform->GetWorldToViewMatrix();
		const XMMATRIX view_to_world          = transform->GetViewToWorldMatrix();
		const XMMATRIX view_to_projection     = camera->GetViewToProjectionMatrix();
		const XMMATRIX world_to_projection    = world_to_view * view_to_projection;

		Material material;
		material.SetDiffuseReflectivity(RGBSpectrum(1.0f));
		material.SetDiffuseReflectivityTexture(m_uv);

		ProcessConstant(world_to_projection, world_to_view, view_to_projection, false);
		ProcessModels(m_scene->m_opaque_models, world_to_projection, view_to_world, &material);
		ProcessModels(m_scene->m_transparent_models, world_to_projection, view_to_world, &material);
	}
	
	void BasicRenderPass::RenderShadingNormal(const CameraNode *node) {
		m_render_mode = RenderMode::ShadingNormal;
		
		m_vs->BindShader();
		RenderingStateCache::Get()->BindDepthDefaultDepthStencilState();
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState();
		RenderingStateCache::Get()->BindOpaqueBlendState();
		PS::BindSampler(0, RenderingStateCache::Get()->GetLinearWrapSamplerState());
		node->GetViewport().BindViewport();

		const TransformNode * const transform = node->GetTransform();
		const Camera        * const camera    = node->GetCamera();
		const XMMATRIX world_to_view          = transform->GetWorldToViewMatrix();
		const XMMATRIX view_to_world          = transform->GetViewToWorldMatrix();
		const XMMATRIX view_to_projection     = camera->GetViewToProjectionMatrix();
		const XMMATRIX world_to_projection    = world_to_view * view_to_projection;

		ProcessConstant(world_to_projection, world_to_view, view_to_projection, false);
		ProcessModels(m_scene->m_opaque_models, world_to_projection, view_to_world);
		ProcessModels(m_scene->m_transparent_models, world_to_projection, view_to_world);
	}

	void BasicRenderPass::RenderTSNMShadingNormal(const CameraNode *node) {
		m_render_mode = RenderMode::TSNMShadingNormal;
		
		m_vs->BindShader();
		RenderingStateCache::Get()->BindDepthDefaultDepthStencilState();
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState();
		RenderingStateCache::Get()->BindOpaqueBlendState();
		PS::BindSampler(0, RenderingStateCache::Get()->GetLinearWrapSamplerState());
		node->GetViewport().BindViewport();

		const TransformNode * const transform = node->GetTransform();
		const Camera        * const camera    = node->GetCamera();
		const XMMATRIX world_to_view          = transform->GetWorldToViewMatrix();
		const XMMATRIX view_to_world          = transform->GetViewToWorldMatrix();
		const XMMATRIX view_to_projection     = camera->GetViewToProjectionMatrix();
		const XMMATRIX world_to_projection    = world_to_view * view_to_projection;

		ProcessConstant(world_to_projection, world_to_view, view_to_projection, false);
		ProcessModels(m_scene->m_opaque_models, world_to_projection, view_to_world);
		ProcessModels(m_scene->m_transparent_models, world_to_projection, view_to_world);
	}

	void BasicRenderPass::RenderDistance(const CameraNode *node) {
		m_render_mode = RenderMode::Distance;
		
		m_vs->BindShader();
		RenderingStateCache::Get()->BindDepthDefaultDepthStencilState();
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState();
		RenderingStateCache::Get()->BindOpaqueBlendState();
		PS::BindSampler(0, RenderingStateCache::Get()->GetLinearWrapSamplerState());
		node->GetViewport().BindViewport();

		const TransformNode * const transform = node->GetTransform();
		const Camera        * const camera    = node->GetCamera();
		const XMMATRIX world_to_view          = transform->GetWorldToViewMatrix();
		const XMMATRIX view_to_world          = transform->GetViewToWorldMatrix();
		const XMMATRIX view_to_projection     = camera->GetViewToProjectionMatrix();
		const XMMATRIX world_to_projection    = world_to_view * view_to_projection;

		ProcessConstant(world_to_projection, world_to_view, view_to_projection, false);
		ProcessModels(m_scene->m_opaque_models, world_to_projection, view_to_world);
		ProcessModels(m_scene->m_transparent_models, world_to_projection, view_to_world);
	}

	void BasicRenderPass::RenderAABB(const CameraNode *node) {
		m_render_mode = RenderMode::None;
		
		m_vs->BindShader();
		RenderingStateCache::Get()->BindDepthDefaultDepthStencilState();
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState();
		RenderingStateCache::Get()->BindOpaqueBlendState();
		PS::BindSampler(0, RenderingStateCache::Get()->GetLinearWrapSamplerState());
		node->GetViewport().BindViewport();

		const TransformNode * const transform = node->GetTransform();
		const Camera        * const camera    = node->GetCamera();
		const XMMATRIX world_to_view          = transform->GetWorldToViewMatrix();
		const XMMATRIX view_to_world          = transform->GetViewToWorldMatrix();
		const XMMATRIX view_to_projection     = camera->GetViewToProjectionMatrix();
		const XMMATRIX world_to_projection    = world_to_view * view_to_projection;

		Material material_light;
		material_light.SetDiffuseReflectivity(RGBSpectrum(1.0f, 0.0f, 0.0f));
		Material material_model;
		material_model.SetDiffuseReflectivity(RGBSpectrum(0.0f, 1.0f, 0.0f));

		ProcessConstant(world_to_projection, world_to_view, view_to_projection, false);
		ProcessModelAABBs(m_scene->m_opaque_models, world_to_projection, view_to_world, &material_model);
		ProcessModelAABBs(m_scene->m_transparent_models, world_to_projection, view_to_world, &material_model);
		ProcessOmniLightAABBs(world_to_projection, view_to_world, &material_light);
		ProcessSpotLightAABBs(world_to_projection, view_to_world, &material_light);
	}

	void BasicRenderPass::RenderWireframe(const CameraNode *node) {
		m_render_mode = RenderMode::None;
		
		m_vs->BindShader();
		RenderingStateCache::Get()->BindDepthDefaultDepthStencilState();
		RenderingStateCache::Get()->BindWireframeRasterizerState();
		RenderingStateCache::Get()->BindOpaqueBlendState();
		PS::BindSampler(0, RenderingStateCache::Get()->GetLinearWrapSamplerState());
		node->GetViewport().BindViewport();
		
		const TransformNode * const transform = node->GetTransform();
		const Camera        * const camera    = node->GetCamera();
		const XMMATRIX world_to_view          = transform->GetWorldToViewMatrix();
		const XMMATRIX view_to_world          = transform->GetViewToWorldMatrix();
		const XMMATRIX view_to_projection     = camera->GetViewToProjectionMatrix();
		const XMMATRIX world_to_projection    = world_to_view * view_to_projection;

		Material material;
		material.SetDiffuseReflectivity(RGBSpectrum(0.0f, 0.0f, 1.0f));

		ProcessConstant(world_to_projection, world_to_view, view_to_projection, false);
		ProcessModels(m_scene->m_opaque_models, world_to_projection, view_to_world, &material);
		ProcessModels(m_scene->m_transparent_models, world_to_projection, view_to_world, &material);
	}
}