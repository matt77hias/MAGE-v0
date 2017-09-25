#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\character_motor_script.hpp"
#include "script\manhattan_motor_script.hpp"
#include "script\mouse_look_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// InputControllerScript
	//-------------------------------------------------------------------------

	template< typename OrientationScriptT, typename MovementScriptT >
	class InputControllerScript final : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit InputControllerScript(TransformNode *transform);
		InputControllerScript(
			const InputControllerScript< OrientationScriptT, MovementScriptT > &script) = delete;
		InputControllerScript(
			InputControllerScript< OrientationScriptT, MovementScriptT > &&script);
		virtual ~InputControllerScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		InputControllerScript< OrientationScriptT, MovementScriptT > &operator=(
			const InputControllerScript< OrientationScriptT, MovementScriptT > &script) = delete;
		InputControllerScript< OrientationScriptT, MovementScriptT > &operator=(
			InputControllerScript< OrientationScriptT, MovementScriptT > &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Update(f64 delta_time) override {
			m_orientation_script->Update(delta_time);
			m_movement_script->Update(delta_time);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		UniquePtr< OrientationScriptT > m_orientation_script;
		UniquePtr< MovementScriptT > m_movement_script;
	};

	//-------------------------------------------------------------------------
	// FPSInputControllerScript
	//-------------------------------------------------------------------------

	using FPSInputControllerScript 
		= InputControllerScript< MouseLookScript, CharacterMotorScript >;

	//-------------------------------------------------------------------------
	// ManhattanInputControllerScript
	//-------------------------------------------------------------------------

	using ManhattanInputControllerScript 
		= InputControllerScript< MouseLookScript, ManhattanMotorScript >;
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\input_controller_script.tpp"

#pragma endregion