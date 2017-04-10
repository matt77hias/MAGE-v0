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
	void Scene::AddScript(SharedPtr< BehaviorScript > script, bool load) {
		if (!script) {
			return;
		}

		m_scripts.push_back(script);

		if (load) {
			script->Load();
		}
	}
	void Scene::RemoveScript(SharedPtr< BehaviorScript > script, bool close) {
		vector< SharedPtr< BehaviorScript > >::iterator it = m_scripts.begin();
		while (it != m_scripts.end()) {
			if ((*it) == script) {
				if (close) {
					(*it)->Close();
				}
				it = m_scripts.erase(it);
				break;
			}
			else {
				++it;
			}
		}
	}
	void Scene::RemoveAllScripts(bool close) {
		vector< SharedPtr< BehaviorScript > >::iterator it = m_scripts.begin();
		if (close) {
			while (it != m_scripts.end()) {
				(*it)->Close();
				it = m_scripts.erase(it);
			}
		}
		else {
			while (it != m_scripts.end()) {
				it = m_scripts.erase(it);
			}
		}
	}

	void Scene::Load() {
		ForEachScript([](BehaviorScript &script) {
			script.Load();
		});
	}
	void Scene::Update(double elapsed_time) {
		// Update scripts.
		ForEachScript([&](BehaviorScript &script) {
			script.Update(elapsed_time, *this);
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
		TransformBuffer transform_buffer(GetCamera());
		m_world->Render3D(transform_buffer);
	}
	void Scene::Close() {
		RemoveAllScripts(true);
	}
}