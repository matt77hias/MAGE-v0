#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\pass\depth_pass.hpp"
#include "rendering\buffer\structured_buffer.hpp"
#include "rendering\buffer\light_buffer.hpp"
#include "rendering\buffer\shadow_map_buffer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class LBufferPass final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a LBuffer pass.

		 @param[in]		device
						A reference to the device.
		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		state_manager
						A reference to the state manager.
		 @param[in]		resource_manager
						A reference to the resource manager.
		 */
		explicit LBufferPass(ID3D11Device& device, 
							 ID3D11DeviceContext& device_context, 
							 StateManager& state_manager, 
							 ResourceManager& resource_manager);
		LBufferPass(const LBufferPass& buffer) = delete;
		LBufferPass(LBufferPass&& buffer) noexcept;
		~LBufferPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		LBufferPass& operator=(const LBufferPass& buffer) = delete;
		LBufferPass& operator=(LBufferPass&& buffer) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		size_t GetNumberOfDirectionalLights() const noexcept {
			return m_directional_lights.size();
		}
		size_t GetNumberOfOmniLights() const noexcept {
			return m_omni_lights.size();
		}
		size_t GetNumberOfSpotLights() const noexcept {
			return m_spot_lights.size();
		}
		size_t GetNumberOfShadowMappedDirectionalLights() const noexcept {
			return m_sm_directional_lights.size();
		}
		size_t GetNumberOfShadowMappedOmniLights() const noexcept {
			return m_sm_omni_lights.size();
		}
		size_t GetNumberOfShadowMappedSpotLights() const noexcept {
			return m_sm_spot_lights.size();
		}

		void XM_CALLCONV Render(const Scene& scene,
			                    FXMMATRIX world_to_projection,
								const Fog& fog);
		
	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void UnbindShadowMaps() const noexcept;
		void BindLBuffer() const noexcept;

		void ProcessLightsData(const Scene& scene, const Fog& fog);

		void XM_CALLCONV ProcessDirectionalLights(const Scene& scene);
		void XM_CALLCONV ProcessOmniLights(const Scene& scene, 
										   FXMMATRIX world_to_projection);
		void XM_CALLCONV ProcessSpotLights(const Scene& scene, 
										   FXMMATRIX world_to_projection);

		void SetupShadowMaps();

		void XM_CALLCONV RenderShadowMaps(const Scene& scene);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to the device context of this LBuffer pass.
		 */
		std::reference_wrapper< ID3D11DeviceContext > m_device_context;

		ConstantBuffer< LightBuffer > m_light_buffer;
		StructuredBuffer< DirectionalLightBuffer > m_directional_lights;
		StructuredBuffer< OmniLightBuffer > m_omni_lights;
		StructuredBuffer< SpotLightBuffer > m_spot_lights;
		StructuredBuffer< ShadowMappedDirectionalLightBuffer > m_sm_directional_lights;
		StructuredBuffer< ShadowMappedOmniLightBuffer > m_sm_omni_lights;
		StructuredBuffer< ShadowMappedSpotLightBuffer > m_sm_spot_lights;

		UniquePtr< ShadowMapBuffer > m_directional_sms;
		UniquePtr< ShadowCubeMapBuffer > m_omni_sms;
		UniquePtr< ShadowMapBuffer > m_spot_sms;

		struct alignas(16) LightCameraInfo final {
			XMMATRIX world_to_light;
			XMMATRIX light_to_projection;
		};

		AlignedVector< LightCameraInfo > m_directional_light_cameras;
		AlignedVector< LightCameraInfo > m_omni_light_cameras;
		AlignedVector< LightCameraInfo > m_spot_light_cameras;

		UniquePtr< DepthPass > m_depth_pass;
	};
}