#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Game Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class CornellScene : public Scene {

	public:

		CornellScene();

		CornellScene(const CornellScene& scene) = delete;

		CornellScene(CornellScene&& scene);

		virtual ~CornellScene();

		CornellScene& operator=(const CornellScene& scene) = delete;

		CornellScene& operator=(CornellScene&& scene) = delete;

	private:

		virtual void Load([[maybe_unused]] Engine& engine) override;
	};
}