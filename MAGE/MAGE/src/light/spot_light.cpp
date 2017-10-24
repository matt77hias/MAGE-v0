//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\spot_light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpotLight::SpotLight()
		: Light(),
		m_intensity(1.0f),
		m_range(1.0f),
		m_cos_penumbra(1.0f), 
		m_cos_umbra(0.707106781f),
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