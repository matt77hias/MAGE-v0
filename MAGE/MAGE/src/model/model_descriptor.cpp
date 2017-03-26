//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	ComPtr< ID3D11Device2 > GetModelRenderingDevice() {
		return GetRenderingDevice();
	}
	ComPtr< ID3D11DeviceContext2 > GetModelRenderingDeviceContext() {
		return GetRenderingDeviceContext();
	}
	ResourceFactory &GetModelResourceFactory() {
		return GetResourceFactory();
	}
}