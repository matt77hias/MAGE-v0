#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "collection\vector.hpp"
#include "logging\logging.hpp"

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
        
        //---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		constexpr explicit Entity(U32 id = 0u) noexcept
			: m_id(id) {}
		
		constexpr Entity(const Entity& entity) noexcept = default;
		
		constexpr Entity(Entity&& entity) noexcept = default;
		
		~Entity() = default;

        //---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------
        
		Entity& operator=(const Entity& entity) noexcept = default;
		
		Entity& operator=(Entity&& entity) noexcept = default;

        //---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------
        
        [[nodiscard]]
		constexpr U32 GetID() const noexcept {
			return m_id;
		}
       
		[[nodiscard]]
		constexpr explicit operator U32() const noexcept {
			return GetID();
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
        
        //---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

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

	//-------------------------------------------------------------------------
	// ComponentManager
	//-------------------------------------------------------------------------

	template< typename T >
	class ComponentManager {

	public:

		//---------------------------------------------------------------------
		// Class Member Types
		//---------------------------------------------------------------------

		using ComponentContainer = AlignedVector< T >;
		
		using EntityContainer    = AlignedVector< Entity >;
		
		using MappingContainer   = std::unordered_map< Entity, std::size_t >;

		using value_type
			= typename ComponentContainer::value_type;
		
		using size_type
			= typename ComponentContainer::size_type;
		
		using difference_type
			= typename ComponentContainer::difference_type;
		
		using reference
			= typename ComponentContainer::reference;
		
		using const_reference
			= typename ComponentContainer::const_reference;
		
		using pointer
			= typename ComponentContainer::pointer;
		
		using const_pointer
			= typename ComponentContainer::const_pointer;

		using iterator
			= typename ComponentContainer::iterator;
		
		using const_iterator
			= typename ComponentContainer::const_iterator;
		
		using reverse_iterator
			= typename ComponentContainer::reverse_iterator;
		
		using const_reverse_iterator
			= typename ComponentContainer::const_reverse_iterator;

		//---------------------------------------------------------------------
		// Record
		//---------------------------------------------------------------------
		
		class Record {

		public:

			//-----------------------------------------------------------------
			// Class Member Types
			//-----------------------------------------------------------------

			using ComponentIterator = typename ComponentManager< T >::iterator;

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			Record() noexcept
				: m_component_it{},
				m_component_manager(nullptr) {}
		
			explicit Record(ComponentIterator component_it,
							ComponentManager* component_manager) noexcept
				: m_component_it(std::move(component_it)),
				m_component_manager(component_manager) {}
		
			Record(const Record& record) noexcept = default;
		
			Record(Record&& record) noexcept = default;
		
			~Record() = default;

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			Record& operator=(const Record& record) = delete;
		
			Record& operator=(Record&& record) noexcept {
				swap(record);
				return *this;
			}
			
			//-----------------------------------------------------------------
			// Member Methods
			//-----------------------------------------------------------------

			[[nodiscard]]
			T& GetComponent() noexcept {
				ASSERT(nullptr != m_component_manager);
				ASSERT(m_component_manager->end() != m_component_it);
            
				return *m_component_it;
			}
        
			[[nodiscard]]
			const T& GetComponent() const noexcept {
				ASSERT(nullptr != m_component_manager);
				ASSERT(m_component_manager->end() != m_component_it);
            
				return *m_component_it;
			}
        
			[[nodiscard]]
			const Entity& GetEntity() const noexcept {
				ASSERT(nullptr != m_component_manager);
				ASSERT(m_component_manager->end() != m_component_it);
            
				const auto begin = m_component_manager->begin();
				const std::size_t index(m_component_it - begin);
				return m_component_manager->m_entities[index];
			}

			void swap(Record& other) noexcept {
				ASSERT(nullptr != m_component_manager);
				ASSERT(m_component_manager == other.m_component_manager);
				ASSERT(m_component_manager->end() != m_component_it);
				ASSERT(m_component_manager->end() != other.m_component_it);

				const auto begin = m_component_manager->begin();
				const std::size_t index1(      m_component_it - begin);
				const std::size_t index2(other.m_component_it - begin);
				m_component_manager->SwapComponents(index1, index2);
			}

			friend void swap(Record lhs, Record rhs) noexcept {
				lhs.swap(rhs);
			}

		private:

			//-----------------------------------------------------------------
			// Member Variables
			//-----------------------------------------------------------------

			ComponentIterator m_component_it;
		
			ComponentManager* m_component_manager;
		};

		//---------------------------------------------------------------------
		// RecordIterator
		//---------------------------------------------------------------------
		
		class RecordIterator {

		public:

			//-----------------------------------------------------------------
			// Class Member Types
			//-----------------------------------------------------------------

			using ComponentIterator = typename ComponentManager< T >::iterator;
        
			using value_type        = Record;
        
			using reference         = Record;
        
			using const_reference   = Record;
        
			using pointer           = void;
        
			using const_pointer     = void;
       
			using difference_type   = std::ptrdiff_t;
       
			using iterator_category = std::random_access_iterator_tag;

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			RecordIterator() noexcept
				: m_component_it{},
				m_component_manager(nullptr) {}
		
			explicit RecordIterator(ComponentIterator component_it,
									ComponentManager* component_manager) noexcept
				: m_component_it(std::move(component_it)), 
				m_component_manager(component_manager) {}
		
			RecordIterator(const RecordIterator& it) noexcept = default;
		
			RecordIterator(RecordIterator&& it) noexcept = default;
		
			~RecordIterator() = default;

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			RecordIterator& operator=(const RecordIterator& it) noexcept = default;
		
			RecordIterator& operator=(RecordIterator&& it) noexcept = default;

			//-----------------------------------------------------------------
			// Member Methods
			//-----------------------------------------------------------------

			[[nodiscard]]
			reference operator*() noexcept {
				return Record(m_component_it, m_component_manager);
			}
		
			[[nodiscard]]
			const_reference operator*() const noexcept {
				return Record(m_component_it, m_component_manager);
			}
        
			pointer operator->() = delete;
        
			const_pointer operator->() const = delete;
        
			[[nodiscard]]
			reference operator[](difference_type n) noexcept {
				return Record(m_component_it + n, m_component_manager);
			}
		
			[[nodiscard]]
			const_reference operator[](difference_type n) const noexcept {
				return Record(m_component_it + n, m_component_manager);
			}

			[[nodiscard]]
			difference_type operator-(const RecordIterator& it) const noexcept {
				return m_component_it - it.m_component_it;
			}

			[[nodiscard]]
			const RecordIterator operator+(difference_type n) const noexcept {
				return RecordIterator(m_component_it + n, m_component_manager);
			}
		
			[[nodiscard]]
			const RecordIterator operator-(difference_type n) const noexcept {
				return RecordIterator(m_component_it - n, m_component_manager);
			}
			
			[[nodiscard]]
			friend const RecordIterator operator+(difference_type n, const RecordIterator& it) noexcept {
				return it + n;
			}
			
			RecordIterator& operator++() noexcept {
				++m_component_it;
				return *this;
			}
		
			RecordIterator& operator--() noexcept {
				--m_component_it;
				return *this;
			}
			
			[[nodiscard]]
			friend const RecordIterator operator++(const RecordIterator& it) noexcept {
				return RecordIterator(it.m_component_it + 1u, it.m_component_manager);
			}
		
			[[nodiscard]]
			friend const RecordIterator operator--(const RecordIterator& it) noexcept {
				return RecordIterator(it.m_component_it - 1u, it.m_component_manager);
			}

			RecordIterator& operator+=(difference_type n) noexcept {
				m_component_it += n;
				return *this;
			}
		
			RecordIterator& operator-=(difference_type n) noexcept {
				m_component_it -= n;
				return *this;
			}

			[[nodiscard]]
			constexpr bool operator==(const RecordIterator& rhs) const noexcept {
				return m_component_it == rhs.m_component_it;
			}
		
			[[nodiscard]]
			constexpr bool operator!=(const RecordIterator& rhs) const noexcept {
				return m_component_it != rhs.m_component_it;
			}
		
			[[nodiscard]]
			constexpr bool operator<=(const RecordIterator& rhs) const noexcept {
				return m_component_it <= rhs.m_component_it;
			}
		
			[[nodiscard]]
			constexpr bool operator>=(const RecordIterator& rhs) const noexcept {
				return m_component_it >= rhs.m_component_it;
			}
		
			[[nodiscard]]
			constexpr bool operator<(const RecordIterator& rhs) const noexcept {
				return m_component_it < rhs.m_component_it;
			}
		
			[[nodiscard]]
			constexpr bool operator>(const RecordIterator& rhs) const noexcept {
				return m_component_it > rhs.m_component_it;
			}
        
			void swap(RecordIterator& other) noexcept {
				using std::swap;
				swap(m_component_it,      other.m_component_it);
				swap(m_component_manager, other.m_component_manager);
			}

		private:
        
			ComponentIterator m_component_it;
		
			ComponentManager* m_component_manager;
		};

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
		pointer data() noexcept {
			return m_components.data();
		}

		[[nodiscard]]
		const_pointer data() const noexcept {
			return m_components.data();
		}

		//---------------------------------------------------------------------
		// Member Methods: Iterators
		//---------------------------------------------------------------------

		[[nodiscard]]
		RecordIterator RecordBegin() noexcept {
			return RecordIterator(begin(), this);
		}

		[[nodiscard]]
		RecordIterator RecordEnd() noexcept {
			return RecordIterator(end(), this);
		}

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

		void push_back(Entity entity, const value_type& value) {
			emplace_back(entity, value);
		}

		void push_back(Entity entity, value_type&& value) {
			emplace_back(entity, std::move(value));
		}

		template< typename... ConstructorArgsT  >
		reference emplace_back(Entity entity, ConstructorArgsT&&... args) {
			if (const auto it = m_mapping.find(entity);
				it != m_mapping.cend()) {
				
				return m_components[it->second];
			}

			m_mapping.emplace(entity, size());
			m_entities.push_back(entity);
			return m_components.emplace_back(std::forward< ConstructorArgsT >(args)...);
		}

		void pop_back() {
			m_mapping.erase(m_entities.back());
			m_components.pop_back();
			m_entities.pop_back();
		}

		void erase(Entity entity) {
			if (const auto it = m_mapping.find(entity);
				it != m_mapping.cend()) {

				const auto index1 = it->second;
				const auto index2 = size() - 1u;
				if (index1 != index2) {
					SwapComponents(index1, index2);
				}
				
				pop_back();
			}
		}

		void swap(ComponentManager& other) noexcept {
            using std::swap;
			swap(m_components, other.m_components);
			swap(m_entities,   other.m_entities);
			swap(m_mapping,    other.m_mapping);
		}
        
    private:
        
        //---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------
        
        void SwapComponents(std::size_t index1, std::size_t index2) noexcept {
			auto& component1 = m_components[index1];
			auto& entity1    = m_entities[index1];
			auto& mapping1   = m_mapping[entity1];
            
            auto& component2 = m_components[index2];
			auto& entity2    = m_entities[index2];
			auto& mapping2   = m_mapping[entity2];

            using std::swap;
			swap(component1, component2);
			swap(entity1, entity2);
			swap(mapping1, mapping2);
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		AlignedVector< value_type > m_components;
		
		AlignedVector< Entity > m_entities;

		std::unordered_map< Entity, std::size_t > m_mapping;
	};
}