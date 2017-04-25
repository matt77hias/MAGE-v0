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

	class Light {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		virtual ~Light() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		Light &operator=(const Light &light) = delete;
		Light &operator=(Light &&light) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this light.

		 @return		A pointer to the clone of this light.
		 */
		SharedPtr< Light > Clone() {
			return std::static_pointer_cast< Light >(CloneImplementation());
		}

		const RGBSpectrum GetIntensity() const {
			return m_intensity;
		}
		void SetIntensity(const RGBSpectrum &intensity) {
			m_intensity = intensity;
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		explicit Light(const RGBSpectrum &intensity)
			: m_intensity(intensity) {}
		Light(const Light &light) = default;
		Light(Light &&light) = default;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual SharedPtr< Light > CloneImplementation() const = 0;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The intensity of this light.
		 */
		RGBSpectrum m_intensity;
	};
}