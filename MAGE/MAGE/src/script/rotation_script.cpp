//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\rotation_script.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	RotationScript::RotationScript(TransformNode *transform, RotationAxis axis)
		: BehaviorScript(), m_transform(transform), m_axis(axis) {

		Assert(m_transform);
	}

	RotationScript::RotationScript(RotationScript &&script) = default;

	RotationScript::~RotationScript() = default;

	void RotationScript::Update(f64 delta_time) {

		switch (m_axis) {
		
		case RotationAxis::X: {
			m_transform->AddRotationX(static_cast< float >(delta_time));
			break;
		}
		case RotationAxis::Y: {
			m_transform->AddRotationY(static_cast< float >(delta_time));
			break; 
		}
		case RotationAxis::Z: {
			m_transform->AddRotationZ(static_cast< float >(delta_time));
			break;
		}
		}
	}
}