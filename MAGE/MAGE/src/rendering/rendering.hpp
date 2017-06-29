#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <d3d11_2.h>
#include <DXGI1_3.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Linker Directives
//-----------------------------------------------------------------------------
#pragma region

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 The supported feature levels.
	 */
	constexpr D3D_FEATURE_LEVEL g_feature_levels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0
	};

	/**
	 Returns the rendering device.

	 @pre			The current engine must be loaded.
	 @return		A pointer to the rendering device.
	 */
	ID3D11Device2 *GetRenderingDevice() noexcept;

	/**
	 Returns the rendering device context.

	 @pre			The current engine must be loaded.
	 @return		A pointer to the rendering device context.
	 */
	ID3D11DeviceContext2 *GetRenderingDeviceContext() noexcept;
}