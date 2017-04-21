#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\omni_light.hpp"
#include "light\spot_light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	__declspec(align(16)) struct LightDataBuffer final : public AlignedData< LightDataBuffer > {

	public:

		LightDataBuffer()
			: Ia(0.0f, 0.0f, 0.0f), nb_omni_lights(0), 
			Id(0.0f, 0.0f, 0.0f), nb_spot_lights(0), 
			d(0.0f, 0.0f, 0.0f), padding(0) {}
		LightDataBuffer(const LightDataBuffer &buffer) = default;
		LightDataBuffer(LightDataBuffer &&buffer) = default;
		~LightDataBuffer() = default;
		LightDataBuffer &operator=(const LightDataBuffer &buffer) = default;
		LightDataBuffer &operator=(LightDataBuffer &&buffer) = default;

		XMFLOAT3 Ia;
		uint32_t nb_omni_lights;
		XMFLOAT3 Id;
		uint32_t nb_spot_lights;
		XMFLOAT3 d;
		uint32_t padding;
	};

	static_assert(sizeof(LightDataBuffer) == 48, "CPU/GPU struct mismatch");

	struct LightBuffer final {

	public:

		LightBuffer() = default;
		LightBuffer(const LightBuffer &buffer) = default;
		LightBuffer(LightBuffer &&buffer) = default;
		~LightBuffer() = default;
		LightBuffer &operator=(const LightBuffer &buffer) = default;
		LightBuffer &operator=(LightBuffer &&buffer) = default;

		void UpdateSizes() {
			light_data.nb_omni_lights = static_cast< uint32_t >(omni_lights.size());
			light_data.nb_spot_lights = static_cast< uint32_t >(spot_lights.size());
		}

		LightDataBuffer light_data;
		vector< OmniLightBuffer > omni_lights;
		vector< SpotLightBuffer > spot_lights;
	};
}