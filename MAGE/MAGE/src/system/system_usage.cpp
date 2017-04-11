//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"
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

	uint64_t GetVirtualMemoryUsage() {
		PROCESS_MEMORY_COUNTERS memory_stats;
		ZeroMemory(&memory_stats, sizeof(memory_stats));
		const BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), &memory_stats, sizeof(memory_stats));
		return (result == 0) ? 0 : static_cast< uint64_t >(memory_stats.PagefileUsage);
	}

	uint64_t GetPhysicalMemoryUsage() {
		PROCESS_MEMORY_COUNTERS memory_stats;
		ZeroMemory(&memory_stats, sizeof(memory_stats));
		const BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), &memory_stats, sizeof(memory_stats));
		return (result == 0) ? 0 : static_cast< uint64_t >(memory_stats.WorkingSetSize);
	}
}