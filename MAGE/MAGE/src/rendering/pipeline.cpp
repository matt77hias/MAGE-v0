//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine_statistics.hpp"
#include "rendering\rendering_manager.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	[[nodiscard]] D3D11Device *Pipeline::GetDevice() noexcept {
		Assert(RenderingManager::Get());

		return RenderingManager::Get()->GetDevice();
	}

	[[nodiscard]] D3D11DeviceContext *Pipeline::GetImmediateDeviceContext() noexcept {
		Assert(RenderingManager::Get());

		return RenderingManager::Get()->GetDeviceContext();
	}

	void Pipeline::OnDraw() noexcept {
		EngineStatistics::Get()->IncrementNumberOfDrawCalls();
	}
}
