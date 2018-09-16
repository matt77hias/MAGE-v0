#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename T >
	T* MemoryArena::AllocData(std::size_t count, bool initialization) {
		// Allocation
		const auto ptr = static_cast< T* >(Alloc(count * sizeof(T)));

		if (!ptr) {
			// The allocation failed.
			return nullptr;
		}

		// Initialization
		if (initialization) {
			for (std::size_t i = 0u; i < count; ++i) {
				new (&ptr[i]) T{};
			}
		}

		return ptr;
	}
}