//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "parallel\parallel.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	size_t NumberOfPhysicalCores() noexcept {

		DWORD length = 0;
		const BOOL result_first = GetLogicalProcessorInformationEx(RelationProcessorCore, nullptr, &length);
		
		Assert(result_first == FALSE);
		Assert(GetLastError() == ERROR_INSUFFICIENT_BUFFER);

		UniquePtr< uint8_t[] > buffer(new uint8_t[length]);
		const PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX info = 
			reinterpret_cast< PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX >(buffer.get());

		const BOOL result_second = GetLogicalProcessorInformationEx(RelationProcessorCore, info, &length);

		Assert(result_second == TRUE);

		size_t nb_physical_cores = 0;
		size_t offset = 0;
		do {
			const PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX current_info =
				reinterpret_cast< PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX >(buffer.get() + offset);
			offset += current_info->Size;
			++nb_physical_cores;
		} while (offset < length);
		
		return nb_physical_cores;
	}

	size_t NumberOfSystemCores() noexcept {
		// Structure containing information about the current computer system. 
		SYSTEM_INFO system_info = {};
		// Retrieve information about the current system.
		GetSystemInfo(&system_info);
		// dwNumberOfProcessors:	The number of logical processors in the current group.
		return static_cast< size_t >(system_info.dwNumberOfProcessors);
	}
}