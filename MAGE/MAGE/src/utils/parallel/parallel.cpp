//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\type\types.hpp"
#include "utils\parallel\parallel.hpp"
#include "utils\exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	size_t NumberOfPhysicalCores() noexcept {

		DWORD length = 0;
		
		// Obtain the buffer length.
		{
			const BOOL result = GetLogicalProcessorInformationEx(
				RelationProcessorCore, nullptr, &length);
			ThrowIfFailed(result, 
				"Retrieving processor information failed.");
			ThrowIfFailed((ERROR_INSUFFICIENT_BUFFER != GetLastError()),
				"Retrieving processor information failed.");
		}
		
		UniquePtr< U8[] > buffer(MakeUnique< U8[] >(length));
		
		// Populate the buffer.
		{
			const PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX info =
				reinterpret_cast< PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX >(
					buffer.get());

			const BOOL result = GetLogicalProcessorInformationEx(
				RelationProcessorCore, info, &length);
			ThrowIfFailed(result, "Retrieving processor information failed.");
		}

		size_t nb_physical_cores = 0;
		size_t offset = 0;
		do {
			
			const PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX current_info =
				reinterpret_cast< PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX >(
					buffer.get() + offset);
			
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
		// dwNumberOfProcessors:	The number of logical processors in the 
		//                          current group.
		return static_cast< size_t >(system_info.dwNumberOfProcessors);
	}
}