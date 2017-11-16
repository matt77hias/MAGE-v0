#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename DataT >
	DataT *SingleEndedMemoryStack::AllocData(
		size_t count, bool initialization) noexcept {
		
		// Allocation
		DataT * const ptr 
			= static_cast< DataT * >(Alloc(count * sizeof(DataT)));

		if (!ptr) {
			// The allocation failed.
			return nullptr;
		}

		// Initialization
		if (initialization) {
			for (size_t i = 0; i < count; ++i) {
				new (&ptr[i]) DataT();
			}
		}

		return ptr;
	}

	template< typename DataT >
	DataT *DoubleEndedMemoryStack::AllocDataLow(
		size_t count, bool initialization) noexcept {
		
		// Allocation
		DataT * const ptr 
			= static_cast< DataT * >(AllocLow(count * sizeof(DataT)));

		if (!ptr) {
			// The allocation failed.
			return nullptr;
		}

		// Initialization
		if (initialization) {
			for (size_t i = 0; i < count; ++i) {
				new (&ptr[i]) DataT();
			}
		}

		return ptr;
	}

	template< typename DataT >
	DataT *DoubleEndedMemoryStack::AllocDataHigh(
		size_t count, bool initialization) noexcept {
		
		// Allocation
		DataT * const ptr 
			= static_cast< DataT * >(AllocHigh(count * sizeof(DataT)));

		if (!ptr) {
			// The allocation failed.
			return nullptr;
		}

		// Initialization
		if (initialization) {
			for (size_t i = 0; i < count; ++i) {
				new (&ptr[i]) DataT();
			}
		}

		return ptr;
	}
}