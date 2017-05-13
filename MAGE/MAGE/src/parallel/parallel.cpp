//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"
#include "parallel\parallel.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	size_t NumberOfSystemCores() noexcept {
		// Structure containing information about the current computer system. 
		SYSTEM_INFO system_info;
		ZeroMemory(&system_info, sizeof(system_info));
		// Retrieve information about the current system.
		GetSystemInfo(&system_info);
		// dwNumberOfProcessors:	The number of logical processors in the current group.
		return static_cast< size_t >(system_info.dwNumberOfProcessors);
	}
}