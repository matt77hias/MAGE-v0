//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "manhattan_motor_script.hpp"
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
		const ManhattanMotorScript& script) noexcept = default;

	ManhattanMotorScript::ManhattanMotorScript(
		ManhattanMotorScript&& script) noexcept = default;

	ManhattanMotorScript::~ManhattanMotorScript() = default;

	ManhattanMotorScript& ManhattanMotorScript::operator=(
		const ManhattanMotorScript& script) noexcept = default;

	ManhattanMotorScript& ManhattanMotorScript::operator=(
		ManhattanMotorScript&& script) noexcept = default;

	void ManhattanMotorScript::Load([[maybe_unused]] Engine& engine) {
		ThrowIfFailed(HasOwner(),
					  "This script needs to be attached to a node.");
	}

	void ManhattanMotorScript::Update([[maybe_unused]] Engine& engine) {
		const auto delta_time
			= static_cast< F32 >(engine.GetTime().GetWallClockDeltaTime().count());
		const auto& input_manager = engine.GetInputManager();
		const auto& keyboard      = input_manager.GetKeyboard();
		auto& transform           = GetOwner()->GetTransform();

		const auto movement_magnitude = delta_time * m_velocity;

		if (     keyboard.IsActive(DIK_UP)
			  || keyboard.IsActive(DIK_W)) {

			transform.AddTranslationZ( movement_magnitude);
		}
		else if (keyboard.IsActive(DIK_DOWN)
			  || keyboard.IsActive(DIK_S)) {

			transform.AddTranslationZ(-movement_magnitude);
		}
		else if (keyboard.IsActive(DIK_RIGHT)
			  || keyboard.IsActive(DIK_D)) {

			transform.AddTranslationX( movement_magnitude);
		}
		else if (keyboard.IsActive(DIK_LEFT)
			  || keyboard.IsActive(DIK_A)) {

			transform.AddTranslationX(-movement_magnitude);
		}
		else if (keyboard.IsActive(DIK_LSHIFT)) {
			transform.AddTranslationY(-movement_magnitude);
		}
		else if (keyboard.IsActive(DIK_RSHIFT)) {
			transform.AddTranslationY( movement_magnitude);
		}
	}
}