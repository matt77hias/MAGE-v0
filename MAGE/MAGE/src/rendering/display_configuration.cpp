//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_manager.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const DisplayConfiguration *DisplayConfiguration::Get() noexcept {
		Assert(RenderingManager::Get());

		return RenderingManager::Get()->GetDisplayConfiguration();
	}
}