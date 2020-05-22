#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <cstddef>
#include <cstdint>
#include <type_traits>

#pragma endregion

//-----------------------------------------------------------------------------
// Type Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Floating Point Scalars
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A floating point type with width of exactly 32 bits.
	 */
	using F32 = float;

	/**
	 A floating point type with width of exactly 64 bits.
	 */
	using F64 = double;

	static_assert(4u == sizeof(F32));
	static_assert(8u == sizeof(F64));

	static_assert(std::is_floating_point_v< F32 >);
	static_assert(std::is_floating_point_v< F64 >);

	#pragma endregion

	//-------------------------------------------------------------------------
	// Signed Integer Scalars
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A signed integer type with width of exactly 8 bits.
	 */
	using S8 = std::int8_t;

	/**
	 A signed integer type with width of exactly 16 bits.
	 */
	using S16 = std::int16_t;

	/**
	 A signed integer type with width of exactly 32 bits.
	 */
	using S32 = std::int32_t;

	/**
	 A signed integer type with width of exactly 64 bits.
	 */
	using S64 = std::int64_t;

	static_assert(1u == sizeof(S8));
	static_assert(2u == sizeof(S16));
	static_assert(4u == sizeof(S32));
	static_assert(8u == sizeof(S64));

	static_assert(std::is_integral_v< S8  >);
	static_assert(std::is_integral_v< S16 >);
	static_assert(std::is_integral_v< S32 >);
	static_assert(std::is_integral_v< S64 >);

	static_assert(std::is_signed_v< S8  >);
	static_assert(std::is_signed_v< S16 >);
	static_assert(std::is_signed_v< S32 >);
	static_assert(std::is_signed_v< S64 >);

	/**
	 The fastest signed integer type with width of at least 8 bits.
	 */
	using FS8 = std::int_fast8_t;

	/**
	 The fastest signed integer type with width of at least 16 bits.
	 */
	using FS16 = std::int_fast16_t;

	/**
	 The fastest signed integer type with width of at least 32 bits.
	 */
	using FS32 = std::int_fast32_t;

	/**
	 The fastest signed integer type with width of at least 64 bits.
	 */
	using FS64 = std::int_fast64_t;

	static_assert(1u <= sizeof(FS8));
	static_assert(2u <= sizeof(FS16));
	static_assert(4u <= sizeof(FS32));
	static_assert(8u <= sizeof(FS64));

	static_assert(std::is_integral_v< FS8  >);
	static_assert(std::is_integral_v< FS16 >);
	static_assert(std::is_integral_v< FS32 >);
	static_assert(std::is_integral_v< FS64 >);

	static_assert(std::is_signed_v< FS8  >);
	static_assert(std::is_signed_v< FS16 >);
	static_assert(std::is_signed_v< FS32 >);
	static_assert(std::is_signed_v< FS64 >);

	#pragma endregion

	//-------------------------------------------------------------------------
	// Unsigned Integer Scalars
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 An unsigned integer type with width of exactly 8 bits.
	 */
	using U8 = std::uint8_t;

	/**
	 An unsigned integer type with width of exactly 16 bits.
	 */
	using U16 = std::uint16_t;

	/**
	 An unsigned integer type with width of exactly 32 bits.
	 */
	using U32 = std::uint32_t;

	/**
	 An unsigned integer type with width of exactly 64 bits.
	 */
	using U64 = std::uint64_t;

	static_assert(1u == sizeof(U8));
	static_assert(2u == sizeof(U16));
	static_assert(4u == sizeof(U32));
	static_assert(8u == sizeof(U64));

	static_assert(std::is_integral_v< U8  >);
	static_assert(std::is_integral_v< U16 >);
	static_assert(std::is_integral_v< U32 >);
	static_assert(std::is_integral_v< U64 >);

	static_assert(std::is_unsigned_v< U8  >);
	static_assert(std::is_unsigned_v< U16 >);
	static_assert(std::is_unsigned_v< U32 >);
	static_assert(std::is_unsigned_v< U64 >);

	/**
	 The fastest unsigned integer type with width of at least 8 bits.
	 */
	using FU8 = std::uint_fast8_t;

	/**
	 The fastest unsigned integer type with width of at least 16 bits.
	 */
	using FU16 = std::uint_fast16_t;

	/**
	 The fastest unsigned integer type with width of at least 32 bits.
	 */
	using FU32 = std::uint_fast32_t;

	/**
	 The fastest unsigned integer type with width of at least 64 bits.
	 */
	using FU64 = std::uint_fast64_t;

	static_assert(1u <= sizeof(FU8));
	static_assert(2u <= sizeof(FU16));
	static_assert(4u <= sizeof(FU32));
	static_assert(8u <= sizeof(FU64));

	static_assert(std::is_integral_v< FU8  >);
	static_assert(std::is_integral_v< FU16 >);
	static_assert(std::is_integral_v< FU32 >);
	static_assert(std::is_integral_v< FU64 >);

	static_assert(std::is_unsigned_v< FU8  >);
	static_assert(std::is_unsigned_v< FU16 >);
	static_assert(std::is_unsigned_v< FU32 >);
	static_assert(std::is_unsigned_v< FU64 >);

	#pragma endregion
}
