//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\light\omni_light.hpp"
#include "scene\node.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	OmniLight::OmniLight() noexcept
		: Component(),
		m_shadows(false), 
		m_clipping_planes(0.1f, 1.0f),
		m_aabb(), 
		m_sphere(), 
		m_base_color(SRGB(1.0f)), 
		m_intensity(1.0f) {

		// Update the bounding volumes.
		UpdateBoundingVolumes();
	}

	OmniLight::OmniLight(const OmniLight& light) noexcept = default;
	
	OmniLight::OmniLight(OmniLight&& light) noexcept = default;
	
	OmniLight::~OmniLight() = default;

	OmniLight& OmniLight::operator=(const OmniLight& light) noexcept = default;

	OmniLight& OmniLight::operator=(OmniLight&& light) noexcept = default;
	
	[[nodiscard]]
	F32 OmniLight::GetWorldRange() const noexcept {
		Assert(HasOwner());

		const auto& transform = GetOwner()->GetTransform();
		return XMStore< F32 >(XMVector3Length(
			transform.TransformObjectToWorldPoint(
				XMVectorSet(0.0f, 0.0f, GetRange(), 1.0f))));

	}

	void OmniLight::UpdateBoundingVolumes() noexcept {
		const auto range = GetRange();

		m_aabb   = AABB(Point3(-range, -range, -range),
			            Point3( range,  range,  range));
		m_sphere = BoundingSphere(Point3(), range);
	}
}