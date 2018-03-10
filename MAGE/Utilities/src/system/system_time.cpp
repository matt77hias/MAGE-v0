//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "system\system_time.hpp"
#include "parallel\parallel.hpp"

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

	//-------------------------------------------------------------------------
	// File Time
	//-------------------------------------------------------------------------
	namespace {

		/**
		 Converts the given file time to an @c U64 (in 100 ns).

		 @param[in]		ftime
						A reference to the file time.
		 @return		A @c U64 (in 100 ns) representing the given file time.
		 */
		[[nodiscard]]
		inline U64 ConvertTimestamp(const FILETIME& ftime) noexcept {
			return static_cast< U64 >(ftime.dwLowDateTime)
				 | static_cast< U64 >(ftime.dwHighDateTime) << 32u;
		}
	}

	//-------------------------------------------------------------------------
	// System Time
	//-------------------------------------------------------------------------
	#pragma region

	namespace {

		/**
		 Returns the current system timestamp (in 100 ns).

		 @return		The current system timestamp (in 100 ns).
		 */
		[[nodiscard]]
		U64 GetSystemTimestamp() noexcept {
			// Retrieves the current system date and time.
			// The information is in Coordinated Universal Time (UTC) format.
			FILETIME ftime;
			GetSystemTimeAsFileTime(&ftime);

			FILETIME local_ftime;
			return (FALSE == FileTimeToLocalFileTime(&ftime, &local_ftime)) 
				   ? 0ull : ConvertTimestamp(local_ftime);
		}
	}

	[[nodiscard]]
	const wstring GetLocalSystemDateAsString() {
		FILETIME ftime;
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

	[[nodiscard]]
	const wstring GetLocalSystemTimeAsString() {
		// Retrieves the current system date and time.
		// The information is in Coordinated Universal Time (UTC) format.
		FILETIME ftime;
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

	[[nodiscard]]
	const wstring GetLocalSystemDateAndTimeAsString() {
		// Retrieves the current system date and time.
		// The information is in Coordinated Universal Time (UTC) format.
		FILETIME ftime;
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

	[[nodiscard]]
	typename const SystemClock::time_point SystemClock::now() noexcept {
		return time_point(duration(GetSystemTimestamp()));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Core Time
	//-------------------------------------------------------------------------
	#pragma region

	namespace {

		/**
		 The number of system cores.
		 */
		const U16 g_nb_system_cores = NumberOfSystemCores();

		/**
		 Returns the current core timestamp (in 100 ns).

		 @param[out]	kernel_mode_timestamp
						A reference to the current kernel mode timestamp of the 
						calling process.
		 @param[out]	user_mode_timestamp
						A reference to the current user mode timestamp of the 
						calling process.
		 @note			If the retrieval fails, both @a kernel_mode_timestamp and 
						@a user_mode_timestamp are zero. To get extended error 
						information, call @c GetLastError.
		 */
		void GetCoreTimestamp(U64& kernel_mode_timestamp, 
							  U64& user_mode_timestamp) noexcept {
		
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
			const BOOL result = GetProcessTimes(GetCurrentProcess(),
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

		/**
		 Returns the current core timestamp (in 100 ns).
	 
		 @return		The current core timestamp of the calling process.
		 */
		[[nodiscard]]
		inline U64 GetCoreTimestamp() noexcept {
			U64 kernel_mode_timestamp = 0ull;
			U64 user_mode_timestamp   = 0ull;
			GetCoreTimestamp(kernel_mode_timestamp, user_mode_timestamp);
		
			return kernel_mode_timestamp + user_mode_timestamp;
		}

		/**
		 Returns the current kernel mode core timestamp (in 100 ns).
	 
		 @return		The current kernel mode core timestamp of the calling 
						process.
		 */
		[[nodiscard]]
		inline U64 GetKernelModeCoreTimestamp() noexcept {
			U64 kernel_mode_timestamp = 0ull;
			U64 user_mode_timestamp   = 0ull;
			GetCoreTimestamp(kernel_mode_timestamp, user_mode_timestamp);
		
			return kernel_mode_timestamp;
		}

		/**
		 Returns the current user mode core timestamp (in 100 ns).
	 
		 @return		The current user mode core timestamp of the calling 
						process.
		 */
		[[nodiscard]]
		inline U64 GetUserModeCoreTimestamp() noexcept {
			U64 kernel_mode_timestamp = 0ull;
			U64 user_mode_timestamp   = 0ull;
			GetCoreTimestamp(kernel_mode_timestamp, user_mode_timestamp);
		
			return user_mode_timestamp;
		}

		/**
		 Returns the current core timestamp per system core (in 100 ns).
	 
		 @return		The current core timestamp of the calling process per 
						system core.
		 */
		[[nodiscard]]
		inline U64 GetCoreTimestampPerCore() noexcept {
			return GetCoreTimestamp() / g_nb_system_cores;
		}

		/**
		 Returns the current kernel mode core timestamp per system core (in 100 ns).
	 
		 @return		The current kernel mode core timestamp of the calling 
						process per system core.
		 */
		[[nodiscard]]
		inline U64 GetKernelModeCoreTimestampPerCore() noexcept {
			return GetKernelModeCoreTimestamp() / g_nb_system_cores;
		}

		/**
		 Returns the current user mode core timestamp per system core (in 100 ns).
	 
		 @return		The current user mode core timestamp of the calling 
						process per system core.
		 */
		[[nodiscard]]
		inline U64 GetUserModeCoreTimestampPerCore() noexcept {
			return GetUserModeCoreTimestamp() / g_nb_system_cores;
		}
	}

	[[nodiscard]]
	typename const CoreClock::time_point CoreClock::now() noexcept {
		return time_point(duration(GetCoreTimestamp()));
	}

	[[nodiscard]]
	typename const KernelModeCoreClock::time_point
		KernelModeCoreClock::now() noexcept {

		return time_point(duration(GetKernelModeCoreTimestamp()));
	}

	[[nodiscard]]
	typename const UserModeCoreClock::time_point
		UserModeCoreClock::now() noexcept {

		return time_point(duration(GetUserModeCoreTimestamp()));
	}

	[[nodiscard]]
	typename const CoreClockPerCore::time_point
		CoreClockPerCore::now() noexcept {

		return time_point(duration(GetCoreTimestampPerCore()));
	}

	[[nodiscard]]
	typename const KernelModeCoreClockPerCore::time_point
		KernelModeCoreClockPerCore::now() noexcept {

		return time_point(duration(GetKernelModeCoreTimestampPerCore()));
	}

	[[nodiscard]]
	typename const UserModeCoreClockPerCore::time_point
		UserModeCoreClockPerCore::now() noexcept {

		return time_point(duration(GetUserModeCoreTimestampPerCore()));
	}

	#pragma endregion
}