//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "world\world_object.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	WorldObject::WorldObject(const string &name)
		: m_name(name),
		m_transform(new Transform()) {}
	WorldObject::WorldObject(const WorldObject &world_object)
		: m_name(world_object.m_name),
		m_transform(new Transform(*world_object.m_transform)) {}

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
		UNUSED(dirty_ancestor);
	}
}