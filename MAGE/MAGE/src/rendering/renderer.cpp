//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_manager.hpp"
#include "logging\error.hpp"

// Include HLSL bindings.
#include "..\..\shaders\hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Renderer *Renderer::Get() noexcept {
		Assert(RenderingManager::Get());
		
		return RenderingManager::Get()->GetRenderer();
	}

	Renderer::Renderer(ID3D11Device2 *device,
		ID3D11DeviceContext2 *device_context, 
		const Viewport &viewport)
		: m_device_context(device_context),
		m_maximum_viewport(viewport),
		m_pass_buffer(MakeUnique< PassBuffer >()),
		m_game_buffer(device),
		m_depth_pass(), 
		m_gbuffer_pass(),
		m_lbuffer_pass(),
		m_deferred_shading_pass(), 
		m_variable_shading_pass(),
		m_sprite_pass(), 
		m_back_buffer_pass(),
		m_sky_pass(),
		m_constant_shading_pass(),
		m_constant_component_pass(), 
		m_variable_component_pass(),
		m_shading_normal_pass(), 
		m_wireframe_pass(), 
		m_bounding_volume_pass() {}
	
	Renderer::Renderer(Renderer &&scene_renderer) = default;
	
	Renderer::~Renderer() = default;

	void Renderer::BindPersistentState() {
		const RenderingManager * const rendering_manager 
			= RenderingManager::Get();
		
		GameBuffer game_buffer;
		game_buffer.m_width             = static_cast< F32 >(rendering_manager->GetWidth());
		game_buffer.m_height            = static_cast< F32 >(rendering_manager->GetHeight());
		game_buffer.m_inv_width_minus1  = 1.0f / (rendering_manager->GetWidth()  - 1.0f);
		game_buffer.m_inv_height_minus1 = 1.0f / (rendering_manager->GetHeight() - 1.0f);
		game_buffer.m_gamma             = rendering_manager->GetGamma();
		game_buffer.m_inv_gamma         = 1.0f / rendering_manager->GetGamma();

		// Update the game buffer.
		m_game_buffer.UpdateData(m_device_context, game_buffer);
		// Bind the game buffer.
		m_game_buffer.Bind< Pipeline >(
			m_device_context, SLOT_CBUFFER_GAME);
	}

	void Renderer::Render(const Scene *scene) {

		const RenderingOutputManager * const output_manager
			= RenderingOutputManager::Get();

		// Update the pass buffer.
		m_pass_buffer->Update(scene);

		output_manager->Clear(m_device_context);

		for (const auto node : m_pass_buffer->GetCameras()) {
			output_manager->BindBegin(m_device_context);

			// Obtain node components.
			const TransformNode  * const transform = node->GetTransform();
			const Camera         * const camera    = node->GetCamera();
			const XMMATRIX world_to_view           = transform->GetWorldToViewMatrix();
			const XMMATRIX view_to_world           = transform->GetViewToWorldMatrix();
			const XMMATRIX view_to_projection      = camera->GetViewToProjectionMatrix();
			const XMMATRIX projection_to_view      = camera->GetProjectionToViewMatrix();
			const XMMATRIX world_to_projection     = world_to_view * view_to_projection;
			const CameraSettings * const settings  = node->GetSettings();
			const RenderMode render_mode           = settings->GetRenderMode();
			const BRDFType brdf                    = settings->GetBRDF();
			const Viewport &viewport               = node->GetViewport();

			// Bind the viewport.
			viewport.BindViewport(m_device_context);

			// RenderMode
			switch (render_mode) {

			case RenderMode::Forward: {
				ExecuteForwardPipeline(viewport, world_to_projection,
					world_to_view, view_to_world, 
					view_to_projection, projection_to_view, brdf);
				
				break;
			}

			case RenderMode::Deferred: {
				ExecuteDeferredPipeline(viewport, world_to_projection,
					world_to_view, view_to_world, 
					view_to_projection, projection_to_view, brdf);
				
				break;
			}

			case RenderMode::Solid: {
				ExecuteSolidForwardPipeline(viewport, world_to_projection,
					world_to_view, view_to_world, view_to_projection);
				
				break;
			}

			case RenderMode::BaseColor:
			case RenderMode::BaseColorCoefficient:
			case RenderMode::BaseColorTexture:
			case RenderMode::Material:
			case RenderMode::MaterialCoefficient:
			case RenderMode::MaterialTexture:
			case RenderMode::NormalTexture: {
				output_manager->BindForward(m_device_context);

				VariableComponentPass * const pass = GetVariableComponentPass();
				pass->BindFixedState(render_mode);
				pass->Render(
					m_pass_buffer.get(), world_to_projection, 
					world_to_view, view_to_world, view_to_projection);
				
				break;
			}

			case RenderMode::UVTexture:
			case RenderMode::Distance: {
				output_manager->BindForward(m_device_context);

				ConstantComponentPass * const pass = GetConstantComponentPass();
				pass->BindFixedState(render_mode);
				pass->Render(
					m_pass_buffer.get(), world_to_projection, 
					world_to_view, view_to_world, view_to_projection);
				
				break;
			}

			case RenderMode::ShadingNormal:
			case RenderMode::TSNMShadingNormal: {
				output_manager->BindForward(m_device_context);

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
		
			output_manager->BindEnd(m_device_context);
		}

		// Bind the maximum viewport.
		m_maximum_viewport.BindViewport(m_device_context);
		
		// Perform a back buffer pass.
		BackBufferPass * const back_buffer_pass = GetBackBufferPass();
		back_buffer_pass->BindFixedState();
		back_buffer_pass->Render();

		// Perform a sprite pass.
		SpritePass * const sprite_pass = GetSpritePass();
		sprite_pass->BindFixedState();
		sprite_pass->Render(m_pass_buffer.get());
	}

	void Renderer::ExecuteSolidForwardPipeline(
		const Viewport &viewport,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world,
		CXMMATRIX view_to_projection) {
		
		const RenderingOutputManager * const output_manager
			= RenderingOutputManager::Get();

		// Perform a LBuffer pass.
		LBufferPass * const lbuffer_pass = GetLBufferPass();
		lbuffer_pass->Render(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world);
		// Restore the viewport.
		viewport.BindViewport(m_device_context);
		
		output_manager->BindForward(m_device_context);
		
		// Perform a forward pass.
		ConstantShadingPass * const forward_pass = GetConstantShadingPass();
		forward_pass->BindFixedState();
		forward_pass->Render(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world, view_to_projection);
	}

	void Renderer::ExecuteForwardPipeline(
		const Viewport &viewport,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world,
		CXMMATRIX view_to_projection,
		CXMMATRIX projection_to_view,
		BRDFType brdf) {

		const RenderingOutputManager * const output_manager
			= RenderingOutputManager::Get();
		
		// Perform a LBuffer pass.
		LBufferPass * const lbuffer_pass = GetLBufferPass();
		lbuffer_pass->Render(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world);
		// Restore the viewport.
		viewport.BindViewport(m_device_context);
		
		output_manager->BindForward(m_device_context);

		// Perform a forward pass: opaque models.
		VariableShadingPass * const forward_pass = GetVariableShadingPass();
		forward_pass->BindFixedState(brdf);
		forward_pass->RenderOpaque(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world, view_to_projection);

		// Perform a sky pass.
		SkyPass * const sky_pass = GetSkyPass();
		sky_pass->BindFixedState();
		sky_pass->Render(
			m_pass_buffer.get(),
			view_to_world, projection_to_view);

		// Perform a forward pass: transparent models.
		forward_pass->BindFixedState(brdf);
		forward_pass->RenderTransparent(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world, view_to_projection);
	}

	void Renderer::ExecuteDeferredPipeline(
		const Viewport &viewport,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world,
		CXMMATRIX view_to_projection,
		CXMMATRIX projection_to_view,
		BRDFType brdf) {

		const RenderingOutputManager * const output_manager
			= RenderingOutputManager::Get();

		// Perform a LBuffer pass.
		LBufferPass * const lbuffer_pass = GetLBufferPass();
		lbuffer_pass->Render(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world);
		// Restore the viewport.
		viewport.BindViewport(m_device_context);

		output_manager->BindGBuffer(m_device_context);

		// Perform a GBuffer pass.
		GBufferPass * const gbuffer_pass = GetGBufferPass();
		gbuffer_pass->BindFixedState();
		gbuffer_pass->Render(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world, view_to_projection);

		output_manager->BindDeferred(m_device_context);

		// Perform a deferred pass.
		DeferredShadingPass *deferred_pass = GetDeferredShadingPass();
		deferred_pass->BindFixedState(brdf);
		deferred_pass->Render(projection_to_view);

		output_manager->BindForward(m_device_context);

		// Perform a forward pass: opaque emissive models.
		VariableShadingPass * const forward_pass = GetVariableShadingPass();
		forward_pass->BindFixedState(brdf);
		forward_pass->RenderOpaqueEmissive(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world, view_to_projection);

		// Perform a sky pass.
		SkyPass * const sky_pass = GetSkyPass();
		sky_pass->BindFixedState();
		sky_pass->Render(
			m_pass_buffer.get(),
			view_to_world, projection_to_view);

		// Perform a forward pass: transparent models.
		forward_pass->BindFixedState(brdf);
		forward_pass->RenderTransparent(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world, view_to_projection);
	}
}