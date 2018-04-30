//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\material_loader.hpp"
#include "loaders\mtl\mtl_loader.hpp"
#include "resource\rendering_resource_manager.hpp"
#include "string\string_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	void ImportMaterialFromFile(const wstring& fname, 
								ResourceManager& resource_manaer, 
								std::vector< Material >& materials) {
		
		auto extension = GetFileExtension(fname);
		TransformToLowerCase(extension);

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