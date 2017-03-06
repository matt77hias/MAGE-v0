//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\material.hpp"
#include "resource\resource_factory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SharedPtr< Texture > CreateMaterialTexture(const wstring &fname) {
		return CreateTexture(fname);
	}
}