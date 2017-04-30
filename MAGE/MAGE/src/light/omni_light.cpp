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

	SharedPtr< Light > OmniLight::CloneImplementation() const {
		return SharedPtr< OmniLight >(new OmniLight(*this));
	}
}