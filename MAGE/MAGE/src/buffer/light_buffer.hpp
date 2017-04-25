#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\allocation.hpp"
#include "math\math.hpp"

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

	__declspec(align(16)) struct OmniLightBuffer final : public AlignedData< OmniLightBuffer > {

	public:

		OmniLightBuffer() 
			: p(0.0f, 0.0f, 0.0f, 0.0f), I(0.0f, 0.0f, 0.0f),
			distance_falloff_start(0.0f), distance_falloff_end(0.0f),
			padding{0} {}
		OmniLightBuffer(const OmniLightBuffer &buffer) = default;
		OmniLightBuffer(OmniLightBuffer &&buffer) = default;
		~OmniLightBuffer() = default;
		OmniLightBuffer &operator=(const OmniLightBuffer &buffer) = default;
		OmniLightBuffer &operator=(OmniLightBuffer &&buffer) = default;

		XMFLOAT4  p;
		XMFLOAT3  I;
		float     distance_falloff_start;
		float     distance_falloff_end;
		uint32_t  padding[3];
	};

	static_assert(sizeof(OmniLightBuffer) == 48, "CPU/GPU struct mismatch");

	__declspec(align(16)) struct SpotLightBuffer final : public AlignedData< SpotLightBuffer > {

	public:

		SpotLightBuffer()
			: p(0.0f, 0.0f, 0.0f, 0.0f), I(0.0f, 0.0f, 0.0f),
			exponent_property(0.0f), d(0.0f, 0.0f, 0.0f),
			distance_falloff_start(0.0f), distance_falloff_end(0.0f),
			cos_penumbra(0.0f), cos_umbra(0.0f), padding(0) {}
		SpotLightBuffer(const SpotLightBuffer &buffer) = default;
		SpotLightBuffer(SpotLightBuffer &&buffer) = default;
		~SpotLightBuffer() = default;
		SpotLightBuffer &operator=(const SpotLightBuffer &buffer) = default;
		SpotLightBuffer &operator=(SpotLightBuffer &&buffer) = default;

		XMFLOAT4 p;
		XMFLOAT3 I;
		float    exponent_property;
		XMFLOAT3 d;
		float    distance_falloff_start;
		float    distance_falloff_end;
		float    cos_penumbra;
		float    cos_umbra;
		uint32_t padding;
	};

	static_assert(sizeof(SpotLightBuffer) == 64, "CPU/GPU struct mismatch");
}