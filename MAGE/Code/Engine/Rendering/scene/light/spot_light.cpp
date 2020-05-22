//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\light\spot_light.hpp"
#include "scene\node.hpp"

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
		m_base_color(RGB(1.0f)),
		m_intensity(1.0f),
		m_clipping_planes(0.1f, 1.0f),
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

	[[nodiscard]]
	F32 SpotLight::GetWorldRange() const noexcept {
		Assert(HasOwner());

		const auto& transform = GetOwner()->GetTransform();
		const auto p1 = transform.GetWorldOrigin();
		const auto p2 = transform.TransformObjectToWorldPoint(
			                      { 0.0f, 0.0f, GetRange(), 1.0f });
		return XMStore< F32 >(XMVector3Length(p1 - p2));
	}

	void SpotLight::UpdateBoundingVolumes() noexcept {
		const auto range     = GetRange();
		const auto a         = 1.0f / (m_cos_umbra * m_cos_umbra);
		const auto tan_umbra = std::sqrt(a - 1.0f);
		const auto rxy       = range * tan_umbra;
		const auto rz        = range * 0.5f;
		const auto r         = std::sqrt(rxy * rxy + rz * rz);

		m_aabb   = AABB(Point3(-rxy, -rxy, 0.0f),
				        Point3( rxy,  rxy, range));

		m_sphere = BoundingSphere(Point3(0.0f, 0.0f, rz), r);
	}
}