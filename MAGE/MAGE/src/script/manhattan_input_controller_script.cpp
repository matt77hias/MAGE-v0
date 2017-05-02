//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\manhattan_input_controller_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	ManhattanInputControllerScript::ManhattanInputControllerScript(TransformNode *transform)
		: BehaviorScript(),
		m_orientation_script(new MouseLookScript(transform)),
		m_movement_script(new ManhattanMotorScript(transform)) {}
	
	ManhattanInputControllerScript::ManhattanInputControllerScript(ManhattanInputControllerScript &&script) = default;
	
	ManhattanInputControllerScript::~ManhattanInputControllerScript() = default;
}