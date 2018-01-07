//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\manhattan_motor_script.hpp"
#include "scene\scene.hpp"
#include "input\keyboard.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	ManhattanMotorScript::ManhattanMotorScript()
		: BehaviorScript(), 
		m_velocity(2.0f) {}

	ManhattanMotorScript::ManhattanMotorScript(
		const ManhattanMotorScript &script) noexcept = default;

	ManhattanMotorScript::ManhattanMotorScript(
		ManhattanMotorScript &&script) noexcept = default;
	
	ManhattanMotorScript::~ManhattanMotorScript() = default;

	void ManhattanMotorScript::Load() {
		ThrowIfFailed(HasOwner(),
			"This script needs to be attached to a node.");
	}

	void ManhattanMotorScript::Update([[maybe_unused]] F64 delta_time) {
		const Keyboard * const keyboard = Keyboard::Get();
		Transform &transform = GetOwner()->GetTransform();

		const F32 movement_magnitude 
			= static_cast< F32 >(delta_time * m_velocity);

		if (     keyboard->GetKeyPress(DIK_UP,     true) 
			  || keyboard->GetKeyPress(DIK_W,      true)) {
			
			transform.AddTranslationZ(movement_magnitude);
		}
		else if (keyboard->GetKeyPress(DIK_DOWN,   true) 
			  || keyboard->GetKeyPress(DIK_S,      true)) {
			
			transform.AddTranslationZ(-movement_magnitude);
		}
		else if (keyboard->GetKeyPress(DIK_RIGHT,  true) 
			  || keyboard->GetKeyPress(DIK_D,      true)) {
			
			transform.AddTranslationX(movement_magnitude);
		}
		else if (keyboard->GetKeyPress(DIK_LEFT,   true) 
			  || keyboard->GetKeyPress(DIK_A,      true)) {
			
			transform.AddTranslationX(-movement_magnitude);
		}
		else if (keyboard->GetKeyPress(DIK_LSHIFT, true)) {
			transform.AddTranslationY(-movement_magnitude);
		}
		else if (keyboard->GetKeyPress(DIK_RSHIFT, true)) {
			transform.AddTranslationY(movement_magnitude);
		}
	}
}