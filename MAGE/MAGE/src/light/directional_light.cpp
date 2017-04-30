//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\directional_light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	DirectionalLight::DirectionalLight(const RGBSpectrum &intensity)
		: Light(intensity) {}

	SharedPtr< Light > DirectionalLight::CloneImplementation() const {
		return SharedPtr< DirectionalLight >(new DirectionalLight(*this));
	}
}