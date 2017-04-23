#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\character_motor_script.hpp"
#include "script\mouse_look_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class FPSInputControllerScript final : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit FPSInputControllerScript(const TransformGroup &transform)
			: BehaviorScript(),
			m_orientation_script(new MouseLookScript(transform)), 
			m_movement_script(new CharacterMotorScript(transform)) {}
		FPSInputControllerScript(const FPSInputControllerScript &script) = delete;
		FPSInputControllerScript(FPSInputControllerScript &&script) = default;
		virtual ~FPSInputControllerScript() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		FPSInputControllerScript &operator=(const FPSInputControllerScript &script) = delete;
		FPSInputControllerScript &operator=(FPSInputControllerScript &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Update(double delta_time) override {
			m_orientation_script->Update(delta_time);
			m_movement_script->Update(delta_time);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		UniquePtr< MouseLookScript > m_orientation_script;
		UniquePtr< CharacterMotorScript > m_movement_script;
	};
}