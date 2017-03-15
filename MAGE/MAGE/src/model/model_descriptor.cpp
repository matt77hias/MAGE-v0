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

	ResourceFactory &GetModelResourceFactory() {
		return GetResourceFactory();
	}
}