//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\variable_component_pass.hpp"
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

#define MAGE_VARIABLE_COMPONENT_PASS_VS_SCENE_BUFFER 0
#define MAGE_VARIABLE_COMPONENT_PASS_VS_MODEL_BUFFER 1
#define MAGE_VARIABLE_COMPONENT_PASS_PS_COLOR_BUFFER 0
#define MAGE_VARIABLE_COMPONENT_PASS_PS_TEXTURE_SRV  0
#define MAGE_VARIABLE_COMPONENT_PASS_PS_SAMPLER      0

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	VariableComponentPass::VariableComponentPass()
		: m_device_context(GetImmediateDeviceContext()), 
		m_vs(CreateMinimalTransformVS()),
		m_ps(CreateConstantColorTexturePS()),
		m_model_buffer(), m_scene_buffer(), 
		m_color_buffer(), m_white(CreateWhiteTexture()) {}

	VariableComponentPass::VariableComponentPass(VariableComponentPass &&render_pass) = default;

	VariableComponentPass::~VariableComponentPass() = default;

	void VariableComponentPass::BindComponent(const Material *material) noexcept {
		switch (m_render_mode) {

		case RenderMode::DiffuseColor: {

			// Update the color buffer.
			m_color_buffer.UpdateData(m_device_context, RGBASpectrum(material->GetDiffuseReflectivity(), material->GetDissolve()));
			// Bind the color buffer.
			PS::BindConstantBuffer(m_device_context,
				MAGE_VARIABLE_COMPONENT_PASS_PS_COLOR_BUFFER, m_color_buffer.Get());

			// Bind the diffuse SRV.
			PS::BindSRV(m_device_context,
				MAGE_VARIABLE_COMPONENT_PASS_PS_TEXTURE_SRV, material->GetDiffuseReflectivitySRV());

			break;
		}
		
		case RenderMode::DiffuseReflectivity: {

			// Update the color buffer.
			m_color_buffer.UpdateData(m_device_context, RGBASpectrum(material->GetDiffuseReflectivity(), material->GetDissolve()));
			// Bind the color buffer.
			PS::BindConstantBuffer(m_device_context,
				MAGE_VARIABLE_COMPONENT_PASS_PS_COLOR_BUFFER, m_color_buffer.Get());

			// Bind the diffuse SRV.
			PS::BindSRV(m_device_context,
				MAGE_VARIABLE_COMPONENT_PASS_PS_TEXTURE_SRV, m_white->Get());

			break;
		}

		case RenderMode::DiffuseReflectivityTexture: {

			// Update the color buffer.
			m_color_buffer.UpdateData(m_device_context, RGBASpectrum(1.0f));
			// Bind the color buffer.
			PS::BindConstantBuffer(m_device_context,
				MAGE_VARIABLE_COMPONENT_PASS_PS_COLOR_BUFFER, m_color_buffer.Get());

			// Bind the diffuse SRV.
			PS::BindSRV(m_device_context,
				MAGE_VARIABLE_COMPONENT_PASS_PS_TEXTURE_SRV, material->GetDiffuseReflectivitySRV());

			break;
		}

		case RenderMode::SpecularColor: {

			// Update the color buffer.
			m_color_buffer.UpdateData(m_device_context, RGBASpectrum(material->GetSpecularReflectivity()));
			// Bind the color buffer.
			PS::BindConstantBuffer(m_device_context,
				MAGE_VARIABLE_COMPONENT_PASS_PS_COLOR_BUFFER, m_color_buffer.Get());

			// Bind the diffuse SRV.
			PS::BindSRV(m_device_context,
				MAGE_VARIABLE_COMPONENT_PASS_PS_TEXTURE_SRV, material->GetSpecularReflectivitySRV());

			break;
		}

		case RenderMode::SpecularReflectivity: {

			// Update the color buffer.
			m_color_buffer.UpdateData(m_device_context, RGBASpectrum(material->GetSpecularReflectivity()));
			// Bind the color buffer.
			PS::BindConstantBuffer(m_device_context,
				MAGE_VARIABLE_COMPONENT_PASS_PS_COLOR_BUFFER, m_color_buffer.Get());

			// Bind the diffuse SRV.
			PS::BindSRV(m_device_context,
				MAGE_VARIABLE_COMPONENT_PASS_PS_TEXTURE_SRV, m_white->Get());

			break;
		}

		case RenderMode::SpecularReflectivityTexture: {

			// Update the color buffer.
			m_color_buffer.UpdateData(m_device_context, RGBASpectrum(1.0f));
			// Bind the color buffer.
			PS::BindConstantBuffer(m_device_context,
				MAGE_VARIABLE_COMPONENT_PASS_PS_COLOR_BUFFER, m_color_buffer.Get());

			// Bind the diffuse SRV.
			PS::BindSRV(m_device_context,
				MAGE_VARIABLE_COMPONENT_PASS_PS_TEXTURE_SRV, material->GetSpecularReflectivitySRV());

			break;
		}

		case RenderMode::NormalTexture: {

			// Update the color buffer.
			m_color_buffer.UpdateData(m_device_context, RGBASpectrum(1.0f));
			// Bind the color buffer.
			PS::BindConstantBuffer(m_device_context,
				MAGE_VARIABLE_COMPONENT_PASS_PS_COLOR_BUFFER, m_color_buffer.Get());

			// Bind the diffuse SRV.
			PS::BindSRV(m_device_context,
				MAGE_VARIABLE_COMPONENT_PASS_PS_TEXTURE_SRV, material->GetNormalSRV());

			break;
		}
		}
	}

	void VariableComponentPass::Render(const PassBuffer *scene, const CameraNode *node) {
		Assert(scene);
		Assert(node);

		// Reset the render mode.
		m_render_mode = node->GetSettings()->GetRenderMode();

		// Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// Bind the pixel shader.
		m_ps->BindShader(m_device_context);
		// Bind the rasterization state.
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// Bind the depth-stencil state.
		RenderingStateCache::Get()->BindDepthDefaultDepthStencilState(m_device_context);
		// Bind the blend state.
		RenderingStateCache::Get()->BindOpaqueBlendState(m_device_context);
		// Bind the sampler.
		PS::BindSampler(m_device_context, MAGE_VARIABLE_COMPONENT_PASS_PS_SAMPLER,
			RenderingStateCache::Get()->GetLinearWrapSamplerState());
			
		// Obtain node components.
		const TransformNode * const transform = node->GetTransform();
		const Camera        * const camera    = node->GetCamera();
		const XMMATRIX world_to_view          = transform->GetWorldToViewMatrix();
		const XMMATRIX view_to_world          = transform->GetViewToWorldMatrix();
		const XMMATRIX view_to_projection     = camera->GetViewToProjectionMatrix();
		const XMMATRIX world_to_projection    = world_to_view * view_to_projection;

		ProcessScene(world_to_view, view_to_projection);
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

	void VariableComponentPass::ProcessScene(FXMMATRIX world_to_view, FXMMATRIX view_to_projection) {
		SceneTransformBuffer buffer;
		buffer.m_world_to_view      = XMMatrixTranspose(world_to_view);
		buffer.m_view_to_projection = XMMatrixTranspose(view_to_projection);

		// Update the scene buffer.
		m_scene_buffer.UpdateData(m_device_context, buffer);
		// Bind the scene buffer.
		VS::BindConstantBuffer(m_device_context, 
			MAGE_VARIABLE_COMPONENT_PASS_VS_SCENE_BUFFER, m_scene_buffer.Get());
	}

	void VariableComponentPass::ProcessModels(const vector< const ModelNode * > &models,
		FXMMATRIX world_to_projection, FXMMATRIX view_to_world) {

		for (const auto node : models) {

			// Obtain node components (1/2).
			const TransformNode * const transform = node->GetTransform();
			const Model         * const model     = node->GetModel();
			const XMMATRIX object_to_world        = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection   = object_to_world * world_to_projection;

			// Apply view frustum culling.
			if (ViewFrustum::Cull(object_to_projection, model->GetAABB())) {
				continue;
			}

			// Obtain node components (2/2).
			const XMMATRIX world_to_object        = transform->GetWorldToObjectMatrix();
			const XMMATRIX view_to_object         = view_to_world * world_to_object;
			const Material * const material       = model->GetMaterial();
				
			ModelTransformBuffer buffer;
			buffer.m_object_to_world = XMMatrixTranspose(object_to_world);
			buffer.m_object_to_view_inverse_transpose = view_to_object;

			// Update the model buffer.
			m_model_buffer.UpdateData(m_device_context, buffer);
			// Bind the model buffer.
			VS::BindConstantBuffer(m_device_context, 
				MAGE_VARIABLE_COMPONENT_PASS_VS_MODEL_BUFFER, m_model_buffer.Get());

			// Bind the component.
			BindComponent(material);
			
			// Bind the model.
			model->BindMesh(m_device_context);
			// Draw the model.
			model->Draw(m_device_context);
		}
	}
}