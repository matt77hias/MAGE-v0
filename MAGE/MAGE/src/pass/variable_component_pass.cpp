//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_renderer.hpp"
#include "rendering\renderer.hpp"
#include "rendering\rendering_state_cache.hpp"
#include "resource\resource_factory.hpp"
#include "math\view_frustum.hpp"
#include "logging\error.hpp"

// Include HLSL bindings.
#include "..\..\shaders\hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	VariableComponentPass *VariableComponentPass::Get() {
		Assert(SceneRenderer::Get());

		return SceneRenderer::Get()->GetVariableComponentPass();
	}

	VariableComponentPass::VariableComponentPass()
		: m_device_context(GetImmediateDeviceContext()), 
		m_vs(CreateMinimalTransformVS()),
		m_ps(CreateConstantColorTexturePS()),
		m_color_buffer(), m_projection_buffer(), m_model_buffer(),
		m_white(CreateWhiteTexture()) {}

	VariableComponentPass::VariableComponentPass(VariableComponentPass &&render_pass) = default;

	VariableComponentPass::~VariableComponentPass() = default;

	void XM_CALLCONV VariableComponentPass::BindProjectionData(
		FXMMATRIX view_to_projection) {

		// Update the projection buffer.
		m_projection_buffer.UpdateData(m_device_context, 
			XMMatrixTranspose(view_to_projection));
		// Bind the projection buffer.
		VS::BindConstantBuffer(m_device_context,
			SLOT_CBUFFER_PER_FRAME, m_projection_buffer.Get());
	}

	void XM_CALLCONV VariableComponentPass::BindModelData(
		FXMMATRIX object_to_view,
		CXMMATRIX view_to_object,
		CXMMATRIX texture_transform,
		const Material *material) {

		ModelNormalTextureTransformBuffer buffer;
		buffer.m_object_to_view = XMMatrixTranspose(object_to_view);
		buffer.m_normal_to_view = view_to_object;

		switch (m_render_mode) {

		case RenderMode::DiffuseColor: {

			buffer.m_texture_transform = texture_transform;

			// Update the color buffer.
			m_color_buffer.UpdateData(m_device_context, 
				RGBASpectrum(material->GetDiffuseReflectivity(), material->GetDissolve()));
			// Bind the color buffer.
			PS::BindConstantBuffer(m_device_context,
				SLOT_CBUFFER_COLOR, m_color_buffer.Get());

			// Bind the diffuse SRV.
			PS::BindSRV(m_device_context,
				SLOT_SRV_TEXTURE, material->GetDiffuseReflectivitySRV());

			break;
		}
		
		case RenderMode::DiffuseReflectivity: {

			buffer.m_texture_transform = texture_transform;

			// Update the color buffer.
			m_color_buffer.UpdateData(m_device_context, 
				RGBASpectrum(material->GetDiffuseReflectivity(), material->GetDissolve()));
			// Bind the color buffer.
			PS::BindConstantBuffer(m_device_context,
				SLOT_CBUFFER_COLOR, m_color_buffer.Get());

			// Bind the diffuse SRV.
			PS::BindSRV(m_device_context,
				SLOT_SRV_TEXTURE, m_white->Get());

			break;
		}

		case RenderMode::DiffuseReflectivityTexture: {

			buffer.m_texture_transform = texture_transform;

			// Update the color buffer.
			m_color_buffer.UpdateData(m_device_context, 
				RGBASpectrum(1.0f));
			// Bind the color buffer.
			PS::BindConstantBuffer(m_device_context,
				SLOT_CBUFFER_COLOR, m_color_buffer.Get());

			// Bind the diffuse SRV.
			PS::BindSRV(m_device_context,
				SLOT_SRV_TEXTURE, material->GetDiffuseReflectivitySRV());

			break;
		}

		case RenderMode::SpecularColor: {

			buffer.m_texture_transform = texture_transform;

			// Update the color buffer.
			m_color_buffer.UpdateData(m_device_context, 
				RGBASpectrum(material->GetSpecularReflectivity()));
			// Bind the color buffer.
			PS::BindConstantBuffer(m_device_context,
				SLOT_CBUFFER_COLOR, m_color_buffer.Get());

			// Bind the diffuse SRV.
			PS::BindSRV(m_device_context,
				SLOT_SRV_TEXTURE, material->GetSpecularReflectivitySRV());

			break;
		}

		case RenderMode::SpecularReflectivity: {

			buffer.m_texture_transform = texture_transform;

			// Update the color buffer.
			m_color_buffer.UpdateData(m_device_context, 
				RGBASpectrum(material->GetSpecularReflectivity()));
			// Bind the color buffer.
			PS::BindConstantBuffer(m_device_context,
				SLOT_CBUFFER_COLOR, m_color_buffer.Get());

			// Bind the diffuse SRV.
			PS::BindSRV(m_device_context,
				SLOT_SRV_TEXTURE, m_white->Get());

			break;
		}

		case RenderMode::SpecularReflectivityTexture: {

			buffer.m_texture_transform = texture_transform;

			// Update the color buffer.
			m_color_buffer.UpdateData(m_device_context, 
				RGBASpectrum(1.0f));
			// Bind the color buffer.
			PS::BindConstantBuffer(m_device_context,
				SLOT_CBUFFER_COLOR, m_color_buffer.Get());

			// Bind the diffuse SRV.
			PS::BindSRV(m_device_context,
				SLOT_SRV_TEXTURE, material->GetSpecularReflectivitySRV());

			break;
		}

		case RenderMode::NormalTexture: {

			buffer.m_texture_transform = XMMatrixIdentity();

			// Update the color buffer.
			m_color_buffer.UpdateData(m_device_context, 
				RGBASpectrum(1.0f));
			// Bind the color buffer.
			PS::BindConstantBuffer(m_device_context,
				SLOT_CBUFFER_COLOR, m_color_buffer.Get());

			// Bind the diffuse SRV.
			PS::BindSRV(m_device_context,
				SLOT_SRV_TEXTURE, material->GetNormalSRV());

			break;
		}
		}

		// Update the model buffer.
		m_model_buffer.UpdateData(m_device_context, buffer);
		// Bind the model buffer.
		VS::BindConstantBuffer(m_device_context,
			SLOT_CBUFFER_PER_DRAW, m_model_buffer.Get());
	}

	void VariableComponentPass::BindFixedState(RenderMode render_mode) {
		// Reset the render mode.
		m_render_mode = render_mode;

		// Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// Bind the pixel shader.
		m_ps->BindShader(m_device_context);
		// Bind the rasterization state.
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// Bind the depth-stencil state.
		RenderingStateCache::Get()->BindDepthDefaultDepthStencilState(m_device_context);
		// Bind the sampler.
		PS::BindSampler(m_device_context, SLOT_SAMPLER_DEFAULT,
			RenderingStateCache::Get()->GetLinearWrapSamplerState());
	}

	void XM_CALLCONV VariableComponentPass::Render(
		const PassBuffer *scene,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world,
		CXMMATRIX view_to_projection) {

		Assert(scene);

		// Bind the projection data.
		BindProjectionData(view_to_projection);
		
		// Bind the blend state.
		RenderingStateCache::Get()->BindOpaqueBlendState(m_device_context);

		// Process the opaque models.
		ProcessModels(scene->GetOpaqueEmissiveModels(), 
			world_to_projection, world_to_view, view_to_world);
		ProcessModels(scene->GetOpaqueBRDFModels(), 
			world_to_projection, world_to_view, view_to_world);
		
		// Bind the blend state.
		if (Renderer::Get()->HasMSAA()) {
			RenderingStateCache::Get()->BindAlphaToCoverageBlendState(m_device_context);
		}
		else {
			RenderingStateCache::Get()->BindAlphaBlendState(m_device_context);
		}
		
		// Process the transparent models.
		ProcessModels(scene->GetTransparentEmissiveModels(), 
			world_to_projection, world_to_view, view_to_world);
		ProcessModels(scene->GetTransparentBRDFModels(), 
			world_to_projection, world_to_view, view_to_world);
	}

	void XM_CALLCONV VariableComponentPass::ProcessModels(
		const vector< const ModelNode * > &models,
		FXMMATRIX world_to_projection, 
		CXMMATRIX world_to_view, 
		CXMMATRIX view_to_world) {

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
			const XMMATRIX object_to_view         = object_to_world * world_to_view;
			const XMMATRIX world_to_object        = transform->GetWorldToObjectMatrix();
			const XMMATRIX view_to_object         = view_to_world * world_to_object;
			const XMMATRIX texture_transform      = node->GetTextureTransform()->GetTransformMatrix();
			const Material * const material       = model->GetMaterial();

			// Bind the model data (inc. PS).
			BindModelData(object_to_view, view_to_object, texture_transform, material);
			// Bind the model mesh.
			model->BindMesh(m_device_context);
			// Draw the model.
			model->Draw(m_device_context);
		}
	}
}