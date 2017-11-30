//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\mouse_look_script.hpp"
#include "input\mouse.hpp"
#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	MouseLookScript::MouseLookScript(TransformNode *transform,
		RotationAxes axes, 
		F32x2 sensitivity,
		F32x2 minimum_rotation, 
		F32x2 maximum_rotation,
		F32x2 direction)
		: BehaviorScript(),
		m_transform(transform),
		m_axes(axes),
		m_sensitivity(std::move(sensitivity)),
		m_minimum_rotation(std::move(minimum_rotation)),
		m_maximum_rotation(std::move(maximum_rotation)),
		m_direction(std::move(direction)) {

		Assert(m_transform);
	}
	
	MouseLookScript::MouseLookScript(MouseLookScript &&script) = default;
	
	MouseLookScript::~MouseLookScript() = default;

	void MouseLookScript::Update([[maybe_unused]] F64 delta_time) {
		const Mouse * const mouse = Mouse::Get();

		switch (m_axes) {

		case RotationAxes::MouseXAndY: {
			
			const F64 rotation_x = m_direction.m_x * mouse->GetDeltaY() * delta_time 
				                 * m_sensitivity.m_x;
			const F64 rotation_y = m_direction.m_y * mouse->GetDeltaX() * delta_time 
				                 * m_sensitivity.m_y;
			m_transform->AddAndClampRotationX(static_cast< F32 >(rotation_x),
				                              m_minimum_rotation.m_x,
				                              m_maximum_rotation.m_x);
			m_transform->AddAndClampRotationY(static_cast< F32 >(rotation_y), 
				                              m_minimum_rotation.m_y,
				                              m_maximum_rotation.m_y);
			break;
		}
		
		case RotationAxes::MouseX: {
			
			const F64 rotation_y = m_direction.m_y * mouse->GetDeltaX() * delta_time 
				                 * m_sensitivity.m_y;
			m_transform->AddAndClampRotationY(static_cast< F32 >(rotation_y), 
				                              m_minimum_rotation.m_y,
				                              m_maximum_rotation.m_y);
			break;
		}
		
		case RotationAxes::MouseY: {
			
			const F64 rotation_x = m_direction.m_x * mouse->GetDeltaY() * delta_time 
				                 * m_sensitivity.m_x;
			m_transform->AddAndClampRotationX(static_cast< F32 >(rotation_x), 
				                              m_minimum_rotation.m_x,
				                              m_maximum_rotation.m_x);
			break;
		}
		}
	}
}