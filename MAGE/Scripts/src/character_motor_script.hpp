#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\behavior_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	class CharacterMotorScript final : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------
		
		CharacterMotorScript();
		CharacterMotorScript(const CharacterMotorScript &script) noexcept;
		CharacterMotorScript(CharacterMotorScript &&script) noexcept;
		virtual ~CharacterMotorScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		CharacterMotorScript &operator=(
			const CharacterMotorScript &script) = delete;
		CharacterMotorScript &operator=(
			CharacterMotorScript &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Load() override;
		virtual void Update([[maybe_unused]] F64 delta_time) override;

		[[nodiscard]]F32 GetVelocity() const noexcept {
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