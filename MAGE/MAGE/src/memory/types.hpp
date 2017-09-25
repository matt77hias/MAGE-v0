#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "string\string.hpp"

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
	using f32 = float;
	
	/**
	 A 64-bit floating point value.
	 */
	using f64 = double;

	static_assert(std::is_same< f32, FLOAT >::value, 
		"MAGE/Windows primitive type mismatch");

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions: Signed Integer Values
	//-------------------------------------------------------------------------

	/**
	 A signed 8-bit integer value.
	 */
	using i8 = signed __int8;

	/**
	 A signed 16-bit integer value.
	 */
	using i16 = signed __int16;
	
	/**
	 A signed 32-bit integer value.
	 */
	using i32 = signed __int32;
	
	/**
	 A signed 64-bit integer value.
	 */
	using i64 = signed __int64;

	static_assert(std::is_same< i32, INT >::value,
		"MAGE/Windows primitive type mismatch");

	static_assert(std::is_same< i8, INT8 >::value,
		"MAGE/Windows primitive type mismatch");

	static_assert(std::is_same< i16, INT16 >::value,
		"MAGE/Windows primitive type mismatch");

	static_assert(std::is_same< i32, INT32 >::value,
		"MAGE/Windows primitive type mismatch");

	static_assert(std::is_same< i64, INT64 >::value,
		"MAGE/Windows primitive type mismatch");

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions: Unsigned Integer Values
	//-------------------------------------------------------------------------

	/**
	 An unsigned 8-bit integer value.
	 */
	using u8 = unsigned __int8;

	/**
	 An unsigned 16-bit integer value.
	 */
	using u16 = unsigned __int16;
	
	/**
	 An unsigned 32-bit integer value.
	 */
	using u32 = unsigned __int32;
	
	/**
	 An unsigned 64-bit integer value.
	 */
	using u64 = unsigned __int64;

	static_assert(std::is_same< u32, UINT >::value,
		"MAGE/Windows primitive type mismatch");

	static_assert(std::is_same< u8, UINT8 >::value,
		"MAGE/Windows primitive type mismatch");

	static_assert(std::is_same< u16, UINT16 >::value,
		"MAGE/Windows primitive type mismatch");

	static_assert(std::is_same< u32, UINT32 >::value,
		"MAGE/Windows primitive type mismatch");

	static_assert(std::is_same< u64, UINT64 >::value,
		"MAGE/Windows primitive type mismatch");
}