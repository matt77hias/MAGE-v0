#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\spectrum.hpp"
#include "math\bounding_volume.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of lights.
	 */
	class Light {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		/**
		 Destructs this light.
		 */
		virtual ~Light();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given light to this light.

		 @param[in]		light
						A reference to the light to copy.
		 @return		A reference to the copy of the given light (i.e. this 
						light).
		 */
		Light &operator=(const Light &light);

		/**
		 Moves the given light to this light.

		 @param[in]		light
						A reference to the light to move.
		 @return		A reference to the moved light (i.e. this light).
		 */
		Light &operator=(Light &&light);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this light.

		 @return		A pointer to the clone of this light.
		 */
		UniquePtr< Light > Clone() const {
			return static_pointer_cast< Light >(CloneImplementation());
		}

		/**
		 Returns the intensity of this light.

		 @return		The intensity of this light.
		 */
		const RGBSpectrum GetIntensity() const noexcept {
			return m_intensity;
		}

		/**
		 Sets the intensity of this light to the given intensity.

		 @param[in]		intensity
						A reference to the intensity.
		 */
		void SetIntensity(const RGBSpectrum &intensity) noexcept {
			m_intensity = intensity;
		}

		/**
		 Sets the intensity of this light to the given intensity.

		 @param[in]		intensity
						A reference to the intensity.
		 */
		void SetIntensity(RGBSpectrum &&intensity) noexcept {
			m_intensity = std::move(intensity);
		}

		/**
		Returns the AABB of this light.

		@return		A reference to the AABB of this light.
		*/
		const AABB &GetAABB() const noexcept {
			return m_aabb;
		}

		/**
		Returns the BS of this light.

		@return		A reference to the BS of this light.
		*/
		const BS &GetBS() const noexcept {
			return m_bs;
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a light.

		 @param[in]		intensity
						A reference to the RGB intensity.
		 */
		explicit Light(const RGBSpectrum &intensity);

		/**
		 Constructs a light.

		 @param[in]		intensity
						A reference to the RGB intensity.
		 */
		explicit Light(RGBSpectrum &&intensity);

		/**
		 Constructs a light from the given light.

		 @param[in]		light
						A reference to the light to copy.
		 */
		Light(const Light &light);

		/**
		 Constructs a light by moving the given light.

		 @param[in]		light
						A reference to the light to move.
		 */
		Light(Light &&light);

		/**
		 Updates the bounding volumes of this omni light.

		 @param[in]		aabb
						A reference to the AABB.
		 @param[in]		bs
						A reference to the BS.
		 */
		void SetBoundingVolumes(const AABB &aabb, const BS &bs) noexcept {
			m_aabb = aabb;
			m_bs   = bs;
		}

		/**
		 Updates the bounding volumes of this omni light.

		 @param[in]		aabb
						A reference to the AABB.
		 @param[in]		bs
						A reference to the BS.
		 */
		void SetBoundingVolumes(AABB &&aabb, BS &&bs) noexcept {
			m_aabb = std::move(aabb);
			m_bs   = std::move(bs);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this light.

		 @return		A pointer to the clone of this light.
		 */
		virtual UniquePtr< Light > CloneImplementation() const = 0;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The intensity of this light.
		 */
		RGBSpectrum m_intensity;

		/**
		 The AABB of this light.
		 */
		AABB m_aabb;

		/**
		 The BS of this light.
		 */
		BS m_bs;
	};
}