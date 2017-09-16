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

	class ForrestScene final : public Scene {

	public:

		ForrestScene();

		ForrestScene(const ForrestScene &scene) = delete;

		ForrestScene(ForrestScene &&scene);

		virtual ~ForrestScene();

		ForrestScene &operator=(const ForrestScene &scene) = delete;

		ForrestScene &operator=(ForrestScene &&scene) = delete;

	private:

		virtual void Load() override;
	};
}