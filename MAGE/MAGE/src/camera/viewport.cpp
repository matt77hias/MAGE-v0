//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\viewport.hpp"
#include "rendering\display_configuration.hpp"
#include "math\math_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const D3D11_VIEWPORT Viewport::GetMaxViewport() noexcept {
		const DisplayConfiguration * const config = DisplayConfiguration::Get();
		
		return GetMaxViewport(config->GetDisplayWidth(), 
			                  config->GetDisplayHeight());
	}

	F32 Viewport::NormalizeWidth(F32 x) noexcept {
		const F32 width = static_cast< F32 >(
			DisplayConfiguration::Get()->GetDisplayWidth());
		return Clamp(x * width, 0.0f, width);
	}

	F32 Viewport::NormalizeHeight(F32 x) noexcept {
		const F32 height = static_cast< F32 >(
			DisplayConfiguration::Get()->GetDisplayHeight());
		return Clamp(x * height, 0.0f, height);
	}
}