//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "system\system_usage.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <psapi.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	U64 GetVirtualMemoryUsage() noexcept {
		
		PROCESS_MEMORY_COUNTERS memory_stats = {};
		const BOOL result = GetProcessMemoryInfo(
			GetCurrentProcess(), &memory_stats, sizeof(memory_stats));
		
		return (result == FALSE) ? 
			0 : static_cast< U64 >(memory_stats.PagefileUsage);
	}

	U64 GetPhysicalMemoryUsage() noexcept {
		
		PROCESS_MEMORY_COUNTERS memory_stats = {};
		const BOOL result = GetProcessMemoryInfo(
			GetCurrentProcess(), &memory_stats, sizeof(memory_stats));
		
		return (result == FALSE) ? 
			0 : static_cast< U64 >(memory_stats.WorkingSetSize);
	}
}