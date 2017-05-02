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
		m_distance_falloff_start(0.0f), m_distance_falloff_end(1.0f) {}

	OmniLight::OmniLight(const OmniLight &light) = default;
	
	OmniLight::OmniLight(OmniLight &&light) = default;
	
	OmniLight::~OmniLight() = default;
	
	OmniLight &OmniLight::operator=(const OmniLight &light) = default;
	
	OmniLight &OmniLight::operator=(OmniLight &&light) = default;

	SharedPtr< Light > OmniLight::CloneImplementation() const {
		return SharedPtr< OmniLight >(new OmniLight(*this));
	}
}