//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\material_loader.hpp"
#include "loaders\mtl\mtl_loader.hpp"
#include "file\file_utils.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	void ImportMaterialFromFile(const wstring &fname, 
		                        std::vector< Material > &materials) {
		
		const wstring extension = GetFileExtension(fname);

		if (extension == L"mtl" || extension == L"MTL") {
			ImportMTLMaterialFromFile(fname, materials);
			return;
		}
		else {
			throw Exception(
				"Unknown material file extension: %ls", fname.c_str());
		}
	}
}