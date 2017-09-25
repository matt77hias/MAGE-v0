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
namespace mage {

	template< typename SceneT >
	SwitchSceneScript< SceneT >::SwitchSceneScript() = default;
	
	template< typename SceneT >
	SwitchSceneScript< SceneT >::SwitchSceneScript(SwitchSceneScript< SceneT > &&script) = default;
	
	template< typename SceneT >
	SwitchSceneScript< SceneT >::~SwitchSceneScript() = default;

	template< typename SceneT >
	void SwitchSceneScript< SceneT >::Update(f64 delta_time) {
		UNUSED(delta_time);

		const Keyboard * const keyboard = Keyboard::Get();

		if (keyboard->GetKeyPress(DIK_C)) {
			SceneManager::Get()->SetScene(MakeUnique< SceneT >());
		}
	}
}