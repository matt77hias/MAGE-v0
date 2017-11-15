//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\character_motor_script.hpp"
#include "input\keyboard.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	CharacterMotorScript::CharacterMotorScript(TransformNode *transform)
		: BehaviorScript(), m_transform(transform), m_velocity(2.0f) {

		Assert(m_transform);
	}
	
	CharacterMotorScript::CharacterMotorScript(
		CharacterMotorScript &&script) = default;
	
	CharacterMotorScript::~CharacterMotorScript() = default;

	void CharacterMotorScript::Update([[maybe_unused]] F64 delta_time) {
		const Keyboard * const keyboard = Keyboard::Get();
		
		const F64 movement_magnitude = delta_time * m_velocity;
		const F64 movement_cos 
			= cos(m_transform->GetRotationY()) * movement_magnitude;
		const F64 movement_sin 
			= sin(m_transform->GetRotationY()) * movement_magnitude;
		
		if (keyboard->GetKeyPress(DIK_UP, true) 
			|| keyboard->GetKeyPress(DIK_W, true)) {
			
			m_transform->AddTranslationX(static_cast< F32 >(movement_sin));
			m_transform->AddTranslationZ(static_cast< F32 >(movement_cos));
		}
		else if (keyboard->GetKeyPress(DIK_DOWN, true) 
			|| keyboard->GetKeyPress(DIK_S, true)) {
			
			m_transform->AddTranslationX(static_cast< F32 >(-movement_sin));
			m_transform->AddTranslationZ(static_cast< F32 >(-movement_cos));
		}
		else if (keyboard->GetKeyPress(DIK_RIGHT, true) 
			|| keyboard->GetKeyPress(DIK_D, true)) {
			
			m_transform->AddTranslationX(static_cast< F32 >( movement_cos));
			m_transform->AddTranslationZ(static_cast< F32 >(-movement_sin));
		}
		else if (keyboard->GetKeyPress(DIK_LEFT, true) 
			|| keyboard->GetKeyPress(DIK_A, true)) {
			
			m_transform->AddTranslationX(static_cast< F32 >(-movement_cos));
			m_transform->AddTranslationZ(static_cast< F32 >( movement_sin));
		}
		else if (keyboard->GetKeyPress(DIK_LSHIFT, true)) {
			m_transform->AddTranslationY(static_cast< F32 >(-movement_magnitude));
		}
		else if (keyboard->GetKeyPress(DIK_RSHIFT, true)) {
			m_transform->AddTranslationY(static_cast< F32 >(movement_magnitude));
		}
	}
}