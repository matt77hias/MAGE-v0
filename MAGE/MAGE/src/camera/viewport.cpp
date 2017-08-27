//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\viewport.hpp"
#include "rendering\renderer.hpp"
#include "math\math_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const D3D11_VIEWPORT Viewport::GetMaxViewport() noexcept {
		D3D11_VIEWPORT viewport = {};
		viewport.Width    = static_cast< FLOAT >(Renderer::Get()->GetWidth());
		viewport.Height   = static_cast< FLOAT >(Renderer::Get()->GetHeight());
		viewport.MaxDepth = 1.0f;
		return viewport;
	}

	float Viewport::NormalizeWidth(float x) noexcept {
		const float width = static_cast< float >(Renderer::Get()->GetWidth());
		return Clamp(x * width, 0.0f, width);
	}

	float Viewport::NormalizeHeight(float x) noexcept {
		const float height = static_cast< float >(Renderer::Get()->GetHeight());
		return Clamp(x * height, 0.0f, height);
	}
}