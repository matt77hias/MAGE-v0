//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\fps_input_controller_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	FPSInputControllerScript::FPSInputControllerScript(TransformNode *transform)
		: BehaviorScript(),
		m_orientation_script(new MouseLookScript(transform)),
		m_movement_script(new CharacterMotorScript(transform)) {}
	
	FPSInputControllerScript::FPSInputControllerScript(FPSInputControllerScript &&script) = default;
	
	FPSInputControllerScript::~FPSInputControllerScript() = default;
}