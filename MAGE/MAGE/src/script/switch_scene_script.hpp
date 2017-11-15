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

	template< typename SceneT >
	class SwitchSceneScript final : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit SwitchSceneScript< SceneT >();
		SwitchSceneScript(const SwitchSceneScript< SceneT > &script) = delete;
		SwitchSceneScript(SwitchSceneScript< SceneT > &&script);
		virtual ~SwitchSceneScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		SwitchSceneScript< SceneT > &operator=(
			const SwitchSceneScript< SceneT > &script) = delete;
		SwitchSceneScript< SceneT > &operator=(
			SwitchSceneScript< SceneT > &&script) = delete;

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

#include "script\switch_scene_script.tpp"

#pragma endregion