#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

// Scalar types.
#include "type\scalar_types.hpp"

#include "collection\array.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Floating Point Vectors
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A 2x1 32-bit floating point vector type.
	 */
	using F32x2 = Array< F32, 2 >;

	/**
	 A 3x1 32-bit floating point vector type.
	 */
	using F32x3 = Array< F32, 3 >;

	/**
	 A 4x1 32-bit floating point vector type.
	 */
	using F32x4 = Array< F32, 4 >;

	static_assert(8  == sizeof(F32x2));
	static_assert(12 == sizeof(F32x3));
	static_assert(16 == sizeof(F32x4));

	/**
	 A 2x1 32-bit floating point aligned vector type.
	 */
	using F32x2A = Array< F32, 2, 16 >;

	/**
	 A 3x1 32-bit floating point aligned vector type.
	 */
	using F32x3A = Array< F32, 3, 16 >;

	/**
	 A 4x1 32-bit floating point aligned vector type.
	 */
	using F32x4A = Array< F32, 4, 16 >;

	static_assert(16 == sizeof(F32x2A));
	static_assert(16 == sizeof(F32x3A));
	static_assert(16 == sizeof(F32x4A));

	/**
	 A 2x1 64-bit floating point vector type.
	 */
	using F64x2 = Array< F64, 2 >;

	/**
	 A 3x1 64-bit floating point vector type.
	 */
	using F64x3 = Array< F64, 3 >;

	/**
	 A 4x1 64-bit floating point vector type.
	 */
	using F64x4 = Array< F64, 4 >;

	static_assert(16 == sizeof(F64x2));
	static_assert(24 == sizeof(F64x3));
	static_assert(32 == sizeof(F64x4));

	#pragma endregion

	//-------------------------------------------------------------------------
	// Signed Integer Vectors
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A 2x1 signed 8-bit integer vector type.
	 */
	using S8x2 = Array< S8, 2 >;

	/**
	 A 3x1 signed 8-bit integer vector type.
	 */
	using S8x3 = Array< S8, 3 >;

	/**
	 A 4x1 signed 8-bit integer vector type.
	 */
	using S8x4 = Array< S8, 4 >;

	static_assert(2 == sizeof(S8x2));
	static_assert(3 == sizeof(S8x3));
	static_assert(4 == sizeof(S8x4));

	/**
	 A 2x1 signed 16-bit integer vector type.
	 */
	using S16x2 = Array< S16, 2 >;

	/**
	 A 3x1 signed 16-bit integer vector type.
	 */
	using S16x3 = Array< S16, 3 >;

	/**
	 A 4x1 signed 16-bit integer vector type.
	 */
	using S16x4 = Array< S16, 4 >;

	static_assert(4 == sizeof(S16x2));
	static_assert(6 == sizeof(S16x3));
	static_assert(8 == sizeof(S16x4));

	/**
	 A 2x1 signed 32-bit integer vector type.
	 */
	using S32x2 = Array< S32, 2 >;

	/**
	 A 3x1 signed 32-bit integer vector type.
	 */
	using S32x3 = Array< S32, 3 >;

	/**
	 A 4x1 signed 32-bit integer vector type.
	 */
	using S32x4 = Array< S32, 4 >;

	static_assert(8  == sizeof(S32x2));
	static_assert(12 == sizeof(S32x3));
	static_assert(16 == sizeof(S32x4));

	/**
	 A 2x1 signed 64-bit integer vector type.
	 */
	using S64x2 = Array< S64, 2 >;

	/**
	 A 3x1 signed 64-bit integer vector type.
	 */
	using S64x3 = Array< S64, 3 >;

	/**
	 A 4x1 signed 64-bit integer vector type.
	 */
	using S64x4 = Array< S64, 4 >;

	static_assert(16 == sizeof(S64x2));
	static_assert(24 == sizeof(S64x3));
	static_assert(32 == sizeof(S64x4));

	#pragma endregion

	//-------------------------------------------------------------------------
	// Unsigned Integer Vectors
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A 2x1 unsigned 8-bit integer vector type.
	 */
	using U8x2 = Array< U8, 2 >;

	/**
	 A 3x1 unsigned 8-bit integer vector type.
	 */
	using U8x3 = Array< U8, 3 >;

	/**
	 A 4x1 unsigned 8-bit integer vector type.
	 */
	using U8x4 = Array< U8, 4 >;

	static_assert(2 == sizeof(U8x2));
	static_assert(3 == sizeof(U8x3));
	static_assert(4 == sizeof(U8x4));

	/**
	 A 2x1 unsigned 16-bit integer vector type.
	 */
	using U16x2 = Array< U16, 2 >;

	/**
	 A 3x1 unsigned 16-bit integer vector type.
	 */
	using U16x3 = Array< U16, 3 >;

	/**
	 A 4x1 unsigned 16-bit integer vector type.
	 */
	using U16x4 = Array< U16, 4 >;

	static_assert(4 == sizeof(U16x2));
	static_assert(6 == sizeof(U16x3));
	static_assert(8 == sizeof(U16x4));

	/**
	 A 2x1 unsigned 32-bit integer vector type.
	 */
	using U32x2 = Array< U32, 2 >;

	/**
	 A 3x1 unsigned 32-bit integer vector type.
	 */
	using U32x3 = Array< U32, 3 >;

	/**
	 A 4x1 unsigned 32-bit integer vector type.
	 */
	using U32x4 = Array< U32, 4 >;

	static_assert(8  == sizeof(U32x2));
	static_assert(12 == sizeof(U32x3));
	static_assert(16 == sizeof(U32x4));

	/**
	 A 2x1 unsigned 64-bit integer vector type.
	 */
	using U64x2 = Array< U64, 2 >;

	/**
	 A 3x1 unsigned 64-bit integer vector type.
	 */
	using U64x3 = Array< U64, 3 >;

	/**
	 A 4x1 unsigned 64-bit integer vector type.
	 */
	using U64x4 = Array< U64, 4 >;

	static_assert(16 == sizeof(U64x2));
	static_assert(24 == sizeof(U64x3));
	static_assert(32 == sizeof(U64x4));

	#pragma endregion
}