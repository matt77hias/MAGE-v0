//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\mouse_look_script.hpp"
#include "math\math_utils.hpp"
#include "core\engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void MouseLookScript::Update(double delta_time) {
		const Mouse * const m_mouse = g_engine->GetInputManager()->GetMouse();
		const float delta = static_cast< float >(delta_time);

		const int32_t mouse_delta_x = m_mouse->GetDeltaX();
		const int32_t mouse_delta_y = m_mouse->GetDeltaY();
		
		switch (m_axes) {

		case RotationAxes_MouseXAndY: {
			m_transform.ForEachTransform([&](Transform &transform) {
				const float rotation_x = transform.GetRotationX() + m_direction.x * mouse_delta_y * delta * m_sensitivity.x;
				const float rotation_y = transform.GetRotationY() + m_direction.y * mouse_delta_x * delta * m_sensitivity.y;
				transform.SetRotationX(ClampAngleRadians(rotation_x, m_minimum_rotation.x, m_maximum_rotation.x));
				transform.SetRotationY(ClampAngleRadians(rotation_y, m_minimum_rotation.y, m_maximum_rotation.y));
			});
			break;
		}
		case RotationAxes_MouseX: {
			m_transform.ForEachTransform([&](Transform &transform) {
				const float rotation_y = transform.GetRotationY() + m_direction.y * mouse_delta_x * delta * m_sensitivity.y;
				transform.SetRotationY(ClampAngleRadians(rotation_y, m_minimum_rotation.y, m_maximum_rotation.y));
			});
			break;
		}
		case RotationAxes_MouseY: {
			m_transform.ForEachTransform([&](Transform &transform) {
				const float rotation_x = transform.GetRotationX() + m_direction.x * mouse_delta_y * delta * m_sensitivity.x;
				transform.SetRotationX(ClampAngleRadians(rotation_x, m_minimum_rotation.x, m_maximum_rotation.x));
			});
			break;
		}
		}
	}
}