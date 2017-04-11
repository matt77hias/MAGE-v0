//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "system\system_time.hpp"
#include "logging\error.hpp"

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

	inline uint64_t ConvertTime(const FILETIME &ftime) {
		return static_cast< uint64_t >(ftime.dwLowDateTime) | static_cast< uint64_t >(ftime.dwHighDateTime << 32);
	}

	uint64_t GetSystemTime() {
		FILETIME ftime;
		// Retrieves the current system date and time.
		// The information is in Coordinated Universal Time (UTC) format.
		GetSystemTimeAsFileTime(&ftime);

		return ConvertTime(ftime);
	}

	void GetCoreTime(uint64_t *kernel_mode_time, uint64_t *user_mode_time) {
		GetCoreTime(GetCurrentProcess(), kernel_mode_time, user_mode_time);
	}

	void GetCoreTime(HANDLE handle_process,
		uint64_t *kernel_mode_time, uint64_t *user_mode_time) {
		Assert(kernel_mode_time);
		Assert(user_mode_time);

		FILETIME ftime;
		FILETIME kernel_mode_ftime;
		FILETIME user_mode_ftime;
		// Retrieves timing information for the specified process.
		// 1. A handle to the process whose timing information is sought.
		// 2. A pointer to a FILETIME structure that receives the creation time of the process.
		// 3. A pointer to a FILETIME structure that receives the exit time of the process.
		// 4. A pointer to a FILETIME structure that receives the amount of time that the process has executed in kernel mode.
		// 5. A pointer to a FILETIME structure that receives the amount of time that the process has executed in user mode.
		const BOOL result = GetProcessTimes(handle_process, &ftime, &ftime, &kernel_mode_ftime, &user_mode_ftime);
		if (result != 0) {
			*kernel_mode_time = ConvertTime(kernel_mode_ftime);
			*user_mode_time   = ConvertTime(user_mode_ftime);
		}
		else {
			*kernel_mode_time = 0;
			*user_mode_time   = 0;
		}
	}
}