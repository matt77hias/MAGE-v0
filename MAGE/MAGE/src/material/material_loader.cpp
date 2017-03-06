//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\material_loader.hpp"
#include "material\mtl\mtl_loader.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT ImportMaterialFromFile(const wstring &fname, vector< Material > &material_buffer) {
		const wstring extension = GetFileExtension(fname);

		if (extension == L"mtl" || extension == L"MTL") {
			return ImportMTLMaterialFromFile(fname, material_buffer);
		}

		Warning("Unknown material file extension: %ls", fname.c_str());
		return E_FAIL;
	}
}