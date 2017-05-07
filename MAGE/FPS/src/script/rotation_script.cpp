//-----------------------------------------------------------------------------
// Game Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\rotation_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Game Definitions
//-----------------------------------------------------------------------------
namespace mage {

	RotationYScript::RotationYScript(TransformNode *transform)
		: BehaviorScript(), m_transform(transform) {}

	RotationYScript::RotationYScript(RotationYScript &&script) = default;

	RotationYScript::~RotationYScript() = default;

	void RotationYScript::Update(double delta_time) {
		m_transform->AddRotationY(static_cast< float >(delta_time));
	}
}