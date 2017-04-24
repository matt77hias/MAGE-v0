#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\light.hpp"

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

	__declspec(align(16)) struct OmniLightBuffer final : public AlignedData< OmniLightBuffer > {

	public:

		OmniLightBuffer() = default;
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

	class OmniLight : public Light {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit OmniLight(const string name, const RGBSpectrum &intensity)
			: Light(name, intensity), 
			m_distance_falloff_start(0.0f), m_distance_falloff_end(1.0f) {}
		OmniLight(const OmniLight &light) = default;
		OmniLight(OmniLight &&light) = default;
		virtual ~OmniLight() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		OmniLight &operator=(const OmniLight &light) = delete;
		OmniLight &operator=(OmniLight &&light) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		SharedPtr< OmniLight > Clone() const {
			return std::static_pointer_cast< OmniLight >(CloneImplementation());
		}
		
		const OmniLightBuffer GetBuffer(const XMMATRIX &world_to_view) const {
			OmniLightBuffer buffer;
			XMStoreFloat4(&buffer.p, GetViewLightPosition(world_to_view));
			buffer.I                      = GetIntensity();
			buffer.distance_falloff_start = m_distance_falloff_start;
			buffer.distance_falloff_end   = m_distance_falloff_end;
			return buffer;
		}

		float GetStartDistanceFalloff() const {
			return m_distance_falloff_start;
		}
		OmniLight &SetStartDistanceFalloff(float distance_falloff_start) {
			m_distance_falloff_start = distance_falloff_start;
			return (*this);
		}
		float GetEndDistanceFalloff() const {
			return m_distance_falloff_end;
		}
		OmniLight &SetEndDistanceFalloff(float distance_falloff_end) {
			m_distance_falloff_end = distance_falloff_end;
			return (*this);
		}
		OmniLight &SetDistanceFalloff(float distance_falloff_start, float distance_falloff_end) {
			SetStartDistanceFalloff(distance_falloff_start);
			SetEndDistanceFalloff(distance_falloff_end);
			return (*this);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual SharedPtr< WorldObject > CloneImplementation() const override {
			return SharedPtr< OmniLight >(new OmniLight(*this));
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		float m_distance_falloff_start;
		float m_distance_falloff_end;
	};
}