#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\light.hpp"
#include "camera\perspective_camera.hpp"
#include "logging\error.hpp"

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
		explicit SpotLight(const RGBSpectrum &intensity 
			= RGBSpectrum(1.0f, 1.0f, 1.0f));
		
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
		 @return		A reference to the copy of the given spotlight (i.e. 
						this spotlight).
		 */
		SpotLight &operator=(const SpotLight &light);

		/**
		 Moves the given spotlight to this spotlight.

		 @param[in]		light
						A reference to the spotlight to move.
		 @return		A reference to the moved spotlight (i.e. this 
						spotlight).
		 */
		SpotLight &operator=(SpotLight &&light);

		//---------------------------------------------------------------------
		// Member Methods: Lighting
		//---------------------------------------------------------------------

		/**
		 Clones this spotlight.

		 @return		A pointer to the clone of this spotlight.
		 */
		UniquePtr< SpotLight > Clone() const {
			return static_pointer_cast< SpotLight >(CloneImplementation());
		}

		/**
		 Returns the distance at which intensity falloff starts of this 
		 spotlight.

		 @return		The distance at which intensity falloff starts of 
						this spotlight.
		 */
		F32 GetStartDistanceFalloff() const noexcept {
			return m_distance_falloff_start;
		}
		
		/**
		 Sets the distance at which intensity falloff starts of this spotlight
		 to the given value.

		 @param[in]		distance_falloff_start
						The distance at which intensity falloff starts.
		 */
		void SetStartDistanceFalloff(F32 distance_falloff_start) noexcept {
			m_distance_falloff_start = distance_falloff_start;
		}
		
		/**
		 Returns the distance at which intensity falloff ends of this 
		 spotlight.

		 @return		The distance at which intensity falloff ends of this 
						spotlight.
		 */
		F32 GetEndDistanceFalloff() const noexcept {
			return m_distance_falloff_end;
		}
		
		/**
		 Sets the distance at which intensity falloff ends of this spotlight
		 to the given value.

		 @pre			@a distance_falloff_end > 0.
		 @param[in]		distance_falloff_end
						The distance at which intensity falloff ends.
		 */
		void SetEndDistanceFalloff(F32 distance_falloff_end) noexcept {
			Assert(distance_falloff_end);
			m_distance_falloff_end = distance_falloff_end;

			// Update the bounding volumes.
			UpdateBoundingVolumes();
		}
		
		/**
		 Sets the distance at which intensity falloff starts and ends of this 
		 spotlight to the given values.

		 @pre			@a distance_falloff_end > 0.
		 @param[in]		distance_falloff_start
						The distance at which intensity falloff starts.
		 @param[in]		distance_falloff_end
						The distance at which intensity falloff ends.
		 */
		void SetDistanceFalloff(
			F32 distance_falloff_start, F32 distance_falloff_end) noexcept {
			
			SetStartDistanceFalloff(distance_falloff_start);
			SetEndDistanceFalloff(distance_falloff_end);
		}
		
		/**
		 Returns the distance range where intensity falloff occurs of this 
		 spotlight.

		 @return		The distance range where intensity falloff occurs of 
						this spotlight.
						@a GetEndDistanceFalloff() - 
						@a GetStartDistanceFalloff().
		 */
		F32 GetRangeDistanceFalloff() const noexcept {
			return m_distance_falloff_end - m_distance_falloff_start;
		}
		
		/**
		 Sets the distance at which intensity falloff starts and the distance 
		 range where intensity falloff occurs of this spotlight to the given 
		 values.

		 @pre			@a distance_falloff_start + @a distance_falloff_range > 
							0.
		 @param[in]		distance_falloff_start
						The distance at which intensity falloff starts.
		 @param[in]		distance_falloff_range
						The distance range where intensity falloff occurs.
		 */
		void SetRangeDistanceFalloff(
			F32 distance_falloff_start, F32 distance_falloff_range) noexcept {
			
			SetDistanceFalloff(distance_falloff_start, 
				distance_falloff_start + distance_falloff_range);
		}

		/**
		 Returns the cosine of the penumbra angle of this spotlight.

		 @return		The cosine of the penumbra angle of this spotlight.
		 */
		F32 GetStartAngularCutoff() const noexcept {
			return m_cos_penumbra;
		}
		
		/**
		 Sets the cosine of the penumbra angle of this spotlight to the given 
		 value.

		 @param[in]		cos_penumbra
						The cosine of the penumbra angle.
		 */
		void SetStartAngularCutoff(F32 cos_penumbra) noexcept {
			m_cos_penumbra = cos_penumbra;
		}
		
		/**
		 Returns the cosine of the umbra angle of this spotlight.

		 @return		The cosine of the umbra angle of this spotlight.
		 */
		F32 GetEndAngularCutoff() const noexcept {
			return m_cos_umbra;
		}
		
		/**
		 Sets the cosine of the umbra angle of this spotlight to the given 
		 value.

		 @pre			@a cos_umbra > 0.
		 @param[in]		cos_umbra
						The cosine of the umbra angle.
		 */
		void SetEndAngularCutoff(F32 cos_umbra) noexcept {
			Assert(cos_umbra);
			m_cos_umbra = cos_umbra;

			// Update the bounding volumes.
			UpdateBoundingVolumes();
		}
		
		/**
		 Sets the cosine of the penumbra and umbra angles of this spotlight to 
		 the given values.

		 @pre			@a cos_umbra > 0.
		 @param[in]		cos_penumbra
						The cosine of the penumbra angle.
		 @param[in]		cos_umbra
						The cosine of the umbra angle.
		 */
		void SetAngularCutoff(F32 cos_penumbra, F32 cos_umbra) noexcept {
			SetStartAngularCutoff(cos_penumbra);
			SetEndAngularCutoff(cos_umbra);
		}
		
		/**
		 Returns the cosine range where intensity falloff occurs of this 
		 spotlight.

		 @return		The cosine range where intensity falloff occurs of this 
						spotlight. @a GetStartAngularCutoff() - 
						@a GetEndAngularCutoff().
		 */
		F32 GetRangeAngularCutoff() const noexcept {
			return m_cos_penumbra - m_cos_umbra;
		}

		/**
		 Returns the penumbra angle (in radians) of this spotlight.

		 @return		The penumbra angle (in radians) of this spotlight.
		 */
		F32 GetPenumbraAngle() const noexcept {
			return acos(m_cos_penumbra);
		}
		
		/**
		 Sets the penumbra angle (in radians) of this spotlight to the given 
		 value (in radians).

		 @param[in]		penumbra
						The penumbra angle (in radians).
		 */
		void SetPenumbraAngle(F32 penumbra) noexcept {
			SetStartAngularCutoff(cos(penumbra));
		}

		/**
		 Returns the umbra angle (in radians) of this spotlight.

		 @return		The umbra angle (in radians) of this spotlight.
		 */
		F32 GetUmbraAngle() const noexcept {
			return acos(m_cos_umbra);
		}
		
		/**
		 Sets the umbra angle (in radians) of this spotlight to the given 
		 value.

		 @pre			cos(@a umbra) > 0.
		 @param[in]		umbra
						The umbra angle (in radians).
		 */
		void SetUmbraAngle(F32 umbra) noexcept {
			SetEndAngularCutoff(cos(umbra));
		}
		
		/**
		 Sets the penumbra and umbra angles (in radians) of this spotlight to 
		 the given values.

		 @pre			cos(@a umbra) > 0.
		 @param[in]		penumbra
						The penumbra angle (in radians).
		 @param[in]		umbra
						The umbra angle (in radians).
		 */
		void SetPenumbraAndUmbraAngles(F32 penumbra, F32 umbra) noexcept {
			SetPenumbraAngle(penumbra);
			SetUmbraAngle(umbra);
		}
		
		/**
		 Returns the exponent property of this spotlight.

		 @return		The exponent property of this spotlight.
		 */
		F32 GetExponentProperty() const noexcept {
			return m_exponent_property;
		}
		
		/**
		 Sets the exponent property of this spotlight to the given value.

		 @param[in]		exponent_property
						The exponent property.
		 */
		void SetExponentProperty(F32 exponent_property) noexcept {
			m_exponent_property = exponent_property;
		}
		
		//---------------------------------------------------------------------
		// Member Methods: Shadowing
		//---------------------------------------------------------------------

		/**
		 Checks whether shadows should be used for this spotlight.

		 @return		@c true if shadows should be used for this spotlight. 
						@c false otherwise.
		 */
		bool UseShadows() const noexcept {
			return m_shadows;
		}

		/**
		 Enables shadows for this spotlight.
		 */
		void EnableShadows() noexcept {
			SetShadows(true);
		}

		/**
		 Dissables shadows for this spotlight.
		 */
		void DissableShadows() noexcept {
			SetShadows(false);
		}

		/**
		 Toggles shadows for this spotlight.
		 */
		void ToggleShadows() noexcept {
			SetShadows(!m_shadows);
		}
		
		/**
		 Sets shadows for this spotlight to the given value.

		 @param[in]		shadows	
						@c true if shadows should be used for this spotlight. 
						@c false otherwise.
		 */
		void SetShadows(bool shadows) noexcept {
			m_shadows = shadows;
		}
		
		/**
		 Returns the (horizontal and vertical) field-of-view of this spotlight.

		 @return		The (horizontal and vertical) field-of-view of this 
						spotlight.
		 */
		F32 GetFOV() const noexcept {
			return 2.0f * GetUmbraAngle();
		}

		/**
		 Returns the aspect ratio of this spotlight.

		 @return		The aspect ratio of this spotlight.
		 */
		F32 GetAspectRatio() const noexcept {
			return 1.0f;
		}

		/**
		 Returns the view-to-projection matrix of the light camera of this spot 
		 light.

		 @return		The view-to-projection matrix of the light camera of 
						this spot light.
		 */
		const XMMATRIX GetViewToProjectionMatrix() const noexcept {
			// Reversed-Z used for the depth buffer.
			return XMMatrixPerspectiveFovLH(
				GetFOV(),
				GetAspectRatio(),
				GetEndDistanceFalloff(),
				MAGE_DEFAULT_LIGHT_CAMERA_NEAR_Z);
		}

		/**
		 Returns the light camera of this spot light.

		 @return		The light camera of this spot light.
		 */
		const PerspectiveCamera GetLightCamera() const noexcept {
			return PerspectiveCamera(
				GetAspectRatio(),
				GetFOV(),
				MAGE_DEFAULT_LIGHT_CAMERA_NEAR_Z,
				GetEndDistanceFalloff());
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

		/**
		 Updates the bounding volumes of this spotlight.
		 */
		void UpdateBoundingVolumes() noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The start of the distance falloff of this spotlight.
		 */
		F32 m_distance_falloff_start;

		/**
		 The end of the distance falloff of this spotlight.
		 */
		F32 m_distance_falloff_end;

		/**
		 The cosine of the penumbra angle of this spotlight.
		 */
		F32 m_cos_penumbra;

		/**
		 The cosine of the umbra angle of this spotlight.
		 */
		F32 m_cos_umbra;

		/**
		 The exponent property of this spotlight.
		 */
		F32 m_exponent_property;

		/**
		 A flag indicating whether shadows should be calculated or not for 
		 this spotlight.
		 */
		bool m_shadows;
	};
}