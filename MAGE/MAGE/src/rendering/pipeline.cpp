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
	
	const D3D_FEATURE_LEVEL Pipeline::s_feature_levels[2] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0
	};

	ID3D11Device2 *Pipeline::GetDevice() noexcept {
		Assert(RenderingManager::Get());

		return RenderingManager::Get()->GetDevice();
	}

	ID3D11DeviceContext2 *Pipeline::GetImmediateDeviceContext() noexcept {
		Assert(RenderingManager::Get());

		return RenderingManager::Get()->GetDeviceContext();
	}

	void Pipeline::OnDraw() noexcept {
		EngineStatistics::Get()->IncrementNumberOfDrawCalls();
	}
}
