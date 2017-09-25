#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Returns the current system timestamp (in 100 ns).

	 @return		The current system timestamp (in 100 ns).
	 */
	u64 GetCurrentSystemTimestamp() noexcept;

	/**
	 Returns the current core timestamp (in 100 ns).

	 @pre			@a handle_process is not equal to @c nullptr.
	 @pre			@a kernel_mode_timestamp is not equal to @c nullptr.
	 @pre			@a user_mode_timestamp is not equal to @c nullptr.
	 @pre			@a handle_process must have the 
					@c PROCESS_QUERY_INFORMATION or 
					@c PROCESS_QUERY_LIMITED_INFORMATION access right.
	 @param[in]		handle_process
					A handle to the process whose timing information is 
					sought.
	 @param[out]	kernel_mode_timestamp
					A pointer to the current kernel mode timestamp of the 
					given process.
	 @param[out]	user_mode_timestamp
					A pointer to the current user mode timestamp of the given 
					process.
	 @note			If the retrieval fails, both @a kernel_mode_timestamp and 
					@a user_mode_timestamp point to zero. To get extended error 
					information, call @c GetLastError.
	 */
	void GetCurrentCoreTimestamp(HANDLE handle_process,
		u64 *kernel_mode_timestamp, u64 *user_mode_timestamp) noexcept;

	/**
	 Returns the current core timestamp (in 100 ns).

	 @pre			@a kernel_mode_timestamp is not equal to @c nullptr.
	 @pre			@a user_mode_timestamp is not equal to @c nullptr.
	 @param[out]	kernel_mode_timestamp
					A pointer to the current kernel mode timestamp of the 
					calling process.
	 @param[out]	user_mode_timestamp
					A pointer to the current user mode timestamp of the 
					calling process.
	 @note			If the retrieval fails, both @a kernel_mode_timestamp and 
					@a user_mode_timestamp point to zero. To get extended 
					error information, call @c GetLastError.
	 */
	inline void GetCurrentCoreTimestamp(
		u64 *kernel_mode_timestamp, u64 *user_mode_timestamp) noexcept {
		
		GetCurrentCoreTimestamp(
			GetCurrentProcess(), kernel_mode_timestamp, user_mode_timestamp);
	}
}