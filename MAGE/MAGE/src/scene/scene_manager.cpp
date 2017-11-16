//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SceneManager *SceneManager::Get() noexcept {
		Assert(Engine::Get());

		return Engine::Get()->GetSceneManager();
	}

	SceneManager::SceneManager()
		: m_scene(), 
		m_requested_scene(), 
		m_has_requested_scene(false) {}

	SceneManager::SceneManager(SceneManager &&scene_behavior) = default;

	SceneManager::~SceneManager() = default;

	void SceneManager::ApplyRequestedScene() {
		if (m_scene) {
			m_scene->Uninitialize();
		}

		m_scene               = std::move(m_requested_scene);
		m_requested_scene     = nullptr;
		m_has_requested_scene = false;

		if (m_scene) {
			m_scene->Initialize();
		}

		Engine::Get()->OnSceneChange();
	}

	void SceneManager::SetScene(UniquePtr< Scene > &&scene) {
		m_requested_scene     = std::move(scene);
		m_has_requested_scene = true;

		if (!m_scene) {
			ApplyRequestedScene();
		}
	}

	void SceneManager::FixedUpdate() {
		m_scene->ForEachScript([this](BehaviorScript *script) {
			script->FixedUpdate();
		});
	}

	void SceneManager::Update(F64 delta_time) {
		m_scene->ForEachScript([this, delta_time](BehaviorScript *script) {

			if (!m_has_requested_scene) {
				script->Update(delta_time);
			}

		});

		if (m_has_requested_scene) {
			ApplyRequestedScene();
		}
	}

	void SceneManager::Render() const {
		Renderer::Get()->Render(GetScene());
	}
}