//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\material_loader.hpp"
#include "material\mtl\mtl_loader.hpp"
#include "file\file_utils.hpp"
#include "logging\exception.hpp"

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