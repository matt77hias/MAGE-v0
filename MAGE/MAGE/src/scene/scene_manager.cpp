//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SceneManager::SceneManager()
		: m_renderer(MakeUnique< SceneRenderer >()), m_scene() {}

	SceneManager::SceneManager(SceneManager &&scene_behavior) = default;

	SceneManager::~SceneManager() = default;

	void SceneManager::SetScene(UniquePtr< Scene > &&scene) {
		if (m_scene) {
			m_scene->Uninitialize();
		}

		m_scene = std::move(scene);

		if (m_scene) {
			m_scene->Initialize();
		}

		Engine::Get()->OnSceneChange();
	}
}