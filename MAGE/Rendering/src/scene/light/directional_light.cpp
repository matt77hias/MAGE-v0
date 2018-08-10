//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\light\directional_light.hpp"
#include "scene\node.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	DirectionalLight::DirectionalLight() noexcept
		: Component(),
		m_shadows(false), 
		m_clipping_planes(0.1f, 1.0f), 
		m_size(1.0f, 1.0f), 
		m_aabb(), 
		m_base_color(RGB(1.0f)), 
		m_irradiance(1.0f) {

		// Update the bounding volumes.
		UpdateBoundingVolumes();
	}

	DirectionalLight::DirectionalLight(
		const DirectionalLight& light) noexcept = default;
	
	DirectionalLight::DirectionalLight(
		DirectionalLight&& light) noexcept = default;
	
	DirectionalLight::~DirectionalLight() = default;

	DirectionalLight& DirectionalLight
		::operator=(const DirectionalLight& light) noexcept = default;

	DirectionalLight& DirectionalLight
		::operator=(DirectionalLight&& light) noexcept = default;

	[[nodiscard]]
	F32 DirectionalLight::GetWorldRange() const noexcept {
		Assert(HasOwner());

		const auto& transform = GetOwner()->GetTransform();
		const auto p1 = transform.GetWorldOrigin();
		const auto p2 = transform.TransformObjectToWorldPoint(
			                      { 0.0f, 0.0f, GetRange(), 1.0f });
		return XMStore< F32 >(XMVector3Length(p1 - p2));
	}

	void DirectionalLight::UpdateBoundingVolumes() noexcept {
		const auto range  = GetRange();
		const auto [x, y] = m_size;

		m_aabb   = AABB(Point3(-0.5f * x, -0.5f * y, 0.0f), 
						Point3( 0.5f * x,  0.5f * y, range));
	}
}