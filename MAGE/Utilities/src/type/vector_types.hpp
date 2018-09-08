#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "collection\array.hpp"
#include "type\scalar_types.hpp"

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
	 A 2x1 vector type for floating points with width of exactly 32 bits.
	 */
	using F32x2 = Array< F32, 2 >;

	/**
	 A 3x1 vector type for floating points with width of exactly 32 bits.
	 */
	using F32x3 = Array< F32, 3 >;

	/**
	 A 4x1 vector type for floating points with width of exactly 32 bits.
	 */
	using F32x4 = Array< F32, 4 >;

	static_assert(2 * sizeof(F32) == sizeof(F32x2));
	static_assert(3 * sizeof(F32) == sizeof(F32x3));
	static_assert(4 * sizeof(F32) == sizeof(F32x4));

	/**
	 A 2x1 vector type for floating points with width of exactly 32 bits with 
	 a 16-byte alignment.
	 */
	using F32x2A = Array< F32, 2, 16 >;

	/**
	 A 3x1 vector type for floating points with width of exactly 32 bits with 
	 a 16-byte alignment.
	 */
	using F32x3A = Array< F32, 3, 16 >;

	/**
	 A 4x1 vector type for floating points with width of exactly 32 bits with 
	 a 16-byte alignment.
	 */
	using F32x4A = Array< F32, 4, 16 >;

	static_assert(16 == sizeof(F32x2A));
	static_assert(16 == sizeof(F32x3A));
	static_assert(16 == sizeof(F32x4A));

	/**
	 A 2x1 vector type for floating points with width of exactly 64 bits.
	 */
	using F64x2 = Array< F64, 2 >;

	/**
	 A 3x1 vector type for floating points with width of exactly 64 bits.
	 */
	using F64x3 = Array< F64, 3 >;

	/**
	 A 4x1 vector type for floating points with width of exactly 64 bits.
	 */
	using F64x4 = Array< F64, 4 >;

	static_assert(2 * sizeof(F64) == sizeof(F64x2));
	static_assert(3 * sizeof(F64) == sizeof(F64x3));
	static_assert(4 * sizeof(F64) == sizeof(F64x4));

	#pragma endregion

	//-------------------------------------------------------------------------
	// Signed Integer Vectors
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A 2x1 vector type for signed integers with width of exactly 8 bits.
	 */
	using S8x2 = Array< S8, 2 >;

	/**
	 A 3x1 vector type for signed integers with width of exactly 8 bits.
	 */
	using S8x3 = Array< S8, 3 >;

	/**
	 A 4x1 vector type for signed integers with width of exactly 8 bits.
	 */
	using S8x4 = Array< S8, 4 >;

	static_assert(2 * sizeof(S8) == sizeof(S8x2));
	static_assert(3 * sizeof(S8) == sizeof(S8x3));
	static_assert(4 * sizeof(S8) == sizeof(S8x4));

	/**
	 A 2x1 vector type for signed integers with width of exactly 16 bits.
	 */
	using S16x2 = Array< S16, 2 >;

	/**
	 A 3x1 vector type for signed integers with width of exactly 16 bits.
	 */
	using S16x3 = Array< S16, 3 >;

	/**
	 A 4x1 vector type for signed integers with width of exactly 16 bits.
	 */
	using S16x4 = Array< S16, 4 >;

	static_assert(2 * sizeof(S16) == sizeof(S16x2));
	static_assert(3 * sizeof(S16) == sizeof(S16x3));
	static_assert(4 * sizeof(S16) == sizeof(S16x4));

	/**
	 A 2x1 vector type for signed integers with width of exactly 32 bits.
	 */
	using S32x2 = Array< S32, 2 >;

	/**
	 A 3x1 vector type for signed integers with width of exactly 32 bits.
	 */
	using S32x3 = Array< S32, 3 >;

	/**
	 A 4x1 vector type for signed integers with width of exactly 32 bits.
	 */
	using S32x4 = Array< S32, 4 >;

	static_assert(2 * sizeof(S32) == sizeof(S32x2));
	static_assert(3 * sizeof(S32) == sizeof(S32x3));
	static_assert(4 * sizeof(S32) == sizeof(S32x4));

	/**
	 A 2x1 vector type for signed integers with width of exactly 64 bits.
	 */
	using S64x2 = Array< S64, 2 >;

	/**
	 A 3x1 vector type for signed integers with width of exactly 64 bits.
	 */
	using S64x3 = Array< S64, 3 >;

	/**
	 A 4x1 vector type for signed integers with width of exactly 64 bits.
	 */
	using S64x4 = Array< S64, 4 >;

	static_assert(2 * sizeof(S64) == sizeof(S64x2));
	static_assert(3 * sizeof(S64) == sizeof(S64x3));
	static_assert(4 * sizeof(S64) == sizeof(S64x4));

	/**
	 A 2x1 vector type for the fastest signed integers with width of at least 
	 8 bits.
	 */
	using FS8x2 = Array< FS8, 2 >;

	/**
	 A 3x1 vector type for the fastest signed integers with width of at least 
	 8 bits.
	 */
	using FS8x3 = Array< FS8, 3 >;

	/**
	 A 4x1 vector type for the fastest signed integers with width of at least 
	 8 bits.
	 */
	using FS8x4 = Array< FS8, 4 >;

	static_assert(2 * sizeof(FS8) == sizeof(FS8x2));
	static_assert(3 * sizeof(FS8) == sizeof(FS8x3));
	static_assert(4 * sizeof(FS8) == sizeof(FS8x4));

	/**
	 A 2x1 vector type for the fastest signed integers with width of at least 
	 16 bits.
	 */
	using FS16x2 = Array< FS16, 2 >;

	/**
	 A 3x1 vector type for the fastest signed integers with width of at least 
	 16 bits.
	 */
	using FS16x3 = Array< FS16, 3 >;

	/**
	 A 4x1 vector type for the fastest signed integers with width of at least 
	 16 bits.
	 */
	using FS16x4 = Array< FS16, 4 >;

	static_assert(2 * sizeof(FS16) == sizeof(FS16x2));
	static_assert(3 * sizeof(FS16) == sizeof(FS16x3));
	static_assert(4 * sizeof(FS16) == sizeof(FS16x4));

	/**
	 A 2x1 vector type for the fastest signed integers with width of at least 
	 32 bits.
	 */
	using FS32x2 = Array< FS32, 2 >;

	/**
	 A 3x1 vector type for the fastest signed integers with width of at least 
	 32 bits.
	 */
	using FS32x3 = Array< FS32, 3 >;

	/**
	 A 4x1 vector type for the fastest signed integers with width of at least 
	 32 bits.
	 */
	using FS32x4 = Array< FS32, 4 >;

	static_assert(2 * sizeof(FS32) == sizeof(FS32x2));
	static_assert(3 * sizeof(FS32) == sizeof(FS32x3));
	static_assert(4 * sizeof(FS32) == sizeof(FS32x4));

	/**
	 A 2x1 vector type for the fastest signed integers with width of at least 
	 64 bits.
	 */
	using FS64x2 = Array< FS64, 2 >;

	/**
	 A 3x1 vector type for the fastest signed integers with width of at least 
	 64 bits.
	 */
	using FS64x3 = Array< FS64, 3 >;

	/**
	 A 4x1 vector type for the fastest signed integers with width of at least 
	 64 bits.
	 */
	using FS64x4 = Array< FS64, 4 >;

	static_assert(2 * sizeof(FS64) == sizeof(FS64x2));
	static_assert(3 * sizeof(FS64) == sizeof(FS64x3));
	static_assert(4 * sizeof(FS64) == sizeof(FS64x4));

	#pragma endregion

	//-------------------------------------------------------------------------
	// Unsigned Integer Vectors
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A 2x1 vector type for unsigned integers with width of exactly 8 bits.
	 */
	using U8x2 = Array< U8, 2 >;

	/**
	 A 3x1 vector type for unsigned integers with width of exactly 8 bits.
	 */
	using U8x3 = Array< U8, 3 >;

	/**
	 A 4x1 vector type for unsigned integers with width of exactly 8 bits.
	 */
	using U8x4 = Array< U8, 4 >;

	static_assert(2 * sizeof(U8) == sizeof(U8x2));
	static_assert(3 * sizeof(U8) == sizeof(U8x3));
	static_assert(4 * sizeof(U8) == sizeof(U8x4));

	/**
	 A 2x1 vector type for unsigned integers with width of exactly 16 bits.
	 */
	using U16x2 = Array< U16, 2 >;

	/**
	 A 3x1 vector type for unsigned integers with width of exactly 16 bits.
	 */
	using U16x3 = Array< U16, 3 >;

	/**
	 A 4x1 vector type for unsigned integers with width of exactly 16 bits.
	 */
	using U16x4 = Array< U16, 4 >;

	static_assert(2 * sizeof(U16) == sizeof(U16x2));
	static_assert(3 * sizeof(U16) == sizeof(U16x3));
	static_assert(4 * sizeof(U16) == sizeof(U16x4));

	/**
	 A 2x1 vector type for unsigned integers with width of exactly 32 bits.
	 */
	using U32x2 = Array< U32, 2 >;

	/**
	 A 3x1 vector type for unsigned integers with width of exactly 32 bits.
	 */
	using U32x3 = Array< U32, 3 >;

	/**
	 A 4x1 vector type for unsigned integers with width of exactly 32 bits.
	 */
	using U32x4 = Array< U32, 4 >;

	static_assert(2 * sizeof(U32) == sizeof(U32x2));
	static_assert(3 * sizeof(U32) == sizeof(U32x3));
	static_assert(4 * sizeof(U32) == sizeof(U32x4));

	/**
	 A 2x1 vector type for unsigned integers with width of exactly 64 bits.
	 */
	using U64x2 = Array< U64, 2 >;

	/**
	 A 3x1 vector type for unsigned integers with width of exactly 64 bits.
	 */
	using U64x3 = Array< U64, 3 >;

	/**
	 A 4x1 vector type for unsigned integers with width of exactly 64 bits.
	 */
	using U64x4 = Array< U64, 4 >;

	static_assert(2 * sizeof(U64) == sizeof(U64x2));
	static_assert(3 * sizeof(U64) == sizeof(U64x3));
	static_assert(4 * sizeof(U64) == sizeof(U64x4));

	/**
	 A 2x1 vector type for the fastest unsigned integers with width of at least 
	 8 bits.
	 */
	using FU8x2 = Array< FU8, 2 >;

	/**
	 A 3x1 vector type for the fastest unsigned integers with width of at least 
	 8 bits.
	 */
	using FU8x3 = Array< FU8, 3 >;

	/**
	 A 4x1 vector type for the fastest unsigned integers with width of at least 
	 8 bits.
	 */
	using FU8x4 = Array< FU8, 4 >;

	static_assert(2 * sizeof(FU8) == sizeof(FU8x2));
	static_assert(3 * sizeof(FU8) == sizeof(FU8x3));
	static_assert(4 * sizeof(FU8) == sizeof(FU8x4));

	/**
	 A 2x1 vector type for the fastest unsigned integers with width of at least 
	 16 bits.
	 */
	using FU16x2 = Array< FU16, 2 >;

	/**
	 A 3x1 vector type for the fastest unsigned integers with width of at least 
	 16 bits.
	 */
	using FU16x3 = Array< FU16, 3 >;

	/**
	 A 4x1 vector type for the fastest unsigned integers with width of at least 
	 16 bits.
	 */
	using FU16x4 = Array< FU16, 4 >;

	static_assert(2 * sizeof(FU16) == sizeof(FU16x2));
	static_assert(3 * sizeof(FU16) == sizeof(FU16x3));
	static_assert(4 * sizeof(FU16) == sizeof(FU16x4));

	/**
	 A 2x1 vector type for the fastest unsigned integers with width of at least 
	 32 bits.
	 */
	using FU32x2 = Array< FU32, 2 >;

	/**
	 A 3x1 vector type for the fastest unsigned integers with width of at least 
	 32 bits.
	 */
	using FU32x3 = Array< FU32, 3 >;

	/**
	 A 4x1 vector type for the fastest unsigned integers with width of at least 
	 32 bits.
	 */
	using FU32x4 = Array< FU32, 4 >;

	static_assert(2 * sizeof(FU32) == sizeof(FU32x2));
	static_assert(3 * sizeof(FU32) == sizeof(FU32x3));
	static_assert(4 * sizeof(FU32) == sizeof(FU32x4));

	/**
	 A 2x1 vector type for the fastest unsigned integers with width of at least 
	 64 bits.
	 */
	using FU64x2 = Array< FU64, 2 >;

	/**
	 A 3x1 vector type for the fastest unsigned integers with width of at least 
	 64 bits.
	 */
	using FU64x3 = Array< FU64, 3 >;

	/**
	 A 4x1 vector type for the fastest unsigned integers with width of at least 
	 64 bits.
	 */
	using FU64x4 = Array< FU64, 4 >;

	static_assert(2 * sizeof(FU64) == sizeof(FU64x2));
	static_assert(3 * sizeof(FU64) == sizeof(FU64x3));
	static_assert(4 * sizeof(FU64) == sizeof(FU64x4));

	#pragma endregion
}