//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\mtl\mtl_loader.hpp"
#include "loaders\mtl\mtl_reader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	void ImportMTLMaterialFromFile(const std::filesystem::path& path,
								   ResourceManager& resource_manager,
								   std::vector< Material >& materials) {

		MTLReader reader(resource_manager, materials);
		reader.ReadFromFile(path);
	}
}