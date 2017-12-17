//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\rotation_script.hpp"
#include "scene\scene.hpp"
#include "utils\exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	RotationScript::RotationScript()
		: BehaviorScript(), 
		m_axis(RotationAxis::Y) {}

	RotationScript::RotationScript(const RotationScript &script) noexcept = default;

	RotationScript::RotationScript(RotationScript &&script) noexcept = default;

	RotationScript::~RotationScript() = default;

	void RotationScript::Load() {
		ThrowIfFailed((nullptr != GetOwner()),
			"This script needs to be attached to a node.");
	}

	void RotationScript::Update([[maybe_unused]] F64 delta_time) {
		switch (m_axis) {
		
		case RotationAxis::X: {
			GetOwner()->GetTransform().AddRotationX(
				static_cast< F32 >(delta_time));
			
			break;
		}
		
		case RotationAxis::Y: {
			GetOwner()->GetTransform().AddRotationY(
				static_cast< F32 >(delta_time));
			
			break; 
		}
		
		case RotationAxis::Z: {
			GetOwner()->GetTransform().AddRotationZ(
				static_cast< F32 >(delta_time));
			
			break;
		}
		}
	}
}