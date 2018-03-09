//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rotation_script.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	RotationScript::RotationScript()
		: BehaviorScript(), 
		m_axis(RotationAxis::Y) {}

	RotationScript::RotationScript(
		const RotationScript& script) noexcept = default;

	RotationScript::RotationScript(
		RotationScript&& script) noexcept = default;

	RotationScript::~RotationScript() = default;

	RotationScript& RotationScript
		::operator=(const RotationScript& script) noexcept = default;
	
	RotationScript& RotationScript
		::operator=(RotationScript&& script) noexcept = default;

	void RotationScript::Load([[maybe_unused]] Engine& engine) {
		ThrowIfFailed(HasOwner(), 
					  "This script needs to be attached to a node.");
	}

	void RotationScript::Update([[maybe_unused]] Engine& engine, 
								[[maybe_unused]] F64 delta_time) {
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