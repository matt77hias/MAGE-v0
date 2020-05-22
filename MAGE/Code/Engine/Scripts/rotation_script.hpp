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

	class RotationScript : public BehaviorScript {

	public:

		enum class RotationAxis : U8 {
			X = 0,
			Y = 1,
			Z = 2,
		};

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		RotationScript();
		RotationScript(const RotationScript& script) noexcept;
		RotationScript(RotationScript&& script) noexcept;
		virtual ~RotationScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		RotationScript& operator=(const RotationScript& script) noexcept;
		RotationScript& operator=(RotationScript&& script) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Load([[maybe_unused]] Engine& engine) override;
		virtual void Update([[maybe_unused]] Engine& engine) override;

		[[nodiscard]]
		RotationAxis GetRotationAxis() const noexcept {
			return m_axis;
		}

		void SetRotationAxis(RotationAxis axis) noexcept {
			m_axis = axis;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		RotationAxis m_axis;
	};
}
