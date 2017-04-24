//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\manhattan_motor_script.hpp"
#include "core\engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void ManhattanMotorScript::Update(double delta_time) {
		const Keyboard * const keyboard = g_engine->GetInputManager()->GetKeyboard();
		const float delta = static_cast< float >(delta_time);

		const float movement_magnitude = delta * m_velocity;

		if (keyboard->GetKeyPress(DIK_UP, true) || keyboard->GetKeyPress(DIK_W, true)) {
			m_transform->AddTranslationZ(movement_magnitude);
		}
		else if (keyboard->GetKeyPress(DIK_DOWN, true) || keyboard->GetKeyPress(DIK_S, true)) {
			m_transform->AddTranslationZ(-movement_magnitude);
		}
		else if (keyboard->GetKeyPress(DIK_RIGHT, true) || keyboard->GetKeyPress(DIK_D, true)) {
			m_transform->AddTranslationX(movement_magnitude);
		}
		else if (keyboard->GetKeyPress(DIK_LEFT, true) || keyboard->GetKeyPress(DIK_A, true)) {
			m_transform->AddTranslationX(-movement_magnitude);
		}
		else if (keyboard->GetKeyPress(DIK_LSHIFT, true)) {
			m_transform->AddTranslationY(-movement_magnitude);
		}
		else if (keyboard->GetKeyPress(DIK_RSHIFT, true)) {
			m_transform->AddTranslationY(movement_magnitude);
		}
	}
}