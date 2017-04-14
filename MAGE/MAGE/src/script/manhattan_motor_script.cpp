//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\manhattan_motor_script.hpp"
#include "engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void ManhattanMotorScript::Update(double delta_time) {
		const Keyboard * const keyboard = g_engine->GetInputManager()->GetKeyboard();
		const float delta = static_cast< float >(delta_time);

		const float movement_magnitude = delta * m_velocity;
		
		if (keyboard->GetKeyPress(DIK_UP, true)) {
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
		}
	}
}