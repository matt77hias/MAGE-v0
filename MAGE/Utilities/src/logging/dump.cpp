//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\dump.hpp"
#include "logging\error.hpp"
#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <dbghelp.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	[[nodiscard]] static inline LONG WINAPI 
		UnhandledExceptionFilter(EXCEPTION_POINTERS *exception_record) noexcept {
		
		CreateMiniDump(exception_record);
		return EXCEPTION_CONTINUE_SEARCH;
	}

	void AddUnhandledExceptionFilter() noexcept {
		SetUnhandledExceptionFilter(UnhandledExceptionFilter);
	}

	void CreateMiniDump(EXCEPTION_POINTERS *exception_record) noexcept {
		Info("Start creating a mini dump file.");

		auto file_handle = CreateUniqueHandle(
			CreateFile(L"MiniDump.dmp", GENERIC_READ | GENERIC_WRITE,
			0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr));

		if (!file_handle) {
			Error("Failed to create file: %u.", GetLastError());
			return;
		}

		MINIDUMP_EXCEPTION_INFORMATION info = {};
		info.ThreadId          = GetCurrentThreadId();
		info.ExceptionPointers = exception_record;
		info.ClientPointers    = FALSE;

		const auto type = static_cast< MINIDUMP_TYPE >(
			                  MiniDumpWithFullMemory |
			                  MiniDumpWithFullMemoryInfo |
			                  MiniDumpWithHandleData |
			                  MiniDumpWithThreadInfo |
			                  MiniDumpWithUnloadedModules);

		const BOOL result = MiniDumpWriteDump(
			GetCurrentProcess(), GetCurrentProcessId(), file_handle.get(), 
			type, (exception_record) ? &info : nullptr, nullptr, nullptr);

		if (TRUE == result) {
			Info("Succeeded to create a mini dump file: MiniDump.dmp.");
		}
		else {
			Error("Failed to create a mini dump file: %u.", GetLastError());
		}
	}
}