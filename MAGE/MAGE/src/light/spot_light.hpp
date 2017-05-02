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

	class SpotLight : public Light {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit SpotLight(const RGBSpectrum &intensity = RGBSpectrum(1.0f, 1.0f, 1.0f));
		SpotLight(const SpotLight &light);
		SpotLight(SpotLight &&light);
		virtual ~SpotLight();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		SpotLight &operator=(const SpotLight &light);
		SpotLight &operator=(SpotLight &&light);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		SharedPtr< SpotLight > Clone() const {
			return std::static_pointer_cast< SpotLight >(CloneImplementation());
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

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual SharedPtr< Light > CloneImplementation() const override;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		float m_exponent_property;
		float m_distance_falloff_start;
		float m_distance_falloff_end;
		float m_cos_penumbra;
		float m_cos_umbra;
	};
}