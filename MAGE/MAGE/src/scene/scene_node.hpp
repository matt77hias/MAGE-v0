#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of scene nodes.
	 */
	class SceneNode {

	public:

		/**
		 Destructs this scene node.
		 */
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

		/**
		 Returns the parent scene node of this scene node.

		 @return		@c nullptr if this scene node has no parent scene node
						(i.e. this scene node is a root node).
		 @return		A pointer to the parent scene node of this scene node.
		 */
		SceneNode *GetParent() const {
			return m_parent;
		}
		
		/**
		 Checks whether this scene node contains the given scene node as a child scene node.

		 @return		@c true if this scene node contains the given scene node as a child scene node.
						@c false otherwise.
		 */
		bool ContainsChild(const SceneNode *child) const {
			return m_childs.find(child) != m_childs.cend();
		}

		/**
		 Adds the given child scene node to the child scene nodes of this scene node.
		 If the given child scene node has already a parent scene node, it is removed
		 from that node since scene nodes may only have at most one parent scene node.

		 @param[in]		child
						A pointer to the child scene node.
		 */
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
		
		/**
		 Removes the given child scene node from the child scene nodes of this scene node.

		 @param[in]		child
						A pointer to the child scene node.
		 */
		void RemoveChild(SceneNode *child) {
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
		
		/**
		 Returns the total number of child scene nodes of this scene node.

		 @return		The total number of child scene nodes of this scene node.
		 */
		size_t GetNbOfChilds() const {
			return m_childs.size();
		}

		/**
		 Returns the transform of this scene node.

		 @return		The transform of this scene node.
		 */
		Transform &GetTransform() {
			return m_transform;
		}

		/**
		 Returns the transform of this scene node.

		 @return		The transform of this scene node.
		 */
		const Transform &GetTransform() const {
			return m_transform;
		}
		
		/**
		 Returns the parent-to-object matrix of this scene node.

		 @return		The parent-to-object matrix of this scene node.
		 */
		XMMATRIX GetParentToObjectMatrix() const {
			return GetTransform().GetWorldToObjectMatrix();
		}

		/**
		 Returns the object-to-parent matrix of this scene node.

		 @return		The object-to-parent matrix of this scene node.
		 */
		XMMATRIX GetParentToWorldMatrix() const {
			return GetTransform().GetObjectToWorldMatrix();
		}

		/**
		 Returns the world-to-object matrix of this scene node.

		 @return		The world-to-object matrix of this scene node.
		 */
		XMMATRIX GetWorldToObjectMatrix() const {
			XMMATRIX transformation = GetParentToObjectMatrix();
			const SceneNode *current_node = m_parent;
			while (current_node) {
				transformation = transformation * current_node->GetParentToObjectMatrix();
				current_node = current_node->m_parent;
			}
			return transformation;
		}
		
		/**
		 Returns the object-to-world matrix of this scene node.

		 @return		The object-to-world matrix of this scene node.
		 */
		XMMATRIX GetObjectToWorldMatrix() const {
			XMMATRIX transformation = GetParentToWorldMatrix();
			const SceneNode *current_node = m_parent;
			while (current_node) {
				transformation = current_node->GetParentToWorldMatrix() * transformation;
				current_node = current_node->m_parent;
			}
			return transformation;
		}

		/**
		 Accepts the given visitor.

		 @param[in]		visitor
						A reference to the visitor.
		 */
		virtual void Accept(SceneNodeVisitor &visitor) = 0;
		
		/**
		 Accepts the given visitor.

		 @param[in]		visitor
						A reference to the visitor.
		 */
		virtual void Accept(SceneNodeVisitor &visitor) const = 0;

	protected:

		/**
		 Constructs a scene node with the given transform.

		 @param[in]		transform
						A reference to the transform.
		 */
		SceneNode(const Transform &transform = Transform()) 
			: m_transform(transform), m_parent(nullptr) {}

		/**
		 Pass the given visitor to the childs of this scene node.

		 @param[in]		visitor
						A reference to the visitor.
		 */
		void PassToChilds(SceneNodeVisitor &visitor) {
			for (set< SceneNode * >::iterator it = m_childs.begin(); it != m_childs.end(); ++it) {
				(*it)->Accept(visitor);
			}
		}
		
		/**
		 Pass the given visitor to the childs of this scene node.

		 @param[in]		visitor
						A reference to the visitor.
		 */
		void PassToChilds(SceneNodeVisitor &visitor) const {
			for (set< SceneNode * >::const_iterator it = m_childs.cbegin(); it != m_childs.cend(); ++it) {
				(*it)->Accept(visitor);
			}
		}

	private:

		/**
		 Sets the parent scene node of this scene node to the given scene node.

		 @param[in]		parent
						A pointer to the parent scene node.
		 */
		void SetParent(SceneNode *parent) {
			m_parent = parent;
		}
		
		/**
		 The transform of this scene node.
		 */
		Transform m_transform;

		/**
		 A pointer to the parent scene node of this scene node.
		 */
		SceneNode *m_parent;

		/**
		 A set containing the child scene nodes of this scene node.
		 */
		set< SceneNode *, std::less<> > m_childs;
	};
}