//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "system\system_time.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Converts the given file time to a @c u64 (in 100 ns).

	 @param[in]		ftime
					A reference to the file time.
	 @return		A @c u64 (in 100 ns) representing the given file time 
					@a ftime.
	 */
	inline u64 ConvertTimestamp(const FILETIME &ftime) noexcept {
		return static_cast< u64 >(ftime.dwLowDateTime) 
			 | static_cast< u64 >(ftime.dwHighDateTime) << 32;
	}

	u64 GetCurrentSystemTimestamp() noexcept {
		
		FILETIME ftime;
		// Retrieves the current system date and time.
		// The information is in Coordinated Universal Time (UTC) format.
		GetSystemTimeAsFileTime(&ftime);

		return ConvertTimestamp(ftime);
	}

	void GetCurrentCoreTimestamp(HANDLE handle_process,
		u64 *kernel_mode_timestamp, u64 *user_mode_timestamp) noexcept {
		
		Assert(kernel_mode_timestamp);
		Assert(user_mode_timestamp);

		FILETIME ftime;
		FILETIME kernel_mode_ftime;
		FILETIME user_mode_ftime;
		// Retrieves timing information for the specified process.
		// 1. A handle to the process whose timing information is sought.
		// 2. A pointer to a FILETIME structure that receives the creation time 
		//    of the process.
		// 3. A pointer to a FILETIME structure that receives the exit time of 
		//    the process.
		// 4. A pointer to a FILETIME structure that receives the amount of time 
		//    that the process has executed in kernel mode.
		// 5. A pointer to a FILETIME structure that receives the amount of time 
		//    that the process has executed in user mode.
		const BOOL result = GetProcessTimes(handle_process, 
			&ftime, &ftime, &kernel_mode_ftime, &user_mode_ftime);
		
		if (result != 0) {
			*kernel_mode_timestamp = ConvertTimestamp(kernel_mode_ftime);
			*user_mode_timestamp   = ConvertTimestamp(user_mode_ftime);
		}
		else {
			*kernel_mode_timestamp = 0;
			*user_mode_timestamp   = 0;
		}
	}
}