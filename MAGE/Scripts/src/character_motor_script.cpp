//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "character_motor_script.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	CharacterMotorScript::CharacterMotorScript()
		: BehaviorScript(), 
		m_velocity(2.0f) {}
	
	CharacterMotorScript::CharacterMotorScript(
		const CharacterMotorScript& script) noexcept = default;

	CharacterMotorScript::CharacterMotorScript(
		CharacterMotorScript&& script) noexcept = default;
	
	CharacterMotorScript::~CharacterMotorScript() = default;

	CharacterMotorScript& CharacterMotorScript::operator=(
		const CharacterMotorScript& script) noexcept = default;
	
	CharacterMotorScript& CharacterMotorScript::operator=(
		CharacterMotorScript&& script) noexcept = default;

	void CharacterMotorScript::Load([[maybe_unused]] Engine& engine) {
		ThrowIfFailed(HasOwner(), 
					  "This script needs to be attached to a node.");
	}

	void CharacterMotorScript::Update([[maybe_unused]] Engine& engine) {
		const auto delta_time
			= static_cast< F32 >(engine.GetTime().GetWallClockDeltaTime().count());
		const auto& input_manager = engine.GetInputManager();
		const auto& keyboard      = input_manager.GetKeyboard();
		auto& transform           = GetOwner()->GetTransform();

		const auto movement_magnitude = delta_time * m_velocity;
		const auto movement_cos       = std::cos(transform.GetRotationY())
			                          * movement_magnitude;
		const auto movement_sin       = std::sin(transform.GetRotationY())
			                          * movement_magnitude;
		
		if (     keyboard.GetKeyPress(DIK_UP,     true) 
			  || keyboard.GetKeyPress(DIK_W,      true)) {
			
			transform.AddTranslationX( movement_sin);
			transform.AddTranslationZ( movement_cos);
		}
		else if (keyboard.GetKeyPress(DIK_DOWN,   true) 
			  || keyboard.GetKeyPress(DIK_S,      true)) {
			
			transform.AddTranslationX(-movement_sin);
			transform.AddTranslationZ(-movement_cos);
		}

		if (     keyboard.GetKeyPress(DIK_RIGHT,  true) 
			  || keyboard.GetKeyPress(DIK_D,      true)) {
			
			transform.AddTranslationX( movement_cos);
			transform.AddTranslationZ(-movement_sin);
		}
		else if (keyboard.GetKeyPress(DIK_LEFT,   true) 
			  || keyboard.GetKeyPress(DIK_A,      true)) {
			
			transform.AddTranslationX(-movement_cos);
			transform.AddTranslationZ( movement_sin);
		}

		if (     keyboard.GetKeyPress(DIK_LSHIFT, true)) {
			transform.AddTranslationY(-movement_magnitude);
		}
		else if (keyboard.GetKeyPress(DIK_RSHIFT, true)) {
			transform.AddTranslationY( movement_magnitude);
		}
	}
}