#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\omni_light.hpp"
#include "light\spot_light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	__declspec(align(16)) struct LightDataBuffer final : public AlignedData< LightDataBuffer > {

	public:

		LightDataBuffer() = default;
		LightDataBuffer(const LightDataBuffer &buffer) = default;
		LightDataBuffer(LightDataBuffer &&buffer) = default;
		~LightDataBuffer() = default;
		LightDataBuffer &operator=(const LightDataBuffer &buffer) = default;
		LightDataBuffer &operator=(LightDataBuffer &&buffer) = default;

		XMFLOAT3 Ia;
		uint32_t nb_omnilights;
		XMFLOAT3 Id;
		uint32_t nb_spotlights;
		XMFLOAT3 d;

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

		LightDataBuffer light_data;
		vector< OmniLightBuffer > omni_lights;
		vector< SpotLightBuffer > spot_lights;
	};
}