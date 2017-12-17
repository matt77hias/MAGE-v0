#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "input\keyboard.hpp"
#include "scene\scene_manager.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	template< typename SceneT >
	SwitchSceneScript< SceneT >::SwitchSceneScript() = default;
	
	template< typename SceneT >
	SwitchSceneScript< SceneT >::SwitchSceneScript(
		const SwitchSceneScript &script) noexcept = default;

	template< typename SceneT >
	SwitchSceneScript< SceneT >::SwitchSceneScript(
		SwitchSceneScript &&script) noexcept = default;
	
	template< typename SceneT >
	SwitchSceneScript< SceneT >::~SwitchSceneScript() = default;
	
	template< typename SceneT >
	void SwitchSceneScript< SceneT >::Update([[maybe_unused]] F64 delta_time) {
		if (Keyboard::Get()->GetKeyPress(DIK_C)) {
			SceneManager::Get()->SetScene(MakeUnique< SceneT >());
		}
	}
}