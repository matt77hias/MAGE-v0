//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\manhattan_motor_script.hpp"
#include "input\keyboard.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	ManhattanMotorScript::ManhattanMotorScript(TransformNode *transform)
		: BehaviorScript(), m_transform(transform), m_velocity(2.0f) {

		Assert(m_transform);
	}

	ManhattanMotorScript::ManhattanMotorScript(
		ManhattanMotorScript &&script) = default;
	
	ManhattanMotorScript::~ManhattanMotorScript() = default;

	void ManhattanMotorScript::Update([[maybe_unused]] F64 delta_time) {
		const Keyboard * const keyboard = Keyboard::Get();

		const F32 movement_magnitude 
			= static_cast< F32 >(delta_time * m_velocity);

		if (keyboard->GetKeyPress(DIK_UP, true) 
			|| keyboard->GetKeyPress(DIK_W, true)) {
			
			m_transform->AddTranslationZ(movement_magnitude);
		}
		else if (keyboard->GetKeyPress(DIK_DOWN, true) 
			|| keyboard->GetKeyPress(DIK_S, true)) {
			
			m_transform->AddTranslationZ(-movement_magnitude);
		}
		else if (keyboard->GetKeyPress(DIK_RIGHT, true) 
			|| keyboard->GetKeyPress(DIK_D, true)) {
			
			m_transform->AddTranslationX(movement_magnitude);
		}
		else if (keyboard->GetKeyPress(DIK_LEFT, true) 
			|| keyboard->GetKeyPress(DIK_A, true)) {
			
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