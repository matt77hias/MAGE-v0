#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	void AddUnhandledExceptionFilter() noexcept;

	void CreateMiniDump(EXCEPTION_POINTERS* exception_record) noexcept;
}