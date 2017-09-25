#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Retrieves the total amount of memory (in bytes) that the memory manager 
	 has committed to the running process.

	 @return		If the retrieval fails, the return value is zero. 
					To get extended error information, call GetLastError.
	 @return		If the retrieval succeeds, the total virtual memory usage 
					of this process (in bytes).
	 */
	u64 GetVirtualMemoryUsage() noexcept;

	/**
	 Retrieves the current working set size (in bytes) of the running process.

	 @return		If the retrieval fails, the return value is zero.
					To get extended error information, call GetLastError.
	 @return		If the retrieval succeeds, the total physical memory usage 
					of this process (in bytes).
	 */
	u64 GetPhysicalMemoryUsage() noexcept;
}