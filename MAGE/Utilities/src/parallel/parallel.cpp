//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "parallel\parallel.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	[[nodiscard]]
	U16 NumberOfPhysicalCores() {

		DWORD length = 0u;
		
		// Obtain the buffer length.
		{
			const BOOL result = GetLogicalProcessorInformationEx(
				RelationProcessorCore, nullptr, &length);
			ThrowIfFailed(result, 
				"Retrieving processor information failed.");
			ThrowIfFailed((ERROR_INSUFFICIENT_BUFFER != GetLastError()),
				"Retrieving processor information failed.");
		}

		auto buffer = MakeUnique< U8[] >(length);
		
		// Populate the buffer.
		{
			const PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX info =
				reinterpret_cast< PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX >(
					buffer.get());

			const BOOL result = GetLogicalProcessorInformationEx(
				RelationProcessorCore, info, &length);
			ThrowIfFailed(result, "Retrieving processor information failed.");
		}

		U16 nb_physical_cores = 0;
		size_t offset = 0u;
		do {
			const PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX current_info =
				reinterpret_cast< PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX >(
					buffer.get() + offset);
			
			offset += current_info->Size;
			++nb_physical_cores;

		} while (offset < length);
		
		return nb_physical_cores;
	}

	[[nodiscard]]
	U16 NumberOfSystemCores() noexcept {
		// Structure containing information about the current computer system. 
		SYSTEM_INFO system_info = {};
		// Retrieve information about the current system.
		GetSystemInfo(&system_info);
		// dwNumberOfProcessors:	The number of logical processors in the 
		//                          current group.
		return static_cast< U16 >(system_info.dwNumberOfProcessors);
	}
}