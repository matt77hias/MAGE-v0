#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	template< typename SceneT >
	SwitchSceneScript< SceneT >::SwitchSceneScript() = default;
	
	template< typename SceneT >
	SwitchSceneScript< SceneT >::SwitchSceneScript(
		const SwitchSceneScript& script) noexcept = default;

	template< typename SceneT >
	SwitchSceneScript< SceneT >::SwitchSceneScript(
		SwitchSceneScript&& script) noexcept = default;
	
	template< typename SceneT >
	SwitchSceneScript< SceneT >::~SwitchSceneScript() = default;
	
	template< typename SceneT >
	SwitchSceneScript< SceneT >& SwitchSceneScript< SceneT >
		::operator=(const SwitchSceneScript& script) noexcept = default;

	template< typename SceneT >
	SwitchSceneScript< SceneT >& SwitchSceneScript< SceneT >
		::operator=(SwitchSceneScript&& script) noexcept = default;

	template< typename SceneT >
	void SwitchSceneScript< SceneT >::Update([[maybe_unused]] Engine& engine) {
		const auto& keyboard = engine.GetInputManager().GetKeyboard();
		
		if (keyboard.GetKeyPress(DIK_F3)) {
			engine.RequestScene(MakeUnique< SceneT >());
		}
	}
}