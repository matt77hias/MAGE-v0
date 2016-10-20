#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Returns the number of system cores (i.e. logical processors).

	 @return		The number of system cores (i.e. logical processors).
	 */
	inline int NumberOfSystemCores() {
		// Structure containing information about the current computer system. 
		SYSTEM_INFO system_info;
		// Retrieve information about the current system.
		GetSystemInfo(&system_info);
		// dwNumberOfProcessors:	The number of logical processors in the current group.
		return system_info.dwNumberOfProcessors;
	}

}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "parallel/atomic.hpp"
#include "parallel/lock.hpp"
#include "parallel/task.hpp"

#pragma endregion