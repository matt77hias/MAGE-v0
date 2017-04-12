#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Returns the current system timestamp (in 100 ns).

	 @return		The current system timestamp (in 100 ns).
	 */
	uint64_t GetCurrentSystemTimestamp();

	/**
	 Returns the current core timestamp (in 100 ns).

	 @param[in]		handle_process
					A handle to the process whose timing information is sought.
	 @param[out]	kernel_mode_timestamp
					A pointer to the current kernel mode timestamp
					of the given process.
	 @param[out]	user_mode_timestamp
					A pointer to the current user mode timestamp
					of the given process.
	 */
	void GetCurrentCoreTimestamp(HANDLE handle_process,
		uint64_t *kernel_mode_timestamp, uint64_t *user_mode_timestamp);

	/**
	 Returns the current core timestamp (in 100 ns).

	 @param[out]	kernel_mode_timestamp
					A pointer to the current kernel mode timestamp
					of the calling process.
	 @param[out]	user_mode_timestamp
					A pointer to the current user mode timestamp
					of the calling process.
	 */
	inline void GetCurrentCoreTimestamp(uint64_t *kernel_mode_timestamp, uint64_t *user_mode_timestamp) {
		GetCurrentCoreTimestamp(GetCurrentProcess(), kernel_mode_timestamp, user_mode_timestamp);
	}
}