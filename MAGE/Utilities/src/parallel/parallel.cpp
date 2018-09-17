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
	FU16 NumberOfPhysicalCores() {
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
			const auto info = reinterpret_cast< 
				PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX >(buffer.get());

			const BOOL result = GetLogicalProcessorInformationEx(
				RelationProcessorCore, info, &length);
			ThrowIfFailed(result, "Retrieving processor information failed.");
		}

		FU16 nb_physical_cores = 0u;
		std::size_t offset = 0u;
		do {
			const auto info = reinterpret_cast< 
				PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX >(buffer.get() + offset);
			
			offset += static_cast< std::size_t >(info->Size);
			++nb_physical_cores;

		} while (offset < static_cast< std::size_t >(length));
		
		return nb_physical_cores;
	}

	[[nodiscard]]
	FU16 NumberOfSystemCores() noexcept {
		SYSTEM_INFO system_info = {};
		GetSystemInfo(&system_info);
		// Return the number of logical processors in the current group.
		return static_cast< FU16 >(system_info.dwNumberOfProcessors);
	}
}
