//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\material_loader.hpp"
#include "loaders\mtl\mtl_loader.hpp"
#include "utils\file\file_utils.hpp"
#include "utils\exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void ImportMaterialFromFile(const wstring &fname, 
		vector< Material > &materials) {
		
		const wstring extension = GetFileExtension(fname);

		if (extension == L"mtl" || extension == L"MTL") {
			ImportMTLMaterialFromFile(fname, materials);
			return;
		}
		else {
			throw FormattedException(
				"Unknown material file extension: %ls", fname.c_str());
		}
	}
}