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

	class DirectionalLight : public Light {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit DirectionalLight(const string name, const RGBSpectrum &intensity)
			: Light(name, intensity) {}
		DirectionalLight(const DirectionalLight &light) = default;
		DirectionalLight(DirectionalLight &&light) = default;
		virtual ~DirectionalLight() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		DirectionalLight &operator=(const DirectionalLight &light) = default;
		DirectionalLight &operator=(DirectionalLight &&light) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual DirectionalLight *Clone() const {
			return new DirectionalLight(*this);
		}
	};
}