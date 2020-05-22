//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\model\material_factory.hpp"
#include "resource\texture\texture_factory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	const Material CreateDefaultMaterial(ResourceManager& resource_manager) {
		const auto white = CreateWhiteTexture(resource_manager);

		Material material;
		material.SetBaseColorTexture(white);
		material.SetMaterialTexture(white);

		return material;
	}
}