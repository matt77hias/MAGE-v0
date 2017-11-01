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
	 Converts the given file time to an @c U64 (in 100 ns).

	 @param[in]		ftime
					A reference to the file time.
	 @return		A @c U64 (in 100 ns) representing the given file time 
					@a ftime.
	 */
	inline U64 ConvertTimestamp(const FILETIME &ftime) noexcept {
		return static_cast< U64 >(ftime.dwLowDateTime) 
			 | static_cast< U64 >(ftime.dwHighDateTime) << 32;
	}

	U64 GetCurrentSystemTimestamp() noexcept {
		
		FILETIME ftime;
		// Retrieves the current system date and time.
		// The information is in Coordinated Universal Time (UTC) format.
		GetSystemTimeAsFileTime(&ftime);

		return ConvertTimestamp(ftime);
	}

	const wstring GetCurrentLocalSystemDateAsString() noexcept {
		
		FILETIME ftime;
		// Retrieves the current system date and time.
		// The information is in Coordinated Universal Time (UTC) format.
		GetSystemTimeAsFileTime(&ftime);

		FILETIME local_ftime;
		{
			const BOOL result = FileTimeToLocalFileTime(&ftime, &local_ftime);
			if (!result) {
				return wstring();
			}
		}

		SYSTEMTIME local_stime;
		{
			const BOOL result = FileTimeToSystemTime(&local_ftime, &local_stime);
			if (!result) {
				return wstring();
			}
		}

		wchar_t str_date[255];

		const int result = GetDateFormat(LOCALE_USER_DEFAULT, 0,
			&local_stime, L"yyyy-MM-dd", str_date, _countof(str_date));
		return (result) ? wstring(str_date) : wstring();
	}

	const wstring GetCurrentLocalSystemTimeAsString() noexcept {
		
		FILETIME ftime;
		// Retrieves the current system date and time.
		// The information is in Coordinated Universal Time (UTC) format.
		GetSystemTimeAsFileTime(&ftime);

		FILETIME local_ftime;
		{
			const BOOL result = FileTimeToLocalFileTime(&ftime, &local_ftime);
			if (!result) {
				return wstring();
			}
		}

		SYSTEMTIME local_stime;
		{
			const BOOL result = FileTimeToSystemTime(&local_ftime, &local_stime);
			if (!result) {
				return wstring();
			}
		}

		wchar_t str_time[255];

		const int result = GetTimeFormat(LOCALE_USER_DEFAULT, 0, 
			&local_stime, L"HH-mm-ss", str_time, _countof(str_time));
		return (result) ? wstring(str_time) : wstring();
	}

	const wstring GetCurrentLocalSystemDateAndTimeAsString() noexcept {
		
		FILETIME ftime;
		// Retrieves the current system date and time.
		// The information is in Coordinated Universal Time (UTC) format.
		GetSystemTimeAsFileTime(&ftime);

		FILETIME local_ftime;
		{
			const BOOL result = FileTimeToLocalFileTime(&ftime, &local_ftime);
			if (!result) {
				return wstring();
			}
		}

		SYSTEMTIME local_stime;
		{
			const BOOL result = FileTimeToSystemTime(&local_ftime, &local_stime);
			if (!result) {
				return wstring();
			}
		}

		wchar_t str_date[255];
		wchar_t str_time[255];

		{
			const int result 
				= GetDateFormat(LOCALE_USER_DEFAULT, 0, 
					&local_stime, L"yyyy-MM-dd", str_date, _countof(str_date));
			if (!result) {
				return wstring();
			}
		}
		{
			const int result 
				= GetTimeFormat(LOCALE_USER_DEFAULT, 0, 
					&local_stime, L"HH-mm-ss", str_time, _countof(str_time));
			if (!result) {
				return wstring();
			}
		}

		return wstring(str_date) + L'-' + wstring(str_time);
	}

	void GetCurrentCoreTimestamp(HANDLE handle_process,
		U64 *kernel_mode_timestamp, U64 *user_mode_timestamp) noexcept {
		
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