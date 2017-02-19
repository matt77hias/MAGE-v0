//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\transform.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Transform::Transform(const CartesianCoordinateSystem &coordinate_system)
		: m_scale(XMFLOAT3(1.0f, 1.0f, 1.0f)) {

		// Calculate translation components.
		const XMVECTOR translation_v = coordinate_system.GetOrigin();
		XMStoreFloat3(&m_translation, translation_v);

		// Calculate rotation components.
		const float rotation_x = acosf(XMVectorGetByIndex(coordinate_system.GetAxisX(), 0));
		const float rotation_y = acosf(XMVectorGetByIndex(coordinate_system.GetAxisY(), 1));
		const float rotation_z = acosf(XMVectorGetByIndex(coordinate_system.GetAxisZ(), 2));
		m_rotation = XMFLOAT3(rotation_x, rotation_y, rotation_z);

		const XMMATRIX &identity = XMMatrixIdentity();
		Update(identity, identity);
	}

	void Transform::AddChild(SharedPtr< Transform > child) {
		Assert(child);
		m_childs.insert(child);
		child->Update(m_world_to_object, m_object_to_world);
	}

	void Transform::RemoveChild(SharedPtr< Transform > child) {
		set< SharedPtr< Transform > >::const_iterator it = m_childs.begin();
		while (it != m_childs.cend()) {
			if ((*it) == child) {
				it = m_childs.erase(it);
				const XMMATRIX &identity = XMMatrixIdentity();
				child->Update(identity, identity);
				break;
			}
			else {
				++it;
			}
		}
	}

	void Transform::Update() {
		m_world_to_object = GetParentToObjectMatrix() * m_world_to_parent;
		m_object_to_world = m_parent_to_world * GetObjectToParentMatrix();
		
		for (set< SharedPtr< Transform > >::iterator it = m_childs.begin(); it != m_childs.end(); ++it) {
			(*it)->Update(m_world_to_object, m_object_to_world);
		}
	}
}