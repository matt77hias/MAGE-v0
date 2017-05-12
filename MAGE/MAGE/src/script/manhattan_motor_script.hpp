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

	class ManhattanMotorScript final : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit ManhattanMotorScript(TransformNode *transform);
		ManhattanMotorScript(const ManhattanMotorScript &script) = delete;
		ManhattanMotorScript(ManhattanMotorScript &&script);
		virtual ~ManhattanMotorScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		ManhattanMotorScript &operator=(const ManhattanMotorScript &script) = delete;
		ManhattanMotorScript &operator=(ManhattanMotorScript &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Update(double delta_time) override;

		float GetVelocity() const noexcept {
			return m_velocity;
		}
		void SetVelocity(float velocity) noexcept {
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