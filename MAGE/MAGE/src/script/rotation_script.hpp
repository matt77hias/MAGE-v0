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
namespace mage::script {

	class RotationScript final : public BehaviorScript {

	public:

		enum struct RotationAxis {
			X = 0,
			Y = 1,
			Z = 2,
		};

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		RotationScript(TransformNode *transform,
			RotationAxis axis = RotationAxis::Y);
		RotationScript(const RotationScript &script) = delete;
		RotationScript(RotationScript &&script);
		virtual ~RotationScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		RotationScript &operator=(const RotationScript &script) = delete;
		RotationScript &operator=(RotationScript &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Update([[maybe_unused]] F64 delta_time) override;

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

		TransformNode * const m_transform;
		RotationAxis m_axis;
	};
}
