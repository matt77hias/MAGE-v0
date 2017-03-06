#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\allocation.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename T >
	T *MemoryArena::Alloc(size_t count, bool initialization) {
		// Allocation
		T *ptr = (T *)Alloc(count * sizeof(T));

		if (ptr == nullptr) {
			// The allocation failed.
			return nullptr;
		}

		// Initialization
		if (initialization) {
			for (size_t i = 0; i < count; ++i) {
				new (&ptr[i]) T();
			}
		}

		return ptr;
	}
}