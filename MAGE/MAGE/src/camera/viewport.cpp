//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\viewport.hpp"
#include "rendering\display_configuration.hpp"
#include "logging\error.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Viewport
	//-------------------------------------------------------------------------
	#pragma region

	[[nodiscard]]const D3D11_VIEWPORT Viewport::GetMaxViewport() noexcept {
		const auto config = DisplayConfiguration::Get();
		
		return GetMaxViewport(config->GetDisplayWidth(), 
			                  config->GetDisplayHeight());
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Viewport Transformations
	//-------------------------------------------------------------------------
	#pragma region

	[[nodiscard]]const XMMATRIX XM_CALLCONV GetViewportTransform() noexcept {
		const auto config = DisplayConfiguration::Get();
		const auto width  = 2.0f / config->GetDisplayWidth();
		const auto height = 2.0f / config->GetDisplayHeight();
		
		// x =  Sx . [0,W] - 1 =  2/W . [0,W] - 1 = [0, 2] - 1 = [-1,  1]
		// y = -Sy . [0,H] + 1 = -2/H . [0,H] + 1 = [0,-2] + 1 = [ 1, -1]

		return XMMATRIX {
			width,    0.0f, 0.0f, 0.0f,
			 0.0f, -height, 0.0f, 0.0f,
		     0.0f,    0.0f, 1.0f, 0.0f,
		    -1.0f,    1.0f, 0.0f, 1.0f
		};
	}

	[[nodiscard]]const XMMATRIX XM_CALLCONV 
		GetViewportTransform(const D3D11_VIEWPORT &viewport) noexcept {
		
		const auto width  = (viewport.Width  > 0.0f) ?
							2.0f / viewport.Width  : 0.0f;
		const auto height = (viewport.Height > 0.0f) ?
							2.0f / viewport.Height : 0.0f;

		// x =  Sx . [0,W] - 1 =  2/W . [0,W] - 1 = [0, 2] - 1 = [-1,  1]
		// y = -Sy . [0,H] + 1 = -2/H . [0,H] + 1 = [0,-2] + 1 = [ 1, -1]
		
		return XMMATRIX {
			width,    0.0f, 0.0f, 0.0f,
			 0.0f, -height, 0.0f, 0.0f,
			 0.0f,    0.0f, 1.0f, 0.0f,
			-1.0f,    1.0f, 0.0f, 1.0f
		};
	}

	#pragma endregion
}