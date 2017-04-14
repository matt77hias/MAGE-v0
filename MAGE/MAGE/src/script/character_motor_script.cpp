//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\character_motor_script.hpp"
#include "engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void CharacterMotorScript::Update(double delta_time) {
		const Keyboard * const keyboard = g_engine->GetInputManager()->GetKeyboard();
		const float delta = static_cast< float >(delta_time);
	
		const float movement_magnitude = delta * m_velocity;
		const float movement_cos = cos(m_transform->GetRotationY()) * movement_magnitude;
		const float movement_sin = sin(m_transform->GetRotationY()) * movement_magnitude;
		
		if (keyboard->GetKeyPress(DIK_UP, true)) {
			m_transform->AddTranslationX(movement_sin);
			m_transform->AddTranslationZ(movement_cos);
		}
		else if (keyboard->GetKeyPress(DIK_DOWN, true)) {
			m_transform->AddTranslationX(-movement_sin);
			m_transform->AddTranslationZ(-movement_cos);
		}
		else if (keyboard->GetKeyPress(DIK_RIGHT, true)) {
			m_transform->AddTranslationX(movement_cos);
			m_transform->AddTranslationZ(-movement_sin);
		}
		else if (keyboard->GetKeyPress(DIK_LEFT, true)) {
			m_transform->AddTranslationX(-movement_cos);
			m_transform->AddTranslationZ(movement_sin);
		}


		/*if (keyboard->GetKeyPress(DIK_UP, true)) {
			m_transform->AddTranslationZ(movement_magnitude);
		}
		else if (keyboard->GetKeyPress(DIK_DOWN, true)) {
			m_transform->AddTranslationZ(-movement_magnitude);
		}
		else if (keyboard->GetKeyPress(DIK_RIGHT, true)) {
			m_transform->AddTranslationX(movement_magnitude);
		}
		else if (keyboard->GetKeyPress(DIK_LEFT, true)) {
			m_transform->AddTranslationX(-movement_magnitude);
		}
		else if (keyboard->GetKeyPress(DIK_U, true)) {
			m_transform->AddTranslationY(movement_magnitude);
		}
		else if (keyboard->GetKeyPress(DIK_D, true)) {
			m_transform->AddTranslationY(-movement_magnitude);
		}*/
	}
}