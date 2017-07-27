//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\character_motor_script.hpp"
#include "core\engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	CharacterMotorScript::CharacterMotorScript(TransformNode *transform)
		: BehaviorScript(), m_transform(transform), m_velocity(2.0f) {}
	
	CharacterMotorScript::CharacterMotorScript(CharacterMotorScript &&script) = default;
	
	CharacterMotorScript::~CharacterMotorScript() = default;

	void CharacterMotorScript::Update(double delta_time) {
		const Keyboard * const keyboard = g_engine->GetInputManager()->GetKeyboard();
		
		const double movement_magnitude = delta_time * m_velocity;
		const double movement_cos = cos(m_transform->GetRotationY()) * movement_magnitude;
		const double movement_sin = sin(m_transform->GetRotationY()) * movement_magnitude;
		
		if (keyboard->GetKeyPress(DIK_UP, true) || keyboard->GetKeyPress(DIK_W, true)) {
			m_transform->AddTranslationX(static_cast< float >(movement_sin));
			m_transform->AddTranslationZ(static_cast< float >(movement_cos));
		}
		else if (keyboard->GetKeyPress(DIK_DOWN, true) || keyboard->GetKeyPress(DIK_S, true)) {
			m_transform->AddTranslationX(static_cast< float >(-movement_sin));
			m_transform->AddTranslationZ(static_cast< float >(-movement_cos));
		}
		else if (keyboard->GetKeyPress(DIK_RIGHT, true) || keyboard->GetKeyPress(DIK_D, true)) {
			m_transform->AddTranslationX(static_cast< float >( movement_cos));
			m_transform->AddTranslationZ(static_cast< float >(-movement_sin));
		}
		else if (keyboard->GetKeyPress(DIK_LEFT, true) || keyboard->GetKeyPress(DIK_A, true)) {
			m_transform->AddTranslationX(static_cast< float >(-movement_cos));
			m_transform->AddTranslationZ(static_cast< float >( movement_sin));
		}
		else if (keyboard->GetKeyPress(DIK_LSHIFT, true)) {
			m_transform->AddTranslationY(static_cast< float >(-movement_magnitude));
		}
		else if (keyboard->GetKeyPress(DIK_RSHIFT, true)) {
			m_transform->AddTranslationY(static_cast< float >(movement_magnitude));
		}
	}
}