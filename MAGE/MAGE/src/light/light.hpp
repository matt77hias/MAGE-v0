#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "material\spectrum.hpp"

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
		 @return		A reference to the copy of the given light
						(i.e. this light).
		 */
		Light &operator=(const Light &light);

		/**
		 Moves the given light to this light.

		 @param[in]		light
						A reference to the light to move.
		 @return		A reference to the moved light
						(i.e. this light).
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
		const RGBSpectrum GetIntensity() const {
			return m_intensity;
		}

		/**
		 Sets the intensity of this light to the given intensity.

		 @param[in]		intensity
						A reference to the intensity.
		 */
		void SetIntensity(const RGBSpectrum &intensity) {
			m_intensity = intensity;
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a light.

		 @param[in]		intensity
						The RGB intensity.
		 */
		explicit Light(const RGBSpectrum &intensity);

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
	};
}