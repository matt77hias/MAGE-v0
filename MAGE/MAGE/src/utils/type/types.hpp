#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

// Scalar types.
// Vector types.
#include "utils\type\vector_types.hpp"

// Platform types.
// Smart pointer types.
#include "utils\memory\memory.hpp"

// String types.
#include "utils\string\string.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions: Floating Point Values
	//-------------------------------------------------------------------------

	static_assert(std::is_same< F32, FLOAT >::value, 
		"MAGE/Windows primitive type mismatch");

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions: Signed Integer Values
	//-------------------------------------------------------------------------

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