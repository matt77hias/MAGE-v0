#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\pass_buffer.hpp"
#include "buffer\constant_buffer.hpp"
#include "buffer\structured_buffer.hpp"
#include "buffer\light_buffer.hpp"

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
			return m_directional_lights_buffer.size();
		}
		size_t GetNumberOfOmniLights() const noexcept {
			return m_omni_lights_buffer.size();
		}
		size_t GetNumberOfSpotLights() const noexcept {
			return m_spot_lights_buffer.size();
		}

		void Update(const PassBuffer *scene, 
			const CameraNode *node);
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

		ID3D11DeviceContext2 * const m_device_context;

		ConstantBuffer< LightBuffer > m_light_buffer;
		StructuredBuffer< DirectionalLightBuffer > m_directional_lights_buffer;
		StructuredBuffer< OmniLightBuffer > m_omni_lights_buffer;
		StructuredBuffer< SpotLightBuffer > m_spot_lights_buffer;
	};
}