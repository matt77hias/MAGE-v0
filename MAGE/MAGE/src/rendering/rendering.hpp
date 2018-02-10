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

#include <d3d11_3.h>
#include <DXGI1_5.h>

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

	using DXGIAdapter = IDXGIAdapter3;
	using DXGIOutput = IDXGIOutput5;
	using DXGISwapChain = IDXGISwapChain4;

	using D3D11Device = ID3D11Device3;
	using D3D11DeviceContext = ID3D11DeviceContext4;
}