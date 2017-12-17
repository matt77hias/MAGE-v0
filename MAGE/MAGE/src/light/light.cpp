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

#define MAGE_DEFAULT_BASE_COLOR 1.0f

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Light::Light() noexcept
		: Component(), 
		m_base_color(SRGB(MAGE_DEFAULT_BASE_COLOR)),
		m_aabb(AABB::Maximum()),
		m_bs(BS::Maximum()) {}

	Light::Light(const Light &light) noexcept = default;
	
	Light::Light(Light &&light) noexcept = default;

	Light::~Light() = default;

	Light &Light::operator=(const Light &light) noexcept = default;

	Light &Light::operator=(Light &&light) noexcept = default;
}