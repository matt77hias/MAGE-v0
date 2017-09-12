#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\pass_buffer.hpp"
#include "buffer\constant_buffer.hpp"
#include "buffer\structured_buffer.hpp"
#include "buffer\light_buffer.hpp"
#include "buffer\shadow_map_buffer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct LBuffer final {

	public:

		LBuffer();
		LBuffer(const LBuffer &buffer) = delete;
		LBuffer(LBuffer &&buffer) = default;
		~LBuffer() = default;

		LBuffer &operator=(const LBuffer &buffer) = delete;
		LBuffer &operator=(LBuffer &&buffer) = delete;

		size_t GetNumberOfDirectionalLights() const noexcept {
			return m_directional_lights.size();
		}
		size_t GetNumberOfOmniLights() const noexcept {
			return m_omni_lights.size();
		}
		size_t GetNumberOfSpotLights() const noexcept {
			return m_spot_lights.size();
		}

		void Update(const PassBuffer *scene, 
			const CameraNode *node);
		
		void ClearGraphicsPipeline() const noexcept;
		void ClearComputePipeline() const noexcept;
		void BindToGraphicsPipeline() const noexcept;
		void BindToComputePipeline() const noexcept;

	private:

		void ProcessLightsData(const PassBuffer *scene) noexcept;

		void XM_CALLCONV ProcessLights(
			const vector< const DirectionalLightNode * > &lights,
			FXMMATRIX world_to_view) noexcept;
		void XM_CALLCONV ProcessLights(
			const vector< const OmniLightNode * > &lights,
			FXMMATRIX world_to_projection,
			FXMMATRIX world_to_view) noexcept;
		void XM_CALLCONV ProcessLights(
			const vector< const SpotLightNode * > &lights,
			FXMMATRIX world_to_projection,
			FXMMATRIX world_to_view) noexcept;

		void XM_CALLCONV ProcessLightsWithShadowMapping(
			const vector< const DirectionalLightNode * > &lights,
			FXMMATRIX world_to_view);
		void XM_CALLCONV ProcessLightsWithShadowMapping(
			const vector< const OmniLightNode * > &lights,
			FXMMATRIX world_to_projection,
			FXMMATRIX world_to_view);
		void XM_CALLCONV ProcessLightsWithShadowMapping(
			const vector< const SpotLightNode * > &lights,
			FXMMATRIX world_to_projection,
			FXMMATRIX world_to_view);

		void SetupDirectionalShadowMaps();
		void SetupOmniShadowMaps();
		void SetupSpotShadowMaps();



		void XM_CALLCONV ProcessModels(
			const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection,
			FXMMATRIX world_to_view) noexcept;

		ID3D11DeviceContext2 * const m_device_context;

		ConstantBuffer< LightBuffer > m_light_buffer;
		StructuredBuffer< DirectionalLightBuffer > m_directional_lights;
		StructuredBuffer< OmniLightBuffer > m_omni_lights;
		StructuredBuffer< SpotLightBuffer > m_spot_lights;

		StructuredBuffer< DirectionalLightWithShadowMappingBuffer > 
			m_sm_directional_lights;
		StructuredBuffer< OmniLightWithShadowMappingBuffer > 
			m_sm_omni_lights;
		StructuredBuffer< SpotLightWithShadowMappingBuffer > 
			m_sm_spot_lights;

		UniquePtr< ShadowMapBuffer > m_directional_sms;
		UniquePtr< ShadowCubeMapBuffer > m_omni_sms;
		UniquePtr< ShadowMapBuffer > m_spot_sms;
	};
}