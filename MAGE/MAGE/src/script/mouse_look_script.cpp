//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\mouse_look_script.hpp"
#include "input\mouse.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	MouseLookScript::MouseLookScript(TransformNode *transform,
		RotationAxes axes, 
		const XMFLOAT2 &sensitivity,
		const XMFLOAT2 &minimum_rotation, 
		const XMFLOAT2 &maximum_rotation,
		const XMFLOAT2 &direction)
		: BehaviorScript(),
		m_transform(transform),
		m_axes(axes),
		m_sensitivity(sensitivity),
		m_minimum_rotation(minimum_rotation),
		m_maximum_rotation(maximum_rotation),
		m_direction(direction) {

		Assert(m_transform);
	}
	
	MouseLookScript::MouseLookScript(MouseLookScript &&script) = default;
	
	MouseLookScript::~MouseLookScript() = default;

	void MouseLookScript::Update([[maybe_unused]] F64 delta_time) {
		const Mouse * const mouse = Mouse::Get();

		switch (m_axes) {

		case RotationAxes::MouseXAndY: {
			
			const F64 rotation_x 
				= m_direction.x * mouse->GetDeltaY() * delta_time * m_sensitivity.x;
			const F64 rotation_y 
				= m_direction.y * mouse->GetDeltaX() * delta_time * m_sensitivity.y;
			m_transform->AddAndClampRotationX(static_cast< F32 >(rotation_x), 
												m_minimum_rotation.x, 
												m_maximum_rotation.x);
			m_transform->AddAndClampRotationY(static_cast< F32 >(rotation_y), 
												m_minimum_rotation.y, 
												m_maximum_rotation.y);
			break;
		}
		
		case RotationAxes::MouseX: {
			
			const F64 rotation_y 
				= m_direction.y * mouse->GetDeltaX() * delta_time * m_sensitivity.y;
			m_transform->AddAndClampRotationY(static_cast< F32 >(rotation_y), 
												m_minimum_rotation.y, 
												m_maximum_rotation.y);
			break;
		}
		
		case RotationAxes::MouseY: {
			
			const F64 rotation_x 
				= m_direction.x * mouse->GetDeltaY() * delta_time * m_sensitivity.x;
			m_transform->AddAndClampRotationX(static_cast< F32 >(rotation_x), 
												m_minimum_rotation.x, 
												m_maximum_rotation.x);
			break;
		}
		}
	}
}