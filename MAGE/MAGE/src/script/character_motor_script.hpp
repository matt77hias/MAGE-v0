#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\behavior_script.hpp"
#include "math\transform_node.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class CharacterMotorScript final : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------
		
		explicit CharacterMotorScript(TransformNode *transform);
		CharacterMotorScript(const CharacterMotorScript &script) = delete;
		CharacterMotorScript(CharacterMotorScript &&script);
		virtual ~CharacterMotorScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		CharacterMotorScript &operator=(const CharacterMotorScript &script) = delete;
		CharacterMotorScript &operator=(CharacterMotorScript &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Update(double delta_time) override;

		float GetVelocity() const {
			return m_velocity;
		}
		void SetVelocity(float velocity) {
			m_velocity = velocity;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		TransformNode * const m_transform;
		float m_velocity;
	};
}