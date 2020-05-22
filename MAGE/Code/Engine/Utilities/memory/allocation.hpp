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

#include <malloc.h>
#include <new>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Allocates memory on a given alignment boundary of the given size.

	 @pre			@a alignment must be an integer power of 2.
	 @param[in]		size
					The requested size in bytes to allocate in memory.
	 @param[in]		alignment
					The alignment in bytes.
	 @return		@c nullptr if the allocation failed.
	 @return		A pointer to the memory block that was allocated. The
					pointer is a multiple of the given alignment.
	 */
	[[nodiscard]]
	inline void* AllocAligned(std::size_t size, std::size_t alignment) noexcept {
		return _aligned_malloc(size, alignment);
	}

	/**
	 Allocates memory on a given alignment boundary.

	 @tparam		T
					The data type.
	 @param[in]		count
					The number of objects of type @c T to allocate in memory.
	 @param[in]		alignment
					The alignment in bytes.
	 @return		@c nullptr if the allocation failed.
	 @return		A pointer to the memory block that was allocated. The
					pointer is a multiple of the given alignment.
	 */
	template< typename T >
	[[nodiscard]]
	inline T* AllocAlignedData(std::size_t count, size_t alignment) noexcept {
		return static_cast< T* >(AllocAligned(count * sizeof(T), alignment));
	}

	/**
	 Frees a block of memory that was allocated with
	 {@link mage::AllocAligned(std::size_t, std::size_t)} or
	 {@link mage::AllocAlignedData<T>(std::size_t, std::size_t)}.

	 @param[in]		ptr
					A pointer to the memory block that was allocated.
	 */
	inline void FreeAligned(void* ptr) noexcept {
		if (!ptr) {
			return;
		}

		_aligned_free(ptr);
	}

	/**
	 A class of aligned allocators.

	 @tparam		T
					The data type.
	 @tparam		A
					The alignment in bytes.
	 */
	template< typename T, std::size_t A = alignof(T) >
	class AlignedAllocator {

	public:

		//---------------------------------------------------------------------
		// Class Member Types
		//---------------------------------------------------------------------

		using value_type = T;

		using size_type = std::size_t;

		using difference_type = std::ptrdiff_t;

		using propagate_on_container_move_assignment = std::true_type;

		using is_always_equal = std::true_type;

		/**
		 A struct of equivalent aligned allocators for other elements with the
		 same alignment.

		 @tparam		U
						The data type.
		 */
		template< typename U >
		struct rebind {

		public:

			//-----------------------------------------------------------------
			// Class Member Types
			//-----------------------------------------------------------------

			/**
			 The equivalent aligned allocator for elements of type @c U with
			 the same alignment as the aligned allocator for elements of type
			 @c T.
			 */
			using other = AlignedAllocator< U, A >;
		};

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an aligned allocator.
		 */
		constexpr AlignedAllocator() noexcept = default;

		/**
		 Constructs an aligned allocator from the given aligned allocator.

		 @param[in]		allocator
						A reference to the aligned allocator to copy.
		 */
		constexpr AlignedAllocator(
			const AlignedAllocator& allocator) noexcept = default;

		/**
		 Constructs an aligned allocator by moving the given aligned allocator.

		 @param[in]		allocator
						A reference to the aligned allocator to move.
		 */
		constexpr AlignedAllocator(
			AlignedAllocator&& allocator) noexcept = default;

		/**
		 Constructs an aligned allocator from the given aligned allocator.

		 @tparam		U
						The data type.
		 @param[in]		allocator
						A reference to the aligned allocator to copy.
		 */
		template< typename U >
		constexpr AlignedAllocator([[maybe_unused]]
			const AlignedAllocator< U, A >& allocator) noexcept {}

		/**
		 Destructs this aligned allocator.
		 */
		~AlignedAllocator() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given aligned allocator to this aligned allocator.

		 @param[in]		allocator
						A reference to the aligned allocator to copy.
		 @return		A reference to the copy of the given aligned allocator
						(i.e. this aligned allocator).
		 */
		AlignedAllocator& operator=(
			const AlignedAllocator& allocator) noexcept = default;

		/**
		 Moves the given aligned allocator to this aligned allocator.

		 @param[in]		allocator
						A reference to the aligned allocator to move.
		 @return		A reference to the moved aligned allocator (i.e. this
						aligned allocator).
		 */
		AlignedAllocator& operator=(
			AlignedAllocator&& allocator) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Allocates a block of storage with a size large enough to contain @a
		 count elements of type @c T, and returns a pointer to the first
		 element.

		 @param[in]		count
						The number of objects of type @c T to allocate in
						memory.
		 @return		A pointer to the memory block that was allocated. The
						pointer is a multiple of the alignment @c A.
		 @throws		std::bad_alloc
						Failed to allocate the memory block.
		 */
		[[nodiscard]]
		T* allocate(std::size_t count) const {
			const auto ptr = AllocAlignedData< T >(count, A);
			if (!ptr) {
				throw std::bad_alloc();
			}

			return ptr;
		}

		/**
		 Allocates a block of storage with a size large enough to contain @a
		 count elements of type @c T, and returns a pointer to the first
		 element.

		 @param[in]		count
						The number of objects of type @c T to allocate in
						memory.
		 @param[in]		hint
						Either @c nullptr or a value previously obtained by
						another call to
						{@link mage::AlignedAllocator<T,std::size_t>::allocate(std::size_t)}
						and not yet freed with
						{@link mage::AlignedAllocator<T,std::size_t>::deallocate(T*, std::size_t)}.
						When not equal to @c nullptr, this value may be used as
						a hint to improve performance by allocating the new
						block near the one specified. The address of an adjacent
						element is often a good choice.
		 @return		A pointer to the memory block that was allocated. The
						pointer is a multiple of the alignment @c A.
		 @throws		std::bad_alloc
						Failed to allocate the memory block.
		 */
		[[nodiscard]]
		T* allocate(std::size_t count,
					[[maybe_unused]] const void* hint) const {

			return allocate(count);
		}

		/**
		 Releases a block of storage previously allocated with
		 {@link mage::AlignedAllocator<T,std::size_t>::allocate(std::size_t)}
		 and not yet released.

		 @param[in]		data
						A pointer to the memory block that needs to be
						released.
		 @param[in]		count
						The number of objects of type @c T allocated on the call
						to allocate this block of storage.
		 @note			The elements in the array are not destroyed.
		 */
		void deallocate(T* data, [[maybe_unused]] std::size_t count) const noexcept {
			FreeAligned(static_cast< void* >(data));
		}

		/**
		 Compares this aligned allocator to the given aligned allocator for
		 equality.

		 @tparam		U
						The data type.
		 @param[in]		rhs
						A reference to the aligned allocator to compare with.
		 @return		@c true if and only if storage allocated from this
						aligned allocator can be deallocated from the given
						aligned allocator, and vice versa. This is always the
						case for stateless allocators. @c false otherwise.
		 */
		template< typename U >
		[[nodiscard]]
		constexpr bool operator==([[maybe_unused]]
								  const AlignedAllocator< U, A >& rhs) const noexcept {
			return true;
		}

		/**
		 Compares this aligned allocator to the given aligned allocator for
		 non-equality.

		 @tparam		U
						The data type.
		 @param[in]		rhs
						A reference to the aligned allocator to compare with.
		 @return		@c true if and only if storage allocated from this
						aligned allocator cannot be deallocated from the given
						aligned allocator, and vice versa. This is never the
						case for stateless allocators. @c false otherwise.
		 */
		template< typename U >
		[[nodiscard]]
		constexpr bool operator!=([[maybe_unused]]
								  const AlignedAllocator< U, A >& rhs) const noexcept {
			return false;
		}
	};
}
