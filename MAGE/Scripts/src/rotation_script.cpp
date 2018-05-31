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

	void RotationScript::Update([[maybe_unused]] Engine& engine) {
		const auto delta_time 
			= static_cast< F32 >(engine.GetTime().GetWallClockDeltaTime().count());
		
		switch (m_axis) {
		
		case RotationAxis::X: {
			GetOwner()->GetTransform().AddRotationX(delta_time);
			break;
		}
		
		case RotationAxis::Y: {
			GetOwner()->GetTransform().AddRotationY(delta_time);
			break; 
		}
		
		case RotationAxis::Z: {
			GetOwner()->GetTransform().AddRotationZ(delta_time);
			break;
		}
		}
	}
}