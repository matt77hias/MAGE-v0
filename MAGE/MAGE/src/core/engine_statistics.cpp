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
		Assert(Engine::Get());
		Assert(Engine::Get()->GetEngineStatistics());

		return Engine::Get()->GetEngineStatistics();
	}
}