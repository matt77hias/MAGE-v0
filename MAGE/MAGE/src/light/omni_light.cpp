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

	OmniLight::OmniLight(const RGBSpectrum &intensity)
		: Light(intensity),
		m_distance_falloff_start(0.0f), m_distance_falloff_end(1.0f), 
		m_shadows(false), m_light_camera() {

		// Update the light camera.
		UpdateLightCamera();

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

	void OmniLight::UpdateLightCamera() noexcept {
		m_light_camera.SetViewToProjectionMatrix(
			1.0f, XM_PIDIV2, 
			MAGE_DEFAULT_CAMERA_NEAR_Z, GetEndDistanceFalloff());
	}

	void OmniLight::UpdateBoundingVolumes() noexcept {

		AABB aabb(
			Point3(-m_distance_falloff_end, -m_distance_falloff_end, -m_distance_falloff_end),
			Point3( m_distance_falloff_end,  m_distance_falloff_end,  m_distance_falloff_end));

		BS bs(Point3(), m_distance_falloff_end);

		SetBoundingVolumes(std::move(aabb), std::move(bs));
	}
}