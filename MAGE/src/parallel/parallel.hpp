#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#include <windows.h>

//-----------------------------------------------------------------------------
// Declarations and Definitions
//-----------------------------------------------------------------------------
inline int NumberOfSystemCores() {
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	return sysinfo.dwNumberOfProcessors;
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "parallel/atomic.hpp"
#include "parallel/lock.hpp"
#include "parallel/task.hpp"