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

	Light::Light(const RGBSpectrum &intensity)
		: m_intensity(intensity), 
		m_aabb(
			Point3(-INFINITY, -INFINITY, -INFINITY), 
			Point3( INFINITY,  INFINITY,  INFINITY)), 
		m_bs(Point3(), INFINITY) {}

	Light::Light(RGBSpectrum &&intensity)
		: m_intensity(std::move(intensity)), m_aabb(), m_bs() {}

	Light::Light(const Light &light) = default;
	
	Light::Light(Light &&light) = default;

	Light::~Light() = default;

	Light &Light::operator=(const Light &light) = default;
	
	Light &Light::operator=(Light &&light) = default;
}