//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_manager.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SceneManager::SceneManager() = default;

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
	}
}