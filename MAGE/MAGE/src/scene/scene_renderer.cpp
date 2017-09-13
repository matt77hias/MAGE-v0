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

	void SceneRenderer::Render(const Scene *scene) {
		const Renderer * const renderer = Renderer::Get();
		
		// Update the pass buffer.
		m_pass_buffer->Update(scene);
		
		for (const auto node : m_pass_buffer->GetCameras()) {
			
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
				GetDepthPass()->BindFixedState();
				GetDepthPass()->Render(
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
				GetVariableShadingPass()->BindFixedState(brdf);
				GetVariableShadingPass()->Render(
					m_pass_buffer.get(), world_to_projection,
					world_to_view, view_to_world, view_to_projection);
				
				break;
			}

			case RenderMode::Deferred: {
				// Bind the GBuffer for packing.
				m_gbuffer->BindPacking(m_device_context);
				// Perform a GBuffer pass.
				GetGBufferPass()->BindFixedState();
				GetGBufferPass()->Render(
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
				GetDeferredShadingPass()->BindFixedState(brdf);
				GetDeferredShadingPass()->Render(
					m_pass_buffer.get(), view_to_projection);

				// Bind the back buffer RTV and depth buffer DSV.
				m_gbuffer->BindRestore(m_device_context);
				// Perform an image pass.
				GetImagePass()->BindFixedState();
				GetImagePass()->Render();

				// Bind the LBuffer to the graphics pipeline.
				m_lbuffer->BindToGraphicsPipeline();
				// Perform a variable shading pass (for the remaining geometry).
				GetVariableShadingPass()->BindFixedState(brdf);
				GetVariableShadingPass()->RenderPostDeferred(
					m_pass_buffer.get(), world_to_projection,
					world_to_view, view_to_world, view_to_projection);
				
				break;
			}

			case RenderMode::DepthAndSolid: {
				// Bind no RTV, but only the depth buffer DSV.
				OM::BindRTVAndDSV(m_device_context, nullptr, renderer->GetDepthBufferDSV());
				// Perform a depth pass.
				GetDepthPass()->BindFixedState();
				GetDepthPass()->Render(
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
				GetConstantShadingPass()->BindFixedState();
				GetConstantShadingPass()->Render(
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
				GetVariableComponentPass()->BindFixedState(render_mode);
				GetVariableComponentPass()->Render(
					m_pass_buffer.get(), world_to_projection, 
					world_to_view, view_to_world, view_to_projection);
				break;
			}

			case RenderMode::UVTexture:
			case RenderMode::Distance: {
				GetConstantComponentPass()->BindFixedState(render_mode);
				GetConstantComponentPass()->Render(
					m_pass_buffer.get(), world_to_projection, 
					world_to_view, view_to_world, view_to_projection);
				break;
			}

			case RenderMode::ShadingNormal:
			case RenderMode::TSNMShadingNormal: {
				GetShadingNormalPass()->BindFixedState(render_mode);
				GetShadingNormalPass()->Render(
					m_pass_buffer.get(), world_to_projection, 
					world_to_view, view_to_projection);
				break;
			}

			}

			// RenderLayer
			if (settings->HasRenderLayer(RenderLayer::Wireframe)) {
				GetWireframePass()->BindFixedState();
				GetWireframePass()->Render(
					m_pass_buffer.get(), world_to_projection, 
					world_to_view, view_to_projection);
			}
			if (settings->HasRenderLayer(RenderLayer::AABB)) {
				GetBoundingVolumePass()->BindFixedState();
				GetBoundingVolumePass()->Render(
					m_pass_buffer.get(), world_to_projection);
			}
		}

		// Bind the maximum viewport.
		m_viewport.BindViewport(m_device_context);
		
		// Perform a sprite pass.
		GetSpritePass()->BindFixedState();
		GetSpritePass()->Render(m_pass_buffer.get());
	}
}