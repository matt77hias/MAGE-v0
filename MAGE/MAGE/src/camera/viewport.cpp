//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\viewport.hpp"
#include "rendering\rendering_manager.hpp"
#include "math\math_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const D3D11_VIEWPORT Viewport::GetMaxViewport() noexcept {
		const RenderingManager * const rendering_manager
			= RenderingManager::Get();
		
		return GetMaxViewport(
			rendering_manager->GetWidth(),
			rendering_manager->GetHeight());
	}

	F32 Viewport::NormalizeWidth(F32 x) noexcept {
		const F32 width = static_cast< F32 >(RenderingManager::Get()->GetWidth());
		return Clamp(x * width, 0.0f, width);
	}

	F32 Viewport::NormalizeHeight(F32 x) noexcept {
		const F32 height = static_cast< F32 >(RenderingManager::Get()->GetHeight());
		return Clamp(x * height, 0.0f, height);
	}
}