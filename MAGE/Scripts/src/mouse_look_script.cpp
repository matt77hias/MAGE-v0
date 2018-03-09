//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mouse_look_script.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	MouseLookScript::MouseLookScript()
		: BehaviorScript(),
		m_locked(false),
		m_axes(RotationAxes::MouseXAndY),
		m_sensitivity(F32x2(1.8f, 1.8f)),
		m_minimum_rotation(F32x2(-XM_PI / 3.0f, -XM_PI)),
		m_maximum_rotation(F32x2( XM_PI / 3.0f,  XM_PI)),
		m_direction(F32x2(1.0f, 1.0f)) {}

	MouseLookScript::MouseLookScript(
		const MouseLookScript& script) noexcept = default;

	MouseLookScript::MouseLookScript(
		MouseLookScript&& script) noexcept = default;
	
	MouseLookScript::~MouseLookScript() = default;

	MouseLookScript& MouseLookScript::operator=(
		const MouseLookScript& script) noexcept = default;

	MouseLookScript& MouseLookScript::operator=(
		MouseLookScript&& script) noexcept = default;

	void MouseLookScript::Load([[maybe_unused]] Engine& engine) {
		ThrowIfFailed(HasOwner(), 
					  "This script needs to be attached to a node.");
	}

	void MouseLookScript::Update([[maybe_unused]] Engine& engine,
								 [[maybe_unused]] F64 delta_time) {
		
		const auto& input_manager = engine.GetInputManager();
		const auto& keyboard      = input_manager.GetKeyboard();

		if (keyboard.GetKeyPress(DIK_F2)) {
			m_locked = !m_locked;
		}
		if (m_locked) {
			return;
		}
		
		const auto& mouse         = input_manager.GetMouse();
		auto& transform           = GetOwner()->GetTransform();

		switch (m_axes) {

		case RotationAxes::MouseXAndY: {
			
			const auto rotation_x = m_direction.m_x * mouse.GetDeltaY() * delta_time 
				                  * m_sensitivity.m_x;
			const auto rotation_y = m_direction.m_y * mouse.GetDeltaX() * delta_time 
				                  * m_sensitivity.m_y;
			transform.AddAndClampRotationX(static_cast< F32 >(rotation_x),
				                           m_minimum_rotation.m_x,
				                           m_maximum_rotation.m_x);
			transform.AddAndClampRotationY(static_cast< F32 >(rotation_y),
				                           m_minimum_rotation.m_y,
				                           m_maximum_rotation.m_y);
			break;
		}
		
		case RotationAxes::MouseX: {
			
			const auto rotation_y = m_direction.m_y * mouse.GetDeltaX() * delta_time
				                  * m_sensitivity.m_y;
			transform.AddAndClampRotationY(static_cast< F32 >(rotation_y),
				                           m_minimum_rotation.m_y,
				                           m_maximum_rotation.m_y);
			break;
		}
		
		case RotationAxes::MouseY: {
			
			const auto rotation_x = m_direction.m_x * mouse.GetDeltaY() * delta_time
				                  * m_sensitivity.m_x;
			transform.AddAndClampRotationX(static_cast< F32 >(rotation_x),
				                           m_minimum_rotation.m_x,
				                           m_maximum_rotation.m_x);
			break;
		}
		}
	}
}