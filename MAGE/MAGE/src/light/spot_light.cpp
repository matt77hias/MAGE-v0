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

#define MAGE_DEFAULT_INTENSITY    1.0f
#define MAGE_DEFAULT_RANGE        1.0f
#define MAGE_DEFAULT_COS_PENUMBRA 1.0f
#define MAGE_DEFAULT_COS_UMBRA    0.707106781f

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpotLight::SpotLight() noexcept
		: Light(),
		m_intensity(MAGE_DEFAULT_INTENSITY),
		m_range(MAGE_DEFAULT_RANGE),
		m_cos_penumbra(MAGE_DEFAULT_COS_PENUMBRA),
		m_cos_umbra(MAGE_DEFAULT_COS_UMBRA),
		m_shadows(false) {

		// Update the bounding volumes.
		UpdateBoundingVolumes();
	}

	SpotLight::SpotLight(const SpotLight &light) noexcept = default;
	
	SpotLight::SpotLight(SpotLight &&light) noexcept = default;
	
	SpotLight::~SpotLight() = default;

	SpotLight &SpotLight::operator=(const SpotLight &light) noexcept = default;

	SpotLight &SpotLight::operator=(SpotLight &&light) noexcept = default;

	void SpotLight::UpdateBoundingVolumes() noexcept {
		const F32 a         = 1.0f / (m_cos_umbra * m_cos_umbra);
		const F32 tan_umbra = sqrt(a - 1.0f);
		const F32 rxy       = m_range * tan_umbra;
		const F32 rz        = m_range * 0.5f;
		const F32 r         = sqrt(rxy * rxy + rz * rz);

		AABB aabb(Point3(-rxy, -rxy, 0.0f),
				  Point3( rxy,  rxy, m_range));

		BS bs(Point3(0.0f, 0.0f, rz), r);

		SetBoundingVolumes(std::move(aabb), std::move(bs));
	}
}