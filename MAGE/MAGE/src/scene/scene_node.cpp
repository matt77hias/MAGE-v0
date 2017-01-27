//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_node.hpp"
#include "scene\scene_node_visitor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SceneNode::~SceneNode() {

		// Detach this node in both directions.
		if (m_parent) {
			m_parent->RemoveChild(this);
		}

		// Detach the childs in one direction.
		for (set< SceneNode * >::iterator it = m_childs.begin(); it != m_childs.end(); ++it) {
			(*it)->SetParent(nullptr);
		}

		// Destructs the childs.
		m_childs.clear();
	}

	SceneNode *SceneNode::DeepClone() const {
		SceneNode *clone = Clone();

		for (set< SceneNode * >::const_iterator it = m_childs.cbegin(); it != m_childs.cend(); ++it) {
			SceneNode *cloned_child = (*it)->DeepClone();
			clone->AddChild(cloned_child);
		}

		return clone;
	}

	void SceneNode::AddChild(SceneNode *child) {
		if (!child) {
			return;
		}

		// Make sure the child is detached.
		if (child->m_parent) {
			child->m_parent->RemoveChild(child);
		}

		// Add the child to this parent.
		m_childs.insert(child);
		// Add this parent to the child.
		child->SetParent(this);
	}

	void SceneNode::RemoveChild(SceneNode *child) {
		if (!child) {
			return;
		}

		set< SceneNode * >::iterator it = m_childs.begin();
		while (it != m_childs.end()) {
			if ((*it) == child) {
				// Remove this parent from the child.
				child->SetParent(nullptr);
				// Remove the child from this parent.
				m_childs.erase(it++);
				break;
			}
			else {
				++it;
			}
		}
	}

	XMMATRIX SceneNode::GetWorldToObjectMatrix() const {
		XMMATRIX transformation = GetParentToObjectMatrix();
		const SceneNode *current_node = m_parent;
		while (current_node) {
			transformation = transformation * current_node->GetParentToObjectMatrix();
			current_node = current_node->m_parent;
		}
		return transformation;
	}

	XMMATRIX SceneNode::GetObjectToWorldMatrix() const {
		XMMATRIX transformation = GetParentToWorldMatrix();
		const SceneNode *current_node = m_parent;
		while (current_node) {
			transformation = current_node->GetParentToWorldMatrix() * transformation;
			current_node = current_node->m_parent;
		}
		return transformation;
	}

	void SceneNode::AcceptRecursive(SceneNodeVisitor &visitor) {
		Accept(visitor);
		// Pass visitor to childs.
		for (set< SceneNode * >::iterator it = m_childs.begin(); it != m_childs.end(); ++it) {
			if (visitor.IsVisitTerminated()) {
				return;
			}
			(*it)->AcceptRecursive(visitor);
		}
	}

	void SceneNode::AcceptRecursive(SceneNodeVisitor &visitor) const {
		Accept(visitor);
		// Pass visitor to childs.
		for (set< SceneNode * >::const_iterator it = m_childs.cbegin(); it != m_childs.cend(); ++it) {
			if (visitor.IsVisitTerminated()) {
				return;
			}
			(*it)->AcceptRecursive(visitor);
		}
	}
}