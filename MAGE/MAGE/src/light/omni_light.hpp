#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class OmniLight : public Light {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit OmniLight(const RGBSpectrum &intensity = RGBSpectrum(1.0f, 1.0f, 1.0f));
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

		virtual SharedPtr< Light > CloneImplementation() const override;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		float m_distance_falloff_start;
		float m_distance_falloff_end;
	};
}