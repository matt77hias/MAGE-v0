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

	uint64_t GetVirtualMemoryUsage() noexcept {
		PROCESS_MEMORY_COUNTERS memory_stats = {};
		const BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), &memory_stats, sizeof(memory_stats));
		return (result == 0) ? 0 : static_cast< uint64_t >(memory_stats.PagefileUsage);
	}

	uint64_t GetPhysicalMemoryUsage() noexcept {
		PROCESS_MEMORY_COUNTERS memory_stats = {};
		const BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), &memory_stats, sizeof(memory_stats));
		return (result == 0) ? 0 : static_cast< uint64_t >(memory_stats.WorkingSetSize);
	}
}