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

	[[nodiscard]] ResourceManager *ResourceManager::Get() noexcept {
		Assert(Engine::Get());

		return Engine::Get()->GetResourceManager();
	}

	ResourceManager::ResourceManager() = default;

	ResourceManager::~ResourceManager() = default;
}
