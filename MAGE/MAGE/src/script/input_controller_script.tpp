#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	template< typename OrientationScriptT, typename MovementScriptT >
	InputControllerScript< OrientationScriptT, MovementScriptT >
		::InputControllerScript(TransformNode *transform)
		: BehaviorScript(),
		m_orientation_script(MakeUnique< OrientationScriptT >(transform)),
		m_movement_script(MakeUnique< MovementScriptT >(transform)) {}

	template< typename OrientationScriptT, typename MovementScriptT >
	InputControllerScript< OrientationScriptT, MovementScriptT >
		::InputControllerScript(InputControllerScript &&script) = default;

	template< typename OrientationScriptT, typename MovementScriptT >
	InputControllerScript< OrientationScriptT, MovementScriptT >
		::~InputControllerScript() = default;
}