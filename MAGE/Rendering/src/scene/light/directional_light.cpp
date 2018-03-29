//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\light\directional_light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	DirectionalLight::DirectionalLight() noexcept
		: Component(),
		m_shadows(false), 
		m_base_color(SRGB(1.0f)), 
		m_irradiance(1.0f) {}

	DirectionalLight::DirectionalLight(
		const DirectionalLight& light) noexcept = default;
	
	DirectionalLight::DirectionalLight(
		DirectionalLight&& light) noexcept = default;
	
	DirectionalLight::~DirectionalLight() = default;

	DirectionalLight& DirectionalLight
		::operator=(const DirectionalLight& light) noexcept = default;

	DirectionalLight& DirectionalLight
		::operator=(DirectionalLight&& light) noexcept = default;
}