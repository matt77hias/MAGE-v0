#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

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
	 An atomic boolean value type.
	 */
	using AtomicBool = std::atomic< bool >;

	#pragma endregion

	//-------------------------------------------------------------------------
	// Floating Point Values
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 An atomic 32-bit floating point value type.
	 */
	using AtomicF32 = std::atomic< F32 >;

	/**
	 An atomic 64-bit floating point value type.
	 */
	using AtomicF64 = std::atomic< F64 >;

	static_assert(4 == sizeof(AtomicF32));
	static_assert(8 == sizeof(AtomicF64));

	#pragma endregion

	//-------------------------------------------------------------------------
	// Signed Integer Values
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 An atomic signed 8-bit integer value type.
	 */
	using AtomicS8 = std::atomic< S8 >;

	/**
	 An atomic signed 16-bit integer value type.
	 */
	using AtomicS16 = std::atomic< S16 >;

	/**
	 An atomic signed 64-bit integer value type.
	 */
	using AtomicS32 = std::atomic< S32 >;

	/**
	 An atomic signed 32-bit integer value type.
	 */
	using AtomicS64 = std::atomic< S64 >;

	static_assert(1 == sizeof(AtomicS8));
	static_assert(2 == sizeof(AtomicS16));
	static_assert(4 == sizeof(AtomicS32));
	static_assert(8 == sizeof(AtomicS64));

	#pragma endregion

	//-------------------------------------------------------------------------
	// Unsigned Integer Values
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 An atomic unsigned 8-bit integer value type.
	 */
	using AtomicU8 = std::atomic< U8 >;

	/**
	 An atomic unsigned 16-bit integer value type.
	 */
	using AtomicU16 = std::atomic< U16 >;

	/**
	 An atomic unsigned 32-bit integer value type.
	 */
	using AtomicU32 = std::atomic< U32 >;

	/**
	 An atomic unsigned 64-bit integer value type.
	 */
	using AtomicU64 = std::atomic< U64 >;

	static_assert(1 == sizeof(AtomicU8));
	static_assert(2 == sizeof(AtomicU16));
	static_assert(4 == sizeof(AtomicU32));
	static_assert(8 == sizeof(AtomicU64));

	#pragma endregion
}