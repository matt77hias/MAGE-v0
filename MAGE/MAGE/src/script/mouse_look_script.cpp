//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\mouse_look_script.hpp"
#include "scene\scene.hpp"
#include "input\mouse.hpp"
#include "utils\exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	MouseLookScript::MouseLookScript()
		: BehaviorScript(),
		m_axes(RotationAxes::MouseXAndY),
		m_sensitivity(F32x2(1.8f, 1.8f)),
		m_minimum_rotation(F32x2(-XM_PI / 3.0f, -XM_PI)),
		m_maximum_rotation(F32x2( XM_PI / 3.0f,  XM_PI)),
		m_direction(F32x2(1.0f, 1.0f)) {}

	MouseLookScript::MouseLookScript(
		const MouseLookScript &script) noexcept = default;

	MouseLookScript::MouseLookScript(
		MouseLookScript &&script) noexcept = default;
	
	MouseLookScript::~MouseLookScript() = default;

	void MouseLookScript::Load() {
		ThrowIfFailed(HasOwner(),
			"This script needs to be attached to a node.");
	}

	void MouseLookScript::Update([[maybe_unused]] F64 delta_time)	 {
		const Mouse * const mouse = Mouse::Get();
		Transform &transform = GetOwner()->GetTransform();

		switch (m_axes) {

		case RotationAxes::MouseXAndY: {
			
			const F64 rotation_x = m_direction.m_x * mouse->GetDeltaY() * delta_time 
				                 * m_sensitivity.m_x;
			const F64 rotation_y = m_direction.m_y * mouse->GetDeltaX() * delta_time 
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
			
			const F64 rotation_y = m_direction.m_y * mouse->GetDeltaX() * delta_time 
				                 * m_sensitivity.m_y;
			transform.AddAndClampRotationY(static_cast< F32 >(rotation_y),
				                           m_minimum_rotation.m_y,
				                           m_maximum_rotation.m_y);
			break;
		}
		
		case RotationAxes::MouseY: {
			
			const F64 rotation_x = m_direction.m_x * mouse->GetDeltaY() * delta_time 
				                 * m_sensitivity.m_x;
			transform.AddAndClampRotationX(static_cast< F32 >(rotation_x),
				                           m_minimum_rotation.m_x,
				                           m_maximum_rotation.m_x);
			break;
		}
		}
	}
}