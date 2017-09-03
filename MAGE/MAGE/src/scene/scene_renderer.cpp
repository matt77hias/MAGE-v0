//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_renderer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SceneRenderer::SceneRenderer()
		: m_device_context(GetImmediateDeviceContext()),
		m_pass_buffer(MakeUnique< PassBuffer >()),
		m_gbuffer(MakeUnique< GBuffer >()),
		m_lbuffer(MakeUnique< LBuffer >()),
		m_bounding_volume_pass(MakeUnique< BoundingVolumePass >()),
		m_constant_component_pass(MakeUnique< ConstantComponentPass >()),
		m_constant_shading_pass(MakeUnique< ConstantShadingPass >()),
		m_gbuffer_pass(MakeUnique< GBufferPass >()),
		m_sprite_pass(MakeUnique< SpritePass >()),
		m_variable_component_pass(MakeUnique< VariableComponentPass >()),
		m_variable_shading_pass(MakeUnique< VariableShadingPass >()),
		m_shading_normal_pass(MakeUnique< ShadingNormalPass >()),
		m_wireframe_pass(MakeUnique< WireframePass >()),
		m_viewport() {}
	
	SceneRenderer::SceneRenderer(SceneRenderer &&scene_renderer) = default;
	
	SceneRenderer::~SceneRenderer() = default;

	void SceneRenderer::Render(const Scene *scene) {
		// Update the pass buffer.
		m_pass_buffer->Update(scene);
		
		for (const auto node : m_pass_buffer->m_cameras) {
			// Bind the maximum viewport.
			node->GetViewport().BindViewport(m_device_context);
			
			const CameraSettings *settings = node->GetSettings();

			// RenderMode
			switch (settings->GetRenderMode()) {

			case RenderMode::Forward: {
				m_lbuffer->Update(m_pass_buffer.get(), node);
				m_variable_shading_pass->Render(m_pass_buffer.get(), node);
				break;
			}

			case RenderMode::Deferred: {
				m_gbuffer->BindPacking(m_device_context);
				m_gbuffer_pass->Render(m_pass_buffer.get(), node);
				m_lbuffer->Update(m_pass_buffer.get(), node);
				m_gbuffer->BindUnpacking(m_device_context, 4);
				m_gbuffer->BindRestore(m_device_context, 4);
				// Render
				m_variable_shading_pass->RenderPostDeferred(m_pass_buffer.get(), node);
				break;
			}

			case RenderMode::Solid: {
				m_lbuffer->Update(m_pass_buffer.get(), node);
				m_constant_shading_pass->Render(m_pass_buffer.get(), node);
				break;
			}

			case RenderMode::DiffuseColor:
			case RenderMode::DiffuseReflectivity:
			case RenderMode::DiffuseReflectivityTexture:
			case RenderMode::SpecularColor:
			case RenderMode::SpecularReflectivity:
			case RenderMode::SpecularReflectivityTexture:
			case RenderMode::NormalTexture: {
				m_variable_component_pass->Render(m_pass_buffer.get(), node);
				break;
			}

			case RenderMode::UVTexture:
			case RenderMode::Distance: {
				m_constant_component_pass->Render(m_pass_buffer.get(), node);
				break;
			}

			case RenderMode::ShadingNormal:
			case RenderMode::TSNMShadingNormal: {
				m_shading_normal_pass->Render(m_pass_buffer.get(), node);
				break;
			}

			}

			// RenderLayer
			if (settings->HasRenderLayer(RenderLayer::Wireframe)) {
				m_wireframe_pass->Render(m_pass_buffer.get(), node);
			}
			if (settings->HasRenderLayer(RenderLayer::AABB)) {
				m_bounding_volume_pass->Render(m_pass_buffer.get(), node);
			}
		}

		// Bind the maximum viewport.
		m_viewport.BindViewport(m_device_context);
		m_sprite_pass->Render(m_pass_buffer.get());
	}
}