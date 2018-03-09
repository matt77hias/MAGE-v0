//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\light\spot_light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	SpotLight::SpotLight() noexcept
		: Component(),
		m_shadows(false), 
		m_aabb(), 
		m_sphere(), 
		m_base_color(SRGB(1.0f)),
		m_intensity(1.0f),
		m_range(1.0f),
		m_cos_penumbra(1.0f),
		m_cos_umbra(0.707106781f) {

		// Update the bounding volumes.
		UpdateBoundingVolumes();
	}

	SpotLight::SpotLight(const SpotLight& light) noexcept = default;
	
	SpotLight::SpotLight(SpotLight&& light) noexcept = default;
	
	SpotLight::~SpotLight() = default;

	SpotLight& SpotLight::operator=(const SpotLight& light) noexcept = default;

	SpotLight& SpotLight::operator=(SpotLight&& light) noexcept = default;

	void SpotLight::UpdateBoundingVolumes() noexcept {
		const auto a         = 1.0f / (m_cos_umbra * m_cos_umbra);
		const auto tan_umbra = sqrt(a - 1.0f);
		const auto rxy       = m_range * tan_umbra;
		const auto rz        = m_range * 0.5f;
		const auto r         = sqrt(rxy * rxy + rz * rz);

		m_aabb   = AABB(Point3(-rxy, -rxy, 0.0f),
				        Point3( rxy,  rxy, m_range));

		m_sphere = BoundingSphere(Point3(0.0f, 0.0f, rz), r);
	}
}