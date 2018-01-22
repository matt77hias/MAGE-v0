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

	[[nodiscard]] const D3D11_VIEWPORT Viewport::GetMaxViewport() noexcept {
		const auto config = DisplayConfiguration::Get();
		
		return GetMaxViewport(config->GetDisplayWidth(), 
			                  config->GetDisplayHeight());
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Viewport Transformations
	//-------------------------------------------------------------------------
	#pragma region

	[[nodiscard]] const XMMATRIX XM_CALLCONV GetViewportTransform() noexcept {
		const auto config  = DisplayConfiguration::Get();
		const auto scale_x = 2.0f / config->GetDisplayWidth();
		const auto scale_y = 2.0f / config->GetDisplayHeight();
		
		// x =  Sx . [0,W] - 1 =  2/W . [0,W] - 1 = [0, 2] - 1 = [-1,  1]
		// y = -Sy . [0,H] + 1 = -2/H . [0,H] + 1 = [0,-2] + 1 = [ 1, -1]

		return XMMATRIX {
			scale_x,     0.0f, 0.0f, 0.0f,
			   0.0f, -scale_y, 0.0f, 0.0f,
			   0.0f,     0.0f, 1.0f, 0.0f,
			  -1.0f,     1.0f, 0.0f, 1.0f
		};
	}

	[[nodiscard]] const XMMATRIX XM_CALLCONV 
		GetViewportTransform(const D3D11_VIEWPORT &viewport) noexcept {
		
		const auto scale_x = (viewport.Width  > 0.0f) ?
							 2.0f / viewport.Width  : 0.0f;
		const auto scale_y = (viewport.Height > 0.0f) ?
							 2.0f / viewport.Height : 0.0f;

		// x =  Sx . [0,W] - 1 =  2/W . [0,W] - 1 = [0, 2] - 1 = [-1,  1]
		// y = -Sy . [0,H] + 1 = -2/H . [0,H] + 1 = [0,-2] + 1 = [ 1, -1]
		
		return XMMATRIX {
			scale_x,     0.0f, 0.0f, 0.0f,
			   0.0f, -scale_y, 0.0f, 0.0f,
			   0.0f,     0.0f, 1.0f, 0.0f,
			  -1.0f,     1.0f, 0.0f, 1.0f
		};
	}

	#pragma endregion
}