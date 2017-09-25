#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\types.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	//-------------------------------------------------------------------------
	// Binary Conversion Utilities: Big Endian
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Reads a @c DataT element from the given big endian byte array.

	 @tparam		DataT
					The data type.
	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 
					@c sizeof(DataT) bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		A pointer to a @c DataT element represented by the big 
					endian byte array @a bytes.
	 */
	template < typename DataT >
	inline const DataT *BytesBigEndianToValue(const u8 *bytes) noexcept {
		Assert(bytes);
		return reinterpret_cast< const DataT * >(bytes);
	}

	/**
	 Reads an @c i8 from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 1 byte.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c i8 represented by the big endian byte array 
					@a bytes.
	 */
	inline i8 BytesBigEndianToI8(const u8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< i8 >(bytes);
	}
	
	/**
	 Reads an @c u8 from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 1 byte.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c u8 represented by the big endian byte array 
					@a bytes.
	 */
	inline u8 BytesBigEndianToU8(const u8 *bytes) noexcept {
		Assert(bytes);
		return bytes[0];
	}
	
	/**
	 Reads an @c i16 from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 2 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c i16 represented by the big endian byte array 
					@a bytes.
	 */
	inline i16 BytesBigEndianToI16(const u8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< i16 >(bytes);
	}
	
	/**
	 Reads an @c u16 from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 2 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c u16 represented by the big endian byte array 
					@a bytes.
	 */
	inline u16 BytesBigEndianToU16(const u8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< u16 >(bytes);
	}
	
	/**
	 Reads an @c i32 from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c i32 represented by the big endian byte array 
					@a bytes.
	 */
	inline i32 BytesBigEndianToI32(const u8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< i32 >(bytes);
	}
	
	/**
	 Reads an @c u32 from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c u32 represented by the big endian byte array 
					@a bytes.
	 */
	inline u32 BytesBigEndianToU32(const u8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< u32 >(bytes);
	}
	
	/**
	 Reads an @c i64 from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c i64 represented by the big endian byte array 
					@a bytes.
	 */
	inline i64 BytesBigEndianToI64(const u8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< i64 >(bytes);
	}
	
	/**
	 Reads an @c u64 from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c u64 represented by the big endian byte array 
					@a bytes.
	 */
	inline u64 BytesBigEndianToU64(const u8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< u64 >(bytes);
	}
	
	/**
	 Reads a @c f32 from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c f32 represented by the big endian byte array 
					@a bytes.
	 */
	inline f32 BytesBigEndianToF32(const u8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< f32 >(bytes);
	}
	
	/**
	 Reads a @c f64 from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c f64 represented by the big endian byte array 
					@a bytes.
	 */
	inline f64 BytesBigEndianToF64(const u8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< f64 >(bytes);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Binary Conversion Utilities: Little Endian
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Reads an @c i8 from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 1 byte.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c i8 represented by the little endian byte array 
					@a bytes.
	 */
	inline i8 BytesLittleEndianToI8(const u8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< i8 >(bytes);
	}
	
	/**
	 Reads an @c u8 from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 1 byte.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c u8 represented by the little endian byte array 
					@a bytes.
	 */
	inline u8 BytesLittleEndianToU8(const u8 *bytes) noexcept {
		Assert(bytes);
		return bytes[0];
	}
	
	/**
	 Reads an @c i16 from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 2 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c i16 represented by the little endian byte array 
					@a bytes.
	 */
	inline i16 BytesLittleEndianToI16(const u8 *bytes) noexcept {
		Assert(bytes);

		const u8 reversed_bytes[] = { bytes[1], bytes[0] };
		
		return BytesBigEndianToI16(reversed_bytes);
	}
	
	/**
	 Reads an @c u16 from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 2 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c u16 represented by the little endian byte array 
					@a bytes.
	 */
	inline u16 BytesLittleEndianToU16(const u8 *bytes) noexcept {
		Assert(bytes);

		const u8 reversed_bytes[] = { bytes[1], bytes[0] };
		
		return BytesBigEndianToU16(reversed_bytes);
	}
	
	/**
	 Reads an @c i32 from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c i32 represented by the little endian byte array 
					@a bytes.
	 */
	inline i32 BytesLittleEndianToI32(const u8 *bytes) noexcept {
		Assert(bytes);

		const u8 reversed_bytes[] = { 
			bytes[3], bytes[2], bytes[1], bytes[0] };
		
		return BytesBigEndianToI32(reversed_bytes);
	}
	
	/**
	 Reads an @c u32 from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c u32 represented by the little endian byte array 
					@a bytes.
	 */
	inline u32 BytesLittleEndianToU32(const u8 *bytes) noexcept {
		Assert(bytes);

		const u8 reversed_bytes[] = { 
			bytes[3], bytes[2], bytes[1], bytes[0] };
		
		return BytesBigEndianToU32(reversed_bytes);
	}
	
	/**
	 Reads an @c i64 from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c i64 represented by the little endian byte array 
					@a bytes.
	 */
	inline i64 BytesLittleEndianToI64(const u8 *bytes) noexcept {
		Assert(bytes);

		const u8 reversed_bytes[] = { 
			bytes[7], bytes[6], bytes[5], bytes[4], 
			bytes[3], bytes[2], bytes[1], bytes[0] };
		
		return BytesBigEndianToI64(reversed_bytes);
	}
	
	/**
	 Reads an @c u64 from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c u64 represented by the little endian byte array 
					@a bytes.
	 */
	inline u64 BytesLittleEndianToU64(const u8 *bytes) noexcept {
		Assert(bytes);

		const u8 reversed_bytes[] = { 
			bytes[7], bytes[6], bytes[5], bytes[4], 
			bytes[3], bytes[2], bytes[1], bytes[0] };
		
		return BytesBigEndianToU64(reversed_bytes);
	}
	
	/**
	 Reads a @c f32 from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c f32 represented by the little endian byte array 
					@a bytes.
	 */
	inline f32 BytesLittleEndianToF32(const u8 *bytes) noexcept {
		Assert(bytes);
		
		const u8 reversed_bytes[] = { 
			bytes[3], bytes[2], bytes[1], bytes[0] };
		
		return BytesBigEndianToF32(reversed_bytes);
	}
	
	/**
	 Reads a @c f64 from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c f64 represented by the little endian byte array 
					@a bytes.
	 */
	inline f64 BytesLittleEndianToF64(const u8 *bytes) noexcept {
		Assert(bytes);
		
		const u8 reversed_bytes[] = { 
			bytes[7], bytes[6], bytes[5], bytes[4], 
			bytes[3], bytes[2], bytes[1], bytes[0] };
		
		return BytesBigEndianToF64(reversed_bytes);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Binary Conversion Utilities: Big | Little Endian
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Reads an @c i8 from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 1 byte.
	 @param[in]		bytes
					A pointer to a byte array.
	 @return		The @c i8 represented by the byte array @a bytes.
	 */
	inline i8 BytesToI8(const u8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< i8 >(bytes);
	}
	
	/**
	 Reads an @c u8 from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 1 byte.
	 @param[in]		bytes
					A pointer to a byte array.
	 @return		The @c u8 represented by the byte array @a bytes.
	 */
	inline u8 BytesToU8(const u8 *bytes) noexcept {
		Assert(bytes);
		return bytes[0];
	}
	
	/**
	 Reads an @c i16 from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 2 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array should be 
					interpreted as big endian or not (i.e. little endian).
	 @return		The @c i16 represented by the byte array @a bytes.
	*/
	inline i16 BytesToI16(const u8 *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? 
			BytesBigEndianToI16(bytes) : BytesLittleEndianToI16(bytes);
	}
	
	/**
	 Reads an @c u16 from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 2 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array should be 
					interpreted as big endian or not (i.e. little endian).
	 @return		The @c u16 represented by the byte array @a bytes.
	 */
	inline u16 BytesToU16(const u8 *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? 
			BytesBigEndianToU16(bytes) : BytesLittleEndianToU16(bytes);
	}
	
	/**
	 Reads an @c i32 from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array should be 
					interpreted as big endian or not (i.e. little endian).
	 @return		The @c i32 represented by the byte array @a bytes.
	 */
	inline i32 BytesToI32(const u8 *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? 
			BytesBigEndianToI32(bytes) : BytesLittleEndianToI32(bytes);
	}
	
	/**
	 Reads an @c u32 from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array should be 
					interpreted as big endian or not (i.e. little endian).
	 @return		The @c u32 represented by the byte array @a bytes.
	 */
	inline u32 BytesToU32(const u8 *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? 
			BytesBigEndianToU32(bytes) : BytesLittleEndianToU32(bytes);
	}
	
	/**
	 Reads an @c i64 from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array should be 
					interpreted as big endian or not (i.e. little endian).
	 @return		The @c i64 represented by the byte array @a bytes.
	 */
	inline i64 BytesToI64(const u8 *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? 
			BytesBigEndianToI64(bytes) : BytesLittleEndianToI64(bytes);
	}
	
	/**
	 Reads an @c u64 from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array should be 
					interpreted as big endian or not (i.e. little endian).
	 @return		The @c u64 represented by the byte array @a bytes.
	 */
	inline u64 BytesToU64(const u8 *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? 
			BytesBigEndianToU64(bytes) : BytesLittleEndianToU64(bytes);
	}
	
	/**
	 Reads a @c f32 from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array should be 
					interpreted as big endian or not (i.e. little endian).
	 @return		The @c f32 represented by the byte array @a bytes.
	 */
	inline f32 BytesToF32(const u8 *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? 
			BytesBigEndianToF32(bytes) : BytesLittleEndianToF32(bytes);
	}
	
	/**
	 Reads a @c f64 from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array should be 
					interpreted as big endian or not (i.e. little endian).
	 @return		The @c f64 represented by the byte array @a bytes.
	 */
	inline f64 BytesToF64(const u8 *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? 
			BytesBigEndianToF64(bytes) : BytesLittleEndianToF64(bytes);
	}

#pragma endregion
}
