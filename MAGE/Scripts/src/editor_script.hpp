#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\script\behavior_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::script {

	class EditorScript final : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		EditorScript();
		EditorScript(const EditorScript& script) noexcept;
		EditorScript(EditorScript&& script) noexcept;
		virtual ~EditorScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		EditorScript& operator=(const EditorScript& script) noexcept;
		EditorScript& operator=(EditorScript&& script) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Update([[maybe_unused]] Engine& engine, 
							[[maybe_unused]] F64 delta_time) override;

		virtual void Close([[maybe_unused]] Engine& engine) override;
	};
}