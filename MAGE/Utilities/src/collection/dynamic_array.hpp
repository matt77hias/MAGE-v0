#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdexcept>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename T >
	class DynamicArray {

	public:

		//---------------------------------------------------------------------
		// Class Member Types
		//---------------------------------------------------------------------

		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type& ;
		using const_reference = const value_type&;
		using pointer = value_type* ;
		using const_pointer = const value_type*;

		using iterator = T * ;
		using const_iterator = const T*;
		using reverse_iterator = std::reverse_iterator< iterator >;
		using const_reverse_iterator = std::reverse_iterator< const_iterator >;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit DynamicArray(size_type size = 0u)
			: m_size(size),
			m_data((0u == size) ? nullptr : MakeUnique< value_type[] >(size)) {}

		DynamicArray(const DynamicArray& a)
			: DynamicArray(a.size()) {

			auto from = a.cbegin();
			for (auto to = begin(); to != end(); ++to, ++from) {
				*to = *from;
			}
		}

		DynamicArray(DynamicArray&& a) noexcept = default;

		~DynamicArray() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		DynamicArray& operator=(const DynamicArray& a) {
			if (size() != a.size()) {
				m_size = a.size();
				m_data = MakeUnique< value_type[] >(m_size);
			}

			auto from = a.cbegin();
			for (auto to = begin(); to != end(); ++to, ++from) {
				*to = *from;
			}

			return *this;
		};

		DynamicArray& operator=(DynamicArray&& a) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods: Element access
		//---------------------------------------------------------------------

		[[nodiscard]]
		reference at(size_type index) {
			if (size() <= index) {
				throw std::out_of_range("DynamicArray index out of range.");
			}

			return m_data[index];
		}

		[[nodiscard]]
		const_reference at(size_type index) const {
			if (size() <= index) {
				throw std::out_of_range("DynamicArray index out of range.");
			}

			return m_data[index];
		}

		[[nodiscard]]
		reference operator[](size_type index) noexcept {
			return m_data[index];
		}

		[[nodiscard]]
		const_reference operator[](size_type index) const noexcept {
			return m_data[index];
		}

		[[nodiscard]]
		reference front() noexcept {
			return m_data[0u];
		}

		[[nodiscard]]
		const_reference front() const noexcept {
			return m_data[0u];
		}

		[[nodiscard]]
		reference back() noexcept {
			return m_data[size() - 1u];
		}

		[[nodiscard]]
		const_reference back() const noexcept {
			return m_data[size() - 1u];
		}

		[[nodiscard]]
		T* data() noexcept {
			return m_data.get();
		}

		[[nodiscard]]
		const T* data() const noexcept {
			return m_data.get();
		}

		//---------------------------------------------------------------------
		// Member Methods: Iterators
		//---------------------------------------------------------------------

		[[nodiscard]]
		iterator begin() noexcept {
			return data();
		}

		[[nodiscard]]
		const_iterator begin() const noexcept {
			return data();
		}

		[[nodiscard]]
		const_iterator cbegin() const noexcept {
			return begin();
		}

		[[nodiscard]]
		iterator end() noexcept {
			return empty() ? nullptr : (data() + size());
		}

		[[nodiscard]]
		const_iterator end() const noexcept {
			return empty() ? nullptr : (data() + size());
		}

		[[nodiscard]]
		const_iterator cend() const noexcept {
			return end();
		}

		[[nodiscard]]
		reverse_iterator rbegin() noexcept {
			return reverse_iterator(end());
		}

		[[nodiscard]]
		const_reverse_iterator rbegin() const noexcept {
			return reverse_iterator(cend());
		}

		[[nodiscard]]
		const_reverse_iterator crbegin() const noexcept {
			return rbegin();
		}

		[[nodiscard]]
		reverse_iterator rend() noexcept {
			return reverse_iterator(begin());
		}

		[[nodiscard]]
		const_reverse_iterator rend() const noexcept {
			return reverse_iterator(cbegin());
		}

		[[nodiscard]]
		const_reverse_iterator crend() const noexcept {
			return rend();
		}

		//---------------------------------------------------------------------
		// Member Methods: Capacity
		//---------------------------------------------------------------------

		[[nodiscard]]
		bool empty() const noexcept {
			return size() == 0u;
		}

		[[nodiscard]]
		size_type size() const noexcept {
			return m_size;
		}

		[[nodiscard]]
		size_type max_size() const noexcept {
			return size();
		}

		//---------------------------------------------------------------------
		// Member Methods: Modifiers
		//---------------------------------------------------------------------

		void fill(const T& value) {
			for (auto& element : *this) {
				element = value;
			}
		}

		void swap(DynamicArray& other) noexcept {
			std::swap(m_size, other.m_size);
			std::swap(m_data, other.m_data);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		std::size_t m_size;

		UniquePtr< T[] > m_data;
	};
}