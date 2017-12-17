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

#define MAGE_DEFAULT_INTENSITY 1.0f
#define MAGE_DEFAULT_RANGE     1.0f

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	OmniLight::OmniLight() noexcept
		: Light(),
		m_intensity(MAGE_DEFAULT_INTENSITY),
		m_range(MAGE_DEFAULT_RANGE),
		m_shadows(false) {

		// Update the bounding volumes.
		UpdateBoundingVolumes();
	}

	OmniLight::OmniLight(const OmniLight &light) noexcept = default;
	
	OmniLight::OmniLight(OmniLight &&light) noexcept = default;
	
	OmniLight::~OmniLight() = default;

	OmniLight &OmniLight::operator=(const OmniLight &light) noexcept = default;

	OmniLight &OmniLight::operator=(OmniLight &&light) noexcept = default;
	
	void OmniLight::UpdateBoundingVolumes() noexcept {
		AABB aabb(Point3(-m_range, -m_range, -m_range),
			      Point3( m_range,  m_range,  m_range));
		BS bs(Point3(), m_range);

		SetBoundingVolumes(std::move(aabb), std::move(bs));
	}
}