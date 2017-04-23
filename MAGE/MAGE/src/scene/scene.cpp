//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	bool Scene::HasScript(const SharedPtr< BehaviorScript > script) const {
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

		// Update and propagate transforms.
		UpdateTransforms();
	}
	void Scene::UpdateTransforms() {
		// Update the camera transform.
		m_camera->UpdateTransform();
		// Update the model transforms.
		m_world->ForEachModel([](Model &model) {
			model.UpdateTransform();
		});
		// Update the light transforms. 
		m_world->ForEachLight([](Light &light) {
			light.UpdateTransform();
		});
	}
	void Scene::Update(double delta_time) {
		// Update scripts.
		ForEachScript([delta_time](BehaviorScript &script) {
			script.Update(delta_time);
		});

		// Update and propagate transforms.
		UpdateTransforms();
	}
	void Scene::Render2D() const {
		m_world->Render2D();
	}
	void Scene::Render3D() const {
		TransformBuffer transform_buffer(*m_camera);
		m_world->Render3D(transform_buffer);
	}
	void Scene::Uninitialize() {
		// Close scene.
		Close();
		
		RemoveAllScripts();
		m_world->Clear();
		m_camera.reset();
	}
}