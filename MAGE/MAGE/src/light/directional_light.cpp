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

	DirectionalLight::DirectionalLight() noexcept
		: Light(), 
		m_radiance(1.0f),
		m_shadows(false) {}

	DirectionalLight::DirectionalLight(
		const DirectionalLight &light) noexcept = default;
	
	DirectionalLight::DirectionalLight(
		DirectionalLight &&light) noexcept = default;
	
	DirectionalLight::~DirectionalLight() = default;

	DirectionalLight &DirectionalLight::operator=(
		const DirectionalLight &light) noexcept = default;
	
	DirectionalLight &DirectionalLight::operator=(
		DirectionalLight &&light) noexcept = default;

	UniquePtr< Light > DirectionalLight::CloneImplementation() const {
		return MakeUnique< DirectionalLight >(*this);
	}
}