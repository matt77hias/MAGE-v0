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
	
	ID3D11Device5 *Pipeline::GetDevice() noexcept {
		Assert(RenderingManager::Get());

		return RenderingManager::Get()->GetDevice();
	}

	ID3D11DeviceContext4 *Pipeline::GetImmediateDeviceContext() noexcept {
		Assert(RenderingManager::Get());

		return RenderingManager::Get()->GetDeviceContext();
	}

	void Pipeline::OnDraw() noexcept {
		EngineStatistics::Get()->IncrementNumberOfDrawCalls();
	}
}
