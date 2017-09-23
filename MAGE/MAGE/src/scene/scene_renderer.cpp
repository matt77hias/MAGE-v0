//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_manager.hpp"
#include "rendering\renderer.hpp"
#include "logging\error.hpp"

// Include HLSL bindings.
#include "..\..\shaders\hlsl.hpp"

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
		m_maximum_viewport(),
		m_pass_buffer(MakeUnique< PassBuffer >()),
		m_gbuffer(MakeUnique< GBuffer >()),
		m_image_buffer(MakeUnique< ImageBuffer >()),
		m_game_buffer(),
		m_depth_pass(), 
		m_gbuffer_pass(),
		m_lbuffer_pass(),
		m_deferred_shading_pass(), 
		m_variable_shading_pass(),
		m_sprite_pass(), 
		m_image_pass(),
		m_constant_shading_pass(),
		m_constant_component_pass(), 
		m_variable_component_pass(),
		m_shading_normal_pass(), 
		m_wireframe_pass(), 
		m_bounding_volume_pass() {

		// Bind the persistent state.
		BindPersistentState();
	}
	
	SceneRenderer::SceneRenderer(SceneRenderer &&scene_renderer) = default;
	
	SceneRenderer::~SceneRenderer() = default;

	void SceneRenderer::BindPersistentState() {
		const Renderer * const renderer = Renderer::Get();
		
		GameBuffer game_buffer;
		game_buffer.m_width             = static_cast< float >(renderer->GetWidth());
		game_buffer.m_height            = static_cast< float >(renderer->GetHeight());
		game_buffer.m_inv_width_minus1  = 1.0f / (renderer->GetWidth() - 1.0f);
		game_buffer.m_inv_height_minus1 = 1.0f / (renderer->GetHeight() - 1.0f);
		game_buffer.m_gamma             = renderer->GetGamma();
		game_buffer.m_inv_gamma         = 1.0f / renderer->GetGamma();

		// Update the game buffer.
		m_game_buffer.UpdateData(m_device_context, game_buffer);
		// Bind the game buffer.
		Pipeline::BindConstantBuffer(m_device_context, 
			SLOT_CBUFFER_GAME, m_game_buffer.Get());
	}

	void SceneRenderer::Render(const Scene *scene) {
		
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
				ExecuteDepthPass(world_to_projection, 
					world_to_view, view_to_projection);
				// Fall through RenderMode::Forward.
			}
			case RenderMode::Forward: {
				ExecuteForwardPipeline(viewport, world_to_projection,
					world_to_view, view_to_world, view_to_projection, brdf);
				break;
			}

			case RenderMode::Deferred: {
				ExecuteDeferredPipeline(viewport, world_to_projection,
					world_to_view, view_to_world, view_to_projection, brdf);
				break;
			}

			case RenderMode::DepthAndSolid: {
				ExecuteDepthPass(world_to_projection,
					world_to_view, view_to_projection);
				// Fall through RenderMode::Forward.
			}
			case RenderMode::Solid: {
				ExecuteSolidForwardPipeline(viewport, world_to_projection,
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
				VariableComponentPass * const pass = GetVariableComponentPass();
				pass->BindFixedState(render_mode);
				pass->Render(
					m_pass_buffer.get(), world_to_projection, 
					world_to_view, view_to_world, view_to_projection);
				break;
			}

			case RenderMode::UVTexture:
			case RenderMode::Distance: {
				ConstantComponentPass * const pass = GetConstantComponentPass();
				pass->BindFixedState(render_mode);
				pass->Render(
					m_pass_buffer.get(), world_to_projection, 
					world_to_view, view_to_world, view_to_projection);
				break;
			}

			case RenderMode::ShadingNormal:
			case RenderMode::TSNMShadingNormal: {
				ShadingNormalPass * const pass = GetShadingNormalPass();
				pass->BindFixedState(render_mode);
				pass->Render(
					m_pass_buffer.get(), world_to_projection, 
					world_to_view, view_to_projection);
				break;
			}

			}

			// RenderLayer
			if (settings->HasRenderLayer(RenderLayer::Wireframe)) {
				WireframePass * const pass = GetWireframePass();
				pass->BindFixedState();
				pass->Render(
					m_pass_buffer.get(), world_to_projection, 
					world_to_view, view_to_projection);
			}
			if (settings->HasRenderLayer(RenderLayer::AABB)) {
				BoundingVolumePass * const pass = GetBoundingVolumePass();
				pass->BindFixedState();
				pass->Render(
					m_pass_buffer.get(), world_to_projection);
			}
		}

		// Bind the maximum viewport.
		m_maximum_viewport.BindViewport(m_device_context);
		
		// Perform a sprite pass.
		SpritePass * const pass = GetSpritePass();
		pass->BindFixedState();
		pass->Render(m_pass_buffer.get());
	}

	void SceneRenderer::ExecuteDepthPass(
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_projection) {

		const Renderer * const renderer = Renderer::Get();

		// Bind no RTV and the depth buffer DSV.
		Pipeline::OM::BindRTVAndDSV(m_device_context, nullptr, 
			renderer->GetDepthBufferDSV());
		
		// Perform a depth pass.
		DepthPass * const depth_pass = GetDepthPass();
		depth_pass->BindFixedState();
		depth_pass->Render(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_projection);
		
		// Bind the back and depth buffer.
		renderer->BindRTVAndDSV();
	}

	void SceneRenderer::ExecuteSolidForwardPipeline(
		const Viewport &viewport,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world,
		CXMMATRIX view_to_projection) {
		
		// Perform a LBuffer pass.
		LBufferPass * const lbuffer_pass = GetLBufferPass();
		lbuffer_pass->Render(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world);

		// Restore the viewport.
		viewport.BindViewport(m_device_context);
		// Bind the back and depth buffer.
		Renderer::Get()->BindRTVAndDSV();
		
		// Perform a forward pass.
		ConstantShadingPass * const forward_pass = GetConstantShadingPass();
		forward_pass->BindFixedState();
		forward_pass->Render(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world, view_to_projection);
	}

	void SceneRenderer::ExecuteForwardPipeline(
		const Viewport &viewport,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world,
		CXMMATRIX view_to_projection,
		BRDFType brdf) {
		
		// Perform a LBuffer pass.
		LBufferPass * const lbuffer_pass = GetLBufferPass();
		lbuffer_pass->Render(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world);

		// Restore the viewport.
		viewport.BindViewport(m_device_context);
		// Bind the back and depth buffer.
		Renderer::Get()->BindRTVAndDSV();
		
		// Perform a forward pass.
		VariableShadingPass * const forward_pass = GetVariableShadingPass();
		forward_pass->BindFixedState(brdf);
		forward_pass->Render(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world, view_to_projection);
	}

	void SceneRenderer::ExecuteDeferredPipeline(
		const Viewport &viewport,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world,
		CXMMATRIX view_to_projection,
		BRDFType brdf) {

		// Bind the GBuffer for packing.
		m_gbuffer->BindPacking(m_device_context);
		
		// Perform a GBuffer pass.
		GBufferPass * const gbuffer_pass = GetGBufferPass();
		gbuffer_pass->BindFixedState();
		gbuffer_pass->Render(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world, view_to_projection);

		// Perform a LBuffer pass.
		LBufferPass * const lbuffer_pass = GetLBufferPass();
		lbuffer_pass->Render(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world);

		// Restore the viewport.
		viewport.BindViewport(m_device_context);
		// Bind the GBuffer for unpacking.
		m_gbuffer->BindUnpacking(m_device_context);
		// Bind the ImageBuffer for packing.
		m_image_buffer->BindPacking(m_device_context);

		// Perform a deferred pass.
		DeferredShadingPass *deferred_pass = GetDeferredShadingPass();
		deferred_pass->BindFixedState(brdf);
		deferred_pass->Render(
			m_pass_buffer.get(), view_to_projection);

		// Bind the ImageBuffer for unpacking.
		m_image_buffer->BindUnpacking(m_device_context);
		// Bind the back and depth buffer.
		Renderer::Get()->BindRTVAndDSV();
		
		// Perform an image pass.
		ImagePass * const image_pass = GetImagePass();
		image_pass->BindFixedState();
		image_pass->Render();

		// Perform a forward pass.
		VariableShadingPass * const forward_pass = GetVariableShadingPass();
		forward_pass->BindFixedState(brdf);
		forward_pass->RenderPostDeferred(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world, view_to_projection);
	}
}