#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\scalar_types.hpp"

#pragma endregion

//-------------------------------------------------------------------------
// System Includes
//-------------------------------------------------------------------------
#pragma region

#include <atomic>

#pragma endregion

//-------------------------------------------------------------------------
// Type Declarations and Definitions
//-------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Boolean Values
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 An atomic boolean type.
	 */
	using AtomicBool = std::atomic< bool >;

	static_assert(sizeof(bool) == sizeof(AtomicBool));

	#pragma endregion

	//-------------------------------------------------------------------------
	// Atomic Floating Point Scalars
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 An atomic floating point type with width of exactly 32 bits.
	 */
	using AtomicF32 = std::atomic< F32 >;

	/**
	 An atomic floating point type with width of exactly 64 bits.
	 */
	using AtomicF64 = std::atomic< F64 >;

	static_assert(sizeof(F32) == sizeof(AtomicF32));
	static_assert(sizeof(F64) == sizeof(AtomicF64));

	#pragma endregion

	//-------------------------------------------------------------------------
	// Atomic Signed Integer Scalars
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 An atomic signed integer type with width of exactly 8 bits.
	 */
	using AtomicS8 = std::atomic< S8 >;

	/**
	 An atomic signed integer type with width of exactly 16 bits.
	 */
	using AtomicS16 = std::atomic< S16 >;

	/**
	 An atomic signed integer type with width of exactly 32 bits.
	 */
	using AtomicS32 = std::atomic< S32 >;

	/**
	 An atomic signed integer type with width of exactly 64 bits.
	 */
	using AtomicS64 = std::atomic< S64 >;

	static_assert(sizeof(S8)  == sizeof(AtomicS8));
	static_assert(sizeof(S16) == sizeof(AtomicS16));
	static_assert(sizeof(S32) == sizeof(AtomicS32));
	static_assert(sizeof(S64) == sizeof(AtomicS64));

	/**
	 The fastest atomic signed integer type with width of at least 8 bits.
	 */
	using AtomicFS8 = std::atomic< FS8 >;

	/**
	 The fastest atomic signed integer type with width of at least 16 bits.
	 */
	using AtomicFS16 = std::atomic< FS16 >;

	/**
	 The fastest atomic signed integer type with width of at least 32 bits.
	 */
	using AtomicFS32 = std::atomic< FS32 >;

	/**
	 The fastest atomic signed integer type with width of at least 64 bits.
	 */
	using AtomicFS64 = std::atomic< FS64 >;

	static_assert(sizeof(FS8)  == sizeof(AtomicFS8));
	static_assert(sizeof(FS16) == sizeof(AtomicFS16));
	static_assert(sizeof(FS32) == sizeof(AtomicFS32));
	static_assert(sizeof(FS64) == sizeof(AtomicFS64));

	#pragma endregion

	//-------------------------------------------------------------------------
	// Atomic Unsigned Integer Scalars
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 An atomic unsigned integer type with width of exactly 8 bits.
	 */
	using AtomicU8 = std::atomic< U8 >;

	/**
	 An atomic unsigned integer type with width of exactly 16 bits.
	 */
	using AtomicU16 = std::atomic< U16 >;

	/**
	 An atomic unsigned integer type with width of exactly 32 bits.
	 */
	using AtomicU32 = std::atomic< U32 >;

	/**
	 An atomic unsigned integer type with width of exactly 64 bits.
	 */
	using AtomicU64 = std::atomic< U64 >;

	static_assert(sizeof(U8)  == sizeof(AtomicU8));
	static_assert(sizeof(U16) == sizeof(AtomicU16));
	static_assert(sizeof(U32) == sizeof(AtomicU32));
	static_assert(sizeof(U64) == sizeof(AtomicU64));

	/**
	 The fastest atomic unsigned integer type with width of at least 8 bits.
	 */
	using AtomicFU8 = std::atomic< FU8 >;

	/**
	 The fastest atomic unsigned integer type with width of at least 16 bits.
	 */
	using AtomicFU16 = std::atomic< FU16 >;

	/**
	 The fastest atomic unsigned integer type with width of at least 32 bits.
	 */
	using AtomicFU32 = std::atomic< FU32 >;

	/**
	 The fastest atomic unsigned integer type with width of at least 64 bits.
	 */
	using AtomicFU64 = std::atomic< FU64 >;

	static_assert(sizeof(FU8)  == sizeof(AtomicFU8));
	static_assert(sizeof(FU16) == sizeof(AtomicFU16));
	static_assert(sizeof(FU32) == sizeof(AtomicFU32));
	static_assert(sizeof(FU64) == sizeof(AtomicFU64));

	#pragma endregion
}