//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_renderer.hpp"
#include "rendering\rendering_state_cache.hpp"
#include "math\view_frustum.hpp"
#include "logging\error.hpp"

// Include HLSL bindings.
#include "..\..\shaders\hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	LBufferPass::LBufferPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_light_buffer(),
		m_directional_lights(3),
		m_omni_lights(32),
		m_spot_lights(32),
		m_sm_directional_lights(1),
		m_sm_omni_lights(1),
		m_sm_spot_lights(1),
		m_directional_sms(MakeUnique< ShadowMapBuffer >()),
		m_omni_sms(MakeUnique< ShadowCubeMapBuffer >()),
		m_spot_sms(MakeUnique< ShadowMapBuffer >()),
		m_directional_light_cameras(),
		m_omni_light_cameras(),
		m_spot_light_cameras() {}

	void XM_CALLCONV LBufferPass::Render(
		const PassBuffer *scene, 
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world) {

		Assert(scene);
		
		// Process the lights without shadow mapping.
		ProcessLights(scene->GetDirectionalLights(),
			world_to_view);
		ProcessLights(scene->GetOmniLights(), 
			world_to_projection, world_to_view);
		ProcessLights(scene->GetSpotLights(), 
			world_to_projection, world_to_view);
		
		// Process the lights with shadow mapping.
		ProcessLightsWithShadowMapping(scene->GetDirectionalLightsWithShadowMapping(), 
			world_to_view, view_to_world);
		ProcessLightsWithShadowMapping(scene->GetOmniLightsWithShadowMapping(), 
			world_to_projection, world_to_view, view_to_world);
		ProcessLightsWithShadowMapping(scene->GetSpotLightsWithShadowMapping(), 
			world_to_projection, world_to_view, view_to_world);
		
		// Unbind the shadow map SRVs.
		UnbindShadowMaps();
		// Setup the shadow maps.
		SetupShadowMaps();
		// Render the shadow maps.
		RenderShadowMaps(scene, world_to_view);

		// Process the lights' data.
		ProcessLightsData(scene);

		// Bind the LBuffer.
		BindLBuffer();
	}

	void LBufferPass::UnbindShadowMaps() const noexcept {
		ID3D11ShaderResourceView * const srvs[3] = {};

		// Unbind the shadow map SRVs.
		Pipeline::PS::BindSRVs(m_device_context,
			SLOT_SRV_SHADOW_MAPS_START,
			_countof(srvs), srvs);
		Pipeline::CS::BindSRVs(m_device_context,
			SLOT_SRV_SHADOW_MAPS_START,
			_countof(srvs), srvs);
	}

	void LBufferPass::BindLBuffer() const noexcept {
		ID3D11ShaderResourceView * const srvs[9] = {
			m_directional_lights.Get(),
			m_omni_lights.Get(),
			m_spot_lights.Get(),
			m_sm_directional_lights.Get(),
			m_sm_omni_lights.Get(),
			m_sm_spot_lights.Get(),
			m_directional_sms->GetSRV(),
			m_omni_sms->GetSRV(),
			m_spot_sms->GetSRV()
		};

		// Bind no RTV and DSV.
		Pipeline::OM::BindRTVAndDSV(m_device_context, nullptr, nullptr);

		// Bind constant buffer.
		Pipeline::PS::BindConstantBuffer(m_device_context,
			SLOT_CBUFFER_LIGHTING,
			m_light_buffer.Get());
		Pipeline::CS::BindConstantBuffer(m_device_context,
			SLOT_CBUFFER_LIGHTING,
			m_light_buffer.Get());
		
		// Bind the SRVs.
		Pipeline::PS::BindSRVs(m_device_context,
			SLOT_SRV_LIGHTS_START,
			_countof(srvs), srvs);
		Pipeline::CS::BindSRVs(m_device_context,
			SLOT_SRV_LIGHTS_START,
			_countof(srvs), srvs);
	}

	void LBufferPass::ProcessLightsData(const PassBuffer *scene) {

		LightBuffer buffer;
		buffer.m_Ia                             = scene->GetAmbientLight();
		
		buffer.m_fog_color                      = scene->GetFog()->GetIntensity();
		buffer.m_fog_distance_falloff_start     = scene->GetFog()->GetStartDistanceFalloff();
		buffer.m_fog_distance_falloff_inv_range = 1.0f / scene->GetFog()->GetRangeDistanceFalloff();

		buffer.m_nb_directional_lights          = static_cast< u32 >(m_directional_lights.size());
		buffer.m_nb_omni_lights                 = static_cast< u32 >(m_omni_lights.size());
		buffer.m_nb_spot_lights                 = static_cast< u32 >(m_spot_lights.size());
		buffer.m_nb_sm_directional_lights       = static_cast< u32 >(m_sm_directional_lights.size());
		buffer.m_nb_sm_omni_lights              = static_cast< u32 >(m_sm_omni_lights.size());
		buffer.m_nb_sm_spot_lights              = static_cast< u32 >(m_sm_spot_lights.size());
		
		// Update the light buffer.
		m_light_buffer.UpdateData(m_device_context, buffer);
	}

	void XM_CALLCONV LBufferPass::ProcessLights(
		const vector< const DirectionalLightNode * > &lights,
		FXMMATRIX world_to_view) {

		vector< DirectionalLightBuffer > buffer;
		buffer.reserve(lights.size());

		for (const auto node : lights) {
			const TransformNode    * const transform = node->GetTransform();
			const DirectionalLight * const light     = node->GetLight();

			// Transform to view space.
			const XMVECTOR d = XMVector3Normalize(XMVector3TransformNormal(transform->GetWorldForward(), world_to_view));

			// Create a directional light buffer.
			DirectionalLightBuffer light_buffer;
			XMStoreFloat3(&light_buffer.m_neg_d, -d);
			light_buffer.m_I = light->GetIntensity();

			// Add directional light buffer to directional light buffers.
			buffer.push_back(std::move(light_buffer));
		}

		// Update the buffer for directional lights.
		m_directional_lights.UpdateData(m_device_context, buffer);
	}

	void XM_CALLCONV LBufferPass::ProcessLights(
		const vector< const OmniLightNode * > &lights,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view) {

		vector< OmniLightBuffer > buffer;
		buffer.reserve(lights.size());

		for (const auto node : lights) {
			const TransformNode * const transform = node->GetTransform();
			const OmniLight     * const light     = node->GetLight();
			const XMMATRIX object_to_world        = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection   = object_to_world * world_to_projection;

			// Cull the light against the view frustum.
			if (ViewFrustum::Cull(object_to_projection, light->GetBS())) {
				continue;
			}

			// Transform to view space.
			const XMVECTOR p = XMVector3TransformCoord(transform->GetWorldEye(), world_to_view);

			// Create an omni light buffer.
			OmniLightBuffer light_buffer;
			XMStoreFloat3(&light_buffer.m_p, p);
			light_buffer.m_I                          = light->GetIntensity();
			light_buffer.m_distance_falloff_end       = light->GetEndDistanceFalloff();
			light_buffer.m_distance_falloff_inv_range = 1.0f / light->GetRangeDistanceFalloff();

			// Add omni light buffer to omni light buffers.
			buffer.push_back(std::move(light_buffer));
		}

		// Update the buffer for omni lights.
		m_omni_lights.UpdateData(m_device_context, buffer);
	}

	void XM_CALLCONV LBufferPass::ProcessLights(
		const vector< const SpotLightNode * > &lights,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view) {

		vector< SpotLightBuffer > buffer;
		buffer.reserve(lights.size());

		for (const auto node : lights) {
			const TransformNode  * const transform = node->GetTransform();
			const SpotLight      * const light     = node->GetLight();
			const XMMATRIX object_to_world         = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection    = object_to_world * world_to_projection;

			// Cull the light against the view frustum.
			if (ViewFrustum::Cull(object_to_projection, light->GetAABB())) {
				continue;
			}

			// Transform to view space.
			const XMVECTOR p = XMVector3TransformCoord(transform->GetWorldEye(), world_to_view);
			const XMVECTOR d = XMVector3Normalize(XMVector3TransformNormal(transform->GetWorldForward(), world_to_view));

			// Create a spotlight buffer.
			SpotLightBuffer light_buffer;
			XMStoreFloat3(&light_buffer.m_p, p);
			XMStoreFloat3(&light_buffer.m_neg_d, -d);
			light_buffer.m_I                          = light->GetIntensity();
			light_buffer.m_exponent_property          = light->GetExponentProperty();
			light_buffer.m_distance_falloff_end       = light->GetEndDistanceFalloff();
			light_buffer.m_distance_falloff_inv_range = 1.0f / light->GetRangeDistanceFalloff();
			light_buffer.m_cos_umbra                  = light->GetEndAngularCutoff();
			light_buffer.m_cos_inv_range              = 1.0f / light->GetRangeAngularCutoff();

			// Add spotlight buffer to spotlight buffers.
			buffer.push_back(std::move(light_buffer));
		}

		// Update the buffer for spotlights.
		m_spot_lights.UpdateData(m_device_context, buffer);
	}

	void XM_CALLCONV LBufferPass::ProcessLightsWithShadowMapping(
		const vector< const DirectionalLightNode * > &lights,
		FXMMATRIX world_to_view,
		CXMMATRIX view_to_world) {

		vector< DirectionalLightWithShadowMappingBuffer > buffer;
		buffer.reserve(lights.size());
		m_directional_light_cameras.clear();

		for (const auto node : lights) {
			const TransformNode    * const transform = node->GetTransform();
			const DirectionalLight * const light     = node->GetLight();

			// Transform to view space.
			const XMVECTOR d = XMVector3Normalize(XMVector3TransformNormal(transform->GetWorldForward(), world_to_view));

			// Create a directional light buffer.
			DirectionalLightWithShadowMappingBuffer light_buffer;
			XMStoreFloat3(&light_buffer.m_light.m_neg_d, -d);
			light_buffer.m_light.m_I = light->GetIntensity();

			// Add directional light buffer to directional light buffers.
			buffer.push_back(std::move(light_buffer));
		}

		// Update the buffer for directional lights.
		m_sm_directional_lights.UpdateData(m_device_context, buffer);
	}

	void XM_CALLCONV LBufferPass::ProcessLightsWithShadowMapping(
		const vector< const OmniLightNode * > &lights,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world) {

		static const XMMATRIX rotations[6] = {
			XMMatrixRotationY(-XM_PIDIV2), // Look: +x
			XMMatrixRotationY( XM_PIDIV2), // Look: -x
			XMMatrixRotationX( XM_PIDIV2), // Look: +y
			XMMatrixRotationX(-XM_PIDIV2), // Look: -y
			XMMatrixIdentity(),            // Look: +z
			XMMatrixRotationY(XM_PI),      // Look: -z
		};

		vector< OmniLightWithShadowMappingBuffer > buffer;
		buffer.reserve(lights.size());
		m_omni_light_cameras.clear();

		for (const auto node : lights) {
			const TransformNode * const transform = node->GetTransform();
			const OmniLight     * const light     = node->GetLight();
			const XMMATRIX object_to_world        = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection   = object_to_world * world_to_projection;

			// Cull the light against the view frustum.
			if (ViewFrustum::Cull(object_to_projection, light->GetBS())) {
				continue;
			}

			// Create six omni light cameras.
			const XMMATRIX world_to_lview         = transform->GetWorldToViewMatrix();
			const XMMATRIX lview_to_lprojection   = light->GetViewToProjectionMatrix();
			for (size_t i = 0; i < _countof(rotations); ++i) {
				LightCameraInfo camera;
				camera.cview_to_lprojection       = view_to_world * world_to_lview * rotations[i] * lview_to_lprojection;

				// Add omni light camera to the omni light cameras.
				m_omni_light_cameras.push_back(std::move(camera));
			}
			const XMMATRIX cview_to_lview         = view_to_world * world_to_lview;

			// Transform to view space.
			const XMVECTOR p = XMVector3TransformCoord(transform->GetWorldEye(), world_to_view);

			// Create an omni light buffer.
			OmniLightWithShadowMappingBuffer light_buffer;
			XMStoreFloat3(&light_buffer.m_light.m_p, p);
			light_buffer.m_light.m_I                          = light->GetIntensity();
			light_buffer.m_light.m_distance_falloff_end       = light->GetEndDistanceFalloff();
			light_buffer.m_light.m_distance_falloff_inv_range = 1.0f / light->GetRangeDistanceFalloff();
			light_buffer.m_cview_to_lview                     = XMMatrixTranspose(cview_to_lview);
			XMStoreFloat2(&light_buffer.m_projection_values, GetNDCZConstructionValues(lview_to_lprojection));

			// Add omni light buffer to omni light buffers.
			buffer.push_back(std::move(light_buffer));
		}

		// Update the buffer for omni lights.
		m_sm_omni_lights.UpdateData(m_device_context, buffer);
	}

	void XM_CALLCONV LBufferPass::ProcessLightsWithShadowMapping(
		const vector< const SpotLightNode * > &lights,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world) {

		vector< SpotLightWithShadowMappingBuffer > buffer;
		buffer.reserve(lights.size());
		m_spot_light_cameras.clear();

		for (const auto node : lights) {
			const TransformNode  * const transform = node->GetTransform();
			const SpotLight      * const light     = node->GetLight();
			const XMMATRIX object_to_world         = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection    = object_to_world * world_to_projection;

			// Cull the light against the view frustum.
			if (ViewFrustum::Cull(object_to_projection, light->GetAABB())) {
				continue;
			}

			const XMMATRIX world_to_lview          = transform->GetWorldToViewMatrix();
			const XMMATRIX lview_to_lprojection    = light->GetViewToProjectionMatrix();
			const XMMATRIX cview_to_lprojection    = view_to_world * world_to_lview * lview_to_lprojection;

			// Create a spotlight camera.
			LightCameraInfo camera;
			camera.cview_to_lprojection            = cview_to_lprojection;

			// Add spotlight camera to the spotlight cameras.
			m_spot_light_cameras.push_back(std::move(camera));

			// Transform to view space.
			const XMVECTOR p = XMVector3TransformCoord(transform->GetWorldEye(), world_to_view);
			const XMVECTOR d = XMVector3Normalize(XMVector3TransformNormal(transform->GetWorldForward(), world_to_view));

			// Create a spotlight buffer.
			SpotLightWithShadowMappingBuffer light_buffer;
			XMStoreFloat3(&light_buffer.m_light.m_p, p);
			XMStoreFloat3(&light_buffer.m_light.m_neg_d, -d);
			light_buffer.m_light.m_I                          = light->GetIntensity();
			light_buffer.m_light.m_exponent_property          = light->GetExponentProperty();
			light_buffer.m_light.m_distance_falloff_end       = light->GetEndDistanceFalloff();
			light_buffer.m_light.m_distance_falloff_inv_range = 1.0f / light->GetRangeDistanceFalloff();
			light_buffer.m_light.m_cos_umbra                  = light->GetEndAngularCutoff();
			light_buffer.m_light.m_cos_inv_range              = 1.0f / light->GetRangeAngularCutoff();
			light_buffer.m_cview_to_lprojection               = XMMatrixTranspose(cview_to_lprojection);

			// Add spotlight buffer to spotlight buffers.
			buffer.push_back(std::move(light_buffer));
		}

		// Update the buffer for spotlights .
		m_sm_spot_lights.UpdateData(m_device_context, buffer);
	}

	void LBufferPass::SetupShadowMaps() {
		// Setup the shadow maps of the directional lights.
		SetupDirectionalShadowMaps();
		// Setup the shadow maps of the omni lights.
		SetupOmniShadowMaps();
		// Setup the shadow maps of the spotlights.
		SetupSpotShadowMaps();
	}

	void LBufferPass::SetupDirectionalShadowMaps() {
		const size_t nb_requested = GetNumberOfDirectionalLightsWithShadowMapping();
		const size_t nb_available = m_directional_sms->GetNumberOfShadowMaps();
		
		if (nb_available < nb_requested) {
			m_directional_sms = MakeUnique< ShadowMapBuffer >(nb_requested);
		}
		
		m_directional_sms->ClearDSVs(m_device_context);
	}
	
	void LBufferPass::SetupOmniShadowMaps() {
		const size_t nb_requested = GetNumberOfOmniLightsWithShadowMapping();
		const size_t nb_available = m_omni_sms->GetNumberOfShadowCubeMaps();

		if (nb_available < nb_requested) {
			m_omni_sms = MakeUnique< ShadowCubeMapBuffer >(nb_requested);
		}
		
		m_omni_sms->ClearDSVs(m_device_context);
	}
	
	void LBufferPass::SetupSpotShadowMaps() {
		const size_t nb_requested = GetNumberOfSpotLightsWithShadowMapping();
		const size_t nb_available = m_spot_sms->GetNumberOfShadowMaps();

		if (nb_available < nb_requested) {
			m_spot_sms = MakeUnique< ShadowMapBuffer >(nb_requested);
		}
		
		m_spot_sms->ClearDSVs(m_device_context);
	}

	void LBufferPass::RenderShadowMaps(
		const PassBuffer *scene, 
		FXMMATRIX world_to_cview) {
		DepthPass * const pass = DepthPass::Get();
		pass->BindFixedState();

		// Render the shadow maps of the directional lights.
		RenderDirectionalShadowMaps(pass, scene, world_to_cview);
		// Render the shadow maps of the omni lights.
		RenderOmniShadowMaps(pass, scene, world_to_cview);
		// Render the shadow maps of the spotlights.
		RenderSpotShadowMaps(pass, scene, world_to_cview);
	}

	void LBufferPass::RenderDirectionalShadowMaps(
		DepthPass *pass, const PassBuffer *scene, 
		FXMMATRIX world_to_cview) {

		// Bind the viewport.
		m_directional_sms->BindViewport(m_device_context);

		for (size_t i = 0; i < m_directional_light_cameras.size(); ++i) {
			const LightCameraInfo &camera = m_directional_light_cameras[i];
			const XMMATRIX world_to_lprojection
				= world_to_cview * camera.cview_to_lprojection;

			// Bind the DSV.
			m_directional_sms->BindDSV(m_device_context, i);

			// Perform the depth pass.
			pass->RenderOccluders(scene,
				world_to_lprojection,
				world_to_cview,
				camera.cview_to_lprojection);
		}
	}

	void LBufferPass::RenderOmniShadowMaps(
		DepthPass *pass, const PassBuffer *scene, 
		FXMMATRIX world_to_cview) {

		// Bind the viewport.
		m_omni_sms->BindViewport(m_device_context);

		for (size_t i = 0; i < m_omni_light_cameras.size(); ++i) {
			const LightCameraInfo &camera = m_omni_light_cameras[i];
			const XMMATRIX world_to_lprojection
				= world_to_cview * camera.cview_to_lprojection;

			// Bind the DSV.
			m_omni_sms->BindDSV(m_device_context, i);

			// Perform the depth pass.
			pass->RenderOccluders(scene,
				world_to_lprojection,
				world_to_cview,
				camera.cview_to_lprojection);
		}
	}
	
	void LBufferPass::RenderSpotShadowMaps(
		DepthPass *pass, const PassBuffer *scene, 
		FXMMATRIX world_to_cview) {

		// Bind the viewport.
		m_spot_sms->BindViewport(m_device_context);

		for (size_t i = 0; i < m_spot_light_cameras.size(); ++i) {
			const LightCameraInfo &camera = m_spot_light_cameras[i];
			const XMMATRIX world_to_lprojection 
				= world_to_cview * camera.cview_to_lprojection;

			// Bind the DSV.
			m_spot_sms->BindDSV(m_device_context, i);

			// Perform the depth pass.
			pass->RenderOccluders(scene,
				world_to_lprojection,
				world_to_cview,
				camera.cview_to_lprojection);
		}
	}
}