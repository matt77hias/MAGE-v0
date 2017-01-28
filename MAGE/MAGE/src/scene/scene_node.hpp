#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\transform.hpp"
#include "collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	// Forward declarations
	class SceneNodeVisitor;

	/**
	 A class of scene nodes.
	 */
	class SceneNode {

	public:

		/**
		 Destructs this scene node.
		 */
		virtual ~SceneNode();

		/**
		 Clones this scene node (non-deep clone).

		 @return		A pointer to a non-deep clone of this scene node.
		 */
		virtual SceneNode *Clone() const = 0;
		
		/**
		 Clones this scene node (deep clone).

		 @return		A pointer to a deep clone of this scene node.
		 */
		SceneNode *DeepClone() const;

		/**
		 Check whether this scene node is enabled.

		 @return		@c true if this scene node is enabled.
						@c false otherwise.
		 */
		bool IsEnabled() const {
			return m_enabled;
		}
		
		/**
		 Enables this scene node.
		 */
		void Enable() {
			m_enabled = true;
		}

		/**
		 Disables this scene node.
		 */
		void Disable() {
			m_enabled = false;
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
		void AddChild(SceneNode *child);
		
		/**
		 Removes the given child scene node from the child scene nodes of this scene node.

		 @param[in]		child
						A pointer to the child scene node.
		 */
		void RemoveChild(SceneNode *child);
		
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
		XMMATRIX GetWorldToObjectMatrix() const;
		
		/**
		 Returns the object-to-world matrix of this scene node.

		 @return		The object-to-world matrix of this scene node.
		 */
		XMMATRIX GetObjectToWorldMatrix() const;

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

		/**
		 Accepts the given visitor recursively.

		 @param[in]		visitor
						A reference to the visitor.
		 */
		void AcceptRecursive(SceneNodeVisitor &visitor);

		/**
		 Accepts the given visitor recursively.

		 @param[in]		visitor
						A reference to the visitor.
		 */
		void AcceptRecursive(SceneNodeVisitor &visitor) const;

	protected:

		/**
		 Constructs a scene node with the given transform.

		 @param[in]		transform
						A reference to the transform.
		 @param[in]		enabled
						Flag indicating whether the scene node is enabled. 
		 */
		SceneNode(const Transform &transform = Transform(), bool enabled = true) 
			: m_enabled(enabled), m_transform(transform), m_parent(nullptr) {}

		/**
		 Constructs a scene node from the given scene node (non-deep clone).

		 @param[in]		scene_node
						The scene node.
		 */
		SceneNode(const SceneNode &scene_node)
			: m_enabled(scene_node.m_enabled), m_transform(scene_node.m_transform), m_parent(nullptr) {
			scene_node.GetParent()->AddChild(this);
		}

	private:

		/**
		 Copies the given scene node to this scene node.

		 @param[in]		scene_node
		 				The scene node.
		 */
		SceneNode &operator=(const SceneNode &scene_node) = delete;

		/**
		 Sets the parent scene node of this scene node to the given scene node.

		 @pre			The given parent must already contain this scene node
						as one of its child nodes.
		 @param[in]		parent
						A pointer to the parent scene node.
		 */
		void SetParent(SceneNode *parent) {
			m_parent = parent;
		}

		/**
		 Flag indicating whether this scene node is enabled.
		 */
		bool m_enabled;

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