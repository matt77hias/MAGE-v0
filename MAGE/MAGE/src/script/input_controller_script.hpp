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
namespace mage::script {

	//-------------------------------------------------------------------------
	// InputControllerScript
	//-------------------------------------------------------------------------

	template< typename OrientationScriptT, typename MovementScriptT >
	class InputControllerScript final : public BehaviorScript {

	public:

		static_assert(
			std::is_base_of< BehaviorScript, OrientationScriptT >::value);
		static_assert(
			std::is_base_of< BehaviorScript, MovementScriptT >::value);

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit InputControllerScript(TransformNode *transform);
		InputControllerScript(const InputControllerScript &script) = delete;
		InputControllerScript(InputControllerScript &&script);
		virtual ~InputControllerScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		InputControllerScript &operator=(
			const InputControllerScript &script) = delete;
		InputControllerScript &operator=(
			InputControllerScript &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Update([[maybe_unused]] F64 delta_time) override {
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