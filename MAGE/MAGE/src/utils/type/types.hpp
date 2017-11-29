#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\memory\memory.hpp"
#include "utils\string\string.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions: Floating Point Values
	//-------------------------------------------------------------------------

	/**
	 A 32-bit floating point value.
	 */
	using F32 = float;
	
	/**
	 A 64-bit floating point value.
	 */
	using F64 = double;

	static_assert(4 == sizeof(F32));
	static_assert(8 == sizeof(F64));

	static_assert(std::is_same< F32, FLOAT >::value, 
		"MAGE/Windows primitive type mismatch");

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions: Signed Integer Values
	//-------------------------------------------------------------------------

	/**
	 A signed 8-bit integer value.
	 */
	using S8 = signed __int8;

	/**
	 A signed 16-bit integer value.
	 */
	using S16 = signed __int16;
	
	/**
	 A signed 32-bit integer value.
	 */
	using S32 = signed __int32;
	
	/**
	 A signed 64-bit integer value.
	 */
	using S64 = signed __int64;

	static_assert(1 == sizeof(S8));
	static_assert(2 == sizeof(S16));
	static_assert(4 == sizeof(S32));
	static_assert(8 == sizeof(S64));

	static_assert(std::is_same< S32, INT >::value,
		"MAGE/Windows primitive type mismatch");

	static_assert(std::is_same< S8, INT8 >::value,
		"MAGE/Windows primitive type mismatch");

	static_assert(std::is_same< S16, INT16 >::value,
		"MAGE/Windows primitive type mismatch");

	static_assert(std::is_same< S32, INT32 >::value,
		"MAGE/Windows primitive type mismatch");

	static_assert(std::is_same< S64, INT64 >::value,
		"MAGE/Windows primitive type mismatch");

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions: Unsigned Integer Values
	//-------------------------------------------------------------------------

	/**
	 An unsigned 8-bit integer value.
	 */
	using U8 = unsigned __int8;

	/**
	 An unsigned 16-bit integer value.
	 */
	using U16 = unsigned __int16;
	
	/**
	 An unsigned 32-bit integer value.
	 */
	using U32 = unsigned __int32;
	
	/**
	 An unsigned 64-bit integer value.
	 */
	using U64 = unsigned __int64;

	static_assert(1 == sizeof(U8));
	static_assert(2 == sizeof(U16));
	static_assert(4 == sizeof(U32));
	static_assert(8 == sizeof(U64));

	static_assert(std::is_same< U32, UINT >::value,
		"MAGE/Windows primitive type mismatch");

	static_assert(std::is_same< U8, UINT8 >::value,
		"MAGE/Windows primitive type mismatch");

	static_assert(std::is_same< U16, UINT16 >::value,
		"MAGE/Windows primitive type mismatch");

	static_assert(std::is_same< U32, UINT32 >::value,
		"MAGE/Windows primitive type mismatch");

	static_assert(std::is_same< U64, UINT64 >::value,
		"MAGE/Windows primitive type mismatch");
}