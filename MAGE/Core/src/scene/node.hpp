#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\component.hpp"
#include "scene\transform.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <typeindex>
#include <unordered_map>
#include <vector>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of nodes.
	 */
	class alignas(16) Node final {

	public:

		//---------------------------------------------------------------------
		// Type Declarations and Definitions
		//---------------------------------------------------------------------

		/**
		 A pointer to a node.
		 */
		using NodePtr = ProxyPtr< Node >;

		/**
		 A pointer to a component.
		 */
		using ComponentPtr = ProxyPtr< Component >;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a node.

		 @param[in]		name
						The name of the node.
		 */
		explicit Node(string name = "");

		/**
		 Constructs a node from the given node.

		 @param[in]		node
						A reference to the node.
		 */
		Node(const Node& node);

		/**
		 Constructs a node by moving the given node.

		 @param[in]		node
						A reference to the node to move.
		 */
		Node(Node&& node) noexcept;

		/**
		 Destructs this node.
		 */
		virtual ~Node();

		//---------------------------------------------------------------------
		// Assignment operators
		//---------------------------------------------------------------------

		/**
		 Copies the given node to this node.

		 @param[in]		node
						A reference to the node to copy.
		 @return		A reference to the copy of the given node (i.e. this 
						node).
		 */
		Node& operator=(const Node& node) = delete;

		/**
		 Moves the given node to this node.

		 @param[in]		node
						A reference to the node to move.
		 @return		A reference to the moved node (i.e. this node).
		 */
		Node& operator=(Node&& node) noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Transform
		//---------------------------------------------------------------------

		/**
		 Returns the transform of this node.

		 @return		A reference to the transform of this node.
		 */
		[[nodiscard]]
		Transform& GetTransform() noexcept {
			return m_transform;
		}
		
		/**
		 Returns the transform of this node.

		 @return		A reference to the transform of this node.
		 */
		[[nodiscard]]
		const Transform& GetTransform() const noexcept {
			return m_transform;
		}

		//---------------------------------------------------------------------
		// Member Methods: Graph
		//---------------------------------------------------------------------

		/**
		 Checks whether this node has a parent.

		 @return		@c true if this node has a parent. @c false otherwise.
		 */
		[[nodiscard]]
		bool HasParent() const noexcept {
			return bool(m_parent);
		}
		
		/**
		 Returns the parent of this node.

		 @return		A pointer to the parent of this node.
		 */
		[[nodiscard]]
		NodePtr GetParent() const noexcept {
			return m_parent;
		}
		
		/**
		 Returns the number of childs of this node.

		 @return		The number of childs of this node.
		 */
		[[nodiscard]]
		size_t GetNumberOfChilds() const noexcept {
			using std::size;
			return size(m_childs);
		}
		
		/**
		 Checks whether this node contains childs.

		 @return		@c true if this node contains at least one child. 
						@c false otherwise.
		 */
		[[nodiscard]]
		bool ContainsChilds() const {
			using std::empty;
			return !empty(m_childs);
		}

		/**
		 Checks whether this node contains the given node as a child.

		 @param[in]		node
						A pointer to the node.
		 @return		@c true if this node contains the given node as a 
						child. @c false otherwise.
		 */
		[[nodiscard]]
		bool ContainsChild(ProxyPtr< const Node > node) const {
			using std::cbegin;
			using std::cend;

			return std::find(cbegin(m_childs), cend(m_childs), node)
				   != cend(m_childs);
		}

		/**
		 Adds the given node to the childs of this node.

		 @param[in]		node
						A pointer to the node.
		 */
		void AddChild(NodePtr node);

		/**
		 Removes the given node from the childs of this node.

		 @param[in]		node
						A pointer to the node.
		 */
		void RemoveChild(NodePtr node);

		/**
		 Removes all childs from this node.
		 */
		void RemoveAllChilds() noexcept;

		/**
		 Traverses all childs of this node.

		 @tparam		ActionT
						An action to perform on all childs of this node. The 
						action must accept @c Node& values.
		 @param[in]		action
						The action.
		 */
		template< typename ActionT >
		void ForEachChild(ActionT&& action) const;
		
		/**
		 Traverses all descendants (childs included) of this node.

		 @tparam		ActionT
						An action to perform on all descendants of this node. 
						The action must accept @c Node& values.
		 @param[in]		action
						The action.
		 */
		template< typename ActionT >
		void ForEachDescendant(ActionT&& action) const;

		//---------------------------------------------------------------------
		// Member Methods: Components
		//---------------------------------------------------------------------

		/**
		 Checks whether this node contains a component of the given type.

		 @tparam		ComponentT
						The component type.
		 @return		@c true if this node contains at least one component 
						of the given type. @c false otherwise.
		 */
		template< typename ComponentT >
		[[nodiscard]]
		bool Contains() const noexcept;

		/**
		 Checks whether this node contains components.

		 @return		@c true if this node contains at least one component. 
						@c false otherwise.
		 */
		[[nodiscard]]
		bool ContainsComponents() const noexcept {
			using std::empty;
			return !empty(m_components);
		}

		/**
		 Returns the number of components of this node.

		 @return		The number of components of this node.
		 */
		[[nodiscard]]
		size_t GetNumberOfComponents() const noexcept {
			using std::size;
			return size(m_components);
		}

		/**
		 Returns the number of components of the given type of this node.

		 @tparam		ComponentT
						The component type.
		 @return		The number of components of the given type of this 
						node.
		 */
		template< typename ComponentT >
		[[nodiscard]]
		size_t GetNumberOf() const noexcept;

		/**
		 Returns the first component of the given type of this node.

		 @tparam		ComponentT
						The component type.
		 @return		@c nullptr if this node has no component of the given 
						type.
		 @return		A pointer to the first component of the given type of 
						this node.
		 */
		template< typename ComponentT >
		[[nodiscard]]
		ProxyPtr< ComponentT > Get() noexcept;

		/**
		 Returns the first component of the given type of this node.

		 @tparam		ComponentT
						The component type.
		 @return		@c nullptr if this node has no component of the given 
						type.
		 @return		A pointer to the first component of the given type of 
						this node.
		 */
		template< typename ComponentT >
		[[nodiscard]]
		ProxyPtr< const ComponentT > Get() const noexcept;

		/**
		 Returns all components of the given type of this node.

		 @tparam		ComponentT
						The component type.
		 @return		A vector containing all components of the given type of 
						this node.
		 */
		template< typename ComponentT >
		[[nodiscard]]
		const std::vector< ProxyPtr< ComponentT > > GetAll();

		/**
		 Returns all components of the given type of this node.

		 @tparam		ComponentT
						The component type.
		 @return		A vector containing all components of the given type of 
						this node.
		 */
		template< typename ComponentT >
		[[nodiscard]]
		const std::vector< ProxyPtr< const ComponentT > > GetAll() const;

		/**
		 Adds the given component to this node.

		 @tparam		ComponentT
						The component type.
		 @param[in]		component
						A pointer to the component.
		 */
		template< typename ComponentT >
		void Add(ProxyPtr< ComponentT > component);

		/**
		 Traverses all components of the given type of this node.

		 @tparam		ComponentT
						The component type.
		 @tparam		ActionT
						An action to perform on all components of the given 
						type of this node. 
						The action must accept @c ComponentT& values.
		 @param[in]		action
						The action.
		 */
		template< typename ComponentT, typename ActionT >
		void ForEach(ActionT&& action);

		/**
		 Traverses all components of the given type of this node.

		 @tparam		ComponentT
						The component type.
		 @tparam		ActionT
						An action to perform on all components of the given 
						type of this node. 
						The action must accept @c const @c ComponentT& values.
		 @param[in]		action
						The action.
		 */
		template< typename ComponentT, typename ActionT >
		void ForEach(ActionT&& action) const;

		/**
		 Traverses all components of this node.

		 @tparam		ActionT
						An action to perform on all components of this node. 
						The action must accept @c Component& values.
		 @param[in]		action
						The action.
		 */
		template< typename ActionT >
		void ForEachComponent(ActionT&& action);

		/**
		 Traverses all components of this node.

		 @tparam		ActionT
						An action to perform on all components of this node. 
						The action must accept @c const @c Component& values.
		 @param[in]		action
						The action.
		 */
		template< typename ActionT >
		void ForEachComponent(ActionT&& action) const;

		//---------------------------------------------------------------------
		// Member Methods: State
		//---------------------------------------------------------------------

		/**
		 Returns the state of this node.

		 @return		The state of this node.
		 */
		[[nodiscard]]
		State GetState() const noexcept {
			return m_state;
		}

		/**
		 Sets the state of this node to the given state.
		
		 @param[in]		state
						The state.
		 */
		void SetState(State state) noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Identification
		//---------------------------------------------------------------------

		/**
		 Returns the guid of this node.

		 @return		The guid of this node.
		 */
		[[nodiscard]]
		U64 GetGuid() const noexcept {
			return m_guid;
		}

		/**
		 Returns a pointer to this node.

		 @return		A pointer to this node.
		 */
		[[nodiscard]]
		NodePtr Get() const noexcept {
			return m_this;
		}

		/**
		 Returns the name of this node.

		 @return		A reference to the name of this node.
		 */
		[[nodiscard]]
		const string& GetName() const noexcept {
			return m_name;
		}

		/**
		 Sets the name of this node to the given string.

		 @param[in]		name
						The name.
		 */
		void SetName(string name) noexcept {
			m_name = std::move(name);
		}

		/**
		 Sets the pointer of this node to the given pointer.

		 @param[in]		ptr
						The pointer.
		 */
		void Set(NodePtr ptr) noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Variables: Transform
		//---------------------------------------------------------------------

		/**
		 The transform of this node.
		 */
		Transform m_transform;

		//---------------------------------------------------------------------
		// Member Variables: Graph
		//---------------------------------------------------------------------

		/**
		 A pointer to the parent of this node.
		 */
		NodePtr m_parent;

		/**
		 A vector containing pointers to the the childs of this node.
		 */
		std::vector< NodePtr > m_childs;

		//---------------------------------------------------------------------
		// Member Variables: Components
		//---------------------------------------------------------------------

		/**
		 A multimap containing pointers to the components of this node as 
		 values with their associated type as key.
		 */
		std::unordered_multimap< std::type_index, ComponentPtr > m_components;

		//---------------------------------------------------------------------
		// Member Variables: State
		//---------------------------------------------------------------------

		/**
		 The state of this node.
		 */
		State m_state;

		//---------------------------------------------------------------------
		// Member Variables: Identification
		//---------------------------------------------------------------------

		/**
		 The guid of this node.
		 */
		U64 m_guid;

		/**
		 A pointer to this node.
		 */
		NodePtr m_this;

		/**
		 The name of this node.
		 */
		string m_name;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\node.tpp"

#pragma endregion