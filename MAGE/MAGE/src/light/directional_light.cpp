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

#define MAGE_DEFAULT_IRRADIANCE 1.0f
#define MAGE_DEFAULT_BASE_COLOR 1.0f

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	DirectionalLight::DirectionalLight() noexcept
		: Component(),
		m_shadows(false), 
		m_irradiance(MAGE_DEFAULT_IRRADIANCE),
		m_base_color(SRGB(MAGE_DEFAULT_BASE_COLOR)) {}

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