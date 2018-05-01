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

	class SibenikScene : public Scene {

	public:

		SibenikScene();

		SibenikScene(const SibenikScene& scene) = delete;

		SibenikScene(SibenikScene&& scene);

		virtual ~SibenikScene();

		SibenikScene& operator=(const SibenikScene& scene) = delete;

		SibenikScene& operator=(SibenikScene&& scene) = delete;

	private:

		virtual void Load([[maybe_unused]] Engine& engine) override;
	};
}