//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "resource\resource_factory.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Scene::Scene(const string &name)
		: m_name(name),
		m_world(new World(GetRenderingDevice(), GetRenderingDeviceContext())),
		m_scripts() {}

	bool Scene::HasScript(SharedPtr< const BehaviorScript > script) const {
		return std::find(m_scripts.begin(), m_scripts.end(), script) != m_scripts.end();
	}
	void Scene::AddScript(SharedPtr< BehaviorScript > script) {
		if (!script) {
			return;
		}

		m_scripts.push_back(script);
	}
	void Scene::RemoveScript(SharedPtr< BehaviorScript > script) {
		vector< SharedPtr< BehaviorScript > >::iterator it = std::find(m_scripts.begin(), m_scripts.end(), script);
		if (it != m_scripts.end()) {
			m_scripts.erase(it);
		}
	}
	void Scene::RemoveAllScripts() {
		vector< SharedPtr< BehaviorScript > >::iterator it = m_scripts.begin();
		m_scripts.clear();
	}

	void Scene::Initialize() {
		// Load scene.
		Load();
	}
	void Scene::Uninitialize() {
		// Close scene.
		Close();
		
		RemoveAllScripts();
		m_world->Clear();
	}
}