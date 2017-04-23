//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "world\world_object.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	WorldObject::WorldObject(const string &name)
		: m_name(name),
		m_transform(new Transform()), 
		m_childs() {}
	WorldObject::WorldObject(const WorldObject &world_object)
		: m_name(world_object.m_name),
		m_transform(new Transform(*world_object.m_transform)) {

		// Deep copy
		world_object.ForEachChild([&](const WorldObject &child) {
			SharedPtr< WorldObject > copy(child.Clone());
			AddChild(copy);
		});
	}
	WorldObject::~WorldObject() {
		RemoveAllChilds();
	}

	void WorldObject::UpdateTransform() {
		if (m_transform->IsDirty()) {
			m_transform->Update();
			UpdateChildTransforms(true);
		}
		else {
			UpdateChildTransforms(false);
		}
	}
	void WorldObject::UpdateTransform(const XMMATRIX &world_to_parent, const XMMATRIX &parent_to_world, bool dirty_ancestor) {
		if (dirty_ancestor || m_transform->IsDirty()) {
			m_transform->Update(world_to_parent, parent_to_world);
			UpdateChildTransforms(true);
		}
		else {
			UpdateChildTransforms(false);
		}
	}
	void WorldObject::UpdateChildTransforms(bool dirty_ancestor) {
		ForEachChild([&](WorldObject &child) {
			child.UpdateTransform(
				GetTransform()->GetWorldToObjectMatrix(),
				GetTransform()->GetObjectToWorldMatrix(),
				dirty_ancestor);
		});
	}

	bool WorldObject::HasChild(const SharedPtr< WorldObject > child) const {
		return std::find(m_childs.begin(), m_childs.end(), child) != m_childs.end();
	}
	void WorldObject::AddChild(SharedPtr< WorldObject > child) {
		if (!child) {
			return;
		}
		m_childs.push_back(child);
	}
	void WorldObject::RemoveChild(SharedPtr< WorldObject > child) {
		vector< SharedPtr< WorldObject > >::iterator it = std::find(m_childs.begin(), m_childs.end(), child);
		if (it != m_childs.end()) {
			m_childs.erase(it);
		}
	}
	void WorldObject::RemoveAllChilds() {
		m_childs.clear();
	}
}