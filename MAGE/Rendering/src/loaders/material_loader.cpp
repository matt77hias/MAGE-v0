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

	void ImportMaterialFromFile(const std::filesystem::path& path, 
								ResourceManager& resource_manaer, 
								std::vector< Material >& materials) {
		
		std::wstring extension(path.extension());
		TransformToLowerCase(extension);

		if (L".mtl" == extension) {
			ImportMTLMaterialFromFile(path, resource_manaer, materials);
			return;
		}
		else {
			throw Exception("Unknown material file extension: {}", path);
		}
	}
}