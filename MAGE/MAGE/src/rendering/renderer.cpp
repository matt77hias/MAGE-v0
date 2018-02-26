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

	//TODO
	constexpr U32 g_voxel_grid_resolution = 128u;
	constexpr F32 g_voxel_size = 0.08f;

	[[nodiscard]] Renderer *Renderer::Get() noexcept {
		Assert(RenderingManager::Get());
		
		return RenderingManager::Get()->GetRenderer();
	}

	Renderer::Renderer(ID3D11Device *device,
		               ID3D11DeviceContext *device_context)
		: m_device_context(device_context),
		m_game_buffer(device),
		m_aa_pass(),
		m_back_buffer_pass(),
		m_bounding_volume_pass(),
		m_deferred_pass(),
		m_depth_pass(),
		m_dof_pass(),
		m_forward_pass(),
		m_lbuffer_pass(),
		m_sky_pass(),
		m_sprite_pass(),
		m_voxelization_pass(), 
		m_voxel_grid_pass() {}
	
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

		//TODO
		buffer.m_voxel_grid_resolution        = g_voxel_grid_resolution;
		buffer.m_voxel_grid_inv_resolution    = 1.0f / buffer.m_voxel_grid_resolution;
		buffer.m_voxel_size                   = g_voxel_size;
		buffer.m_voxel_inv_size               = 1.0f / buffer.m_voxel_size;

		// Update the game buffer.
		m_game_buffer.UpdateData(m_device_context, buffer);
		// Bind the game buffer.
		m_game_buffer.Bind< Pipeline >(m_device_context, SLOT_CBUFFER_GAME);
	}

	void Renderer::Render(const Scene &scene) {
		// Update the buffers.
		UpdateBuffers(scene);

		// Render the scene for each camera.
		scene.ForEach< Camera >([this, &scene](const Camera &camera) {
			if (State::Active != camera.GetState()) {
				return;
			}

			// Render the scene.
			Render(scene, camera);
		});

		// Bind the maximum viewport.
		Viewport().BindViewport(m_device_context);

		// Perform a sprite pass.
		GetSpritePass()->Render(scene);
	}

	void Renderer::UpdateBuffers(const Scene &scene) const {
		// Update the buffer of each camera.
		scene.ForEach< Camera >(
			[device_context(m_device_context)](const Camera &camera) {
				if (State::Active == camera.GetState()) {
					camera.UpdateBuffer(device_context);
				}
			}
		);

		// Update the buffer of each model..
		scene.ForEach< Model >(
			[device_context(m_device_context)](const Model &model) {
				if (State::Active == model.GetState()) {
					model.UpdateBuffer(device_context);
				}
			}
		);
	}

	void Renderer::Render(const Scene &scene, const Camera &camera) {
		// Bind the camera to the pipeline.
		camera.BindBuffer< Pipeline >(m_device_context,
									  SLOT_CBUFFER_PRIMARY_CAMERA);

		// Obtain the world-to-projection transformation matrix of the 
		// camera for view frustum culling.
		const auto &transform           = camera.GetOwner()->GetTransform();
		const auto world_to_camera      = transform.GetWorldToObjectMatrix();
		const auto camera_to_projection = camera.GetCameraToProjectionMatrix();
		const auto world_to_projection  = world_to_camera * camera_to_projection;

		const auto output_manager       = OutputManager::Get();
		const auto render_mode          = camera.GetSettings().GetRenderMode();

		output_manager->BindBegin(m_device_context);

		//---------------------------------------------------------------------
		// RenderMode
		//---------------------------------------------------------------------
		switch (render_mode) {

		case RenderMode::Forward: {
			RenderForward(scene, camera, world_to_projection);
			break;
		}
		
		case RenderMode::Deferred: {
			RenderDeferred(scene, camera, world_to_projection);
			break;
		}
		
		case RenderMode::Solid: {
			RenderSolid(scene, camera, world_to_projection);
			break;
		}
		
		case RenderMode::VoxelGrid: {
			RenderVoxelGrid(scene, camera, world_to_projection);
			break;
		}

		case RenderMode::FalseColor_BaseColor: {
			RenderFalseColor(scene, camera, world_to_projection, 
							 FalseColor::BaseColor);
			break;
		}
		case RenderMode::FalseColor_BaseColorCoefficient: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::BaseColorCoefficient);
			break;
		}
		case RenderMode::FalseColor_BaseColorTexture: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::BaseColorTexture);
			break;
		}
		case RenderMode::FalseColor_Material: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::Material);
			break;
		}
		case RenderMode::FalseColor_MaterialCoefficient: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::MaterialCoefficient);
			break;
		}
		case RenderMode::FalseColor_MaterialTexture: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::MaterialTexture);
			break;
		}
		case RenderMode::FalseColor_Roughness: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::Roughness);
			break;
		}
		case RenderMode::FalseColor_RoughnessCoefficient: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::RoughnessCoefficient);
			break;
		}
		case RenderMode::FalseColor_RoughnessTexture: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::RoughnessTexture);
			break;
		}
		case RenderMode::FalseColor_Metalness: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::Metalness);
			break;
		}
		case RenderMode::FalseColor_MetalnessCoefficient: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::MetalnessCoefficient);
			break;
		}
		case RenderMode::FalseColor_MetalnessTexture: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::MetalnessTexture);
			break;
		}
		case RenderMode::FalseColor_ShadingNormal: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::ShadingNormal);
			break;
		}
		case RenderMode::FalseColor_TSNMShadingNormal: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::TSNMShadingNormal);
			break;
		}
		case RenderMode::FalseColor_Depth: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::Depth);
			break;
		}
		case RenderMode::FalseColor_Distance: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::Distance);
			break;
		}
		case RenderMode::FalseColor_UV: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::UV);
			break;
		}

		default: {
			camera.BindSSViewport(m_device_context);
			output_manager->BindBeginForward(m_device_context);

			break;
		}

		}

		//---------------------------------------------------------------------
		// RenderLayer
		//---------------------------------------------------------------------
		const auto &settings = camera.GetSettings();
		if (settings.ContainsRenderLayer(RenderLayer::Wireframe)) {
			GetForwardPass()->RenderWireframe(scene, world_to_projection);
		}
		if (settings.ContainsRenderLayer(RenderLayer::AABB)) {
			GetBoundingVolumePass()->Render(scene, world_to_projection);
		}

		output_manager->BindEndForward(m_device_context);

		//---------------------------------------------------------------------
		// Anti-aliasing
		//---------------------------------------------------------------------
		
		RenderAA(camera);

		//---------------------------------------------------------------------
		// Post-processing
		//---------------------------------------------------------------------
		
		RenderPostProcessing(camera);

		//---------------------------------------------------------------------
		// Back Buffer
		//---------------------------------------------------------------------
		
		output_manager->BindEnd(m_device_context);

		// Perform a back buffer pass.
		GetBackBufferPass()->Render();
	}

	void XM_CALLCONV Renderer::RenderForward(const Scene &scene,
											 const Camera &camera,
											 FXMMATRIX world_to_projection) {

		const auto output_manager = OutputManager::Get();
		const auto vct            = false;

		//---------------------------------------------------------------------
		// LBuffer
		//---------------------------------------------------------------------
		GetLBufferPass()->Render(scene, world_to_projection, 
								 camera.GetSettings().GetFog());

		//---------------------------------------------------------------------
		// Voxelization
		//---------------------------------------------------------------------
		if (vct) {
			//TODO
			const auto r = g_voxel_grid_resolution * 0.5f * g_voxel_size;
			const auto world_to_voxel = XMMatrixOrthographicOffCenterLH(-r, r,
																	   -r, r,
																	   -r, r);
			GetVoxelizationPass()->Render(scene, world_to_voxel,
										  camera.GetSettings().GetBRDF(), 
										  g_voxel_grid_resolution);
		}

		camera.BindSSViewport(m_device_context);
		output_manager->BindBeginForward(m_device_context);

		//---------------------------------------------------------------------
		// Forward: opaque fragments
		//---------------------------------------------------------------------
		GetForwardPass()->Render(scene, world_to_projection, 
								 camera.GetSettings().GetBRDF(), vct);

		//---------------------------------------------------------------------
		// Sky
		//---------------------------------------------------------------------
		GetSkyPass()->Render(camera.GetSettings().GetSky());

		//---------------------------------------------------------------------
		// Forward: transparent fragments
		//---------------------------------------------------------------------
		GetForwardPass()->RenderTransparent(scene, world_to_projection, 
											camera.GetSettings().GetBRDF(), vct);
	}

	void XM_CALLCONV Renderer::RenderDeferred(const Scene &scene,
											  const Camera &camera,
											  FXMMATRIX world_to_projection) {
		
		const auto output_manager = OutputManager::Get();
		const auto vct = false;

		//---------------------------------------------------------------------
		// LBuffer
		//---------------------------------------------------------------------
		GetLBufferPass()->Render(scene, world_to_projection,
								 camera.GetSettings().GetFog());

		//---------------------------------------------------------------------
		// Voxelization
		//---------------------------------------------------------------------
		if (vct) {
			//TODO
			const auto r = g_voxel_grid_resolution * 0.5f * g_voxel_size;
			const auto world_to_voxel = XMMatrixOrthographicOffCenterLH(-r, r,
																		-r, r,
																		-r, r);
			GetVoxelizationPass()->Render(scene, world_to_voxel,
										  camera.GetSettings().GetBRDF(),
										  g_voxel_grid_resolution);
		}

		camera.BindSSViewport(m_device_context);
		output_manager->BindBeginGBuffer(m_device_context);

		//---------------------------------------------------------------------
		// GBuffer: opaque fragments
		//---------------------------------------------------------------------
		GetForwardPass()->RenderGBuffer(scene, world_to_projection);

		output_manager->BindEndGBuffer(m_device_context);
		output_manager->BindBeginDeferred(m_device_context);

		//---------------------------------------------------------------------
		// Deferred: opaque fragments
		//---------------------------------------------------------------------
		if (DisplayConfiguration::Get()->UsesMSAA()) {
			GetDeferredPass()->Render(camera.GetSettings().GetBRDF(), vct);
		}
		else {
			GetDeferredPass()->Dispatch(camera.GetSSViewport(), 
										camera.GetSettings().GetBRDF(), vct);
		}

		output_manager->BindEndDeferred(m_device_context);
		output_manager->BindBeginForward(m_device_context);

		//---------------------------------------------------------------------
		// Forward: emissive fragments.
		//---------------------------------------------------------------------
		GetForwardPass()->RenderEmissive(scene, world_to_projection);

		//---------------------------------------------------------------------
		// Perform a sky pass.
		//---------------------------------------------------------------------
		GetSkyPass()->Render(camera.GetSettings().GetSky());

		//---------------------------------------------------------------------
		// Forward: transparent fragments
		//---------------------------------------------------------------------
		GetForwardPass()->RenderTransparent(scene, world_to_projection,
											camera.GetSettings().GetBRDF(), vct);
	}

	void XM_CALLCONV Renderer::RenderSolid(const Scene &scene,
										   const Camera &camera,
										   FXMMATRIX world_to_projection) {

		//---------------------------------------------------------------------
		// LBuffer
		//---------------------------------------------------------------------
		GetLBufferPass()->Render(scene, world_to_projection, 
								 camera.GetSettings().GetFog());

		camera.BindSSViewport(m_device_context);
		OutputManager::Get()->BindBeginForward(m_device_context);

		//---------------------------------------------------------------------
		// Forward
		//---------------------------------------------------------------------
		GetForwardPass()->RenderSolid(scene, world_to_projection);
	}

	void XM_CALLCONV Renderer::RenderFalseColor(const Scene &scene, 
												const Camera &camera,
												FXMMATRIX world_to_projection, 
												FalseColor false_color) {
		
		camera.BindSSViewport(m_device_context);
		OutputManager::Get()->BindBeginForward(m_device_context);

		//---------------------------------------------------------------------
		// Forward
		//---------------------------------------------------------------------
		GetForwardPass()->RenderFalseColor(scene, world_to_projection, false_color);
	}

	void XM_CALLCONV Renderer::RenderVoxelGrid(const Scene &scene, 
											   const Camera &camera,
											   FXMMATRIX world_to_projection) {

		//---------------------------------------------------------------------
		// LBuffer
		//---------------------------------------------------------------------
		GetLBufferPass()->Render(scene, world_to_projection,
								 camera.GetSettings().GetFog());

		//---------------------------------------------------------------------
		// Voxelization
		//---------------------------------------------------------------------
		//TODO
		const auto r = g_voxel_grid_resolution * 0.5f * g_voxel_size;
		const auto world_to_voxel = XMMatrixOrthographicOffCenterLH(-r, r, 
																	-r, r, 
																	-r, r);
		GetVoxelizationPass()->Render(scene, world_to_voxel, 
									  camera.GetSettings().GetBRDF(), 
									  g_voxel_grid_resolution);

		camera.BindSSViewport(m_device_context);
		OutputManager::Get()->BindBeginForward(m_device_context);
		
		//---------------------------------------------------------------------
		// Voxel Grid
		//---------------------------------------------------------------------
		GetVoxelGridPass()->Render(g_voxel_grid_resolution);
	}

	void Renderer::RenderPostProcessing(const Camera &camera) {
		const auto output_manager = OutputManager::Get();

		camera.BindViewport(m_device_context);
		output_manager->BindBeginPostProcessing(m_device_context);

		//---------------------------------------------------------------------
		// Depth-of-field
		//---------------------------------------------------------------------
		if (camera.GetLens().HasFiniteAperture()) {
			output_manager->BindPingPong(m_device_context);

			// Perform a depth-of-field pass.
			GetDOFPass()->Dispatch(camera.GetViewport());
		}
	}

	void Renderer::RenderAA(const Camera &camera) {
		const auto output_manager = OutputManager::Get();
		const auto desc = DisplayConfiguration::Get()->GetAADescriptor();
		const auto viewport = camera.GetSSViewport();

		switch (desc) {

		case AADescriptor::FXAA: {
			output_manager->BindBeginResolve(m_device_context);

			//-----------------------------------------------------------------
			// AA pre-processing
			//-----------------------------------------------------------------
			GetAAPass()->DispatchPreprocess(viewport, AADescriptor::FXAA);

			output_manager->BindEndResolve(m_device_context);
			output_manager->BindPingPong(m_device_context);

			//-----------------------------------------------------------------
			// FXAA
			//-----------------------------------------------------------------
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

			//-----------------------------------------------------------------
			// MSAA/SSAA
			//-----------------------------------------------------------------
			GetAAPass()->Dispatch(viewport, desc);

			output_manager->BindEndResolve(m_device_context);
			break;
		}

		}
	}
}