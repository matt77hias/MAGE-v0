#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//@TODO: constexpr C++14

	/**
	 Returns the number of bits per pixel of the given DXGI format.

	 @param[in]		format
					The DXGI format.
	 @return		The number of bits per pixel of the given DXGI format.
	 */
	size_t BitsPerPixel(DXGI_FORMAT format) noexcept;

	/**
	 Converts the given DXGI format to an SRGB DXGI format.

	 @param[in]		format
					The DXGI format.
	 @return		The matching SRGB converted DXGI format
					of the given DXGI format.
	 */
	DXGI_FORMAT ConvertToSRGB(DXGI_FORMAT format) noexcept;

	/**
	 Checks whether the given DXGI format contains an alpha component.

	 @param[in]		format
					The DXGI format.
	 @return		@c true if and only if the given DXGI format contains
					an alpha component.
	*/
	bool HasAlpha(DXGI_FORMAT format) noexcept;
}