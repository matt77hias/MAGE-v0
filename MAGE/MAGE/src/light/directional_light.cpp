//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_RADIANCE 1.0f

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	DirectionalLight::DirectionalLight() noexcept
		: Light(), 
		m_radiance(MAGE_DEFAULT_RADIANCE),
		m_shadows(false) {}

	DirectionalLight::DirectionalLight(
		const DirectionalLight &light) noexcept = default;
	
	DirectionalLight::DirectionalLight(
		DirectionalLight &&light) noexcept = default;
	
	DirectionalLight::~DirectionalLight() = default;

	DirectionalLight &DirectionalLight
		::operator=(const DirectionalLight &light) noexcept = default;

	DirectionalLight &DirectionalLight
		::operator=(DirectionalLight &&light) noexcept = default;
}