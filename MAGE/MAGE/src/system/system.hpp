#pragma once

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

	uint64_t GetVirtualMemoryUsage();

	uint64_t GetPhysicalMemoryUsage();

	double GetProcessorUsage();

}