#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\component.hpp"
#include "spectrum\spectrum.hpp"
#include "geometry\bounding_volume.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	#pragma warning( push )
	#pragma warning( disable : 4324 ) // Added padding.

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
		SpotLight(const SpotLight& light) noexcept;

		/**
		 Constructs a spotlight by moving the given spotlight.

		 @param[in]		light
						A reference to the spotlight to move.
		 */
		SpotLight(SpotLight&& light) noexcept;

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
		SpotLight& operator=(const SpotLight& light) noexcept;

		/**
		 Moves the given spotlight to this spotlight.

		 @param[in]		light
						A reference to the spotlight to move.
		 @return		A reference to the moved spotlight (i.e. this 
						spotlight).
		 */
		SpotLight& operator=(SpotLight&& light) noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Lighting
		//---------------------------------------------------------------------

		/**
		 Returns the (linear) base color of this omni light.

		 @return		A reference to the sRGB base color of this omni light.
		 */
		[[nodiscard]]
		RGB& GetBaseColor() noexcept {
			return m_base_color;
		}

		/**
		 Returns the (linear) base color of this omni light.

		 @return		A reference to the sRGB base color of this omni light.
		 */
		[[nodiscard]]
		const RGB& GetBaseColor() const noexcept {
			return m_base_color;
		}

		/**
		 Returns the power of this spotlight.

		 @return		The power in watts of this spotlight.
		 */
		[[nodiscard]]
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
		[[nodiscard]]
		const RGB GetPowerSpectrum() const noexcept {
			const auto P = GetPower() * XMLoad(m_base_color);
			return RGB(XMStore< F32x3 >(P));
		}

		/**
		 Returns the radiant intensity of this spotlight.

		 @return		The radiant intensity in watts per steradians of this 
						spotlight.
		 */
		[[nodiscard]]
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
			m_intensity = std::abs(intensity);
		}

		/**
		 Returns the radiant intensity spectrum of this spotlight.

		 @return		The radiant intensity spectrum of this spotlight.
		 */
		[[nodiscard]]
		const RGB GetIntensitySpectrum() const noexcept {
			const auto I = GetIntensity() * XMLoad(m_base_color);
			return RGB(XMStore< F32x3 >(I));
		}

		//---------------------------------------------------------------------
		// Member Methods: Range
		//---------------------------------------------------------------------

		/**
		 Returns the AABB of this spotlight.

		 @return		A reference to the AABB of this spotlight.
		 */
		[[nodiscard]]
		const AABB& GetAABB() const noexcept {
			return m_aabb;
		}

		/**
		 Returns the BoundingSphere of this spotlight.

		 @return		A reference to the BoundingSphere of this spotlight.
		 */
		[[nodiscard]]
		const BoundingSphere& GetBoundingSphere() const noexcept {
			return m_sphere;
		}

		//---------------------------------------------------------------------
		// Member Methods: Attenuation
		//---------------------------------------------------------------------

		/**
		 Returns the range of this spotlight expressed in light space.

		 @return		The range of this spotlight expressed in light space.
		 */
		[[nodiscard]]
		F32 GetRange() const noexcept {
			return m_clipping_planes.m_y;
		}

		/**
		 Returns the range of this spotlight expressed in world space.

		 @return		The range of this spotlight expressed in world space.
		 @note			Non-uniform scaling is not supported for spotlights.
		 */
		[[nodiscard]]
		F32 GetWorldRange() const noexcept;

		/**
		 Sets the range of this spotlight to the given value expressed in light 
		 space.

		 @param[in]		range
						The range expressed in light space.
		 */
		void SetRange(F32 range) noexcept {
			m_clipping_planes.m_y = range;

			// Update the bounding volumes.
			UpdateBoundingVolumes();
		}

		/**
		 Returns the cosine of the penumbra angle of this spotlight.

		 @return		The cosine of the penumbra angle of this spotlight.
		 */
		[[nodiscard]]
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
		[[nodiscard]]
		F32 GetEndAngularCutoff() const noexcept {
			return m_cos_umbra;
		}
		
		/**
		 Sets the cosine of the umbra angle of this spotlight to the given 
		 value.

		 @param[in]		cos_umbra
						The cosine of the umbra angle.
		 */
		void SetEndAngularCutoff(F32 cos_umbra) noexcept {
			m_cos_umbra = std::max(0.001f, cos_umbra);

			// Update the bounding volumes.
			UpdateBoundingVolumes();
		}
		
		/**
		 Sets the cosine of the penumbra and umbra angles of this spotlight to 
		 the given values.

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
		[[nodiscard]]
		F32 GetRangeAngularCutoff() const noexcept {
			return std::max(0.001f, m_cos_penumbra - m_cos_umbra);
		}

		/**
		 Returns the penumbra angle (in radians) of this spotlight.

		 @return		The penumbra angle (in radians) of this spotlight.
		 */
		[[nodiscard]]
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
		[[nodiscard]]
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
		[[nodiscard]]
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
		 Returns the clipping planes of this spotlight expressed in light 
		 space.

		 @return		The clipping planes of this spotlight expressed in 
						light space.
		 */
		[[nodiscard]]
		const F32x2 GetClippingPlanes() const noexcept {
			return m_clipping_planes;
		}
		
		/**
		 Sets the clipping planes of this spotlight expressed in light space to 
		 the given clipping planes.

		 @param[in]		clipping_planes
						The clipping planes.
		 */
		void SetClippingPlanes(F32x2 clipping_planes) noexcept {
			m_clipping_planes = std::move(clipping_planes);
		}

		/**
		 Returns the (horizontal and vertical) field-of-view of this spotlight.

		 @return		The (horizontal and vertical) field-of-view of this 
						spotlight.
		 */
		[[nodiscard]]
		F32 GetFOV() const noexcept {
			return 2.0f * GetUmbraAngle();
		}

		/**
		 Returns the light-to-projection matrix of the light camera of this spot 
		 light.

		 @return		The light-to-projection matrix of the light camera of 
						this spot light.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV 
			GetLightToProjectionMatrix() const noexcept {

			#ifdef DISABLE_INVERTED_Z_BUFFER
			const auto near_plane = m_clipping_planes.m_x;
			const auto far_plane  = m_clipping_planes.m_y;
			#else  // DISABLE_INVERTED_Z_BUFFER
			const auto near_plane = m_clipping_planes.m_y;
			const auto far_plane  = m_clipping_planes.m_x;
			#endif // DISABLE_INVERTED_Z_BUFFER

			const auto fov = 2.0f * GetUmbraAngle();

			return XMMatrixPerspectiveFovLH(fov, 1.0f, near_plane, far_plane);
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
		 The BoundingSphere of this spotlight.
		 */
		BoundingSphere m_sphere;

		/**
		 The (linear) base color of this spotlight.
		 */
		RGB m_base_color;

		/**
		 The radiant intensity in watts per steradians of this spotlight.
		 */
		F32 m_intensity;

		/**
		 The clipping planes of this light expressed in light space.
		 */
		F32x2 m_clipping_planes;

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