//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\spot_light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <algorithm>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpotLight::SpotLight(const RGBSpectrum &intensity)
		: Light(intensity),
		m_distance_falloff_start(0.0f), m_distance_falloff_end(1.0f),
		m_cos_penumbra(0.96592583f), m_cos_umbra(0.86602540f),
		m_exponent_property(1.0f) {}

	SpotLight::SpotLight(const SpotLight &light) = default;
	
	SpotLight::SpotLight(SpotLight &&light) = default;
	
	SpotLight::~SpotLight() = default;

	SpotLight &SpotLight::operator=(const SpotLight &light) = default;
	
	SpotLight &SpotLight::operator=(SpotLight &&light) = default;

	UniquePtr< Light > SpotLight::CloneImplementation() const {
		return MakeUnique< SpotLight >(*this);
	}

	const AABB SpotLight::GetAABB() const noexcept {
		const float tan_umbra = sqrt(1.0f / (m_cos_umbra * m_cos_umbra) - 1.0f);
		const float rxy       = m_distance_falloff_end * tan_umbra;
		return AABB(Point3(-rxy, -rxy, 0.0f),
					Point3( rxy,  rxy, m_distance_falloff_end));
	}

	const BS SpotLight::GetBS() const noexcept {
		const float rz        = 0.5f * m_distance_falloff_end;
		const float tan_umbra = sqrt(1.0f / (m_cos_umbra * m_cos_umbra) - 1.0f);
		const float r         = rz * std::max(1.0f, 2.0f * tan_umbra);
		return BS(Point3(0.0f, 0.0f, rz), r);
	}
}