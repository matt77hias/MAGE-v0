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

	class SibenikScene final : public Scene {

	public:

		SibenikScene();

		SibenikScene(const SibenikScene &scene) = delete;

		SibenikScene(SibenikScene &&scene);

		virtual ~SibenikScene();

		SibenikScene &operator=(const SibenikScene &scene) = delete;

		SibenikScene &operator=(SibenikScene &&scene) = delete;

	private:

		virtual void Load() override;
	};
}