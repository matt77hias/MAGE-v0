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

	class SponzaScene final : public Scene {

	public:

		SponzaScene();

		SponzaScene(const SponzaScene &scene) = delete;

		SponzaScene(SponzaScene &&scene);

		virtual ~SponzaScene();

		SponzaScene &operator=(const SponzaScene &scene) = delete;

		SponzaScene &operator=(SponzaScene &&scene) = delete;

	private:

		virtual void Load() override;
	};
}