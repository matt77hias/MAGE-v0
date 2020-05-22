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

	class VoxelGridAnchorScript : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		VoxelGridAnchorScript();
		VoxelGridAnchorScript(const VoxelGridAnchorScript& script) noexcept;
		VoxelGridAnchorScript(VoxelGridAnchorScript&& script) noexcept;
		virtual ~VoxelGridAnchorScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		VoxelGridAnchorScript& operator=(
			const VoxelGridAnchorScript& script) noexcept;
		VoxelGridAnchorScript& operator=(
			VoxelGridAnchorScript&& script) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Load([[maybe_unused]] Engine& engine) override;
		virtual void Update([[maybe_unused]] Engine& engine) override;
	};
}