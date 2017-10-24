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

	AmbientLight::AmbientLight() 
		: Light(), m_radiance(1.0f) {}

	AmbientLight::AmbientLight(const AmbientLight &light) = default;
	
	AmbientLight::AmbientLight(AmbientLight &&light) = default;
	
	AmbientLight::~AmbientLight() = default;

	AmbientLight &AmbientLight::operator=(const AmbientLight &light) = default;
	
	AmbientLight &AmbientLight::operator=(AmbientLight &&light) = default;

	UniquePtr< Light > AmbientLight::CloneImplementation() const {
		return MakeUnique< AmbientLight >(*this);
	}
}