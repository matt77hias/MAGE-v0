#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Scene: Creation
	//-------------------------------------------------------------------------
	#pragma region

	template< typename ElementT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< Node, ElementT >,
		ProxyPtr< ElementT > > Scene::Create(ConstructorArgsT &&...args) {

		const auto ptr = AddElement(m_nodes, 
									std::forward< ConstructorArgsT >(args)...);
		
		ptr->Set(ptr);
		
		return ptr;
	}

	template< typename ElementT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_base_of_v< BehaviorScript, ElementT >,
		ProxyPtr< ElementT > > Scene::Create(ConstructorArgsT &&...args) {

		return AddElementPtr< ElementT >(m_scripts,
			                             std::forward< ConstructorArgsT >(args)...);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Scene: Count
	//-------------------------------------------------------------------------
	#pragma region

	template< typename ElementT >
	[[nodiscard]]
	inline size_t Scene::GetNumberOf() const noexcept {
		size_t count = 0;
		ForEach< ElementT >([&count](
			[[maybe_unused]] const ElementT& element) noexcept {
				++count;
			}
		);
		
		return count;
	}
	
	#pragma endregion

	//-------------------------------------------------------------------------
	// Scene: Iteration
	//-------------------------------------------------------------------------
	#pragma region

	template< typename ElementT, typename ActionT >
	inline void Scene::ForEach(ActionT action) {

		if constexpr (std::is_same_v< Node, ElementT >) {
			for (auto& element : m_nodes) {
				if (State::Terminated != element.GetState()) {
					action(element);
				}
			}
		}

		if constexpr (std::is_same_v< BehaviorScript, ElementT >) {
			for (auto& element : m_scripts) {
				if (State::Terminated != element->GetState()) {
					action(*element);
				}
			}
		}
	}

	template< typename ElementT, typename ActionT >
	inline void Scene::ForEach(ActionT action) const {

		if constexpr (std::is_same_v< Node, ElementT >) {
			for (const auto& element : m_nodes) {
				if (State::Terminated != element.GetState()) {
					action(element);
				}
			}
		}

		if constexpr (std::is_same_v< BehaviorScript, ElementT >) {
			for (const auto& element : m_scripts) {
				if (State::Terminated != element->GetState()) {
					action(static_cast< const BehaviorScript& >(*element));
				}
			}
		}
	}

	#pragma endregion
}