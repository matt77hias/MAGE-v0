#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\component.hpp"
#include "material\spectrum.hpp"
#include "math\geometry\bounding_volume.hpp"
#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <algorithm>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	#pragma warning( push )
	#pragma warning( disable : 4324)

	/**
	 A class of spotlights.
	 */
	class alignas(16) SpotLight final : public Component {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a spotlight.
		 */
		SpotLight() noexcept;
		
		/**
		 Constructs a spotlight from the given spotlight.

		 @param[in]		light
						A reference to the spotlight to copy.
		 */
		SpotLight(const SpotLight &light) noexcept;

		/**
		 Constructs a spotlight by moving the given spotlight.

		 @param[in]		light
						A reference to the spotlight to move.
		 */
		SpotLight(SpotLight &&light) noexcept;

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
		SpotLight &operator=(const SpotLight &light) noexcept;

		/**
		 Moves the given spotlight to this spotlight.

		 @param[in]		light
						A reference to the spotlight to move.
		 @return		A reference to the moved spotlight (i.e. this 
						spotlight).
		 */
		SpotLight &operator=(SpotLight &&light) noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Lighting
		//---------------------------------------------------------------------

		/**
		 Returns the sRGB base color of this omni light.

		 @return		A reference to the sRGB base color of this omni light.
		 */
		SRGB &GetBaseColor() noexcept {
			return m_base_color;
		}

		/**
		 Returns the sRGB base color of this omni light.

		 @return		A reference to the sRGB base color of this omni light.
		 */
		const SRGB &GetBaseColor() const noexcept {
			return m_base_color;
		}

		/**
		 Returns the power of this spotlight.

		 @return		The power in watts of this spotlight.
		 */
		F32 GetPower() const noexcept {
			// [Frostbite]
			return GetIntensity() * XM_1DIVPI;
		}

		/**
		 Sets the power of this omni light to the given radiance.
		 
		 @param[in]		power
						The power in watts.
		 */
		void SetPower(F32 power) noexcept {
			// [Frostbite]
			SetIntensity(power * XM_PI);
		}

		/**
		 Returns the power spectrum of this spotlight.

		 @return		The power spectrum of this spotlight.
		 */
		const RGB GetPowerSpectrum() const noexcept {
			const XMVECTOR P_v = GetPower()
				               * SRGBtoRGB(XMLoadFloat3(&m_base_color));
			RGB P;
			XMStoreFloat3(&P, P_v);
			return P;
		}

		/**
		 Returns the radiant intensity of this spotlight.

		 @return		The radiant intensity in watts per steradians of this 
						spotlight.
		 */
		F32 GetIntensity() const noexcept {
			return m_intensity;
		}

		/**
		 Sets the radiant intensity of this spotlight to the given radial 
		 intensity.
		 
		 @param[in]		intensity
						The radiant intensity in watts per steradians.
		 */
		void SetIntensity(F32 intensity) noexcept {
			m_intensity = intensity;
		}

		/**
		 Returns the radiant intensity spectrum of this spotlight.

		 @return		The radiant intensity spectrum of this spotlight.
		 */
		const RGB GetIntensitySpectrum() const noexcept {
			const XMVECTOR I_v = GetIntensity()
				               * SRGBtoRGB(XMLoadFloat3(&m_base_color));
			RGB I;
			XMStoreFloat3(&I, I_v);
			return I;
		}

		//---------------------------------------------------------------------
		// Member Methods: Range
		//---------------------------------------------------------------------

		/**
		 Returns the AABB of this spotlight.

		 @return		A reference to the AABB of this spotlight.
		 */
		const AABB &GetAABB() const noexcept {
			return m_aabb;
		}

		/**
		 Returns the BS of this spotlight.

		 @return		A reference to the BS of this spotlight.
		 */
		const BS &GetBS() const noexcept {
			return m_bs;
		}

		//---------------------------------------------------------------------
		// Member Methods: Attenuation
		//---------------------------------------------------------------------

		/**
		 Returns the range of this spotlight.

		 @return		The range of this spotlight.
		 */
		F32 GetRange() const noexcept {
			return m_range;
		}

		/**
		 Sets the range of this spotlight to the given value.

		 @pre			@a range must be greater than 0.
		 @param[in]		range
						The range.
		 */
		void SetRange(F32 range) noexcept {
			Assert(range > 0.0f);
			m_range = range;

			// Update the bounding volumes.
			UpdateBoundingVolumes();
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

		 @pre			@a cos_umbra must be greater than 0.
		 @param[in]		cos_umbra
						The cosine of the umbra angle.
		 */
		void SetEndAngularCutoff(F32 cos_umbra) noexcept {
			Assert(cos_umbra > 0.0f);
			m_cos_umbra = cos_umbra;

			// Update the bounding volumes.
			UpdateBoundingVolumes();
		}
		
		/**
		 Sets the cosine of the penumbra and umbra angles of this spotlight to 
		 the given values.

		 @pre			@a cos_umbra must be greater than 0.
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
		 Returns the cosine range where intensity attenuation occurs of this 
		 spotlight.

		 @return		The cosine range where intensity attenuation occurs of 
						this spotlight. @a GetStartAngularCutoff() - 
						@a GetEndAngularCutoff().
		 */
		F32 GetRangeAngularCutoff() const noexcept {
			return std::max(0.001f, m_cos_penumbra - m_cos_umbra);
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

		 @pre			cos(@a umbra) must be greater than 0.
		 @param[in]		umbra
						The umbra angle (in radians).
		 */
		void SetUmbraAngle(F32 umbra) noexcept {
			SetEndAngularCutoff(cos(umbra));
		}
		
		/**
		 Sets the penumbra and umbra angles (in radians) of this spotlight to 
		 the given values.

		 @pre			cos(@a umbra) must be greater than 0.
		 @param[in]		penumbra
						The penumbra angle (in radians).
		 @param[in]		umbra
						The umbra angle (in radians).
		 */
		void SetPenumbraAndUmbraAngles(F32 penumbra, F32 umbra) noexcept {
			SetPenumbraAngle(penumbra);
			SetUmbraAngle(umbra);
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
		 Returns the view-to-projection matrix of the light camera of this spot 
		 light.

		 @return		The view-to-projection matrix of the light camera of 
						this spot light.
		 */
		const XMMATRIX XM_CALLCONV GetViewToProjectionMatrix() const noexcept {
			static const F32 near_plane = 0.1f;
			const F32 fov = 2.0f * GetUmbraAngle();

			#ifdef DISSABLE_INVERTED_Z_BUFFER
			return XMMatrixPerspectiveFovLH(fov, 1.0f, near_plane, m_range);
			#else  // DISSABLE_INVERTED_Z_BUFFER
			return XMMatrixPerspectiveFovLH(fov, 1.0f, m_range, near_plane);
			#endif // DISSABLE_INVERTED_Z_BUFFER
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Updates the bounding volumes of this spotlight.
		 */
		void UpdateBoundingVolumes() noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A flag indicating whether shadows should be calculated or not for 
		 this spotlight.
		 */
		bool m_shadows;

		/**
		 The AABB of this spotlight.
		 */
		AABB m_aabb;

		/**
		 The BS of this spotlight.
		 */
		BS m_bs;

		/**
		 The sRGB base color of this spotlight.
		 */
		SRGB m_base_color;

		/**
		 The radiant intensity in watts per steradians of this spotlight.
		 */
		F32 m_intensity;

		/**
		 The range of this spotlight.
		 */
		F32 m_range;

		/**
		 The cosine of the penumbra angle of this spotlight.
		 */
		F32 m_cos_penumbra;

		/**
		 The cosine of the umbra angle of this spotlight.
		 */
		F32 m_cos_umbra;
	};

	#pragma warning( pop )
}