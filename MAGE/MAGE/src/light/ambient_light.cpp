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

	AmbientLight::AmbientLight() noexcept
		: Light(), 
		m_radiance(MAGE_DEFAULT_RADIANCE) {}

	AmbientLight::AmbientLight(const AmbientLight &light) noexcept = default;
	
	AmbientLight::AmbientLight(AmbientLight &&light) noexcept = default;
	
	AmbientLight::~AmbientLight() = default;

	AmbientLight &AmbientLight
		::operator=(const AmbientLight &light) noexcept = default;

	AmbientLight &AmbientLight
		::operator=(AmbientLight &&light) noexcept = default;
}