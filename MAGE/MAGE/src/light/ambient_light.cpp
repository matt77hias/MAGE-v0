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

	AmbientLight::AmbientLight(const AmbientLight &light) = default;
	
	AmbientLight::AmbientLight(AmbientLight &&light) = default;
	
	AmbientLight::~AmbientLight() = default;

	AmbientLight &AmbientLight::operator=(const AmbientLight &light) = default;
	
	AmbientLight &AmbientLight::operator=(AmbientLight &&light) = default;

	SharedPtr< Light > AmbientLight::CloneImplementation() const {
		return SharedPtr< AmbientLight >(new AmbientLight(*this));
	}
}