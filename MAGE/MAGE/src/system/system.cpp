//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"
#include "system\system.hpp"
#include "parallel\parallel.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <psapi.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	uint64_t GetVirtualMemoryUsage() {
		PROCESS_MEMORY_COUNTERS_EX memory_stats;
		ZeroMemory(&memory_stats, sizeof(memory_stats));
		const BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *)&memory_stats, sizeof(memory_stats));
		return (result == 0) ? 0 : static_cast< uint64_t >(memory_stats.PrivateUsage);
	}

	uint64_t GetPhysicalMemoryUsage() {
		PROCESS_MEMORY_COUNTERS_EX memory_stats;
		ZeroMemory(&memory_stats, sizeof(memory_stats));
		const BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *)&memory_stats, sizeof(memory_stats));
		return (result == 0) ? 0 : static_cast< uint64_t >(memory_stats.WorkingSetSize);
	}

	static bool IsInitialized = false;
	static ULARGE_INTEGER last_time;
	static ULARGE_INTEGER last_kernel_mode_time;
	static ULARGE_INTEGER last_user_mode_time;

	static void InitTimes() {
		FILETIME ftime;
		// Retrieves the current system date and time.
		// The information is in Coordinated Universal Time (UTC) format.
		GetSystemTimeAsFileTime(&ftime);
		
		memcpy(&last_time, &ftime, sizeof(FILETIME));

		FILETIME kernel_mode_ftime;
		FILETIME user_mode_ftime;
		// Retrieves timing information for the specified process.
		// 1. A handle to the process whose timing information is sought.
		// 2. A pointer to a FILETIME structure that receives the creation time of the process.
		// 3. A pointer to a FILETIME structure that receives the exit time of the process.
		// 4. A pointer to a FILETIME structure that receives the amount of time that the process has executed in kernel mode.
		// 5. A pointer to a FILETIME structure that receives the amount of time that the process has executed in user mode.
		GetProcessTimes(GetCurrentProcess(), &ftime, &ftime, &kernel_mode_ftime, &user_mode_ftime);
		
		memcpy(&last_kernel_mode_time, &kernel_mode_ftime, sizeof(FILETIME));
		memcpy(&last_user_mode_time, &user_mode_ftime, sizeof(FILETIME));
	}

	double GetProcessorUsage() {
		if (!IsInitialized) {
			InitTimes();
			IsInitialized = true;
		}

		FILETIME ftime;
		// Retrieves the current system date and time.
		// The information is in Coordinated Universal Time (UTC) format.
		GetSystemTimeAsFileTime(&ftime);

		ULARGE_INTEGER now_time;
		memcpy(&now_time, &ftime, sizeof(FILETIME));

		FILETIME kernel_mode_ftime;
		FILETIME user_mode_ftime;
		// Retrieves timing information for the specified process.
		// 1. A handle to the process whose timing information is sought.
		// 2. A pointer to a FILETIME structure that receives the creation time of the process.
		// 3. A pointer to a FILETIME structure that receives the exit time of the process.
		// 4. A pointer to a FILETIME structure that receives the amount of time that the process has executed in kernel mode.
		// 5. A pointer to a FILETIME structure that receives the amount of time that the process has executed in user mode.
		const BOOL result = GetProcessTimes(GetCurrentProcess(), &ftime, &ftime, &kernel_mode_ftime, &user_mode_ftime);

		ULARGE_INTEGER kernel_mode_time;
		memcpy(&kernel_mode_time, &kernel_mode_ftime, sizeof(FILETIME));

		ULARGE_INTEGER user_mode_time;
		memcpy(&user_mode_time, &user_mode_ftime, sizeof(FILETIME));
		
		const double numerator   = (kernel_mode_time.QuadPart - last_kernel_mode_time.QuadPart) +
								   (user_mode_time.QuadPart   - last_user_mode_time.QuadPart);
		const double denominator = (now_time.QuadPart         - last_time.QuadPart) * NumberOfSystemCores();
		const double percentage = 100.0 * numerator / denominator;

		last_time             = now_time;
		last_kernel_mode_time = kernel_mode_time;
		last_user_mode_time   = user_mode_time;

		return (result == 0 || denominator == 0) ? 0 : percentage;
	}
}