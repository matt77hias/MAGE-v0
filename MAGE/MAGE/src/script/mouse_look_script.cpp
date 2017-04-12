//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\mouse_look_script.hpp"
#include "math\math_utils.hpp"
#include "engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void MouseLookScript::Update(double delta_time) {
		const Mouse * const m_mouse = g_engine->GetInputManager()->GetMouse();
		const float delta = static_cast< float >(delta_time);
		
		switch (m_axes) {

		case RotationAxes_MouseXAndY: {
			const float rotation_x = m_transform->GetRotationX() - m_mouse->GetDeltaY() * delta * m_sensitivity.x;
			const float rotation_y = m_transform->GetRotationY() + m_mouse->GetDeltaX() * delta * m_sensitivity.y;
			m_transform->SetRotationX(ClampAngleRadians(rotation_x, m_min.x, m_max.x));
			m_transform->SetRotationY(ClampAngleRadians(rotation_y, m_min.y, m_max.y));
			break;
		}
		case RotationAxes_MouseX: {
			const float rotation_x = m_transform->GetRotationX() - m_mouse->GetDeltaY() * delta * m_sensitivity.x;
			m_transform->SetRotationX(ClampAngleRadians(rotation_x, m_min.x, m_max.x));
			break;
		}
		case RotationAxes_MouseY: {
			const float rotation_y = m_transform->GetRotationY() + m_mouse->GetDeltaX() * delta * m_sensitivity.y;
			m_transform->SetRotationY(ClampAngleRadians(rotation_y, m_min.y, m_max.y));
			break;
		}
		}
	}
}