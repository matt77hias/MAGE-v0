#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Game Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class RotationYScript final : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		RotationYScript(TransformNode *transform);
		RotationYScript(const RotationYScript &script) = delete;
		RotationYScript(RotationYScript &&script);
		virtual ~RotationYScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		RotationYScript &operator=(const RotationYScript &script) = delete;
		RotationYScript &operator=(RotationYScript &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Update(double delta_time) override;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		TransformNode * const m_transform;
	};
}