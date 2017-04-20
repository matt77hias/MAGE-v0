#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "world\world_object.hpp"
#include "material\spectrum.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class Light : public WorldObject {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		virtual ~Light() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		Light &operator=(const Light &light) = default;
		Light &operator=(Light &&light) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual Light *Clone() const = 0;

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

		explicit Light(const string name, const RGBSpectrum &intensity)
			: WorldObject(name), m_intensity(intensity) {}
		Light(const Light &light) = default;
		Light(Light &&light) = default;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The intensity of this light.
		 */
		RGBSpectrum m_intensity;
	};
}