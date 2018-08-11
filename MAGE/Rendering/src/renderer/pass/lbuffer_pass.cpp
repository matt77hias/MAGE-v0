//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\pass\lbuffer_pass.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	LBufferPass::LBufferPass(ID3D11Device& device,
							 ID3D11DeviceContext& device_context,
							 StateManager& state_manager,
							 ResourceManager& resource_manager)
		: m_device_context(device_context),
		m_light_buffer(device),
		m_directional_lights(device, 3u),
		m_omni_lights(device, 32u),
		m_spot_lights(device, 32u),
		m_sm_directional_lights(device, 1u),
		m_sm_omni_lights(device, 1u),
		m_sm_spot_lights(device, 1u),
		m_directional_sms(MakeUnique< ShadowMapBuffer >(device, 1u)),
		m_omni_sms(MakeUnique< ShadowCubeMapBuffer >(device, 1u)),
		m_spot_sms(MakeUnique< ShadowMapBuffer >(device, 1u)),
		m_directional_light_cameras(),
		m_omni_light_cameras(),
		m_spot_light_cameras(), 
		m_depth_pass(MakeUnique< DepthPass >(device, 
											 device_context,
											 state_manager, 
											 resource_manager)) {}

	LBufferPass::LBufferPass(LBufferPass&& buffer) noexcept = default;
	
	LBufferPass::~LBufferPass() = default;

	LBufferPass& LBufferPass::operator=(LBufferPass&& pass) noexcept = default;

	void XM_CALLCONV LBufferPass
		::Render(const World& world, 
				 FXMMATRIX world_to_projection) {

		// Process the lights.
		ProcessDirectionalLights(world, world_to_projection);
		ProcessOmniLights(world, world_to_projection);
		ProcessSpotLights(world, world_to_projection);
		
		// Unbind the shadow map SRVs.
		UnbindShadowMaps();
		// Setup the shadow maps.
		SetupShadowMaps();
		// Render the shadow maps.
		RenderShadowMaps(world);

		// Process the lights' data.
		ProcessLightsData(world);

		// Bind the LBuffer.
		BindLBuffer();
	}

	void LBufferPass::UnbindShadowMaps() const noexcept {
		static_assert(SLOT_SRV_OMNI_SHADOW_MAPS == SLOT_SRV_DIRECTIONAL_SHADOW_MAPS + 1);
		static_assert(SLOT_SRV_SPOT_SHADOW_MAPS == SLOT_SRV_DIRECTIONAL_SHADOW_MAPS + 2);
		
		ID3D11ShaderResourceView* const srvs[3] = {};

		// Unbind the shadow map SRVs.
		Pipeline::PS::BindSRVs(m_device_context, SLOT_SRV_DIRECTIONAL_SHADOW_MAPS, 
							   static_cast< U32 >(std::size(srvs)), srvs);
		Pipeline::CS::BindSRVs(m_device_context, SLOT_SRV_DIRECTIONAL_SHADOW_MAPS, 
							   static_cast< U32 >(std::size(srvs)), srvs);
	}

	void LBufferPass::BindLBuffer() const noexcept {
		static_assert(SLOT_SRV_OMNI_LIGHTS                      == SLOT_SRV_DIRECTIONAL_LIGHTS + 1);
		static_assert(SLOT_SRV_SPOT_LIGHTS                      == SLOT_SRV_DIRECTIONAL_LIGHTS + 2);
		static_assert(SLOT_SRV_SHADOW_MAPPED_DIRECTIONAL_LIGHTS == SLOT_SRV_DIRECTIONAL_LIGHTS + 3);
		static_assert(SLOT_SRV_SHADOW_MAPPED_OMNI_LIGHTS        == SLOT_SRV_DIRECTIONAL_LIGHTS + 4);
		static_assert(SLOT_SRV_SHADOW_MAPPED_SPOT_LIGHTS        == SLOT_SRV_DIRECTIONAL_LIGHTS + 5);
		static_assert(SLOT_SRV_DIRECTIONAL_SHADOW_MAPS          == SLOT_SRV_DIRECTIONAL_LIGHTS + 6);
		static_assert(SLOT_SRV_OMNI_SHADOW_MAPS                 == SLOT_SRV_DIRECTIONAL_LIGHTS + 7);
		static_assert(SLOT_SRV_SPOT_SHADOW_MAPS                 == SLOT_SRV_DIRECTIONAL_LIGHTS + 8);
		
		ID3D11ShaderResourceView* const srvs[] = {
			&m_directional_lights.Get(),
			&m_omni_lights.Get(),
			&m_spot_lights.Get(),
			&m_sm_directional_lights.Get(),
			&m_sm_omni_lights.Get(),
			&m_sm_spot_lights.Get(),
			&m_directional_sms->GetSRV(),
			&m_omni_sms->GetSRV(),
			&m_spot_sms->GetSRV()
		};

		// Bind no RTV and DSV.
		Pipeline::OM::BindRTVAndDSV(m_device_context, nullptr, nullptr);

		// Bind constant buffer.
		Pipeline::PS::BindConstantBuffer(m_device_context, 
										 SLOT_CBUFFER_LIGHTING, &m_light_buffer.Get());
		Pipeline::CS::BindConstantBuffer(m_device_context, 
										 SLOT_CBUFFER_LIGHTING, &m_light_buffer.Get());
		
		// Bind the SRVs.
		Pipeline::PS::BindSRVs(m_device_context, SLOT_SRV_DIRECTIONAL_LIGHTS, 
							   static_cast< U32 >(std::size(srvs)), srvs);
		Pipeline::CS::BindSRVs(m_device_context, SLOT_SRV_DIRECTIONAL_LIGHTS, 
							   static_cast< U32 >(std::size(srvs)), srvs);
	}

	void LBufferPass::ProcessLightsData(const World& world) {
		LightBuffer buffer;

		buffer.m_nb_directional_lights    = static_cast< U32 >(m_directional_lights.size());
		buffer.m_nb_omni_lights           = static_cast< U32 >(m_omni_lights.size());
		buffer.m_nb_spot_lights           = static_cast< U32 >(m_spot_lights.size());
		buffer.m_nb_sm_directional_lights = static_cast< U32 >(m_sm_directional_lights.size());
		buffer.m_nb_sm_omni_lights        = static_cast< U32 >(m_sm_omni_lights.size());
		buffer.m_nb_sm_spot_lights        = static_cast< U32 >(m_sm_spot_lights.size());

		world.ForEach< AmbientLight >([&buffer](const AmbientLight& light) {
			if (State::Active != light.GetState()) {
				return;
			}

			buffer.m_La = light.GetRadianceSpectrum();
		});
		
		// Update the light buffer.
		m_light_buffer.UpdateData(m_device_context, buffer);
	}

	void XM_CALLCONV LBufferPass
		::ProcessDirectionalLights(const World& world, 
								   FXMMATRIX world_to_projection) {

		AlignedVector< DirectionalLightBuffer > lights;
		lights.reserve(m_directional_lights.size());

		AlignedVector< DirectionalLightBuffer > sm_lights;
		sm_lights.reserve(m_sm_directional_lights.size());
		m_directional_light_cameras.clear();

		// Process the directional lights.
		world.ForEach< DirectionalLight >([this, &lights, &sm_lights, world_to_projection]
		(const DirectionalLight& light) {

			if (State::Active != light.GetState()) {
				return;
			}

			const auto& transform           = light.GetOwner()->GetTransform();
			const auto  light_to_world      = transform.GetObjectToWorldMatrix();
			const auto  light_to_projection = light_to_world * world_to_projection;

			// Cull the light against the view frustum.
			if (BoundingFrustum::Cull(light_to_projection, light.GetAABB())) {
				return;
			}

			const auto  neg_d               = -transform.GetWorldAxisZ();
			const auto world_to_light       = transform.GetWorldToObjectMatrix();
			const auto light_to_lprojection = light.GetLightToProjectionMatrix();
			const auto world_to_lprojection = world_to_light * light_to_lprojection;

			// Create a directional light buffer.
			DirectionalLightBuffer buffer;
			buffer.m_neg_d = Direction3(XMStore< F32x3 >(neg_d));
			buffer.m_E     = light.GetIrradianceSpectrum();
			buffer.m_world_to_projection = XMMatrixTranspose(world_to_lprojection);

			if (light.UseShadows()) {
				// Create a spotlight camera.
				LightCameraInfo camera;
				camera.world_to_light      = world_to_light;
				camera.light_to_projection = light_to_lprojection;

				// Add directional light camera to the directional cameras.
				m_directional_light_cameras.push_back(std::move(camera));

				// Add directional light buffer to directional light buffers.
				sm_lights.push_back(std::move(buffer));
			}
			else {
				// Add directional light buffer to directional light buffers.
				lights.push_back(std::move(buffer));
			}
		});

		// Update the buffers for directional lights.
		m_directional_lights.UpdateData(m_device_context, lights);
		m_sm_directional_lights.UpdateData(m_device_context, sm_lights);
	}

	void XM_CALLCONV LBufferPass
		::ProcessOmniLights(const World& world, 
							FXMMATRIX world_to_projection) {
		
		AlignedVector< OmniLightBuffer > lights;
		lights.reserve(m_omni_lights.size());

		AlignedVector< ShadowMappedOmniLightBuffer > sm_lights;
		sm_lights.reserve(m_sm_omni_lights.size());
		m_omni_light_cameras.clear();

		// Process the omni lights.
		world.ForEach< OmniLight >([this, &lights, &sm_lights, world_to_projection]
		(const OmniLight& light) {
			
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

			const auto& transform           = light.GetOwner()->GetTransform();
			const auto  light_to_world      = transform.GetObjectToWorldMatrix();
			const auto  light_to_projection = light_to_world * world_to_projection;

			// Cull the light against the view frustum.
			if (BoundingFrustum::Cull(light_to_projection, light.GetBoundingSphere())) {
				return;
			}

			const auto p     = transform.GetWorldOrigin();
			const auto range = light.GetWorldRange();

			if (light.UseShadows()) {
				// Create six omni light cameras.
				const auto world_to_light       = transform.GetWorldToObjectMatrix();
				const auto light_to_lprojection = light.GetLightToProjectionMatrix();

				for (size_t i = 0; i < std::size(rotations); ++i) {
					LightCameraInfo camera;
					camera.world_to_light      = world_to_light * rotations[i];
					camera.light_to_projection = light_to_lprojection;

					// Add omni light camera to the omni light cameras.
					m_omni_light_cameras.push_back(std::move(camera));
				}

				// Create an omni light buffer.
				ShadowMappedOmniLightBuffer buffer;
				buffer.m_light.m_p             = Point3(XMStore< F32x3 >(p));
				buffer.m_light.m_inv_sqr_range = 1.0f / (range * range);
				buffer.m_light.m_I             = light.GetIntensitySpectrum();
				buffer.m_world_to_light        = XMMatrixTranspose(world_to_light);
				buffer.m_projection_values     = XMStore< F32x2 >(GetNDCZConstructionValues(
					                                              light_to_lprojection));

				// Add omni light buffer to omni light buffers.
				sm_lights.push_back(std::move(buffer));
			}
			else {
				// Create an omni light buffer.
				OmniLightBuffer buffer;
				buffer.m_p             = Point3(XMStore< F32x3 >(p));
				buffer.m_inv_sqr_range = 1.0f / (range * range);
				buffer.m_I             = light.GetIntensitySpectrum();

				// Add omni light buffer to omni light buffers.
				lights.push_back(std::move(buffer));
			}
		});

		// Update the buffers for omni lights.
		m_omni_lights.UpdateData(m_device_context, lights);
		m_sm_omni_lights.UpdateData(m_device_context, sm_lights);
	}

	void XM_CALLCONV LBufferPass
		::ProcessSpotLights(const World& world, 
							FXMMATRIX world_to_projection) {
		
		AlignedVector< SpotLightBuffer > lights;
		lights.reserve(m_spot_lights.size());

		AlignedVector< ShadowMappedSpotLightBuffer > sm_lights;
		sm_lights.reserve(m_sm_spot_lights.size());
		m_spot_light_cameras.clear();

		// Process the spotlights.
		world.ForEach< SpotLight >([this, &lights, &sm_lights, world_to_projection]
		(const SpotLight& light) {
			
			if (State::Active != light.GetState()) {
				return;
			}

			const auto& transform           = light.GetOwner()->GetTransform();
			const auto  light_to_world      = transform.GetObjectToWorldMatrix();
			const auto  light_to_projection = light_to_world * world_to_projection;

			// Cull the light against the view frustum.
			if (BoundingFrustum::Cull(light_to_projection, light.GetAABB())) {
				return;
			}

			const auto p     =  transform.GetWorldOrigin();
			const auto neg_d = -transform.GetWorldAxisZ();
			const auto range =  light.GetWorldRange();

			if (light.UseShadows()) {
				const auto world_to_light       = transform.GetWorldToObjectMatrix();
				const auto light_to_lprojection = light.GetLightToProjectionMatrix();
				const auto world_to_lprojection = world_to_light * light_to_lprojection;

				// Create a spotlight camera.
				LightCameraInfo camera;
				camera.world_to_light          = world_to_light;
				camera.light_to_projection     = light_to_lprojection;

				// Add spotlight camera to the spotlight cameras.
				m_spot_light_cameras.push_back(std::move(camera));

				// Create a spotlight buffer.
				ShadowMappedSpotLightBuffer buffer;
				buffer.m_light.m_p             = Point3(XMStore< F32x3 >(p));
				buffer.m_light.m_neg_d         = Direction3(XMStore< F32x3 >(neg_d));
				buffer.m_light.m_inv_sqr_range = 1.0f / (range * range);
				buffer.m_light.m_I             = light.GetIntensitySpectrum();
				buffer.m_light.m_cos_umbra     = light.GetEndAngularCutoff();
				buffer.m_light.m_cos_inv_range = 1.0f / light.GetRangeAngularCutoff();
				buffer.m_world_to_projection   = XMMatrixTranspose(world_to_lprojection);

				// Add spotlight buffer to spotlight buffers.
				sm_lights.push_back(std::move(buffer));
			}
			else {
				// Create an omni light buffer.
				SpotLightBuffer buffer;
				buffer.m_p             = Point3(XMStore< F32x3 >(p));
				buffer.m_neg_d         = Direction3(XMStore< F32x3 >(neg_d));
				buffer.m_inv_sqr_range = 1.0f / (range * range);
				buffer.m_I             = light.GetIntensitySpectrum();
				buffer.m_cos_umbra     = light.GetEndAngularCutoff();
				buffer.m_cos_inv_range = 1.0f / light.GetRangeAngularCutoff();

				// Add spotlight buffer to spotlight buffers.
				lights.push_back(std::move(buffer));
			}
		});

		// Update the buffers for spotlights.
		m_spot_lights.UpdateData(m_device_context, lights);
		m_sm_spot_lights.UpdateData(m_device_context, sm_lights);
	}

	void LBufferPass::SetupShadowMaps() {
		// Setup the shadow maps for the directional lights.
		{
			const auto nb_requested = m_sm_directional_lights.size();
			const auto nb_available = m_directional_sms->GetNumberOfShadowMaps();

			if (nb_available < nb_requested) {
				ComPtr< ID3D11Device > device;
				m_device_context.get().GetDevice(device.ReleaseAndGetAddressOf());
				m_directional_sms = MakeUnique< ShadowMapBuffer >(*device.Get(), 
																  nb_requested);
			}

			m_directional_sms->ClearDSVs(m_device_context);
		}

		// Setup the shadow maps for the omni lights.
		{
			const auto nb_requested = m_sm_omni_lights.size();
			const auto nb_available = m_omni_sms->GetNumberOfShadowCubeMaps();

			if (nb_available < nb_requested) {
				ComPtr< ID3D11Device > device;
				m_device_context.get().GetDevice(device.ReleaseAndGetAddressOf());
				m_omni_sms = MakeUnique< ShadowCubeMapBuffer >(*device.Get(), 
															   nb_requested);
			}

			m_omni_sms->ClearDSVs(m_device_context);
		}

		// Setup the shadow maps for the spotlights.
		{
			const auto nb_requested = m_sm_spot_lights.size();
			const auto nb_available = m_spot_sms->GetNumberOfShadowMaps();

			if (nb_available < nb_requested) {
				ComPtr< ID3D11Device > device;
				m_device_context.get().GetDevice(device.ReleaseAndGetAddressOf());
				m_spot_sms = MakeUnique< ShadowMapBuffer >(*device.Get(), 
														   nb_requested);
			}

			m_spot_sms->ClearDSVs(m_device_context);
		}
	}

	void XM_CALLCONV LBufferPass::RenderShadowMaps(const World& world) {
		// Bind the fixed state.
		m_depth_pass->BindFixedState();

		// Render the shadow maps of the directional lights.
		{
			// Bind the viewport.
			m_directional_sms->Bind(m_device_context);
			// Bind the rasterizer state.
			m_directional_sms->BindRasterizerState(m_device_context);

			size_t i = 0;
			for (const auto& camera : m_directional_light_cameras) {
				// Bind the DSV.
				m_directional_sms->BindDSV(m_device_context, i++);

				// Perform the depth pass.
				m_depth_pass->RenderOccluders(world, 
											  camera.world_to_light, 
											  camera.light_to_projection);
			}
		}

		// Render the shadow maps of the omni lights.
		{
			// Bind the viewport.
			m_omni_sms->Bind(m_device_context);
			// Bind the rasterizer state.
			m_omni_sms->BindRasterizerState(m_device_context);

			size_t i = 0;
			for (const auto& camera : m_omni_light_cameras) {
				// Bind the DSV.
				m_omni_sms->BindDSV(m_device_context, i++);

				// Perform the depth pass.
				m_depth_pass->RenderOccluders(world,
											  camera.world_to_light,
											  camera.light_to_projection);
			}
		}

		// Render the shadow maps of the spotlights.
		{
			// Bind the viewport.
			m_spot_sms->Bind(m_device_context);
			// Bind the rasterizer state.
			m_spot_sms->BindRasterizerState(m_device_context);

			size_t i = 0;
			for (const auto& camera : m_spot_light_cameras) {
				// Bind the DSV.
				m_spot_sms->BindDSV(m_device_context, i++);

				// Perform the depth pass.
				m_depth_pass->RenderOccluders(world,
											  camera.world_to_light,
											  camera.light_to_projection);
			}
		}
	}
}