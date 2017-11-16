//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"
#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	EngineStatistics *EngineStatistics::Get() noexcept {
		Assert(Engine::Get());

		return Engine::Get()->GetEngineStatistics();
	}
}