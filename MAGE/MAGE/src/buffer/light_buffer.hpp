#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\allocation.hpp"
#include "material\spectrum.hpp"

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
			: m_Ia(), m_nb_omni_lights(0),
			m_Id(), m_nb_spot_lights(0),
			m_d(), m_padding(0) {}
		LightDataBuffer(const LightDataBuffer &buffer) = default;
		LightDataBuffer(LightDataBuffer &&buffer) = default;
		~LightDataBuffer() = default;
		LightDataBuffer &operator=(const LightDataBuffer &buffer) = default;
		LightDataBuffer &operator=(LightDataBuffer &&buffer) = default;

		RGBSpectrum m_Ia;
		uint32_t    m_nb_omni_lights;
		RGBSpectrum m_Id;
		uint32_t    m_nb_spot_lights;
		Direction3  m_d;
		uint32_t    m_padding;
	};

	static_assert(sizeof(LightDataBuffer) == 48, "CPU/GPU struct mismatch");

	__declspec(align(16)) struct OmniLightBuffer final : public AlignedData< OmniLightBuffer > {

	public:

		OmniLightBuffer() 
			: m_p(0.0f, 0.0f, 0.0f, 0.0f), m_I(),
			m_distance_falloff_start(0.0f), m_distance_falloff_end(0.0f),
			m_padding{0} {}
		OmniLightBuffer(const OmniLightBuffer &buffer) = default;
		OmniLightBuffer(OmniLightBuffer &&buffer) = default;
		~OmniLightBuffer() = default;
		OmniLightBuffer &operator=(const OmniLightBuffer &buffer) = default;
		OmniLightBuffer &operator=(OmniLightBuffer &&buffer) = default;

		XMFLOAT4     m_p;
		RGBSpectrum  m_I;
		float        m_distance_falloff_start;
		float        m_distance_falloff_end;
		uint32_t     m_padding[3];
	};

	static_assert(sizeof(OmniLightBuffer) == 48, "CPU/GPU struct mismatch");

	__declspec(align(16)) struct SpotLightBuffer final : public AlignedData< SpotLightBuffer > {

	public:

		SpotLightBuffer()
			: m_p(0.0f, 0.0f, 0.0f, 0.0f), m_I(),
			m_exponent_property(0.0f), m_d(),
			m_distance_falloff_start(0.0f), m_distance_falloff_end(0.0f),
			m_cos_penumbra(0.0f), m_cos_umbra(0.0f), m_padding(0) {}
		SpotLightBuffer(const SpotLightBuffer &buffer) = default;
		SpotLightBuffer(SpotLightBuffer &&buffer) = default;
		~SpotLightBuffer() = default;
		SpotLightBuffer &operator=(const SpotLightBuffer &buffer) = default;
		SpotLightBuffer &operator=(SpotLightBuffer &&buffer) = default;

		XMFLOAT4    m_p;
		RGBSpectrum m_I;
		float       m_exponent_property;
		Direction3  m_d;
		float       m_distance_falloff_start;
		float       m_distance_falloff_end;
		float       m_cos_penumbra;
		float       m_cos_umbra;
		uint32_t    m_padding;
	};

	static_assert(sizeof(SpotLightBuffer) == 64, "CPU/GPU struct mismatch");
}