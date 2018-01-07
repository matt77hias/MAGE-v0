//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// ResourceManager
	//-------------------------------------------------------------------------
	
	ResourceManager *ResourceManager::Get() noexcept {
		Assert(Engine::Get());

		return Engine::Get()->GetResourceManager();
	}

	ResourceManager::ResourceManager() = default;

	ResourceManager::ResourceManager(ResourceManager &&manager) = default;

	ResourceManager::~ResourceManager() = default;
}
