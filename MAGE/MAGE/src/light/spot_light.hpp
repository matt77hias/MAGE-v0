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
	class SpotLight final : public Light {

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
		 Returns the distance at which intensity falloff starts of this spotlight.

		 @return		The distance at which intensity falloff starts of this spotlight.
		 */
		float GetStartDistanceFalloff() const noexcept {
			return m_distance_falloff_start;
		}
		
		/**
		 Sets the distance at which intensity falloff starts of this spotlight
		 to the given value.

		 @param[in]		distance_falloff_start
						The distance at which intensity falloff starts.
		 */
		void SetStartDistanceFalloff(float distance_falloff_start) noexcept {
			m_distance_falloff_start = distance_falloff_start;
		}
		
		/**
		 Returns the distance at which intensity falloff ends of this spotlight.

		 @return		The distance at which intensity falloff ends of this spotlight.
		 */
		float GetEndDistanceFalloff() const noexcept {
			return m_distance_falloff_end;
		}
		
		/**
		 Sets the distance at which intensity falloff ends of this spotlight
		 to the given value.

		 @param[in]		distance_falloff_end
						The distance at which intensity falloff ends.
		 */
		void SetEndDistanceFalloff(float distance_falloff_end) noexcept {
			m_distance_falloff_end = distance_falloff_end;
		}
		
		/**
		 Sets the distance at which intensity falloff starts and ends of this spotlight
		 to the given values.

		 @param[in]		distance_falloff_start
						The distance at which intensity falloff starts.
		 @param[in]		distance_falloff_end
						The distance at which intensity falloff ends.
		 */
		void SetDistanceFalloff(float distance_falloff_start, float distance_falloff_end) noexcept {
			SetStartDistanceFalloff(distance_falloff_start);
			SetEndDistanceFalloff(distance_falloff_end);
		}

		/**
		 Returns the distance range where intensity falloff occurs of this spotlight.

		 @return		The distance range where intensity falloff occurs of this spotlight.
						@a GetEndDistanceFalloff() - @a GetStartDistanceFalloff()
		 */
		float GetRangeDistanceFalloff() const noexcept {
			return m_distance_falloff_end - m_distance_falloff_start;
		}

		/**
		 Returns the cosine of the penumbra angle of this spotlight.

		 @return		The cosine of the penumbra angle of this spotlight.
		 */
		float GetStartAngularCutoff() const noexcept {
			return m_cos_penumbra;
		}
		
		/**
		 Sets the cosine of the penumbra angle of this spotlight
		 to the given value.

		 @param[in]		cos_penumbra
						The cosine of the penumbra angle.
		 */
		void SetStartAngularCutoff(float cos_penumbra) noexcept {
			m_cos_penumbra = cos_penumbra;
		}
		
		/**
		 Returns the cosine of the umbra angle of this spotlight.

		 @return		The cosine of the umbra angle of this spotlight.
		 */
		float GetEndAngularCutoff() const noexcept {
			return m_cos_umbra;
		}
		
		/**
		 Sets the cosine of the umbra angle of this spotlight
		 to the given value.

		 @param[in]		cos_umbra
						The cosine of the umbra angle.
		 */
		void SetEndAngularCutoff(float cos_umbra) noexcept {
			m_cos_umbra = cos_umbra;
		}
		
		/**
		 Sets the cosine of the penumbra and umbra angles of this spotlight
		 to the given values.

		 @param[in]		cos_penumbra
						The cosine of the penumbra angle.
		 @param[in]		cos_umbra
						The cosine of the umbra angle.
		 */
		void SetAngularCutoff(float cos_penumbra, float cos_umbra) noexcept {
			SetStartAngularCutoff(cos_penumbra);
			SetEndAngularCutoff(cos_umbra);
		}

		/**
		 Returns the cosine range where intensity falloff occurs of this spotlight.

		 @return		The cosine range where intensity falloff occurs of this spotlight.
						@a GetStartAngularCutoff() - @a GetEndAngularCutoff()
		 */
		float GetRangeAngularCutoff() const noexcept {
			return m_cos_penumbra - m_cos_umbra;
		}

		/**
		 Returns the penumbra angle (in radians) of this spotlight.

		 @return		The penumbra angle (in radians) of this spotlight.
		 */
		float GetPenumbraAngle() const noexcept {
			return acos(m_cos_penumbra);
		}

		/**
		 Sets the penumbra angle (in radians) of this spotlight
		 to the given value (in radians).

		 @param[in]		penumbra
						The penumbra angle (in radians).
		 */
		void SetPenumbraAngle(float penumbra) noexcept {
			m_cos_penumbra = cos(penumbra);
		}

		/**
		 Returns the umbra angle (in radians) of this spotlight.

		 @return		The umbra angle (in radians) of this spotlight.
		 */
		float GetUmbraAngle() const noexcept {
			return acos(m_cos_umbra);
		}

		/**
		 Sets the umbra angle (in radians) of this spotlight
		 to the given value.

		 @param[in]		umbra
						The umbra angle (in radians).
		 */
		void SetUmbraAngle(float umbra) noexcept {
			m_cos_umbra = cos(umbra);
		}

		/**
		 Sets the penumbra and umbra angles (in radians) of this spotlight
		 to the given values.

		 @param[in]		penumbra
						The penumbra angle (in radians).
		 @param[in]		umbra
						The umbra angle (in radians).
		 */
		void SetPenumbraAndUmbraAngles(float penumbra, float umbra) noexcept {
			SetPenumbraAngle(penumbra);
			SetUmbraAngle(umbra);
		}

		/**
		 Returns the exponent property of this spotlight.

		 @return		The exponent property of this spotlight.
		 */
		float GetExponentProperty() const noexcept {
			return m_exponent_property;
		}
		
		/**
		 Sets the exponent property of this spotlight
		 to the given value.

		 @param[in]		exponent_property
						The exponent property.
		 */
		void SetExponentProperty(float exponent_property) noexcept {
			m_exponent_property = exponent_property;
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