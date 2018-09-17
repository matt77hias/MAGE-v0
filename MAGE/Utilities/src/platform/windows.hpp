#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

// Scalar types.
#include "type\scalar_types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Defines
//-----------------------------------------------------------------------------
#pragma region

// Exclude APIs such as Cryptography, DDE, RPC, Shell, and Windows Sockets.
#define WIN32_LEAN_AND_MEAN

// Inhibit definitions: macros min(a,b) and max(a,b).
#define NOMINMAX

// Inhibit definitions: DrawText() and DT_*.
#define NODRAWTEXT

// Inhibit definitions: all GDI defines and routines.
#define NOGDI

// Inhibit definitions
#define NOBITMAP

// Inhibit definitions: typedef MSG and associated routines.
#define NOMCX

// Inhibit definitions: all Service Controller routines, SERVICE_ equates, etc.
#define NOSERVICE

// Inhibit definitions: help engine interface.
#define NOHELP

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <type_traits>
#include <windows.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Type Checks
//-----------------------------------------------------------------------------
namespace mage {

	static_assert(std::is_same_v< F32, FLOAT  >, "MAGE/Windows type mismatch");

	static_assert(std::is_same_v< S32, INT    >, "MAGE/Windows type mismatch");
	static_assert(std::is_same_v< S8,  INT8   >, "MAGE/Windows type mismatch");
	static_assert(std::is_same_v< S16, INT16  >, "MAGE/Windows type mismatch");
	static_assert(std::is_same_v< S32, INT32  >, "MAGE/Windows type mismatch");
	static_assert(std::is_same_v< S64, INT64  >, "MAGE/Windows type mismatch");
	
	static_assert(std::is_same_v< U32, UINT   >, "MAGE/Windows type mismatch");
	static_assert(std::is_same_v< U8,  UINT8  >, "MAGE/Windows type mismatch");
	static_assert(std::is_same_v< U16, UINT16 >, "MAGE/Windows type mismatch");
	static_assert(std::is_same_v< U32, UINT32 >, "MAGE/Windows type mismatch");
	static_assert(std::is_same_v< U64, UINT64 >, "MAGE/Windows type mismatch");

	static_assert(std::is_same_v< U8,  BYTE   >, "MAGE/Windows type mismatch");

	static_assert(sizeof(U16) == sizeof(WORD), 
				  "MAGE/Windows type mismatch");
	static_assert(std::is_unsigned_v< WORD >, 
				  "MAGE/Windows type mismatch");

	static_assert(sizeof(U32) == sizeof(DWORD), 
				  "MAGE/Windows type mismatch");
	static_assert(std::is_unsigned_v< DWORD >, 
				  "MAGE/Windows type mismatch");
	static_assert(sizeof(U64) == sizeof(DWORDLONG), 
				  "MAGE/Windows type mismatch");
	static_assert(std::is_unsigned_v< DWORDLONG >, 
				  "MAGE/Windows type mismatch");
	static_assert(sizeof(U32) == sizeof(DWORD32), 
				  "MAGE/Windows type mismatch");
	static_assert(std::is_unsigned_v< DWORD32 >, 
				  "MAGE/Windows type mismatch");
	static_assert(sizeof(U64) == sizeof(DWORD64), 
				  "MAGE/Windows type mismatch");
	static_assert(std::is_unsigned_v< DWORD64 >,  
				  "MAGE/Windows type mismatch");

	static_assert(sizeof(S32) == sizeof(LONG), 
				  "MAGE/Windows type mismatch");
	static_assert(std::is_signed_v< LONG >, 
				  "MAGE/Windows type mismatch");
	static_assert(sizeof(S64) == sizeof(LONGLONG), 
				  "MAGE/Windows type mismatch");
	static_assert(std::is_signed_v< LONGLONG >, 
				  "MAGE/Windows type mismatch");
	static_assert(sizeof(S32) == sizeof(LONG32), 
				  "MAGE/Windows type mismatch");
	static_assert(std::is_signed_v< LONG32 >, 
				  "MAGE/Windows type mismatch");
	static_assert(sizeof(S64) == sizeof(LONG64), 
				  "MAGE/Windows type mismatch");
	static_assert(std::is_signed_v< LONG64 >, 
				  "MAGE/Windows type mismatch");

	static_assert(sizeof(U32) == sizeof(ULONG), 
				  "MAGE/Windows type mismatch");
	static_assert(std::is_unsigned_v< ULONG >, 
				  "MAGE/Windows type mismatch");
	static_assert(sizeof(U64) == sizeof(ULONGLONG), 
				  "MAGE/Windows type mismatch");
	static_assert(std::is_unsigned_v< ULONGLONG >, 
				  "MAGE/Windows type mismatch");
	static_assert(sizeof(U32) == sizeof(ULONG32), 
				  "MAGE/Windows type mismatch");
	static_assert(std::is_unsigned_v< ULONG32 >, 
				  "MAGE/Windows type mismatch");
	static_assert(sizeof(U64) == sizeof(ULONG64), 
				  "MAGE/Windows type mismatch");
	static_assert(std::is_unsigned_v< ULONG64 >, 
				  "MAGE/Windows type mismatch");

	static_assert(sizeof(std::size_t) == sizeof(SIZE_T), 
				  "MAGE/Windows type mismatch");
	static_assert(std::is_unsigned_v< SIZE_T >,
				  "MAGE/Windows type mismatch");
}