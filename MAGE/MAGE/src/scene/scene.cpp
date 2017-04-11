//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "model\meshmodel.hpp"
#include "light\point_light.hpp"
#include "text\sprite_text.hpp"
#include "sprite\sprite_image.hpp"
#include "scripting\behavior_script.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	bool Scene::HasScript(const SharedPtr< BehaviorScript > script) const {
		vector< SharedPtr< BehaviorScript > >::const_iterator it = m_scripts.cbegin();
		while (it != m_scripts.cend()) {
			if ((*it) == script) {
				return true;
			}
			else {
				++it;
			}
		}
		return false;
	}
	void Scene::AddScript(SharedPtr< BehaviorScript > script) {
		if (!script) {
			return;
		}

		m_scripts.push_back(script);
	}
	void Scene::RemoveScript(SharedPtr< BehaviorScript > script) {
		vector< SharedPtr< BehaviorScript > >::iterator it = m_scripts.begin();
		while (it != m_scripts.end()) {
			if ((*it) == script) {
				it = m_scripts.erase(it);
				break;
			}
			else {
				++it;
			}
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
	void Scene::Update(double elapsed_time) {
		// Update scripts.
		ForEachScript([elapsed_time](BehaviorScript &script) {
			script.Update(elapsed_time);
		});

		// Update and propagate transforms.
		m_camera->UpdateTransform();
		m_world->ForEachObject3D([](WorldObject &world_object) {
			world_object.UpdateTransform();
		});
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