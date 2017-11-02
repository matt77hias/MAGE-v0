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
		m_camera_buffer(device),
		m_back_buffer_pass(),
		m_bounding_volume_pass(),
		m_constant_component_pass(),
		m_constant_shading_pass(),
		m_deferred_shading_pass(),
		m_depth_pass(), 
		m_fxaa_pass(),
		m_gbuffer_pass(),
		m_lbuffer_pass(),
		m_shading_normal_pass(),
		m_sky_pass(),
		m_sprite_pass(),
		m_tone_mapper_pass(),
		m_variable_component_pass(),
		m_variable_shading_pass(),
		m_wireframe_pass() {}
	
	Renderer::Renderer(Renderer &&scene_renderer) = default;
	
	Renderer::~Renderer() = default;

	void Renderer::BindPersistentState() {
		const RenderingManager * const rendering_manager 
			= RenderingManager::Get();
		
		GameBuffer game_buffer;
		game_buffer.m_width             = rendering_manager->GetWidth();
		game_buffer.m_height            = rendering_manager->GetHeight();
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

	void Renderer::BindCameraBuffer(
		const Viewport &viewport,
		FXMMATRIX view_to_projection,
		CXMMATRIX projection_to_view,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world) {

		CameraBuffer camera_buffer;
		camera_buffer.m_view_to_projection  = XMMatrixTranspose(view_to_projection);
		camera_buffer.m_projection_to_view  = XMMatrixTranspose(projection_to_view);
		camera_buffer.m_world_to_view       = XMMatrixTranspose(world_to_view);
		camera_buffer.m_view_to_world       = XMMatrixTranspose(view_to_world);
		camera_buffer.m_viewport_top_left_x = static_cast< U32 >(viewport.GetTopLeftX());
		camera_buffer.m_viewport_top_left_y = static_cast< U32 >(viewport.GetTopLeftY());
		camera_buffer.m_viewport_width      = static_cast< U32 >(viewport.GetWidth());
		camera_buffer.m_viewport_height     = static_cast< U32 >(viewport.GetHeight());
		camera_buffer.m_viewport_inv_width_minus1  = 1.0f / (viewport.GetWidth()  - 1.0f);
		camera_buffer.m_viewport_inv_height_minus1 = 1.0f / (viewport.GetHeight() - 1.0f);

		// Update the camera buffer.
		m_camera_buffer.UpdateData(m_device_context, camera_buffer);
		// Bind the game buffer.
		m_camera_buffer.Bind< Pipeline >(
			m_device_context, SLOT_CBUFFER_PRIMARY_CAMERA);
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

			// Bind the camera buffer.
			BindCameraBuffer(viewport, view_to_projection, 
				projection_to_view, world_to_view, view_to_world);
			
			// RenderMode
			switch (render_mode) {

			case RenderMode::Forward: {
				ExecuteForwardPipeline(viewport, world_to_projection,
					world_to_view, view_to_world, brdf);
				
				break;
			}

			case RenderMode::Deferred: {
				ExecuteDeferredPipeline(viewport, world_to_projection,
					world_to_view, view_to_world, brdf);
				
				break;
			}

			case RenderMode::Solid: {
				ExecuteSolidForwardPipeline(viewport, world_to_projection,
					world_to_view, view_to_world);
				
				break;
			}

			case RenderMode::BaseColor:
			case RenderMode::BaseColorCoefficient:
			case RenderMode::BaseColorTexture:
			case RenderMode::Material:
			case RenderMode::MaterialCoefficient:
			case RenderMode::MaterialTexture:
			case RenderMode::NormalTexture: {
				// Bind the viewport.
				viewport.BindViewport(m_device_context);

				output_manager->BindBeginForward(m_device_context);

				VariableComponentPass * const pass = GetVariableComponentPass();
				pass->BindFixedState(render_mode);
				pass->Render(
					m_pass_buffer.get(), world_to_projection, 
					world_to_view, view_to_world);
				
				break;
			}

			case RenderMode::UVTexture:
			case RenderMode::Distance: {
				// Bind the viewport.
				viewport.BindViewport(m_device_context);

				output_manager->BindBeginForward(m_device_context);

				ConstantComponentPass * const pass = GetConstantComponentPass();
				pass->BindFixedState(render_mode);
				pass->Render(
					m_pass_buffer.get(), world_to_projection, 
					world_to_view, view_to_world);
				
				break;
			}

			case RenderMode::ShadingNormal:
			case RenderMode::TSNMShadingNormal: {
				// Bind the viewport.
				viewport.BindViewport(m_device_context);

				output_manager->BindBeginForward(m_device_context);

				ShadingNormalPass * const pass = GetShadingNormalPass();
				pass->BindFixedState(render_mode);
				pass->Render(
					m_pass_buffer.get(), world_to_projection, 
					world_to_view);
				
				break;
			}

			case RenderMode::None: {
				// Bind the viewport.
				viewport.BindViewport(m_device_context);

				output_manager->BindBeginForward(m_device_context);
				break;
			}

			}

			// RenderLayer
			if (settings->HasRenderLayer(RenderLayer::Wireframe)) {
				WireframePass * const pass = GetWireframePass();
				pass->BindFixedState();
				pass->Render(
					m_pass_buffer.get(), world_to_projection, 
					world_to_view);
			}
			if (settings->HasRenderLayer(RenderLayer::AABB)) {
				BoundingVolumePass * const pass = GetBoundingVolumePass();
				pass->BindFixedState();
				pass->Render(
					m_pass_buffer.get(), world_to_projection, 
					world_to_view);
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
		CXMMATRIX view_to_world) {
		
		const RenderingOutputManager * const output_manager
			= RenderingOutputManager::Get();

		// Perform a LBuffer pass.
		LBufferPass * const lbuffer_pass = GetLBufferPass();
		lbuffer_pass->Render(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world);
		// Restore the viewport.
		viewport.BindViewport(m_device_context);
		
		output_manager->BindBeginForward(m_device_context);
		
		// Perform a forward pass.
		ConstantShadingPass * const forward_pass = GetConstantShadingPass();
		forward_pass->BindFixedState();
		forward_pass->Render(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world);
	}

	void Renderer::ExecuteForwardPipeline(
		const Viewport &viewport,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world,
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
		
		output_manager->BindBeginForward(m_device_context);

		// Perform a forward pass.
		VariableShadingPass * const forward_pass = GetVariableShadingPass();
		forward_pass->BindFixedState(brdf);
		forward_pass->Render(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world);

		// Perform a sky pass.
		SkyPass * const sky_pass = GetSkyPass();
		sky_pass->BindFixedState();
		sky_pass->Render(
			m_pass_buffer.get());

		// Perform a forward pass: transparent models.
		forward_pass->BindFixedState(brdf);
		forward_pass->RenderTransparent(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world);
	}

	void Renderer::ExecuteDeferredPipeline(
		const Viewport &viewport,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world,
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

		output_manager->BindBeginGBuffer(m_device_context);

		// Perform a GBuffer pass.
		GBufferPass * const gbuffer_pass = GetGBufferPass();
		gbuffer_pass->BindFixedState();
		gbuffer_pass->Render(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world);

		output_manager->BindEndGBuffer(m_device_context);
		output_manager->BindBeginDeferred(m_device_context);

		// Perform a deferred pass.
		DeferredShadingPass *deferred_pass = GetDeferredShadingPass();
		deferred_pass->BindFixedState(brdf);
		deferred_pass->Render(viewport);

		output_manager->BindEndDeferred(m_device_context);
		output_manager->BindBeginForward(m_device_context);

		// Perform a forward pass: emissive models.
		VariableShadingPass * const forward_pass = GetVariableShadingPass();
		forward_pass->BindFixedState(brdf);
		forward_pass->RenderEmissive(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world);

		// Perform a sky pass.
		SkyPass * const sky_pass = GetSkyPass();
		sky_pass->BindFixedState();
		sky_pass->Render(
			m_pass_buffer.get());

		// Perform a forward pass: transparent models.
		forward_pass->BindFixedState(brdf);
		forward_pass->RenderTransparent(
			m_pass_buffer.get(), world_to_projection,
			world_to_view, view_to_world);
	}
}