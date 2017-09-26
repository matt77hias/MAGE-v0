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
		m_distance_falloff_start(0.0f), 
		m_distance_falloff_end(1.0f),
		m_cos_penumbra(1.0f), 
		m_cos_umbra(0.707106781f),
		m_exponent_property(1.0f), 
		m_shadows(false) {

		// Update the bounding volumes.
		UpdateBoundingVolumes();
	}

	SpotLight::SpotLight(const SpotLight &light) = default;
	
	SpotLight::SpotLight(SpotLight &&light) = default;
	
	SpotLight::~SpotLight() = default;

	SpotLight &SpotLight::operator=(const SpotLight &light) = default;
	
	SpotLight &SpotLight::operator=(SpotLight &&light) = default;

	UniquePtr< Light > SpotLight::CloneImplementation() const {
		return MakeUnique< SpotLight >(*this);
	}

	void SpotLight::UpdateBoundingVolumes() noexcept {
		const f32 a         = 1.0f / (m_cos_umbra * m_cos_umbra);
		const f32 tan_umbra = sqrt(a - 1.0f);
		const f32 rxy       = m_distance_falloff_end * tan_umbra;
		const f32 rz        = m_distance_falloff_end * 0.5f;
		const f32 r         = m_distance_falloff_end * sqrt(a - 0.75f);

		AABB aabb(Point3(-rxy, -rxy, 0.0f),
				  Point3( rxy,  rxy, m_distance_falloff_end));

		BS bs(Point3(0.0f, 0.0f, rz), r);

		SetBoundingVolumes(std::move(aabb), std::move(bs));
	}
}