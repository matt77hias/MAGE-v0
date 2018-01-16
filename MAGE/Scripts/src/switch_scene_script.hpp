#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\behavior_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::script {

	template< typename SceneT >
	class SwitchSceneScript final : public BehaviorScript {

	public:

		static_assert(std::is_base_of< Scene, SceneT >::value);

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		SwitchSceneScript();
		SwitchSceneScript(const SwitchSceneScript &script) noexcept;
		SwitchSceneScript(SwitchSceneScript &&script) noexcept;
		virtual ~SwitchSceneScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		SwitchSceneScript &operator=(const SwitchSceneScript &script) = delete;
		SwitchSceneScript &operator=(SwitchSceneScript &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Update([[maybe_unused]] F64 delta_time) override;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "switch_scene_script.tpp"

#pragma endregion