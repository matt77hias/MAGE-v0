//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\material_loader.hpp"
#include "loaders\mtl\mtl_loader.hpp"
#include "resource\rendering_resource_manager.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <algorithm>
#include <cwctype>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	void ImportMaterialFromFile(const wstring& fname, 
								ResourceManager& resource_manaer, 
								std::vector< Material >& materials) {
		
		auto extension = GetFileExtension(fname);
		std::transform(extension.begin(), extension.end(), extension.begin(),
					   std::towlower);

		if (L"mtl" == extension) {
			ImportMTLMaterialFromFile(fname, resource_manaer, materials);
			return;
		}
		else {
			throw Exception("Unknown material file extension: %ls", 
				            fname.c_str());
		}
	}
}