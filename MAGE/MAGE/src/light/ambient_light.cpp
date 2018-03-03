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

#define MAGE_DEFAULT_RADIANCE   1.0f
#define MAGE_DEFAULT_BASE_COLOR 1.0f

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	AmbientLight::AmbientLight() noexcept
		: Component(),
		m_radiance(MAGE_DEFAULT_RADIANCE),
		m_base_color(SRGB(MAGE_DEFAULT_BASE_COLOR)) {}

	AmbientLight::AmbientLight(const AmbientLight& light) noexcept = default;
	
	AmbientLight::AmbientLight(AmbientLight&& light) noexcept = default;
	
	AmbientLight::~AmbientLight() = default;

	AmbientLight& AmbientLight
		::operator=(const AmbientLight& light) noexcept = default;

	AmbientLight& AmbientLight
		::operator=(AmbientLight&& light) noexcept = default;
}