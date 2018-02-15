//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_manager.hpp"
#include "logging\error.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	[[nodiscard]] Renderer *Renderer::Get() noexcept {
		Assert(RenderingManager::Get());
		
		return RenderingManager::Get()->GetRenderer();
	}

	Renderer::Renderer(D3D11Device *device,
		               D3D11DeviceContext *device_context, 
		               U32 width, 
		               U32 height)
		: m_device_context(device_context),
		m_maximum_viewport(width, height),
		m_game_buffer(device),
		m_camera_buffer(device),
		m_aa_pass(),
		m_back_buffer_pass(),
		m_bounding_volume_pass(),
		m_constant_component_pass(),
		m_constant_shading_pass(),
		m_deferred_shading_pass(),
		m_depth_pass(),
		m_dof_pass(),
		m_gbuffer_pass(),
		m_lbuffer_pass(),
		m_shading_normal_pass(),
		m_sky_pass(),
		m_sprite_pass(),
		m_variable_component_pass(),
		m_variable_shading_pass(),
		m_voxelization_pass(),
		m_wireframe_pass() {}
	
	Renderer::Renderer(Renderer &&scene_renderer) noexcept = default;
	
	Renderer::~Renderer() = default;

	void Renderer::BindPersistentState() {
		const auto config = DisplayConfiguration::Get();
		
		GameBuffer buffer;
		buffer.m_display_width                = config->GetDisplayWidth();
		buffer.m_display_height               = config->GetDisplayHeight();
		buffer.m_display_inv_width_minus1     = 1.0f / (buffer.m_display_width  - 1.0f);
		buffer.m_display_inv_height_minus1    = 1.0f / (buffer.m_display_height - 1.0f);
		
		buffer.m_ss_display_width             = config->GetSSDisplayWidth();
		buffer.m_ss_display_height            = config->GetSSDisplayHeight();
		buffer.m_ss_display_inv_width_minus1  = 1.0f / (buffer.m_ss_display_width  - 1.0f);
		buffer.m_ss_display_inv_height_minus1 = 1.0f / (buffer.m_ss_display_height - 1.0f);
		
		buffer.m_gamma                        = config->GetGamma();
		buffer.m_inv_gamma                    = 1.0f / buffer.m_gamma;

		// Update the game buffer.
		m_game_buffer.UpdateData(m_device_context, buffer);
		// Bind the game buffer.
		m_game_buffer.Bind< Pipeline >(m_device_context, SLOT_CBUFFER_GAME);
	}

	void XM_CALLCONV Renderer::BindCameraBuffer(const Camera &camera,
		                                        FXMMATRIX view_to_projection,
		                                        CXMMATRIX projection_to_view,
		                                        CXMMATRIX world_to_view,
		                                        CXMMATRIX view_to_world) {
		CameraBuffer buffer;
		buffer.m_view_to_projection            = XMMatrixTranspose(view_to_projection);
		buffer.m_projection_to_view            = XMMatrixTranspose(projection_to_view);
		buffer.m_world_to_view                 = XMMatrixTranspose(world_to_view);
		buffer.m_view_to_world                 = XMMatrixTranspose(view_to_world);
		
		const auto &viewport                   = camera.GetViewport();
		buffer.m_viewport_top_left_x           = static_cast< U32 >(viewport.GetTopLeftX());
		buffer.m_viewport_top_left_y           = static_cast< U32 >(viewport.GetTopLeftY());
		buffer.m_viewport_width                = static_cast< U32 >(viewport.GetWidth());
		buffer.m_viewport_height               = static_cast< U32 >(viewport.GetHeight());
		buffer.m_viewport_inv_width_minus1     = 1.0f / (viewport.GetWidth()  - 1.0f);
		buffer.m_viewport_inv_height_minus1    = 1.0f / (viewport.GetHeight() - 1.0f);

		const auto ss_viewport                 = camera.GetSSViewport();
		buffer.m_ss_viewport_top_left_x        = static_cast< U32 >(ss_viewport.GetTopLeftX());
		buffer.m_ss_viewport_top_left_y        = static_cast< U32 >(ss_viewport.GetTopLeftY());
		buffer.m_ss_viewport_width             = static_cast< U32 >(ss_viewport.GetWidth());
		buffer.m_ss_viewport_height            = static_cast< U32 >(ss_viewport.GetHeight());
		buffer.m_ss_viewport_inv_width_minus1  = 1.0f / (ss_viewport.GetWidth()  - 1.0f);
		buffer.m_ss_viewport_inv_height_minus1 = 1.0f / (ss_viewport.GetHeight() - 1.0f);

		//TODO
		buffer.m_voxel_grid_resolution         = 8u;
		buffer.m_voxel_grid_inv_resolution     = 1.0f / buffer.m_voxel_grid_resolution;
		buffer.m_voxel_size                    = 0.1;
		buffer.m_voxel_inv_size                = 1.0f / buffer.m_voxel_size;
		
		buffer.m_lens_radius                   = camera.GetLens().GetLensRadius();
		buffer.m_focal_length                  = camera.GetLens().GetFocalLength();
		buffer.m_max_coc_radius                = camera.GetLens().GetMaximumCoCRadius();

		// Update the camera buffer.
		m_camera_buffer.UpdateData(m_device_context, buffer);
		// Bind the game buffer.
		m_camera_buffer.Bind< Pipeline >(m_device_context, SLOT_CBUFFER_PRIMARY_CAMERA);
	}

	void Renderer::Render(const Scene &scene) {
		const auto output_manager = RenderingOutputManager::Get();

		scene.ForEach< Camera >([this, &scene, output_manager](const Camera &camera) {
			if (State::Active != camera.GetState()) {
				return;
			}
			
			output_manager->BindBegin(m_device_context);

			const auto &transform          = camera.GetOwner()->GetTransform();
			const auto world_to_view       = transform.GetWorldToViewMatrix();
			const auto view_to_world       = transform.GetViewToWorldMatrix();
			const auto view_to_projection  = camera.GetViewToProjectionMatrix();
			const auto projection_to_view  = camera.GetProjectionToViewMatrix();
			const auto world_to_projection = world_to_view * view_to_projection;

			// Bind the camera buffer.
			BindCameraBuffer(camera, 
							 view_to_projection, projection_to_view, 
							 world_to_view, view_to_world);

			const auto render_mode = camera.GetSettings().GetRenderMode();

			// RenderMode
			switch (render_mode) {

			case RenderMode::Forward: {
				ExecuteForwardPipeline(scene, 
					                   camera, 
					                   world_to_projection, 
					                   world_to_view, 
					                   view_to_world);
				break;
			}

			case RenderMode::Deferred: {
				ExecuteDeferredPipeline(scene, 
					                    camera, 
					                    world_to_projection, 
					                    world_to_view, 
					                    view_to_world);
				break;
			}

			case RenderMode::Solid: {
				ExecuteSolidForwardPipeline(scene, 
					                        camera, 
					                        world_to_projection, 
					                        world_to_view, 
					                        view_to_world);
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
				camera.BindSSViewport(m_device_context);

				output_manager->BindBeginForward(m_device_context);

				GetVariableComponentPass()->Render(scene, 
												   world_to_projection, 
												   world_to_view, 
												   view_to_world, 
												   render_mode);
				break;
			}

			case RenderMode::UVTexture:
			case RenderMode::Distance: {
				// Bind the viewport.
				camera.BindSSViewport(m_device_context);

				output_manager->BindBeginForward(m_device_context);

				GetConstantComponentPass()->Render(scene, 
												   world_to_projection, 
												   world_to_view, 
												   view_to_world,
												   render_mode);
				break;
			}

			case RenderMode::ShadingNormal:
			case RenderMode::TSNMShadingNormal: {
				// Bind the viewport.
				camera.BindSSViewport(m_device_context);

				output_manager->BindBeginForward(m_device_context);

				GetShadingNormalPass()->Render(scene,
											   world_to_projection, 
											   world_to_view, 
											   render_mode);
				break;
			}

			default: {
				// Bind the viewport.
				camera.BindSSViewport(m_device_context);

				output_manager->BindBeginForward(m_device_context);
				break;
			}

			}

			// RenderLayer
			const auto &settings = camera.GetSettings();
			if (settings.ContainsRenderLayer(RenderLayer::Wireframe)) {
				GetWireframePass()->Render(scene, 
										   world_to_projection, 
										   world_to_view);
			}
			if (settings.ContainsRenderLayer(RenderLayer::AABB)) {
				GetBoundingVolumePass()->Render(scene, 
												world_to_projection, 
												world_to_view);
			}
			
			output_manager->BindEndForward(m_device_context);

			ExecuteAAPipeline(camera);

			output_manager->BindBeginPostProcessing(m_device_context);

			// Bind the viewport.
			camera.BindViewport(m_device_context);
			
			if (camera.GetLens().HasFiniteAperture()) {
				output_manager->BindPingPong(m_device_context);
				GetDOFPass()->Dispatch(camera.GetViewport());
			}

			output_manager->BindEnd(m_device_context);

			// Perform a back buffer pass.
			GetBackBufferPass()->Render();
		});
		
		// Bind the maximum viewport.
		m_maximum_viewport.BindViewport(m_device_context);
		
		// Perform a sprite pass.
		GetSpritePass()->Render(scene);
	}

	void XM_CALLCONV Renderer
		::ExecuteSolidForwardPipeline(const Scene &scene,
		                              const Camera &camera,
		                              FXMMATRIX world_to_projection,
		                              CXMMATRIX world_to_view,
		                              CXMMATRIX view_to_world) {
		
		//---------------------------------------------------------------------
		// Perform a LBuffer pass.
		//---------------------------------------------------------------------
		GetLBufferPass()->Render(scene, world_to_projection, 
								 world_to_view, view_to_world, 
								 camera.GetSettings().GetFog());
		
		// Restore the viewport.
		camera.BindSSViewport(m_device_context);
		
		RenderingOutputManager::Get()->BindBeginForward(m_device_context);
		
		//---------------------------------------------------------------------
		// Perform a forward pass.
		//---------------------------------------------------------------------
		GetConstantShadingPass()->Render(scene, world_to_projection, 
										 world_to_view, view_to_world);
	}

	void XM_CALLCONV Renderer
		::ExecuteForwardPipeline(const Scene &scene,
		                         const Camera &camera,
		                         FXMMATRIX world_to_projection,
		                         CXMMATRIX world_to_view,
		                         CXMMATRIX view_to_world) {

		const auto output_manager = RenderingOutputManager::Get();
		const auto viewport = camera.GetSSViewport();
		const auto brdf = camera.GetSettings().GetBRDF();
		const auto vct = true;

		//---------------------------------------------------------------------
		// Perform a LBuffer pass.
		//---------------------------------------------------------------------
		GetLBufferPass()->Render(scene, world_to_projection,
								 world_to_view, view_to_world,
								 camera.GetSettings().GetFog());

		//---------------------------------------------------------------------
		// Perform a voxelization pass.
		//---------------------------------------------------------------------
		if (vct) {
			//TODO
			const auto view_to_voxel = XMMatrixOrthographicOffCenterLH(-0.4f, 0.4f,
																	   -0.4f, 0.4f,
																	   -0.4f, 0.4f);
			const auto world_to_voxel = world_to_view * view_to_voxel;
			GetVoxelizationPass()->Render(scene, world_to_voxel,
										  world_to_view, view_to_world,
										  brdf, 8u);
		}

		// Restore the viewport.
		viewport.BindViewport(m_device_context);
		
		output_manager->BindBeginForward(m_device_context);

		//---------------------------------------------------------------------
		// Perform a forward pass: opaque fragments.
		//---------------------------------------------------------------------
		GetVariableShadingPass()->Render(scene, world_to_projection, 
										 world_to_view, view_to_world, 
										 brdf, vct);

		//---------------------------------------------------------------------
		// Perform a sky pass.
		//---------------------------------------------------------------------
		GetSkyPass()->Render(camera.GetSettings().GetSky());

		//---------------------------------------------------------------------
		// Perform a forward pass: transparent fragments.
		//---------------------------------------------------------------------
		GetVariableShadingPass()->RenderTransparent(scene, world_to_projection, 
													world_to_view, view_to_world, 
													brdf, vct);
	}

	void XM_CALLCONV Renderer
		::ExecuteDeferredPipeline(const Scene &scene,
		                          const Camera &camera,
		                          FXMMATRIX world_to_projection,
		                          CXMMATRIX world_to_view,
		                          CXMMATRIX view_to_world) {

		const auto output_manager = RenderingOutputManager::Get();
		const auto viewport = camera.GetSSViewport();
		const auto brdf = camera.GetSettings().GetBRDF();
		const auto vct = false;

		//---------------------------------------------------------------------
		// Perform a LBuffer pass.
		//---------------------------------------------------------------------
		GetLBufferPass()->Render(scene, world_to_projection,
								 world_to_view, view_to_world,
								 camera.GetSettings().GetFog());

		//---------------------------------------------------------------------
		// Perform a voxelization pass.
		//---------------------------------------------------------------------
		if (vct) {
			//TODO
			const auto view_to_voxel = XMMatrixOrthographicOffCenterLH(-0.4f, 0.4f,
																	   -0.4f, 0.4f,
																	   -0.4f, 0.4f);
			const auto world_to_voxel = world_to_view * view_to_voxel;
			GetVoxelizationPass()->Render(scene, world_to_voxel,
										  world_to_view, view_to_world,
										  brdf, 8u);
		}

		// Restore the viewport.
		viewport.BindViewport(m_device_context);

		output_manager->BindBeginGBuffer(m_device_context);

		//---------------------------------------------------------------------
		// Perform a GBuffer pass: opaque fragments.
		//---------------------------------------------------------------------
		GetGBufferPass()->Render(scene, world_to_projection, 
								 world_to_view, view_to_world);

		output_manager->BindEndGBuffer(m_device_context);
		output_manager->BindBeginDeferred(m_device_context);

		//---------------------------------------------------------------------
		// Perform a deferred pass.
		//---------------------------------------------------------------------
		if (DisplayConfiguration::Get()->UsesMSAA()) {
			GetDeferredShadingPass()->Render(brdf, vct);
		}
		else {
			GetDeferredShadingPass()->Dispatch(viewport, brdf, vct);
		}

		output_manager->BindEndDeferred(m_device_context);
		output_manager->BindBeginForward(m_device_context);

		//---------------------------------------------------------------------
		// Perform a forward pass: emissive fragments.
		//---------------------------------------------------------------------
		GetVariableShadingPass()->RenderEmissive(scene, world_to_projection, 
												 world_to_view, view_to_world);

		//---------------------------------------------------------------------
		// Perform a sky pass.
		//---------------------------------------------------------------------
		GetSkyPass()->Render(camera.GetSettings().GetSky());

		//---------------------------------------------------------------------
		// Perform a forward pass: transparent fragments.
		//---------------------------------------------------------------------
		GetVariableShadingPass()->RenderTransparent(scene, world_to_projection, 
													world_to_view, view_to_world, 
													brdf, vct);
	}

	void Renderer::ExecuteAAPipeline(const Camera &camera) {
		const auto output_manager = RenderingOutputManager::Get();
		const auto desc = DisplayConfiguration::Get()->GetAADescriptor();
		const auto viewport = camera.GetSSViewport();

		switch (desc) {

		case AADescriptor::FXAA: {
			output_manager->BindBeginResolve(m_device_context);

			// Perform an AA pass.
			GetAAPass()->DispatchPreprocess(viewport, AADescriptor::FXAA);

			output_manager->BindEndResolve(m_device_context);
			output_manager->BindPingPong(m_device_context);

			// Perform a FXAA pass.
			GetAAPass()->Dispatch(viewport, AADescriptor::FXAA);

			break;
		}

		case AADescriptor::MSAA_2x:
		case AADescriptor::MSAA_4x:
		case AADescriptor::MSAA_8x:
		case AADescriptor::SSAA_2x:
		case AADescriptor::SSAA_3x:
		case AADescriptor::SSAA_4x: {
			output_manager->BindBeginResolve(m_device_context);

			// Perform an AA pass.
			GetAAPass()->Dispatch(viewport, desc);

			output_manager->BindEndResolve(m_device_context);
			break;
		}

		}
	}
}