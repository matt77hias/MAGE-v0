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

	template< typename SceneT >
	class SwitchSceneScript : public BehaviorScript {

	public:

		static_assert(std::is_base_of< Scene, SceneT >::value);

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		SwitchSceneScript();
		SwitchSceneScript(const SwitchSceneScript& script) noexcept;
		SwitchSceneScript(SwitchSceneScript&& script) noexcept;
		virtual ~SwitchSceneScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		SwitchSceneScript& operator=(const SwitchSceneScript& script) noexcept;
		SwitchSceneScript& operator=(SwitchSceneScript&& script) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Update([[maybe_unused]] Engine& engine) override;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "switch_scene_script.tpp"

#pragma endregion