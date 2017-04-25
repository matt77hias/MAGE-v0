#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "script\manhattan_motor_script.hpp"
#include "script\mouse_look_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class ManhattanInputControllerScript final : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit ManhattanInputControllerScript(TransformNode *transform)
			: BehaviorScript(),
			m_orientation_script(new MouseLookScript(transform)),
			m_movement_script(new ManhattanMotorScript(transform)) {}
		ManhattanInputControllerScript(const ManhattanInputControllerScript &script) = delete;
		ManhattanInputControllerScript(ManhattanInputControllerScript &&script) = default;
		virtual ~ManhattanInputControllerScript() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		ManhattanInputControllerScript &operator=(const ManhattanInputControllerScript &script) = delete;
		ManhattanInputControllerScript &operator=(ManhattanInputControllerScript &&script) = delete;

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
		UniquePtr< ManhattanMotorScript > m_movement_script;
	};
}
