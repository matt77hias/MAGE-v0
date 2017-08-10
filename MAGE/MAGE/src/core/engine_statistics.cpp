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

	EngineStatistics *EngineStatistics::Get() noexcept {
		Assert(g_engine);
		Assert(g_engine->IsLoaded());

		return g_engine->GetEngineStatistics();
	}
}