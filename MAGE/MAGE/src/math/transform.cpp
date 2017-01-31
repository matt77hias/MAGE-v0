//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\transform.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Transform::Transform(const CartesianCoordinateSystem &coordinate_system)
		: m_scale(XMFLOAT3(1.0f, 1.0f, 1.0f)), m_parent(nullptr) {

		// Calculate translation components.
		const XMVECTOR translation_v = coordinate_system.GetOrigin();
		XMStoreFloat3(&m_translation, translation_v);

		// Calculate rotation components.
		const float rotation_x = acosf(XMVectorGetByIndex(coordinate_system.GetAxisX(), 0));
		const float rotation_y = acosf(XMVectorGetByIndex(coordinate_system.GetAxisY(), 1));
		const float rotation_z = acosf(XMVectorGetByIndex(coordinate_system.GetAxisZ(), 2));
		SetRotation(rotation_x, rotation_y, rotation_z);
	}

	Transform::Transform(const Transform &transform)
		: Transform(transform.m_translation, transform.m_rotation, transform.m_scale) {

		transform.GetParent()->AddChild(this);
	}

	Transform::~Transform() {
		// Detach this node in both directions.
		if (GetParent()) {
			GetParent()->RemoveChild(this);
		}

		RemoveAllChilds();
	}

	Transform &Transform::operator=(const Transform &transform) {
		m_translation = transform.GetTranslation();
		m_rotation    = transform.GetRotation();
		m_scale       = transform.GetScale();
		Update();
		
		transform.GetParent()->AddChild(this);
		return (*this);
	}

	Transform *Transform::Clone() const {
		return new Transform(*this);
	}

	Transform *Transform::DeepClone() const {
		Transform *clone = Clone();

		for (set< Transform * >::const_iterator it = m_childs.cbegin(); it != m_childs.cend(); ++it) {
			Transform *cloned_child = (*it)->DeepClone();
			clone->AddChild(cloned_child);
		}

		return clone;
	}

	void Transform::AddChild(Transform *child) {
		if (!child || child->GetParent() == this) {
			return;
		}

		// Make sure the child is detached.
		if (child->GetParent()) {
			child->GetParent()->RemoveChild(child);
		}

		// Add the child to this parent.
		m_childs.insert(child);
		// Add this parent to the child.
		child->SetParent(this);

		child->Update();
	}

	void Transform::RemoveChild(Transform *child) {
		if (!child || child->GetParent() != this) {
			return;
		}

		// Remove this parent from the child.
		child->SetParent(nullptr);

		set< Transform * >::iterator it = m_childs.begin();
		while (it != m_childs.end()) {
			if ((*it) == child) {
				// Remove the child from this parent.
				it = m_childs.erase(it);
				break;
			}
			else {
				++it;
			}
		}

		child->Update();
	}

	void Transform::RemoveAllChilds() {
		set< Transform * >::iterator it = m_childs.begin();
		while (it != m_childs.end()) {
			// Remove this parent from the child.
			(*it)->SetParent(nullptr);

			// Destruct the child.
			delete (*it);

			// Remove this child from the parent.
			it = m_childs.erase(it);
		}
	}

	void Transform::Update() {
		if (GetParent()) {
			m_world_to_object = GetParentToObjectMatrix() * GetParent()->GetWorldToObjectMatrix();
			m_object_to_world = GetParent()->GetObjectToWorldMatrix() * GetObjectToParentMatrix();
		}
		else {
			m_world_to_object = GetParentToObjectMatrix();
			m_object_to_world = GetObjectToParentMatrix();
		}

		for (set< Transform * >::iterator it = m_childs.begin(); it != m_childs.end(); ++it) {
			(*it)->Update();
		}
	}
}