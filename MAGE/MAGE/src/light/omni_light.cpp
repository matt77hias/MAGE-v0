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

#define MAGE_DEFAULT_RANGE      1.0f
#define MAGE_DEFAULT_INTENSITY  1.0f
#define MAGE_DEFAULT_BASE_COLOR 1.0f

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	OmniLight::OmniLight() noexcept
		: Component(),
		m_shadows(false), 
		m_range(MAGE_DEFAULT_RANGE), 
		m_intensity(MAGE_DEFAULT_INTENSITY),
		m_aabb(), 
		m_sphere(), 
		m_base_color(SRGB(MAGE_DEFAULT_BASE_COLOR)) {

		// Update the bounding volumes.
		UpdateBoundingVolumes();
	}

	OmniLight::OmniLight(const OmniLight &light) noexcept = default;
	
	OmniLight::OmniLight(OmniLight &&light) noexcept = default;
	
	OmniLight::~OmniLight() = default;

	OmniLight &OmniLight::operator=(const OmniLight &light) noexcept = default;

	OmniLight &OmniLight::operator=(OmniLight &&light) noexcept = default;
	
	void OmniLight::UpdateBoundingVolumes() noexcept {
		m_aabb   = AABB(Point3(-m_range, -m_range, -m_range),
			            Point3( m_range,  m_range,  m_range));
		m_sphere = BoundingSphere(Point3(), m_range);
	}
}