//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void Transform::SetDirty() const noexcept {
		m_dirty_object_to_world = true;
		m_dirty_world_to_object = true;

		if (HasOwner()) {
			m_owner->ForEachChild([](const Node &node) noexcept {
				node.GetTransform().SetDirty();
			});
		}
	}

	void Transform::UpdateObjectToWorldMatrix() const noexcept {
		if (m_dirty_object_to_world) {
			m_dirty_object_to_world = false;

			Assert(HasOwner());
			const auto parent = m_owner->GetParent();
			
			if (nullptr != parent) {
				m_object_to_world = GetObjectToParentMatrix() 
					              * parent->GetTransform().GetObjectToWorldMatrix();
			}
			else {
				m_object_to_world = GetObjectToParentMatrix();
			}
		}
	}

	void Transform::UpdateWorldToObjectMatrix() const noexcept {
		if (m_dirty_world_to_object) {
			m_dirty_world_to_object = false;

			Assert(HasOwner());
			const auto parent = m_owner->GetParent();
			
			if (nullptr != parent) {
				m_world_to_object = parent->GetTransform().GetWorldToObjectMatrix() 
					              * GetParentToObjectMatrix();
			}
			else {
				m_world_to_object = GetParentToObjectMatrix();
			}
		}
	}
}