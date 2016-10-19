#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#include <malloc.h>

namespace mage {

	//-----------------------------------------------------------------------------
	// Declarations and Definitions
	//-----------------------------------------------------------------------------

	/// <summary>
	/// Allocates memory on an alignment boundary of 64 bytes.
	/// </summary>
	/// <param name="size">
	/// The requested size in bytes to allocate in memory.
	/// </param>
	/// <returns>
	/// A pointer to the memory block that was allocated or NULL if the operation failed.
	/// The pointer is a multiple of the alignment of 64 bytes.
	/// </returns>
	inline void *AllocAligned(size_t size) {
		return _aligned_malloc(size, MAGE_L1_CACHE_LINE_SIZE);
	}

	/// <summary>
	/// Allocates memory on an alignment boundary of 64 bytes.
	/// </summary>
	/// <typeparam name='T'>
	/// The type of objects to allocate in memory.
	/// </typeparam>
	/// <param name="count">
	/// The number of objects of type T to allocate in memory.
	/// </param>
	/// <returns>
	/// A pointer to the memory block that was allocated or NULL if the operation failed.
	/// The pointer is a multiple of the alignment of 64 bytes.
	/// </returns>
	template <typename T>
	inline T *AllocAligned(uint32_t count) {
		return (T *)AllocAligned(count * sizeof(T));
	}

	/// <summary>
	/// Frees a block of memory that was allocated with AllocAligned.
	/// </summary>
	/// <param name="ptr">
	/// A pointer to the memory block that was allocated.
	/// This function returns if <paramref name="ptr"/> points to NULL.
	/// </param>
	inline void FreeAligned(void *ptr) {
		if (!ptr) {
			return;
		}

		_aligned_free(ptr);
	}
}