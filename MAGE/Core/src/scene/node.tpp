#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//---------------------------------------------------------------------
	// Member Methods: Graph
	//---------------------------------------------------------------------
	#pragma region

	template< typename ActionT >
	void Node::ForEachChild(ActionT&& action) const {
		for (const auto& child : m_childs) {
			// Visit child node.
			action(*child);
		}
	}

	template< typename ActionT >
	void Node::ForEachDescendant(ActionT&& action) const {
		for (const auto& child : m_childs) {
			// Visit child node.
			action(*child);
			// Visit child node's child nodes.
			child->ForEachDescendantNode(action);
		}
	}

	#pragma endregion

	//---------------------------------------------------------------------
	// Member Methods: Components
	//---------------------------------------------------------------------
	#pragma region

	template< typename ComponentT >
	[[nodiscard]]
	inline bool Node::Contains() const noexcept {
		return m_components.find(typeid(ComponentT)) != m_components.cend();
	}

	template< typename ComponentT >
	[[nodiscard]]
	inline size_t Node::GetNumberOf() const noexcept {
		return m_components.count(typeid(ComponentT));
	}

	template< typename ComponentT >
	[[nodiscard]]
	inline ProxyPtr< ComponentT > Node::Get() noexcept {
		const auto it = m_components.find(typeid(ComponentT));
		return (it != m_components.end()) ? 
			static_pointer_cast< ComponentT >(it->second) : nullptr;
	}

	template< typename ComponentT >
	[[nodiscard]]
	inline ProxyPtr< const ComponentT > Node::Get() const noexcept {
		const auto it = m_components.find(typeid(ComponentT));
		return (it != m_components.cend()) ? 
			static_pointer_cast< const ComponentT >(it->second) : nullptr;
	}

	template< typename ComponentT >
	[[nodiscard]]
	const std::vector< ProxyPtr< ComponentT > > Node::GetAll() {
		std::vector< ProxyPtr< ComponentT > > components;
		
		const auto range = m_components.equal_range(typeid(ComponentT));
		for_each(range.first, range.second, 
			[&components](decltype(m_components)::value_type& x) {
				components.push_back(static_pointer_cast< ComponentT >(x.second));
			}
		);
		
		return components;
	}

	template< typename ComponentT >
	[[nodiscard]]
	const std::vector< ProxyPtr< const ComponentT > > Node::GetAll() const {
		std::vector< ProxyPtr< const ComponentT > > components;
		
		const auto range = m_components.equal_range(typeid(ComponentT));
		for_each(range.first, range.second,
			[&components](decltype(m_components)::value_type& x) {
				components.push_back(static_pointer_cast< const ComponentT >(x.second));
			}
		);
		
		return components;
	}

	template< typename ComponentT >
	void Node::Add(ProxyPtr< ComponentT > component) {
		if (nullptr == component
			|| component->HasOwner()
			|| State::Terminated == m_state
			|| State::Terminated == component->GetState()) {
			return;
		}

		ComponentClient::SetOwner(*component, m_this);

		m_components.emplace(typeid(*component), std::move(component));
	}

	template< typename ComponentT, typename ActionT >
	void Node::ForEach(ActionT&& action) {
		const auto range = m_components.equal_range(typeid(ComponentT));
		for_each(range.first, range.second,
			[&action](decltype(m_components)::value_type& x) {
				action(static_cast< ComponentT& >(*x.second));
			}
		);
	}

	template< typename ComponentT, typename ActionT >
	void Node::ForEach(ActionT&& action) const {
		const auto range = m_components.equal_range(typeid(ComponentT));
		for_each(range.first, range.second,
			[&action](decltype(m_components)::value_type& x) {
				action(static_cast< const ComponentT& >(*x.second));
			}
		);
	}

	template< typename ActionT >
	void Node::ForEachComponent(ActionT&& action) {
		for (const auto& [key, value] : m_components) {
			(void)key; // Unused
			action(*value);
		}
	}

	template< typename ActionT >
	void Node::ForEachComponent(ActionT&& action) const {
		for (const auto& [key, value] : m_components) {
			(void)key; // Unused
			action(static_cast< const Component& >(*value));
		}
	}

	#pragma endregion
}