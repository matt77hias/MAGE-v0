#pragma once

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
	 Allocates memory on an alignment boundary of 64 bytes of the given size.
	 
	 @param[in]		size
					The requested size in bytes to allocate in memory.
	 @return		@c NULL if the allocation failed.
	 @return		A pointer to the memory block that was allocated.
	 				The pointer is a multiple of the alignment of 64 bytes.
	 */
	inline void *AllocAligned(size_t size) {
		return _aligned_malloc(size, MAGE_L1_CACHE_LINE_SIZE);
	}

	/**
	 Allocates memory on an alignment boundary of 64 bytes.

	 @tparam		T
					The type of objects to allocate in memory.
	 @param[in]		count	The number of objects of type @c T to allocate in memory.
	 @return		@c NULL if the allocation failed.
	 @return		A pointer to the memory block that was allocated.
	 				The pointer is a multiple of the alignment of 64 bytes.
	*/
	template <typename T>
	inline T *AllocAligned(uint32_t count) {
		return (T *)AllocAligned(count * sizeof(T));
	}

	/**
	 Frees a block of memory that was allocated with {@link mage::AllocAligned(size_t)} or {@link mage::AllocAligned<T>(uint32_t)}.
	
	 @param[in]		ptr
					A pointer to the memory block that was allocated.
	*/
	inline void FreeAligned(void *ptr) {
		if (!ptr) {
			return;
		}

		_aligned_free(ptr);
	}
}