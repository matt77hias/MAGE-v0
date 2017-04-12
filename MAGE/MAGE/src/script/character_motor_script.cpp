//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\character_motor_script.hpp"
#include "engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void CharacterMotorScript::Update(double delta_time) {
		const Keyboard * const keyboard = g_engine->GetInputManager()->GetKeyboard();
		const float delta = static_cast< float >(delta_time);
		const float movement = delta * m_velocity;
		
		if (keyboard->GetKeyPress(DIK_UP, true)) {
			m_transform->AddTranslationZ(movement);
		}
		else if (keyboard->GetKeyPress(DIK_DOWN, true)) {
			m_transform->AddTranslationZ(-movement);
		}
		else if (keyboard->GetKeyPress(DIK_LEFT, true)) {
			m_transform->AddTranslationX(-movement);
		}
		else if (keyboard->GetKeyPress(DIK_RIGHT, true)) {
			m_transform->AddTranslationX(movement);
		}
	}
}