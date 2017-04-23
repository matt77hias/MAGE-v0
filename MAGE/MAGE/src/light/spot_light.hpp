#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\light.hpp"
#include "memory\allocation.hpp"

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

	__declspec(align(16)) struct SpotLightBuffer final : public AlignedData< SpotLightBuffer > {

	public:

		SpotLightBuffer() = default;
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

	class SpotLight : public Light {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit SpotLight(const string name, const RGBSpectrum &intensity)
			: Light(name, intensity),
			m_distance_falloff_start(0.0f), m_distance_falloff_end(1.0f),
			m_cos_penumbra(0.96592583f), m_cos_umbra(0.86602540f),
			m_exponent_property(1.0f) {}
		SpotLight(const SpotLight &light) = default;
		SpotLight(SpotLight &&light) = default;
		virtual ~SpotLight() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		SpotLight &operator=(const SpotLight &light) = delete;
		SpotLight &operator=(SpotLight &&light) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual SpotLight *Clone() const {
			return new SpotLight(*this);
		}

		const SpotLightBuffer GetBuffer(const XMMATRIX &world_to_view) const {
			SpotLightBuffer buffer;

			XMStoreFloat4(&buffer.p, GetViewLightPosition(world_to_view));
			buffer.I                      = GetIntensity();
			buffer.exponent_property      = m_exponent_property;
			XMStoreFloat3(&buffer.d, GetViewLightDirection(world_to_view));
			buffer.distance_falloff_start = m_distance_falloff_start;
			buffer.distance_falloff_end   = m_distance_falloff_end;
			buffer.cos_penumbra           = m_cos_penumbra;
			buffer.cos_umbra              = m_cos_umbra;
			return buffer;
		}

		float GetStartDistanceFalloff() const {
			return m_distance_falloff_start;
		}
		SpotLight &SetStartDistanceFalloff(float distance_falloff_start) {
			m_distance_falloff_start = distance_falloff_start;
			return (*this);
		}
		float GetEndDistanceFalloff() const {
			return m_distance_falloff_end;
		}
		SpotLight &SetEndDistanceFalloff(float distance_falloff_end) {
			m_distance_falloff_end = distance_falloff_end;
			return (*this);
		}
		SpotLight &SetDistanceFalloff(float distance_falloff_start, float distance_falloff_end) {
			SetStartDistanceFalloff(distance_falloff_start);
			SetEndDistanceFalloff(distance_falloff_end);
			return (*this);
		}

		float GetStartAngualCutoff() const {
			return m_cos_penumbra;
		}
		SpotLight &SetStartAngualCutoff(float cos_penumbra) {
			m_cos_penumbra = cos_penumbra;
			return (*this);
		}
		float GetEndAngualCutoff() const {
			return m_cos_umbra;
		}
		SpotLight &SetEndAngualCutoff(float cos_umbra) {
			m_cos_umbra = cos_umbra;
			return (*this);
		}
		SpotLight &SetAngualCutoff(float cos_penumbra, float cos_umbra) {
			SetStartAngualCutoff(cos_penumbra);
			SetEndAngualCutoff(cos_umbra);
			return (*this);
		}

		float GetExponentProperty() const {
			return m_exponent_property;
		}
		SpotLight &SetExponentProperty(float exponent_property) {
			m_exponent_property = exponent_property;
			return (*this);
		}

	private:

		float m_exponent_property;
		float m_distance_falloff_start;
		float m_distance_falloff_end;
		float m_cos_penumbra;
		float m_cos_umbra;
	};
}