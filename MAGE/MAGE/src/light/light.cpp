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

	Light::Light()
		: m_base_color(RGBSpectrum(1.0f)),
		m_aabb(MaximumAABB()),
		m_bs(MaximumBS()) {}

	Light::Light(const Light &light) = default;
	
	Light::Light(Light &&light) = default;

	Light::~Light() = default;

	Light &Light::operator=(const Light &light) = default;
	
	Light &Light::operator=(Light &&light) = default;
}