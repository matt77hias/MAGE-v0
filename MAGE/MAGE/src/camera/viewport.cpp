//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\viewport.hpp"
#include "rendering\renderer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	inline D3D11_VIEWPORT GetMaxViewport() noexcept {
		D3D11_VIEWPORT viewport = {};
		viewport.Width    = static_cast<FLOAT>(Renderer::Get()->GetWidth());
		viewport.Height   = static_cast<FLOAT>(Renderer::Get()->GetHeight());
		viewport.MaxDepth = 1.0f;
		return viewport;
	}

	Viewport::Viewport()
		: Viewport(GetMaxViewport()) {}

	void Viewport::SetMaximumViewport() noexcept {
		SetViewport(GetMaxViewport());
	}
}