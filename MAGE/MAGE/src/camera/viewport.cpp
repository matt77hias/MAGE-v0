//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\viewport.hpp"
#include "rendering\display_configuration.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <algorithm>

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
		return std::clamp(x * width, 0.0f, width);
	}

	F32 Viewport::NormalizeHeight(F32 x) noexcept {
		const F32 height = static_cast< F32 >(
			DisplayConfiguration::Get()->GetDisplayHeight());
		return std::clamp(x * height, 0.0f, height);
	}
}