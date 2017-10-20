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
		: m_scene(nullptr), 
		m_requested_scene(nullptr) {}

	SceneManager::SceneManager(SceneManager &&scene_behavior) = default;

	SceneManager::~SceneManager() = default;

	void SceneManager::ApplyRequestedScene() {
		Assert(m_requested_scene);
		
		if (m_scene) {
			m_scene->Uninitialize();
		}

		m_scene           = std::move(m_requested_scene);
		m_requested_scene = nullptr;

		if (m_scene) {
			m_scene->Initialize();
		}

		Engine::Get()->OnSceneChange();
	}

	void SceneManager::SetScene(UniquePtr< Scene > &&scene) {
		m_requested_scene = std::move(scene);

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

			if (!m_requested_scene) {
				script->Update(delta_time);
			}

		});

		if (m_requested_scene) {
			ApplyRequestedScene();
		}
	}

	void SceneManager::Render() const {
		Renderer::Get()->Render(GetScene());
	}
}