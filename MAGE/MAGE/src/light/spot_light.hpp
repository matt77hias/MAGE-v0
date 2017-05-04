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

	/**
	 A class of spotlights.
	 */
	class SpotLight : public Light {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a spotlight.

		 @param[in]		intensity
						The RGB intensity.
		 */
		explicit SpotLight(const RGBSpectrum &intensity = RGBSpectrum(1.0f, 1.0f, 1.0f));
		
		/**
		 Constructs a spotlight from the given spotlight.

		 @param[in]		light
						A reference to the spotlight to copy.
		 */
		SpotLight(const SpotLight &light);

		/**
		 Constructs a spotlight by moving the given spotlight.

		 @param[in]		light
						A reference to the spotlight to move.
		 */
		SpotLight(SpotLight &&light);

		/**
		 Destructs this spotlight.
		 */
		virtual ~SpotLight();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given spotlight to this spotlight.

		 @param[in]		light
						A reference to the spotlight to copy.
		 @return		A reference to the copy of the given spotlight
						(i.e. this spotlight).
		 */
		SpotLight &operator=(const SpotLight &light);

		/**
		 Moves the given spotlight to this spotlight.

		 @param[in]		light
						A reference to the spotlight to move.
		 @return		A reference to the moved spotlight
						(i.e. this spotlight).
		 */
		SpotLight &operator=(SpotLight &&light);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this spotlight.

		 @return		A pointer to the clone of this spotlight.
		 */
		UniquePtr< SpotLight > Clone() const {
			return static_pointer_cast< SpotLight >(CloneImplementation());
		}

		/**
		 Returns the start of the distance falloff of this spotlight.

		 @return		The start of the distance falloff of this spotlight.
		 */
		float GetStartDistanceFalloff() const {
			return m_distance_falloff_start;
		}
		
		/**
		 Sets the start of the distance falloff of this spotlight
		 to the given value.

		 @param[in]		distance_falloff_start
						The start of the distance falloff.
		 @return		A reference to this spotlight.
		 */
		SpotLight &SetStartDistanceFalloff(float distance_falloff_start) {
			m_distance_falloff_start = distance_falloff_start;
			return (*this);
		}
		
		/**
		 Returns the end of the distance falloff of this spotlight.

		 @return		The end of the distance falloff of this spotlight.
		 */
		float GetEndDistanceFalloff() const {
			return m_distance_falloff_end;
		}
		
		/**
		 Sets the end of the distance falloff of this spotlight
		 to the given value.

		 @param[in]		distance_falloff_end
						The end of the distance falloff.
		 @return		A reference to this spotlight.
		 */
		SpotLight &SetEndDistanceFalloff(float distance_falloff_end) {
			m_distance_falloff_end = distance_falloff_end;
			return (*this);
		}
		
		/**
		 Sets the start and end of the distance falloff of this spotlight
		 to the given values.

		 @param[in]		distance_falloff_start
						The start of the distance falloff.
		 @param[in]		distance_falloff_end
						The end of the distance falloff.
		 @return		A reference to this spotlight.
		 */
		SpotLight &SetDistanceFalloff(float distance_falloff_start, float distance_falloff_end) {
			SetStartDistanceFalloff(distance_falloff_start);
			SetEndDistanceFalloff(distance_falloff_end);
			return (*this);
		}

		/**
		 Returns cosine of the penumbra angle of this spotlight.

		 @return		The cosine of the penumbra angle of this spotlight.
		 */
		float GetStartAngularCutoff() const {
			return m_cos_penumbra;
		}
		
		/**
		 Sets the cosine of the penumbra angle of this spotlight
		 to the given value.

		 @param[in]		cos_penumbra
						The cosine of the penumbra angle.
		 @return		A reference to this spotlight.
		 */
		SpotLight &SetStartAngularCutoff(float cos_penumbra) {
			m_cos_penumbra = cos_penumbra;
			return (*this);
		}
		
		/**
		 Returns cosine of the umbra angle of this spotlight.

		 @return		The cosine of the umbra angle of this spotlight.
		 */
		float GetEndAngularCutoff() const {
			return m_cos_umbra;
		}
		
		/**
		 Sets the cosine of the umbra angle of this spotlight
		 to the given value.

		 @param[in]		cos_umbra
						The cosine of the umbra angle.
		 @return		A reference to this spotlight.
		 */
		SpotLight &SetEndAngularCutoff(float cos_umbra) {
			m_cos_umbra = cos_umbra;
			return (*this);
		}
		
		/**
		 Sets the cosine of the penumbra and umbra angles of this spotlight
		 to the given values.

		 @param[in]		cos_penumbra
						The cosine of the penumbra angle.
		 @param[in]		cos_umbra
						The cosine of the umbra angle.
		 @return		A reference to this spotlight.
		 */
		SpotLight &SetAngularCutoff(float cos_penumbra, float cos_umbra) {
			SetStartAngularCutoff(cos_penumbra);
			SetEndAngularCutoff(cos_umbra);
			return (*this);
		}

		/**
		 Returns the penumbra angle (in radians) of this spotlight.

		 @return		The penumbra angle (in radians) of this spotlight.
		 */
		float GetPenumbraAngle() const {
			return acos(m_cos_penumbra);
		}

		/**
		 Sets the penumbra angle (in radians) of this spotlight
		 to the given value (in radians).

		 @param[in]		penumbra
						The penumbra angle (in radians).
		 @return		A reference to this spotlight.
		 */
		SpotLight &SetPenumbraAngle(float penumbra) {
			m_cos_penumbra = cos(penumbra);
			return (*this);
		}

		/**
		 Returns the umbra angle (in radians) of this spotlight.

		 @return		The umbra angle (in radians) of this spotlight.
		 */
		float GetUmbraAngle() const {
			return acos(m_cos_umbra);
		}

		/**
		 Sets the umbra angle (in radians) of this spotlight
		 to the given value.

		 @param[in]		umbra
						The umbra angle (in radians).
		 @return		A reference to this spotlight.
		 */
		SpotLight &SetUmbraAngle(float umbra) {
			m_cos_umbra = cos(umbra);
			return (*this);
		}

		/**
		 Sets the penumbra and umbra angles (in radians) of this spotlight
		 to the given values.

		 @param[in]		penumbra
						The penumbra angle (in radians).
		 @param[in]		umbra
						The umbra angle (in radians).
		 @return		A reference to this spotlight.
		 */
		SpotLight &SetPenumbraAndUmbraAngles(float penumbra, float umbra) {
			SetPenumbraAngle(penumbra);
			SetUmbraAngle(umbra);
			return (*this);
		}

		/**
		 Returns the exponent property of this spotlight.

		 @return		The exponent property of this spotlight.
		 */
		float GetExponentProperty() const {
			return m_exponent_property;
		}
		
		/**
		 Sets the exponent property of this spotlight
		 to the given value.

		 @param[in]		exponent_property
						The exponent property.
		 @return		A reference to this spotlight.
		 */
		SpotLight &SetExponentProperty(float exponent_property) {
			m_exponent_property = exponent_property;
			return (*this);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this spotlight.

		 @return		A pointer to the clone of this spotlight.
		 */
		virtual UniquePtr< Light > CloneImplementation() const override;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The exponent property of this spotlight.
		 */
		float m_exponent_property;

		/**
		 The start of the distance falloff of this spotlight.
		 */
		float m_distance_falloff_start;

		/**
		 The end of the distance falloff of this spotlight.
		 */
		float m_distance_falloff_end;

		/**
		 The cosine of the penumbra angle of this spotlight.
		 */
		float m_cos_penumbra;

		/**
		 The cosine of the umbra angle of this spotlight.
		 */
		float m_cos_umbra;
	};
}