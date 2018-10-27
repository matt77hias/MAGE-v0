#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "collection\vector.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <unordered_map>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class Entity {

	public:

		constexpr explicit Entity(U32 id = 0u) noexcept
			: m_id(id) {}
		constexpr Entity(const Entity& entity) noexcept = default;
		constexpr Entity(Entity&& entity) noexcept = default;
		~Entity() = default;

		Entity& operator=(const Entity& entity) noexcept = default;
		Entity& operator=(Entity&& entity) noexcept = default;

		[[nodiscard]]
		constexpr explicit operator bool() const noexcept {
			return IsValid();
		}
		[[nodiscard]]
		constexpr bool IsValid() const noexcept {
			return 0u != m_id;
		}

		[[nodiscard]]
		constexpr bool operator==(const Entity& rhs) const noexcept {
			return m_id == rhs.m_id;
		}
		[[nodiscard]]
		constexpr bool operator!=(const Entity& rhs) const noexcept {
			return m_id != rhs.m_id;
		}
		[[nodiscard]]
		constexpr bool operator<=(const Entity& rhs) const noexcept {
			return m_id <= rhs.m_id;
		}
		[[nodiscard]]
		constexpr bool operator>=(const Entity& rhs) const noexcept {
			return m_id >= rhs.m_id;
		}
		[[nodiscard]]
		constexpr bool operator<(const Entity& rhs) const noexcept {
			return m_id < rhs.m_id;
		}
		[[nodiscard]]
		constexpr bool operator>(const Entity& rhs) const noexcept {
			return m_id > rhs.m_id;
		}

		[[nodiscard]]
		std::size_t Hash() const noexcept {
			return std::hash< U32 >()(m_id);
		}

	private:

		U32 m_id;
	};

	static_assert(sizeof(U32) == sizeof(Entity));

}

namespace std {

	template<>
	struct hash< mage::Entity > {

		size_t operator()(const mage::Entity& entity) const {
			return entity.Hash();
		}
	};
}

namespace mage {

	template< typename T >
	class ComponentManager {

	public:

		//---------------------------------------------------------------------
		// Class Member Types
		//---------------------------------------------------------------------

		using value_type 
			= typename AlignedVector< T >::value_type;
		using size_type 
			= typename AlignedVector< T >::size_type;
		using difference_type 
			= typename AlignedVector< T >::difference_type;
		using reference 
			= typename AlignedVector< T >::reference;
		using const_reference 
			= typename AlignedVector< T >::const_reference;
		using pointer 
			= typename AlignedVector< T >::pointer;
		using const_pointer 
			= typename AlignedVector< T >::const_pointer;

		using iterator 
			= typename AlignedVector< T >::iterator;
		using const_iterator 
			= typename AlignedVector< T >::const_iterator;
		using reverse_iterator 
			= typename AlignedVector< T >::reverse_iterator;
		using const_reverse_iterator 
			= typename AlignedVector< T >::const_reverse_iterator;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		ComponentManager() = default;
		ComponentManager(const ComponentManager& manager) = default;
		ComponentManager(ComponentManager&& manager) noexcept = default;
		~ComponentManager() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		ComponentManager& operator=(const ComponentManager& manager) = default;
		ComponentManager& operator=(ComponentManager&& manager) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods: Element access
		//---------------------------------------------------------------------

		[[nodiscard]]
		bool Contains(Entity entity) const noexcept {
			return m_mapping.find(entity) != m_mapping.cend();
		}

		[[nodiscard]]
		pointer Get(Entity entity) noexcept {
			if (const auto it = m_mapping.find(entity);
				it != m_mapping.cend()) {

				return &m_components[it->second];
			}

			return nullptr;
		}

		[[nodiscard]]
		const_pointer Get(Entity entity) const noexcept {
			if (const auto it = m_mapping.find(entity);
				it != m_mapping.cend()) {

				return &m_components[it->second];
			}

			return nullptr;
		}

		[[nodiscard]]
		reference at(size_type index) {
			return m_components.at(index);
		}

		[[nodiscard]]
		const_reference at(size_type index) const {
			return m_components.at(index);
		}

