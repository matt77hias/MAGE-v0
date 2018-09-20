//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "parallel\parallel.hpp"
#include "system\system_time.hpp"

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
				   ? 0u : ConvertTimestamp(local_ftime);
		}
	}

	[[nodiscard]]
	const std::wstring GetLocalSystemDateAsString() {
		FILETIME ftime;
		GetSystemTimeAsFileTime(&ftime);

		FILETIME local_ftime;
		if (FALSE == FileTimeToLocalFileTime(&ftime, &local_ftime)) {
			return {};
		}

		SYSTEMTIME local_stime;
		if (FALSE == FileTimeToSystemTime(&local_ftime, &local_stime)) {
			return {};
		}

		wchar_t str_date[255];

		const int result = GetDateFormat(LOCALE_USER_DEFAULT,
			                             0,
			                             &local_stime,
			                             L"yyyy-MM-dd",
			                             str_date,
			                             static_cast< int >(std::size(str_date)));

		return (result) ? std::wstring(str_date) : std::wstring();
	}

	[[nodiscard]]
	const std::wstring GetLocalSystemTimeAsString() {
		// Retrieves the current system date and time.
		// The information is in Coordinated Universal Time (UTC) format.
		FILETIME ftime;
		GetSystemTimeAsFileTime(&ftime);

		FILETIME local_ftime;
		if (FALSE == FileTimeToLocalFileTime(&ftime, &local_ftime)) {
			return {};
		}

		SYSTEMTIME local_stime;
		if (FALSE == FileTimeToSystemTime(&local_ftime, &local_stime)) {
			return {};
		}

		wchar_t str_time[255];

		const int result = GetTimeFormat(LOCALE_USER_DEFAULT,
			                             0,
			                             &local_stime,
			                             L"HH-mm-ss",
			                             str_time,
			                             static_cast< int >(std::size(str_time)));

		return (result) ? std::wstring(str_time) : std::wstring();
	}

	[[nodiscard]]
	const std::wstring GetLocalSystemDateAndTimeAsString() {
		// Retrieves the current system date and time.
		// The information is in Coordinated Universal Time (UTC) format.
		FILETIME ftime;
		GetSystemTimeAsFileTime(&ftime);

		FILETIME local_ftime;
		if (FALSE == FileTimeToLocalFileTime(&ftime, &local_ftime)) {
			return {};
		}

		SYSTEMTIME local_stime;
		if (FALSE == FileTimeToSystemTime(&local_ftime, &local_stime)) {
			return {};
		}

		wchar_t str_date[255];
		wchar_t str_time[255];

		if (!GetDateFormat(LOCALE_USER_DEFAULT,
			               0,
			               &local_stime,
			               L"yyyy-MM-dd",
			               str_date,
			               static_cast< int >(std::size(str_date)))) {

			return {};
		}

		if (!GetTimeFormat(LOCALE_USER_DEFAULT,
			               0,
			               &local_stime,
			               L"HH-mm-ss",
			               str_time,
			               static_cast< int >(std::size(str_time)))) {

			return {};
		}

		return std::wstring(str_date) + L'-' + std::wstring(str_time);
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
		const FU16 g_nb_system_cores = NumberOfSystemCores();

		/**
		 Returns the current core timestamps (in 100 ns).

		 @return		A pair containing the current kernel and user mode
						timestamp of the calling process.
		 @note			If the retrieval fails, both the kernel and user mode
						timestamp are zero. To get extended error information,
						call @c GetLastError.
		 */
		[[nodiscard]]
		const std::pair< U64, U64 > GetCoreTimestamps() noexcept {
			FILETIME ftime;
			FILETIME kernel_mode_ftime;
			FILETIME user_mode_ftime;
			// Retrieve timing information for the process.
			const BOOL result = GetProcessTimes(GetCurrentProcess(),
												&ftime,
												&ftime,
												&kernel_mode_ftime,
												&user_mode_ftime);
			if (FALSE == result) {
				return {};
			}

			return {
				ConvertTimestamp(kernel_mode_ftime),
				ConvertTimestamp(user_mode_ftime)
			};
		}

		/**
		 Returns the current core timestamp (in 100 ns).

		 @return		The current core timestamp of the calling process.
		 */
		[[nodiscard]]
		inline U64 GetCoreTimestamp() noexcept {
			const auto timestamps = GetCoreTimestamps();
			return timestamps.first + timestamps.second;
		}

		/**
		 Returns the current kernel mode core timestamp (in 100 ns).

		 @return		The current kernel mode core timestamp of the calling
						process.
		 */
		[[nodiscard]]
		inline U64 GetKernelModeCoreTimestamp() noexcept {
			const auto timestamps = GetCoreTimestamps();
			return timestamps.first;
		}

		/**
		 Returns the current user mode core timestamp (in 100 ns).

		 @return		The current user mode core timestamp of the calling
						process.
		 */
		[[nodiscard]]
		inline U64 GetUserModeCoreTimestamp() noexcept {
			const auto timestamps = GetCoreTimestamps();
			return timestamps.second;
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
