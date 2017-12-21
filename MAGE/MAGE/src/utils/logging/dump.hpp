#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\platform\windows.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Linker Directives
//-----------------------------------------------------------------------------
#pragma region

#pragma comment ( lib, "dbghelp.lib" )

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	void AddUnhandledExceptionFilter() noexcept;

	void CreateMiniDump(EXCEPTION_POINTERS *exception_record) noexcept;
}