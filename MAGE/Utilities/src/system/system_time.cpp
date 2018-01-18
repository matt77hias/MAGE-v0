//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "system\system_time.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <iterator>

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
	[[nodiscard]] static inline U64 
		ConvertTimestamp(const FILETIME &ftime) noexcept {
		
		return static_cast< U64 >(ftime.dwLowDateTime) 
			 | static_cast< U64 >(ftime.dwHighDateTime) << 32;
	}

	[[nodiscard]] U64 GetCurrentSystemTimestamp() noexcept {
		FILETIME ftime;
		// Retrieves the current system date and time.
		// The information is in Coordinated Universal Time (UTC) format.
		GetSystemTimeAsFileTime(&ftime);

		return ConvertTimestamp(ftime);
	}

	[[nodiscard]] const wstring GetCurrentLocalSystemDateAsString() {
		FILETIME ftime;
		// Retrieves the current system date and time.
		// The information is in Coordinated Universal Time (UTC) format.
		GetSystemTimeAsFileTime(&ftime);

		FILETIME local_ftime;
		if (FALSE == FileTimeToLocalFileTime(&ftime, &local_ftime)) {
			return wstring();
		}

		SYSTEMTIME local_stime;
		if (FALSE == FileTimeToSystemTime(&local_ftime, &local_stime)) {
			return wstring();
		}

		wchar_t str_date[255];

		const int result = GetDateFormat(LOCALE_USER_DEFAULT, 
			                             0,
			                             &local_stime, 
			                             L"yyyy-MM-dd", 
			                             str_date, 
			                             static_cast< int >(std::size(str_date)));
		
		return (result) ? wstring(str_date) : wstring();
	}

	[[nodiscard]] const wstring GetCurrentLocalSystemTimeAsString() {
		FILETIME ftime;
		// Retrieves the current system date and time.
		// The information is in Coordinated Universal Time (UTC) format.
		GetSystemTimeAsFileTime(&ftime);

		FILETIME local_ftime;
		if (FALSE == FileTimeToLocalFileTime(&ftime, &local_ftime)) {
			return wstring();
		}

		SYSTEMTIME local_stime;
		if (FALSE == FileTimeToSystemTime(&local_ftime, &local_stime)) {
			return wstring();
		}

		wchar_t str_time[255];

		const int result = GetTimeFormat(LOCALE_USER_DEFAULT, 
			                             0, 
			                             &local_stime, 
			                             L"HH-mm-ss", 
			                             str_time, 
			                             static_cast< int >(std::size(str_time)));
		
		return (result) ? wstring(str_time) : wstring();
	}

	[[nodiscard]] const wstring GetCurrentLocalSystemDateAndTimeAsString() {
		FILETIME ftime;
		// Retrieves the current system date and time.
		// The information is in Coordinated Universal Time (UTC) format.
		GetSystemTimeAsFileTime(&ftime);

		FILETIME local_ftime;
		if (FALSE == FileTimeToLocalFileTime(&ftime, &local_ftime)) {
			return wstring();
		}

		SYSTEMTIME local_stime;
		if (FALSE == FileTimeToSystemTime(&local_ftime, &local_stime)) {
			return wstring();
		}

		wchar_t str_date[255];
		wchar_t str_time[255];

		if (!GetDateFormat(LOCALE_USER_DEFAULT, 
			               0, 
			               &local_stime, 
			               L"yyyy-MM-dd", 
			               str_date, 
			               static_cast< int >(std::size(str_date)))) {

			return wstring();
		}
		
		if (!GetTimeFormat(LOCALE_USER_DEFAULT, 
			               0, 
			               &local_stime, 
			               L"HH-mm-ss", 
			               str_time, 
			               static_cast< int >(std::size(str_time)))) {

			return wstring();
		}

		return wstring(str_date) + L'-' + wstring(str_time);
	}

	void GetCurrentCoreTimestamp(HANDLE handle_process,
		                         U64 &kernel_mode_timestamp, 
		                         U64 &user_mode_timestamp) noexcept {
		
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
			                                &ftime, 
			                                &ftime, 
			                                &kernel_mode_ftime, 
			                                &user_mode_ftime);
		
		if (TRUE == result) {
			kernel_mode_timestamp = ConvertTimestamp(kernel_mode_ftime);
			user_mode_timestamp   = ConvertTimestamp(user_mode_ftime);
		}
		else {
			kernel_mode_timestamp = 0ull;
			user_mode_timestamp   = 0ull;
		}
	}
}