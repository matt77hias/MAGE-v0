#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <malloc.h>

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
					The alignment.
	 @return		@c nullptr if the allocation failed.
	 @return		A pointer to the memory block that was allocated. The 
					pointer is a multiple of the given alignment.
	 */
	inline void *AllocAligned(size_t size, size_t alignment = 16) noexcept {
		return _aligned_malloc(size, alignment);
	}

	/**
	 Allocates memory on an alignment boundary of 16 bytes.

	 @tparam		DataT
					The type of objects to allocate in memory.
	 @param[in]		count
					The number of objects of type @c DataT to allocate in 
					memory.
	 @return		@c nullptr if the allocation failed.
	 @return		A pointer to the memory block that was allocated. The 
					pointer is a multiple of the alignment of 16 bytes.
	 */
	template < typename DataT >
	inline DataT *AllocAligned(size_t count) noexcept {
		return static_cast< DataT * >(AllocAligned(count * sizeof(DataT)));
	}

	/**
	 Frees a block of memory that was allocated with 
	 {@link mage::AllocAligned(size_t)} or {@link mage::AllocAligned<T>(size_t)}.
	
	 @param[in]		ptr
					A pointer to the memory block that was allocated.
	 */
	inline void FreeAligned(void *ptr) noexcept {
		if (!ptr) {
			return;
		}

		_aligned_free(ptr);
	}

	/**
	 A struct of aligned data.

	 @tparam		The data type.
	 */
	template< typename DataT >
	struct AlignedData {

	public:

		//---------------------------------------------------------------------
		// Allocation Operators
		//---------------------------------------------------------------------	

		/**
		 Allocates @a size bytes of storage, suitably aligned to represent any 
		 object of that size, and returns a non-null pointer to the first byte 
		 of this block.

		 @param[in]		size
						The requested size in bytes to allocate in memory.
		 @return		A pointer to the memory block that was allocated.
	 					The pointer is a multiple of the given alignment.
		 @throws		std::bad_alloc
						Failed to allocate the memory block.
		 */
		static void *operator new(size_t size) {
			const size_t alignment = __alignof(DataT);
			
			// __declspec(align) on DataT is required
			static_assert(alignment > 8, 
				"AlignedData is only useful for types with > 8 byte alignment.");
			
			void * const ptr = AllocAligned(size, alignment);
			if (!ptr) {
				throw std::bad_alloc();
			}

			return ptr;
		}

		/**
		 Deallocates the memory block pointed by @a ptr (if not nullptr), 
		 releasing the storage space previously allocated to it by a call to 
		 operator new and rendering that pointer location invalid.

		 @param[in]		ptr
						A pointer to the memory block that was allocated.
		 */
		static void operator delete(void *ptr) noexcept {
			FreeAligned(ptr);
		}

		/**
		 Allocates @a size bytes of storage, suitably aligned to represent any 
		 object of that size, and returns a non-null pointer to the first byte 
		 of this block.

		 @param[in]		size
						The requested size in bytes to allocate in memory.
		 @return		A pointer to the memory block that was allocated.
						The pointer is a multiple of the given alignment.
		 @throws		std::bad_alloc
						Failed to allocate the memory block.
		 */
		static void *operator new[](size_t size) {
			return operator new(size);
		}

		/**
		 Deallocates the memory block pointed to by @a ptr (if not nullptr), 
		 releasing the storage space previously allocated to it by a call to 
		 operator new[] and rendering that pointer location invalid.

		 @param[in]		ptr
						A pointer to the memory block that was allocated.
		 */
		static void operator delete[](void *ptr) noexcept {
			operator delete(ptr);
		}
	};
}