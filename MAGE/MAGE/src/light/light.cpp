//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Light::Light() noexcept
		: m_base_color(SRGB(1.0f)),
		m_aabb(AABB::Maximum()),
		m_bs(BS::Maximum()) {}

	Light::Light(const Light &light) noexcept = default;
	
	Light::Light(Light &&light) noexcept = default;

	Light::~Light() = default;

	Light &Light::operator=(const Light &light) noexcept = default;
	
	Light &Light::operator=(Light &&light) noexcept = default;
}