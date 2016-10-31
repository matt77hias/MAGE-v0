//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	GraphicsManager::GraphicsManager() {
		const D3D_FEATURE_LEVEL feature_levels[] = {
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};
		const UINT creation_flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

		// Get the ID3D11Device.
		ID3D11Device *device;
		const HRESULT result_device = D3D11CreateDevice(
			NULL,								// Default adapter
			D3D_DRIVER_TYPE_HARDWARE,			// Driver type
			NULL,								// A handle to a DLL that implements a software rasterizer.
			creation_flags,						// The runtime layers to enable.
			feature_levels,						// The order of feature levels to attempt to create.
			_countof(feature_levels),			// The number of feature levels.
			D3D11_SDK_VERSION,					// The SDK version.
			&device,							// The address of a pointer to the ID3D11Device that represents the device created.
			NULL,								// No need to determine which feature level is supported.
			NULL								// No ID3D11DeviceContext will be returned.
		);
		if (result_device) {
			Severe("D3D11CreateDevice: %d", result_device);
		}
		ID3D11Device2 *device2;
		const HRESULT result_device2 = device->QueryInterface(__uuidof(ID3D11Device2), (void **)&device2);
		if (result_device2) {
			Severe("ID3D11Device::QueryInterface: %d", result_device2);
		}

		// Get the IDXGIDevice3.
		const HRESULT result_dxgi_device = device->QueryInterface(__uuidof(IDXGIDevice3), (void **)&m_device);
		if (result_device2) {
			Severe("Error ID3D11Device2::QueryInterface: %d", result_dxgi_device);
		}

		g_device_enumeration = new DeviceEnumeration();
		const INT_PTR result_enumeration = g_device_enumeration->Enumerate(m_device);
		if (result_enumeration != IDOK) {
			return; //TODO return value
		}
	}
}