#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <algorithm>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//---------------------------------------------------------------------
	// Member Methods: Graph
	//---------------------------------------------------------------------

	template< typename ActionT >
	inline void Node::ForEachChild(ActionT action) const {
		
		for (const auto &child : m_childs) {
			// Visit child node.
			action(*child);
		}
	}

	template< typename ActionT >
	inline void Node::ForEachDescendant(ActionT action) const {
		
		for (const auto &child : m_childs) {
			// Visit child node.
			action(*child);
			// Visit child node's child nodes.
			child->ForEachDescendantNode(action);
		}
	}

	//---------------------------------------------------------------------
	// Member Methods: Components
	//---------------------------------------------------------------------

	template< typename ComponentT >
	inline bool Node::Contains() const noexcept {
		return m_components.find(typeid(ComponentT)) != m_components.cend();
	}

	template< typename ComponentT >
	inline size_t Node::GetNumberOf() const noexcept {
		return m_components.count(typeid(ComponentT));
	};

	template< typename ComponentT >
	inline ProxyPtr< ComponentT > Node::Get() noexcept {
		const auto it = m_components.find(typeid(ComponentT));
		return (it != m_components.end()) ? 
			static_pointer_cast< ComponentT >(it->second) : nullptr;
	}

	template< typename ComponentT >
	inline ProxyPtr< const ComponentT > Node::Get() const noexcept {
		const auto it = m_components.find(typeid(ComponentT));
		return (it != m_components.cend()) ? 
			static_pointer_cast< const ComponentT >(it->second) : nullptr;
	}

	template< typename ComponentT >
	inline const std::vector< ProxyPtr< ComponentT > > Node::GetAll() {
		std::vector< ProxyPtr< ComponentT > > components;
		
		const auto range = m_components.equal_range(typeid(ComponentT));
		for_each(range.first, range.second, 
			[&components](decltype(m_components)::value_type &x) {
				components.push_back(static_pointer_cast< ComponentT >(x.second));
			}
		);
		
		return components;
	}

	template< typename ComponentT >
	inline const std::vector< ProxyPtr< const ComponentT > > Node::GetAll() const {
		std::vector< ProxyPtr< const ComponentT > > components;
		
		const auto range = m_components.equal_range(typeid(ComponentT));
		for_each(range.first, range.second,
			[&components](decltype(m_components)::value_type &x) {
				components.push_back(static_pointer_cast< const ComponentT >(x.second));
			}
		);
		
		return components;
	}

	template< typename ComponentT, typename ActionT >
	inline void Node::ForEach(ActionT action) {
		const auto range = m_components.equal_range(typeid(ComponentT));
		for_each(range.first, range.second,
			[&action](decltype(m_components)::value_type &x) {
				action(static_cast< ComponentT & >(*x.second));
			}
		);
	}

	template< typename ComponentT, typename ActionT >
	inline void Node::ForEach(ActionT action) const {
		const auto range = m_components.equal_range(typeid(ComponentT));
		for_each(range.first, range.second,
			[&action](decltype(m_components)::value_type &x) {
				action(static_cast< const ComponentT & >(*x.second));
			}
		);
	}

	template< typename ActionT >
	inline void Node::ForEachComponent(ActionT action) {
		for (const auto &[key, value] : m_components) {
			(void)key; // Unused
			action(*value);
		}
	}

	template< typename ActionT >
	inline void Node::ForEachComponent(ActionT action) const {
		for (const auto &[key, value] : m_components) {
			(void)key; // Unused
			action(static_cast< const Component & >(*value));
		}
	}
}