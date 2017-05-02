#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
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

		explicit FPSInputControllerScript(TransformNode *transform);
		FPSInputControllerScript(const FPSInputControllerScript &script) = delete;
		FPSInputControllerScript(FPSInputControllerScript &&script);
		virtual ~FPSInputControllerScript();

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