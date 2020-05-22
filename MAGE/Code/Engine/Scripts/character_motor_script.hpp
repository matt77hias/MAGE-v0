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

	class CharacterMotorScript : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		CharacterMotorScript();
		CharacterMotorScript(const CharacterMotorScript& script) noexcept;
		CharacterMotorScript(CharacterMotorScript&& script) noexcept;
		virtual ~CharacterMotorScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		CharacterMotorScript& operator=(
			const CharacterMotorScript& script) noexcept;
		CharacterMotorScript& operator=(
			CharacterMotorScript&& script) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Load([[maybe_unused]] Engine& engine) override;
		virtual void Update([[maybe_unused]] Engine& engine) override;

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