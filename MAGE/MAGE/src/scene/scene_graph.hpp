#pragma once

namespace mage {

	class SceneNode {

	public:

		bool ContainsChild(SceneNode *child) const {
			return m_childs.find(child) != m_childs.cend();
		}

		void AddChild(SceneNode *child) {
			if (!child) {
				return;
			}

			// Add the child to this parent.
			m_childs.insert(child);
			// Add this parent to the child.
			child->SetParent(this);
		}

		void RemoveChild(SceneNode *child) {
			set< SceneNode * >::const_iterator it = m_childs.cbegin();
			while (it != m_childs.cend()) {
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

	protected:

		SceneNode();

	private:

		void SetParent(const SceneNode *parent) const {
			m_parent = parent;
		}
		
		mutable const SceneNode *m_parent;
		set< SceneNode * > m_childs;
	};
}

