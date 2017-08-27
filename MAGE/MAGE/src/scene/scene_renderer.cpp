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
		m_bounding_volume_pass(MakeUnique< BoundingVolumePass >()),
		m_constant_component_pass(MakeUnique< ConstantComponentPass >()),
		m_constant_shading_pass(MakeUnique< ConstantShadingPass >()),
		m_sprite_pass(MakeUnique< SpritePass >()),
		m_variable_component_pass(MakeUnique< VariableComponentPass >()),
		m_variable_shading_pass(MakeUnique< VariableShadingPass >()),
		m_shading_normal_pass(MakeUnique< ShadingNormalPass >()),
		m_wireframe_pass(MakeUnique< WireframePass >()),
		m_viewport() {}
	
	SceneRenderer::SceneRenderer(SceneRenderer &&scene_renderer) = default;
	
	SceneRenderer::~SceneRenderer() = default;

	void SceneRenderer::Render(const Scene *scene) {
		PassBuffer buffer(scene);
		
		for (const auto node : buffer.m_cameras) {
			// Bind the maximum viewport.
			node->GetViewport().BindViewport(m_device_context);

			const CameraSettings *settings = node->GetSettings();

			// RenderMode
			switch (settings->GetRenderMode()) {

			case RenderMode::Default: {
				m_variable_shading_pass->Render(&buffer, node);
				break;
			}

			case RenderMode::Solid: {
				m_constant_shading_pass->Render(&buffer, node);
				break;
			}

			case RenderMode::DiffuseTexture: {
				m_variable_component_pass->Render(&buffer, node);
				break;
			}

			case RenderMode::UVTexture:
			case RenderMode::Distance: {
				m_constant_component_pass->Render(&buffer, node);
				break;
			}

			case RenderMode::ShadingNormal:
			case RenderMode::TSNMShadingNormal: {
				m_shading_normal_pass->Render(&buffer, node);
				break;
			}

			}

			// RenderLayer
			if (settings->HasRenderLayer(RenderLayer::Wireframe)) {
				m_wireframe_pass->Render(&buffer, node);
			}
			if (settings->HasRenderLayer(RenderLayer::AABB)) {
				m_bounding_volume_pass->Render(&buffer, node);
			}
		}

		// Bind the maximum viewport.
		m_viewport.BindViewport(m_device_context);
		
		m_sprite_pass->Render(&buffer);

	}
}