		[[nodiscard]]
		reference operator[](size_type index) noexcept {
			return m_components[index];
		}

		[[nodiscard]]
		const_reference operator[](size_type index) const noexcept {
			return m_components[index];
		}

		[[nodiscard]]
		reference front() noexcept {
			return m_components.front();
		}

		[[nodiscard]]
		const_reference front() const noexcept {
			return m_components.front();
		}

		[[nodiscard]]
		reference back() noexcept {
			return m_components.back();
		}

		[[nodiscard]]
		const_reference back() const noexcept {
			return m_components.back();
		}

		[[nodiscard]]
		T* data() noexcept {
			return m_components.data();
		}

		[[nodiscard]]
		const T* data() const noexcept {
			return m_components.data();
		}

		//---------------------------------------------------------------------
		// Member Methods: Iterators
		//---------------------------------------------------------------------

		[[nodiscard]]
		iterator begin() noexcept {
			return m_components.begin();
		}

		[[nodiscard]]
		const_iterator begin() const noexcept {
			return m_components.begin();
		}

		[[nodiscard]]
		const_iterator cbegin() const noexcept {
			return m_components.cbegin();
		}

		[[nodiscard]]
		iterator end() noexcept {
			return m_components.end();
		}

		[[nodiscard]]
		const_iterator end() const noexcept {
			return m_components.end();
		}

		[[nodiscard]]
		const_iterator cend() const noexcept {
			return m_components.end();
		}

		[[nodiscard]]
		reverse_iterator rbegin() noexcept {
			return m_components.rbegin();
		}

		[[nodiscard]]
		const_reverse_iterator rbegin() const noexcept {
			return m_components.rbegin();
		}

		[[nodiscard]]
		const_reverse_iterator crbegin() const noexcept {
			return m_components.crbegin();
		}

		[[nodiscard]]
		reverse_iterator rend() noexcept {
			return m_components.rend();
		}

		[[nodiscard]]
		const_reverse_iterator rend() const noexcept {
			return m_components.rend();
		}

		[[nodiscard]]
		const_reverse_iterator crend() const noexcept {
			return m_components.crend();
		}

		//---------------------------------------------------------------------
		// Member Methods: Capacity
		//---------------------------------------------------------------------

		[[nodiscard]]
		bool empty() const noexcept {
			return m_components.empty();
		}

		[[nodiscard]]
		size_type size() const noexcept {
			return m_components.size();
		}

		[[nodiscard]]
		size_type max_size() const noexcept {
			return m_components.max_size();
		}

		void reserve(size_type new_capacity) {
			m_components.reserve(new_capacity);
			m_entities.reserve(new_capacity);
			m_mapping.reserve(new_capacity);
		}

		[[nodiscard]]
		size_type capacity() const noexcept {
			return m_components.capacity();
		}

		void shrink_to_fit() {
			m_components.shrink_to_fit();
			m_entities.shrink_to_fit();
		}

		//---------------------------------------------------------------------
		// Member Methods: Modifiers
		//---------------------------------------------------------------------

		void clear() noexcept {
			m_components.clear();
			m_entities.clear();
			m_mapping.clear();
		}

		void push_back(Entity entity, const T& value) {
			emplace_back(entity, value);
		}

		void push_back(Entity entity, T&& value) {
			emplace_back(entity, std::move(value));
		}

		template< typename... ConstructorArgsT  >
		reference emplace_back(Entity entity, ConstructorArgsT&&... args) {
			if (Contains(entity)) {
				return;
			}

			m_mapping.emplace(entity, size());
			m_entities.push_back(entity);
			return m_components.emplace_back(
				std::forward< ConstructorArgsT >(args)...);
		}

		void pop_back() {
			m_mapping.erase(m_entities.back());
			m_components.pop_back();
			m_entities.pop_back();
		}

		void swap(ComponentManager& other) noexcept {
			std::swap(m_components, other.m_components);
			std::swap(m_entities,   other.m_entities);
			std::swap(m_mapping,    other.m_mapping);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		AlignedVector< T > m_components;
		
		AlignedVector< Entity > m_entities;

		std::unordered_map< Entity, std::size_t > m_mapping;
	};
}
