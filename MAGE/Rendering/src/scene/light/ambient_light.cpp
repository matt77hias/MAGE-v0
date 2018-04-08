//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\light\ambient_light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	AmbientLight::AmbientLight() noexcept
		: Component(),
		m_base_color(RGB(1.0f)), 
		m_radiance(1.0f) {}

	AmbientLight::AmbientLight(const AmbientLight& light) noexcept = default;
	
	AmbientLight::AmbientLight(AmbientLight&& light) noexcept = default;
	
	AmbientLight::~AmbientLight() = default;

	AmbientLight& AmbientLight
		::operator=(const AmbientLight& light) noexcept = default;

	AmbientLight& AmbientLight
		::operator=(AmbientLight&& light) noexcept = default;
}