//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\directional_light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	DirectionalLight::DirectionalLight()
		: Light(), 
		m_radiance(1.0f),
		m_shadows(false) {}

	DirectionalLight::DirectionalLight(
		const DirectionalLight &light) = default;
	
	DirectionalLight::DirectionalLight(
		DirectionalLight &&light) = default;
	
	DirectionalLight::~DirectionalLight() = default;

	DirectionalLight &DirectionalLight::operator=(
		const DirectionalLight &light) = default;
	
	DirectionalLight &DirectionalLight::operator=(
		DirectionalLight &&light) = default;

	UniquePtr< Light > DirectionalLight::CloneImplementation() const {
		return MakeUnique< DirectionalLight >(*this);
	}
}