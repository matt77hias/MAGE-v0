#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class SceneNode {

	public:

		virtual ~SceneNode() {
			
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

		bool ContainsChild(SceneNode *child) const {
			return m_childs.find(child) != m_childs.cend();
		}

		void AddChild(SceneNode *child) {
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

		void RemoveChild(SceneNode *child) {
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
	
		size_t GetNbOfChilds() const {
			return m_childs.size();
		}

		virtual Transform &GetTransform() = 0;
		virtual const Transform &GetTransform() const = 0;

	protected:

		SceneNode() : m_parent(nullptr), m_childs(set< SceneNode * >()) {}

	private:

		void SetParent(SceneNode *parent) {
			m_parent = parent;
		}
		
		SceneNode *m_parent;
		set< SceneNode * > m_childs;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\camera_node.hpp"

#pragma endregion