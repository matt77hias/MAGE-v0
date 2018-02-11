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

#include <d3d11.h>
#include <DXGI.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Linker Directives
//-----------------------------------------------------------------------------
#pragma region

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")

#pragma endregion

//-----------------------------------------------------------------------------
// Type Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 The type of DXGI adapter.
	 */
	using DXGIAdapter = IDXGIAdapter;

	/**
	 The type of DXGI output.
	 */
	using DXGIOutput = IDXGIOutput;

	/**
	 The type of DXGI swap chain.
	 */
	using DXGISwapChain = IDXGISwapChain;

	/**
	 The type of D3D11 device.
	 */
	using D3D11Device = ID3D11Device;

	/**
	 The type of D3D11 device context.
	 */
	using D3D11DeviceContext = ID3D11DeviceContext;
}