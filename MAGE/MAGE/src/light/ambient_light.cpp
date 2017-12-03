//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\ambient_light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	AmbientLight::AmbientLight() noexcept
		: Light(), m_radiance(1.0f) {}

	AmbientLight::AmbientLight(const AmbientLight &light) noexcept = default;
	
	AmbientLight::AmbientLight(AmbientLight &&light) noexcept = default;
	
	AmbientLight::~AmbientLight() = default;

	AmbientLight &AmbientLight::operator=(
		const AmbientLight &light) noexcept = default;
	
	AmbientLight &AmbientLight::operator=(
		AmbientLight &&light) noexcept = default;

	UniquePtr< Light > AmbientLight::CloneImplementation() const {
		return MakeUnique< AmbientLight >(*this);
	}
}