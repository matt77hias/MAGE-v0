#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\script\behavior_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	class ManhattanMotorScript final : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		ManhattanMotorScript();
		ManhattanMotorScript(const ManhattanMotorScript& script) noexcept;
		ManhattanMotorScript(ManhattanMotorScript&& script) noexcept;
		virtual ~ManhattanMotorScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		ManhattanMotorScript& operator=(
			const ManhattanMotorScript& script) noexcept;
		ManhattanMotorScript& operator=(
			ManhattanMotorScript&& script) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Load([[maybe_unused]] Engine& engine) override;
		
		virtual void Update([[maybe_unused]] Engine& engine, 
							[[maybe_unused]] F64 delta_time) override;

		[[nodiscard]]
		F32 GetVelocity() const noexcept {
			return m_velocity;
		}

		void SetVelocity(F32 velocity) noexcept {
			m_velocity = velocity;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		F32 m_velocity;
	};
}