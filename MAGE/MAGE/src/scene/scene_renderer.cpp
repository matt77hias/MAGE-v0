//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_manager.hpp"
#include "rendering\renderer.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SceneRenderer *SceneRenderer::Get() noexcept {
		Assert(SceneManager::Get());
		
		return SceneManager::Get()->GetRenderer();
	}

	SceneRenderer::SceneRenderer()
		: m_device_context(GetImmediateDeviceContext()),
		m_pass_buffer(MakeUnique< PassBuffer >()),
		m_gbuffer(MakeUnique< GBuffer >()),
		m_lbuffer(MakeUnique< LBuffer >()),
		m_depth_pass(), 
		m_gbuffer_pass(),
		m_deferred_shading_pass(), 
		m_variable_shading_pass(),
		m_sprite_pass(), 
		m_image_pass(),
		m_constant_shading_pass(),
		m_constant_component_pass(), 
		m_variable_component_pass(),
		m_shading_normal_pass(), 
		m_wireframe_pass(), 
		m_bounding_volume_pass(),
		m_viewport() {}
	
	SceneRenderer::SceneRenderer(SceneRenderer &&scene_renderer) = default;
	
	SceneRenderer::~SceneRenderer() = default;

	DepthPass *SceneRenderer::GetDepthPass() {
		if (!m_depth_pass) {
			m_depth_pass = MakeUnique< DepthPass >();
		}
		return m_depth_pass.get();
	}

	GBufferPass *SceneRenderer::GetGBufferPass() {
		if (!m_gbuffer_pass) {
			m_gbuffer_pass = MakeUnique< GBufferPass >();
		}
		return m_gbuffer_pass.get();
	}

	DeferredShadingPass *SceneRenderer::GetDeferredShadingPass() {
		if (!m_deferred_shading_pass) {
			m_deferred_shading_pass = MakeUnique< DeferredShadingPass >();
		}
		return m_deferred_shading_pass.get();
	}

	VariableShadingPass *SceneRenderer::GetVariableShadingPass() {
		if (!m_variable_shading_pass) {
			m_variable_shading_pass = MakeUnique< VariableShadingPass >();
		}
		return m_variable_shading_pass.get();
	}

	SpritePass *SceneRenderer::GetSpritePass() {
		if (!m_sprite_pass) {
			m_sprite_pass = MakeUnique< SpritePass >();
		}
		return m_sprite_pass.get();
	}

	ImagePass *SceneRenderer::GetImagePass() {
		if (!m_image_pass) {
			m_image_pass = MakeUnique< ImagePass >();
		}
		return m_image_pass.get();
	}

	ConstantShadingPass *SceneRenderer::GetConstantShadingPass() {
		if (!m_constant_shading_pass) {
			m_constant_shading_pass = MakeUnique< ConstantShadingPass >();
		}
		return m_constant_shading_pass.get();
	}

	ConstantComponentPass *SceneRenderer::GetConstantComponentPass() {
		if (!m_constant_component_pass) {
			m_constant_component_pass = MakeUnique< ConstantComponentPass >();
		}
		return m_constant_component_pass.get();
	}

	VariableComponentPass *SceneRenderer::GetVariableComponentPass() {
		if (!m_variable_component_pass) {
			m_variable_component_pass = MakeUnique< VariableComponentPass >();
		}
		return m_variable_component_pass.get();
	}

	ShadingNormalPass *SceneRenderer::GetShadingNormalPass() {
		if (!m_shading_normal_pass) {
			m_shading_normal_pass = MakeUnique< ShadingNormalPass >();
		}
		return m_shading_normal_pass.get();
	}

	WireframePass *SceneRenderer::GetWireframePass() {
		if (!m_wireframe_pass) {
			m_wireframe_pass = MakeUnique< WireframePass >();
		}
		return m_wireframe_pass.get();
	}

	BoundingVolumePass *SceneRenderer::GetBoundingVolumePass() {
		if (!m_bounding_volume_pass) {
			m_bounding_volume_pass = MakeUnique< BoundingVolumePass >();
		}
		return m_bounding_volume_pass.get();
	}

	void SceneRenderer::Render(const Scene *scene) {
		const Renderer * const renderer = Renderer::Get();
		
		// Update the pass buffer.
		m_pass_buffer->Update(scene);
		
		for (const auto node : m_pass_buffer->m_cameras) {
			
			// Obtain node components.
			const TransformNode  * const transform = node->GetTransform();
			const Camera         * const camera    = node->GetCamera();
			const XMMATRIX world_to_view           = transform->GetWorldToViewMatrix();
			const XMMATRIX view_to_world           = transform->GetViewToWorldMatrix();
			const XMMATRIX view_to_projection      = camera->GetViewToProjectionMatrix();
			const XMMATRIX world_to_projection     = world_to_view * view_to_projection;
			const CameraSettings * const settings  = node->GetSettings();
			const RenderMode render_mode           = settings->GetRenderMode();
			const BRDFType brdf                    = settings->GetBRDF();
			const Viewport &viewport               = node->GetViewport();

			// Bind the viewport.
			viewport.BindViewport(m_device_context);

			// RenderMode
			switch (render_mode) {

			case RenderMode::DepthAndForward: {
				// Bind no RTV, but only the depth buffer DSV.
				OM::BindRTVAndDSV(m_device_context, nullptr, renderer->GetDepthBufferDSV());
				// Perform a depth pass.
				m_depth_pass->BindFixedState();
				m_depth_pass->Render(
					m_pass_buffer.get(), world_to_projection,
					world_to_view, view_to_projection);
				// Bind the back buffer RTV and depth buffer DSV.
				renderer->BindRTVAndDSV();
				// Fall through RenderMode::Forward.
			}
			case RenderMode::Forward: {
				// Create the LBuffer.
				m_lbuffer->Render(
					m_pass_buffer.get(), world_to_projection,
					world_to_view, view_to_world);
				
				// Bind the LBuffer to the graphics pipeline.
				m_lbuffer->BindToGraphicsPipeline();
				// Perform a variable shading pass.
				m_variable_shading_pass->BindFixedState(brdf);
				m_variable_shading_pass->Render(
					m_pass_buffer.get(), world_to_projection,
					world_to_view, view_to_world, view_to_projection);
				
				break;
			}

			case RenderMode::Deferred: {
				// Bind the GBuffer for packing.
				m_gbuffer->BindPacking(m_device_context);
				// Perform a GBuffer pass.
				m_gbuffer_pass->BindFixedState();
				m_gbuffer_pass->Render(
					m_pass_buffer.get(), world_to_projection,
					world_to_view, view_to_world, view_to_projection);
				
				// Create the LBuffer.
				m_lbuffer->Render(
					m_pass_buffer.get(), world_to_projection,
					world_to_view, view_to_world);
				
				// Bind the GBuffer for unpacking to the compute pipeline.
				m_gbuffer->BindUnpacking(m_device_context);
				// Bind the LBuffer to the compute pipeline.
				m_lbuffer->BindToComputePipeline();
				// Perform a deferred shading pass.
				m_deferred_shading_pass->BindFixedState(brdf);
				m_deferred_shading_pass->Render(
					m_pass_buffer.get(), view_to_projection);

				// Bind the back buffer RTV and depth buffer DSV.
				m_gbuffer->BindRestore(m_device_context);
				// Perform an image pass.
				m_image_pass->BindFixedState();
				m_image_pass->Render();

				// Bind the LBuffer to the graphics pipeline.
				m_lbuffer->BindToGraphicsPipeline();
				// Perform a variable shading pass (for the remaining geometry).
				m_variable_shading_pass->BindFixedState(brdf);
				m_variable_shading_pass->RenderPostDeferred(
					m_pass_buffer.get(), world_to_projection,
					world_to_view, view_to_world, view_to_projection);
				
				break;
			}

			case RenderMode::DepthAndSolid: {
				// Bind no RTV, but only the depth buffer DSV.
				OM::BindRTVAndDSV(m_device_context, nullptr, renderer->GetDepthBufferDSV());
				// Perform a depth pass.
				m_depth_pass->BindFixedState();
				m_depth_pass->Render(
					m_pass_buffer.get(), world_to_projection,
					world_to_view, view_to_projection);
				// Bind the back buffer RTV and depth buffer DSV.
				renderer->BindRTVAndDSV();
				// Fall through RenderMode::Forward.
			}
			case RenderMode::Solid: {
				// Create the LBuffer.
				m_lbuffer->Render(
					m_pass_buffer.get(), world_to_projection,
					world_to_view, view_to_world);
				
				// Bind the LBuffer to the graphics pipeline.
				m_lbuffer->BindToGraphicsPipeline();
				// Perform a constant shading pass.
				m_constant_shading_pass->BindFixedState();
				m_constant_shading_pass->Render(
					m_pass_buffer.get(), world_to_projection, 
					world_to_view, view_to_world, view_to_projection);
				
				break;
			}

			case RenderMode::DiffuseColor:
			case RenderMode::DiffuseReflectivity:
			case RenderMode::DiffuseReflectivityTexture:
			case RenderMode::SpecularColor:
			case RenderMode::SpecularReflectivity:
			case RenderMode::SpecularReflectivityTexture:
			case RenderMode::NormalTexture: {
				m_variable_component_pass->BindFixedState(render_mode);
				m_variable_component_pass->Render(
					m_pass_buffer.get(), world_to_projection, 
					world_to_view, view_to_world, view_to_projection);
				break;
			}

			case RenderMode::UVTexture:
			case RenderMode::Distance: {
				m_constant_component_pass->BindFixedState(render_mode);
				m_constant_component_pass->Render(
					m_pass_buffer.get(), world_to_projection, 
					world_to_view, view_to_world, view_to_projection);
				break;
			}

			case RenderMode::ShadingNormal:
			case RenderMode::TSNMShadingNormal: {
				m_shading_normal_pass->BindFixedState(render_mode);
				m_shading_normal_pass->Render(
					m_pass_buffer.get(), world_to_projection, 
					world_to_view, view_to_projection);
				break;
			}

			}

			// RenderLayer
			if (settings->HasRenderLayer(RenderLayer::Wireframe)) {
				m_wireframe_pass->BindFixedState();
				m_wireframe_pass->Render(
					m_pass_buffer.get(), world_to_projection, 
					world_to_view, view_to_projection);
			}
			if (settings->HasRenderLayer(RenderLayer::AABB)) {
				m_bounding_volume_pass->BindFixedState();
				m_bounding_volume_pass->Render(
					m_pass_buffer.get(), world_to_projection);
			}
		}

		// Bind the maximum viewport.
		m_viewport.BindViewport(m_device_context);
		
		// Perform a sprite pass.
		m_sprite_pass->BindFixedState();
		m_sprite_pass->Render(m_pass_buffer.get());
	}
}