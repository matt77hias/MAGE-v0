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

	void MouseLookScript::Update(double elapsed_time) {
		const Mouse *mouse = g_engine->GetInputManager()->GetMouse();
		Transform *transform = m_camera->GetTransform();

		switch (m_axes) {

		case RotationAxes_MouseXAndY: {
			const float rotation_x = m_rotation.x + mouse->GetDeltaX() * m_sensitivity.x;
			const float rotation_y = m_rotation.y + mouse->GetDeltaY() * m_sensitivity.y;
			transform->AddRotationX(ClampAngleRadians(rotation_x, m_min.x, m_max.x));
			transform->AddRotationY(ClampAngleRadians(rotation_y, m_min.y, m_max.y));
			break;
		}
		case RotationAxes_MouseX: {
			const float rotation_x = m_rotation.x + mouse->GetDeltaX() * m_sensitivity.x;
			transform->AddRotationX(ClampAngleRadians(rotation_x, m_min.x, m_max.x));
			break;
		}
		case RotationAxes_MouseY: {
			const float rotation_y = m_rotation.y + mouse->GetDeltaY() * m_sensitivity.y;
			transform->AddRotationY(ClampAngleRadians(rotation_y, m_min.y, m_max.y));
			break;
		}
		}
	}
}