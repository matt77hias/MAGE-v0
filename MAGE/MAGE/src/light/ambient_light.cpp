//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\ambient_light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	AmbientLight::AmbientLight(const RGBSpectrum &intensity)
		: Light(intensity) {}

	SharedPtr< Light > AmbientLight::CloneImplementation() const {
		return SharedPtr< AmbientLight >(new AmbientLight(*this));
	}
}