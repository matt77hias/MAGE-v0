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

#include <windows.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Type Checks
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Same Types
	//-------------------------------------------------------------------------

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

	//-------------------------------------------------------------------------
	// Equivalent Types
	//-------------------------------------------------------------------------

	template< typename T, typename U >
	struct is_equivalent_integral : public std::bool_constant<
		(sizeof(T) == sizeof(U))
		&& std::is_integral_v< T >
		&& std::is_integral_v< U >
		&& (std::is_signed_v< T >   == std::is_signed_v< U >)
		&& (std::is_unsigned_v< T > == std::is_unsigned_v< U >) >{};

	template< typename T, typename U >
	constexpr bool is_equivalent_integral_v = is_equivalent_integral< T, U >::value;

	static_assert(is_equivalent_integral_v< U16, WORD >,
				  "MAGE/Windows type mismatch");

	static_assert(is_equivalent_integral_v< U32, DWORD >,
				  "MAGE/Windows type mismatch");
	static_assert(is_equivalent_integral_v< U64, DWORDLONG >,
				  "MAGE/Windows type mismatch");
	static_assert(is_equivalent_integral_v< U32, DWORD32 >,
				  "MAGE/Windows type mismatch");
	static_assert(is_equivalent_integral_v< U64, DWORD64 >,
				  "MAGE/Windows type mismatch");

	static_assert(is_equivalent_integral_v< S32, LONG >,
				  "MAGE/Windows type mismatch");
	static_assert(is_equivalent_integral_v< S64, LONGLONG >,
				  "MAGE/Windows type mismatch");
	static_assert(is_equivalent_integral_v< S32, LONG32 >,
				  "MAGE/Windows type mismatch");
	static_assert(is_equivalent_integral_v< S64, LONG64 >,
				  "MAGE/Windows type mismatch");

	static_assert(is_equivalent_integral_v< U32, ULONG >,
				  "MAGE/Windows type mismatch");
	static_assert(is_equivalent_integral_v< U64, ULONGLONG >,
				  "MAGE/Windows type mismatch");
	static_assert(is_equivalent_integral_v< U32, ULONG32 >,
				  "MAGE/Windows type mismatch");
	static_assert(is_equivalent_integral_v< U64, ULONG64 >,
				  "MAGE/Windows type mismatch");

	static_assert(is_equivalent_integral_v< std::size_t, SIZE_T >,
				  "MAGE/Windows type mismatch");
}