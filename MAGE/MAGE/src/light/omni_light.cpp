//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\omni_light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	OmniLight::OmniLight()
		: Light(),
		m_intensity(1.0f),
		m_range(1.0f), 
		m_shadows(false) {

		// Update the bounding volumes.
		UpdateBoundingVolumes();
	}

	OmniLight::OmniLight(const OmniLight &light) = default;
	
	OmniLight::OmniLight(OmniLight &&light) = default;
	
	OmniLight::~OmniLight() = default;
	
	OmniLight &OmniLight::operator=(const OmniLight &light) = default;
	
	OmniLight &OmniLight::operator=(OmniLight &&light) = default;

	UniquePtr< Light > OmniLight::CloneImplementation() const {
		return MakeUnique< OmniLight >(*this);
	}

	void OmniLight::UpdateBoundingVolumes() noexcept {
		AABB aabb(Point3(-m_range, -m_range, -m_range),
			      Point3( m_range,  m_range,  m_range));
		BS bs(Point3(), m_range);

		SetBoundingVolumes(std::move(aabb), std::move(bs));
	}
}