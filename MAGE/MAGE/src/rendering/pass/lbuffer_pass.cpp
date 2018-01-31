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
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <iterator>

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

	LBufferPass::LBufferPass(LBufferPass &&buffer) noexcept = default;
	
	LBufferPass::~LBufferPass() = default;

	void XM_CALLCONV LBufferPass::Render(
		const Scene &scene, 
		const Fog &fog, 
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world) {
		
		// Process the lights.
		ProcessDirectionalLights(scene, world_to_view, view_to_world);
		ProcessOmniLights(scene, world_to_projection, world_to_view, view_to_world);
		ProcessSpotLights(scene, world_to_projection, world_to_view, view_to_world);
		
		// Unbind the shadow map SRVs.
		UnbindShadowMaps();
		
		// Setup the shadow maps.
		SetupDirectionalShadowMaps();
		SetupOmniShadowMaps();
		SetupSpotShadowMaps();
		
		// Render the shadow maps.
		DepthPass * const pass = DepthPass::Get();
		pass->BindFixedState();
		RenderDirectionalShadowMaps(pass, scene, world_to_view);
		RenderOmniShadowMaps(pass, scene, world_to_view);
		RenderSpotShadowMaps(pass, scene, world_to_view);

		// Process the lights' data.
		ProcessLightsData(scene, fog);

		// Bind the LBuffer.
		BindLBuffer();
	}

	void LBufferPass::UnbindShadowMaps() const noexcept {
		static_assert(SLOT_SRV_OMNI_SHADOW_MAPS == SLOT_SRV_DIRECTIONAL_SHADOW_MAPS + 1);
		static_assert(SLOT_SRV_SPOT_SHADOW_MAPS == SLOT_SRV_DIRECTIONAL_SHADOW_MAPS + 2);
		
		ID3D11ShaderResourceView * const srvs[3] = {};

		// Unbind the shadow map SRVs.
		Pipeline::PS::BindSRVs(m_device_context, SLOT_SRV_DIRECTIONAL_SHADOW_MAPS,
			static_cast< U32 >(std::size(srvs)), srvs);
		Pipeline::CS::BindSRVs(m_device_context, SLOT_SRV_DIRECTIONAL_SHADOW_MAPS,
			static_cast< U32 >(std::size(srvs)), srvs);
	}

	void LBufferPass::BindLBuffer() const noexcept {
		static_assert(SLOT_SRV_OMNI_LIGHTS                   == SLOT_SRV_DIRECTIONAL_LIGHTS + 1);
		static_assert(SLOT_SRV_SPOT_LIGHTS                   == SLOT_SRV_DIRECTIONAL_LIGHTS + 2);
		static_assert(SLOT_SRV_SHADOW_MAPPED_DIRECTIONAL_LIGHTS == SLOT_SRV_DIRECTIONAL_LIGHTS + 3);
		static_assert(SLOT_SRV_SHADOW_MAPPED_OMNI_LIGHTS        == SLOT_SRV_DIRECTIONAL_LIGHTS + 4);
		static_assert(SLOT_SRV_SHADOW_MAPPED_SPOT_LIGHTS        == SLOT_SRV_DIRECTIONAL_LIGHTS + 5);
		static_assert(SLOT_SRV_DIRECTIONAL_SHADOW_MAPS       == SLOT_SRV_DIRECTIONAL_LIGHTS + 6);
		static_assert(SLOT_SRV_OMNI_SHADOW_MAPS              == SLOT_SRV_DIRECTIONAL_LIGHTS + 7);
		static_assert(SLOT_SRV_SPOT_SHADOW_MAPS              == SLOT_SRV_DIRECTIONAL_LIGHTS + 8);
		
		ID3D11ShaderResourceView * const srvs[] = {
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
			SLOT_CBUFFER_LIGHTING, m_light_buffer.Get());
		Pipeline::CS::BindConstantBuffer(m_device_context,
			SLOT_CBUFFER_LIGHTING, m_light_buffer.Get());
		
		// Bind the SRVs.
		Pipeline::PS::BindSRVs(m_device_context, SLOT_SRV_DIRECTIONAL_LIGHTS,
			static_cast< U32 >(std::size(srvs)), srvs);
		Pipeline::CS::BindSRVs(m_device_context, SLOT_SRV_DIRECTIONAL_LIGHTS,
			static_cast< U32 >(std::size(srvs)), srvs);
	}

	void LBufferPass::ProcessLightsData(const Scene &scene, const Fog &fog) {
		LightBuffer buffer;
		
		scene.ForEach< AmbientLight >([&buffer](const AmbientLight &light) {
			if (State::Active != light.GetState()) {
				return;
			}
			
			buffer.m_La = light.GetRadianceSpectrum();
		});

		buffer.m_fog_color                = RGB(fog.GetBaseColor());
		buffer.m_fog_density              = fog.GetDensity();

		buffer.m_nb_directional_lights    = static_cast< U32 >(m_directional_lights.size());
		buffer.m_nb_omni_lights           = static_cast< U32 >(m_omni_lights.size());
		buffer.m_nb_spot_lights           = static_cast< U32 >(m_spot_lights.size());
		buffer.m_nb_sm_directional_lights = static_cast< U32 >(m_sm_directional_lights.size());
		buffer.m_nb_sm_omni_lights        = static_cast< U32 >(m_sm_omni_lights.size());
		buffer.m_nb_sm_spot_lights        = static_cast< U32 >(m_sm_spot_lights.size());
		
		// Update the light buffer.
		m_light_buffer.UpdateData(m_device_context, buffer);
	}

	void XM_CALLCONV LBufferPass::ProcessDirectionalLights(
		const Scene &scene,
		FXMMATRIX world_to_view, 
		CXMMATRIX view_to_world) {

		AlignedVector< DirectionalLightBuffer > lights;
		lights.reserve(m_directional_lights.size());

		AlignedVector< ShadowMappedDirectionalLightBuffer > sm_lights;
		sm_lights.reserve(m_sm_directional_lights.size());
		m_directional_light_cameras.clear();

		// Process the directional lights.
		scene.ForEach< DirectionalLight >([this, &lights, &sm_lights,
			world_to_view, view_to_world](const DirectionalLight &light) {

			if (State::Active != light.GetState()) {
				return;
			}

			const Transform &transform = light.GetOwner()->GetTransform();

			// Transform to view space.
			const XMVECTOR d = XMVector3Normalize(XMVector3TransformNormal(
				transform.GetWorldForward(), world_to_view));

			if (light.UseShadows()) {
				// Create a directional light buffer.
				ShadowMappedDirectionalLightBuffer buffer;
				buffer.m_light.m_neg_d = Direction3(XMStore< F32x3 >(-d));
				buffer.m_light.m_L     = light.GetRadianceSpectrum();

				// Add directional light buffer to directional light buffers.
				sm_lights.push_back(std::move(buffer));
			}
			else {
				// Create a directional light buffer.
				DirectionalLightBuffer buffer;
				buffer.m_neg_d = Direction3(XMStore< F32x3 >(-d));
				buffer.m_L     = light.GetRadianceSpectrum();

				// Add directional light buffer to directional light buffers.
				lights.push_back(std::move(buffer));
			}
		});

		// Update the buffer for directional lights.
		m_directional_lights.UpdateData(m_device_context, lights);
		m_sm_directional_lights.UpdateData(m_device_context, sm_lights);
	}

	void XM_CALLCONV LBufferPass::ProcessOmniLights(
		const Scene &scene,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world) {

		AlignedVector< OmniLightBuffer > lights;
		lights.reserve(m_omni_lights.size());

		AlignedVector< ShadowMappedOmniLightBuffer > sm_lights;
		sm_lights.reserve(m_sm_omni_lights.size());
		m_omni_light_cameras.clear();

		// Process the omni lights.
		scene.ForEach< OmniLight >([this, &lights, &sm_lights,
			world_to_projection, world_to_view, view_to_world](const OmniLight &light) {
			
			static const XMMATRIX rotations[6] = {
				XMMatrixRotationY(-XM_PIDIV2), // Look: +x
				XMMatrixRotationY(XM_PIDIV2),  // Look: -x
				XMMatrixRotationX(XM_PIDIV2),  // Look: +y
				XMMatrixRotationX(-XM_PIDIV2), // Look: -y
				XMMatrixIdentity(),            // Look: +z
				XMMatrixRotationY(XM_PI),      // Look: -z
			};

			if (State::Active != light.GetState()) {
				return;
			}

			const Transform &transform = light.GetOwner()->GetTransform();

			const XMMATRIX object_to_world      = transform.GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection = object_to_world * world_to_projection;

			// Cull the light against the view frustum.
			if (BoundingFrustum::Cull(object_to_projection, light.GetBoundingSphere())) {
				return;
			}

			// Transform to view space.
			const XMVECTOR p = XMVector3TransformCoord(
				transform.GetWorldEye(), world_to_view);

			if (light.UseShadows()) {
				// Create six omni light cameras.
				const XMMATRIX world_to_lview       = transform.GetWorldToViewMatrix();
				const XMMATRIX lview_to_lprojection = light.GetViewToProjectionMatrix();
				for (size_t i = 0; i < std::size(rotations); ++i) {
					LightCameraInfo camera;
					camera.cview_to_lprojection = view_to_world * world_to_lview * rotations[i] * lview_to_lprojection;

					// Add omni light camera to the omni light cameras.
					m_omni_light_cameras.push_back(std::move(camera));
				}
				const XMMATRIX cview_to_lview = view_to_world * world_to_lview;

				// Create an omni light buffer.
				ShadowMappedOmniLightBuffer buffer;
				buffer.m_light.m_p             = Point3(XMStore< F32x3 >(p));
				buffer.m_light.m_inv_sqr_range = 1.0f / (light.GetRange() * light.GetRange());
				buffer.m_light.m_I             = light.GetIntensitySpectrum();
				buffer.m_cview_to_lview        = XMMatrixTranspose(cview_to_lview);
				buffer.m_projection_values     = XMStore< F32x2 >(GetNDCZConstructionValues(
					                                                        lview_to_lprojection));

				// Add omni light buffer to omni light buffers.
				sm_lights.push_back(std::move(buffer));
			}
			else {
				// Create an omni light buffer.
				OmniLightBuffer buffer;
				buffer.m_p             = Point3(XMStore< F32x3 >(p));
				buffer.m_inv_sqr_range = 1.0f / (light.GetRange() * light.GetRange());
				buffer.m_I             = light.GetIntensitySpectrum();

				// Add omni light buffer to omni light buffers.
				lights.push_back(std::move(buffer));
			}
		});

		// Update the buffer for omni lights.
		m_omni_lights.UpdateData(m_device_context, lights);
		m_sm_omni_lights.UpdateData(m_device_context, sm_lights);
	}

	void XM_CALLCONV LBufferPass::ProcessSpotLights(
		const Scene &scene,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world) {

		AlignedVector< SpotLightBuffer > lights;
		lights.reserve(m_spot_lights.size());

		AlignedVector< ShadowMappedSpotLightBuffer > sm_lights;
		sm_lights.reserve(m_sm_spot_lights.size());
		m_spot_light_cameras.clear();

		// Process the omni lights.
		scene.ForEach< SpotLight >([this, &lights, &sm_lights,
			world_to_projection, world_to_view, view_to_world](const SpotLight &light) {
			
			if (State::Active != light.GetState()) {
				return;
			}

			const Transform &transform = light.GetOwner()->GetTransform();

			const XMMATRIX object_to_world      = transform.GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection = object_to_world * world_to_projection;

			// Cull the light against the view frustum.
			if (BoundingFrustum::Cull(object_to_projection, light.GetAABB())) {
				return;
			}

			// Transform to view space.
			const XMVECTOR p = XMVector3TransformCoord(
				transform.GetWorldEye(), world_to_view);
			const XMVECTOR d = XMVector3Normalize(XMVector3TransformNormal(
				transform.GetWorldForward(), world_to_view));

			if (light.UseShadows()) {
				const XMMATRIX world_to_lview       = transform.GetWorldToViewMatrix();
				const XMMATRIX lview_to_lprojection = light.GetViewToProjectionMatrix();
				const XMMATRIX cview_to_lprojection = view_to_world * world_to_lview * lview_to_lprojection;

				// Create a spotlight camera.
				LightCameraInfo camera;
				camera.cview_to_lprojection = cview_to_lprojection;

				// Add spotlight camera to the spotlight cameras.
				m_spot_light_cameras.push_back(std::move(camera));

				// Create a spotlight buffer.
				ShadowMappedSpotLightBuffer buffer;
				buffer.m_light.m_p             = Point3(XMStore< F32x3 >(p));
				buffer.m_light.m_neg_d         = Direction3(XMStore< F32x3 >(-d));
				buffer.m_light.m_inv_sqr_range = 1.0f / (light.GetRange() * light.GetRange());
				buffer.m_light.m_I             = light.GetIntensitySpectrum();
				buffer.m_light.m_cos_umbra     = light.GetEndAngularCutoff();
				buffer.m_light.m_cos_inv_range = 1.0f / light.GetRangeAngularCutoff();
				buffer.m_cview_to_lprojection  = XMMatrixTranspose(cview_to_lprojection);

				// Add omni light buffer to omni light buffers.
				sm_lights.push_back(std::move(buffer));
			}
			else {
				// Create an omni light buffer.
				SpotLightBuffer buffer;
				buffer.m_p             = Point3(XMStore< F32x3 >(p));
				buffer.m_neg_d         = Direction3(XMStore< F32x3 >(-d));
				buffer.m_inv_sqr_range = 1.0f / (light.GetRange() * light.GetRange());
				buffer.m_I             = light.GetIntensitySpectrum();
				buffer.m_cos_umbra     = light.GetEndAngularCutoff();
				buffer.m_cos_inv_range = 1.0f / light.GetRangeAngularCutoff();

				// Add omni light buffer to omni light buffers.
				lights.push_back(std::move(buffer));
			}
		});

		// Update the buffer for omni lights.
		m_spot_lights.UpdateData(m_device_context, lights);
		m_sm_spot_lights.UpdateData(m_device_context, sm_lights);
	}

	void LBufferPass::SetupDirectionalShadowMaps() {
		const auto nb_requested = GetNumberOfDirectionalLightsWithShadowMapping();
		const auto nb_available = m_directional_sms->GetNumberOfShadowMaps();
		
		if (nb_available < nb_requested) {
			m_directional_sms = MakeUnique< ShadowMapBuffer >(nb_requested);
		}
		
		m_directional_sms->ClearDSVs(m_device_context);
	}
	
	void LBufferPass::SetupOmniShadowMaps() {
		const auto nb_requested = GetNumberOfOmniLightsWithShadowMapping();
		const auto nb_available = m_omni_sms->GetNumberOfShadowCubeMaps();

		if (nb_available < nb_requested) {
			m_omni_sms = MakeUnique< ShadowCubeMapBuffer >(nb_requested);
		}
		
		m_omni_sms->ClearDSVs(m_device_context);
	}
	
	void LBufferPass::SetupSpotShadowMaps() {
		const auto nb_requested = GetNumberOfSpotLightsWithShadowMapping();
		const auto nb_available = m_spot_sms->GetNumberOfShadowMaps();

		if (nb_available < nb_requested) {
			m_spot_sms = MakeUnique< ShadowMapBuffer >(nb_requested);
		}
		
		m_spot_sms->ClearDSVs(m_device_context);
	}

	void XM_CALLCONV LBufferPass::RenderDirectionalShadowMaps(
		DepthPass *pass, const Scene &scene,
		FXMMATRIX world_to_cview) {

		// Bind the viewport.
		m_directional_sms->BindViewport(m_device_context);
		// Bind the rasterizer state.
		m_directional_sms->BindRasterizerState(m_device_context);

		size_t i = 0;
		for (const auto &camera : m_directional_light_cameras) {
			const XMMATRIX world_to_lprojection
				= world_to_cview * camera.cview_to_lprojection;

			// Bind the DSV.
			m_directional_sms->BindDSV(m_device_context, i++);

			// Perform the depth pass.
			pass->RenderOccluders(scene,
				                  world_to_lprojection,
				                  world_to_cview,
				                  camera.cview_to_lprojection);
		}
	}

	void XM_CALLCONV LBufferPass::RenderOmniShadowMaps(
		DepthPass *pass, const Scene &scene,
		FXMMATRIX world_to_cview) {

		// Bind the viewport.
		m_omni_sms->BindViewport(m_device_context);
		// Bind the rasterizer state.
		m_omni_sms->BindRasterizerState(m_device_context);

		size_t i = 0;
		for (const auto &camera : m_omni_light_cameras) {
			const XMMATRIX world_to_lprojection
				= world_to_cview * camera.cview_to_lprojection;

			// Bind the DSV.
			m_omni_sms->BindDSV(m_device_context, i++);

			// Perform the depth pass.
			pass->RenderOccluders(scene,
				                  world_to_lprojection,
				                  world_to_cview,
				                  camera.cview_to_lprojection);
		}
	}
	
	void XM_CALLCONV LBufferPass::RenderSpotShadowMaps(
		DepthPass *pass, const Scene &scene, 
		FXMMATRIX world_to_cview) {

		// Bind the viewport.
		m_spot_sms->BindViewport(m_device_context);
		// Bind the rasterizer state.
		m_spot_sms->BindRasterizerState(m_device_context);

		size_t i = 0;
		for (const auto &camera : m_spot_light_cameras) {
			const XMMATRIX world_to_lprojection 
				= world_to_cview * camera.cview_to_lprojection;

			// Bind the DSV.
			m_spot_sms->BindDSV(m_device_context, i++);

			// Perform the depth pass.
			pass->RenderOccluders(scene,
				                  world_to_lprojection,
				                  world_to_cview,
				                  camera.cview_to_lprojection);
		}
	}
}