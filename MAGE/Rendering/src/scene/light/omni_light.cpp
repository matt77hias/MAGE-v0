//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\node.hpp"
#include "scene\light\omni_light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	OmniLight::OmniLight() noexcept
		: Component(),
		m_shadows(false), 
		m_range(1.0f),
		m_intensity(1.0f),
		m_aabb(), 
		m_sphere(), 
		m_base_color(SRGB(1.0f)) {

		// Update the bounding volumes.
		UpdateBoundingVolumes();
	}

	OmniLight::OmniLight(const OmniLight& light) noexcept = default;
	
	OmniLight::OmniLight(OmniLight&& light) noexcept = default;
	
	OmniLight::~OmniLight() = default;

	OmniLight& OmniLight::operator=(const OmniLight& light) noexcept = default;

	OmniLight& OmniLight::operator=(OmniLight&& light) noexcept = default;
	
	void OmniLight::UpdateBoundingVolumes() noexcept {
		m_aabb   = AABB(Point3(-m_range, -m_range, -m_range),
			            Point3( m_range,  m_range,  m_range));
		m_sphere = BoundingSphere(Point3(), m_range);
	}
}