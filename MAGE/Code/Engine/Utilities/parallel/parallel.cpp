//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "exception\exception.hpp"
#include "parallel\parallel.hpp"

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

		auto buffer = DynamicArray< U8 >(length);

		// Populate the buffer.
		{
			const auto info = reinterpret_cast<
				PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX >(buffer.data());

			const BOOL result = GetLogicalProcessorInformationEx(
				RelationProcessorCore, info, &length);
			ThrowIfFailed(result, "Retrieving processor information failed.");
		}

		FU16 nb_physical_cores = 0u;
		DWORD offset = 0u;
		do {
			const auto info = reinterpret_cast<
				PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX >(buffer.data() + offset);

			offset += info->Size;
			++nb_physical_cores;

		} while (offset < length);

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
