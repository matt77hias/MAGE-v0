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

	RenderingDevice GetModelRenderingDevice() {
		return GetRenderingDevice();
	}

	ResourceFactory &GetModelResourceFactory() {
		return GetResourceFactory();
	}
}