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
	 Returns the system time of this timer.

	 @return		The current system time.
	 */
	uint64_t GetSystemTime();

	/**
	 Returns the core time of this timer.

	 @param[out]	kernel_mode_time
					A pointer to the amount of time that
					the process has executed in kernel mode.
	 @param[out]	user_mode_time
					A pointer to the amount of time that
					the process has executed in user mode.
	 */
	void GetCoreTime(uint64_t *kernel_mode_time, uint64_t *user_mode_time);

	/**
	 Returns the core time of this timer.

	 @param[in]		handle_process
					A handle to the process whose timing information is sought.
	 @param[out]	kernel_mode_time
					A pointer to the amount of time that
					the process has executed in kernel mode.
	 @param[out]	user_mode_time
					A pointer to the amount of time that
					the process has executed in user mode.
	 */
	void GetCoreTime(HANDLE handle_process,
		uint64_t *kernel_mode_time, uint64_t *user_mode_time);
}