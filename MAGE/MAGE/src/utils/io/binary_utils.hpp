#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\type\types.hpp"
#include "utils\logging\error.hpp"

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
	inline const DataT *BytesBigEndianToValue(const U8 *bytes) noexcept {
		Assert(bytes);
		return reinterpret_cast< const DataT * >(bytes);
	}

	/**
	 Reads a @c S8 from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 1 byte.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c S8 represented by the big endian byte array 
					@a bytes.
	 */
	inline S8 BytesBigEndianToS8(const U8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< S8 >(bytes);
	}
	
	/**
	 Reads an @c U8 from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 1 byte.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c U8 represented by the big endian byte array 
					@a bytes.
	 */
	inline U8 BytesBigEndianToU8(const U8 *bytes) noexcept {
		Assert(bytes);
		return bytes[0];
	}
	
	/**
	 Reads a @c S16 from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 2 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c S16 represented by the big endian byte array 
					@a bytes.
	 */
	inline S16 BytesBigEndianToS16(const U8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< S16 >(bytes);
	}
	
	/**
	 Reads an @c U16 from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 2 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c U16 represented by the big endian byte array 
					@a bytes.
	 */
	inline U16 BytesBigEndianToU16(const U8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< U16 >(bytes);
	}
	
	/**
	 Reads a @c S32 from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c S32 represented by the big endian byte array 
					@a bytes.
	 */
	inline S32 BytesBigEndianToS32(const U8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< S32 >(bytes);
	}
	
	/**
	 Reads an @c U32 from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c U32 represented by the big endian byte array 
					@a bytes.
	 */
	inline U32 BytesBigEndianToU32(const U8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< U32 >(bytes);
	}
	
	/**
	 Reads a @c S64 from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c S64 represented by the big endian byte array 
					@a bytes.
	 */
	inline S64 BytesBigEndianToS64(const U8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< S64 >(bytes);
	}
	
	/**
	 Reads an @c U64 from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c U64 represented by the big endian byte array 
					@a bytes.
	 */
	inline U64 BytesBigEndianToU64(const U8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< U64 >(bytes);
	}
	
	/**
	 Reads a @c F32 from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c F32 represented by the big endian byte array 
					@a bytes.
	 */
	inline F32 BytesBigEndianToF32(const U8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< F32 >(bytes);
	}
	
	/**
	 Reads a @c F64 from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c F64 represented by the big endian byte array 
					@a bytes.
	 */
	inline F64 BytesBigEndianToF64(const U8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< F64 >(bytes);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Binary Conversion Utilities: Little Endian
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Reads a @c S8 from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 1 byte.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c S8 represented by the little endian byte array 
					@a bytes.
	 */
	inline S8 BytesLittleEndianToS8(const U8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< S8 >(bytes);
	}
	
	/**
	 Reads an @c U8 from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 1 byte.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c U8 represented by the little endian byte array 
					@a bytes.
	 */
	inline U8 BytesLittleEndianToU8(const U8 *bytes) noexcept {
		Assert(bytes);
		return bytes[0];
	}
	
	/**
	 Reads a @c S16 from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 2 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c S16 represented by the little endian byte array 
					@a bytes.
	 */
	inline S16 BytesLittleEndianToS16(const U8 *bytes) noexcept {
		Assert(bytes);

		const U8 reversed_bytes[] = { bytes[1], bytes[0] };
		
		return BytesBigEndianToS16(reversed_bytes);
	}
	
	/**
	 Reads an @c U16 from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 2 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c U16 represented by the little endian byte array 
					@a bytes.
	 */
	inline U16 BytesLittleEndianToU16(const U8 *bytes) noexcept {
		Assert(bytes);

		const U8 reversed_bytes[] = { bytes[1], bytes[0] };
		
		return BytesBigEndianToU16(reversed_bytes);
	}
	
	/**
	 Reads a @c S32 from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c S32 represented by the little endian byte array 
					@a bytes.
	 */
	inline S32 BytesLittleEndianToS32(const U8 *bytes) noexcept {
		Assert(bytes);

		const U8 reversed_bytes[] = { 
			bytes[3], bytes[2], bytes[1], bytes[0] };
		
		return BytesBigEndianToS32(reversed_bytes);
	}
	
	/**
	 Reads an @c U32 from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c U32 represented by the little endian byte array 
					@a bytes.
	 */
	inline U32 BytesLittleEndianToU32(const U8 *bytes) noexcept {
		Assert(bytes);

		const U8 reversed_bytes[] = { 
			bytes[3], bytes[2], bytes[1], bytes[0] };
		
		return BytesBigEndianToU32(reversed_bytes);
	}
	
	/**
	 Reads a @c S64 from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c S64 represented by the little endian byte array 
					@a bytes.
	 */
	inline S64 BytesLittleEndianToS64(const U8 *bytes) noexcept {
		Assert(bytes);

		const U8 reversed_bytes[] = { 
			bytes[7], bytes[6], bytes[5], bytes[4], 
			bytes[3], bytes[2], bytes[1], bytes[0] };
		
		return BytesBigEndianToS64(reversed_bytes);
	}
	
	/**
	 Reads an @c U64 from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c U64 represented by the little endian byte array 
					@a bytes.
	 */
	inline U64 BytesLittleEndianToU64(const U8 *bytes) noexcept {
		Assert(bytes);

		const U8 reversed_bytes[] = { 
			bytes[7], bytes[6], bytes[5], bytes[4], 
			bytes[3], bytes[2], bytes[1], bytes[0] };
		
		return BytesBigEndianToU64(reversed_bytes);
	}
	
	/**
	 Reads a @c F32 from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c F32 represented by the little endian byte array 
					@a bytes.
	 */
	inline F32 BytesLittleEndianToF32(const U8 *bytes) noexcept {
		Assert(bytes);
		
		const U8 reversed_bytes[] = { 
			bytes[3], bytes[2], bytes[1], bytes[0] };
		
		return BytesBigEndianToF32(reversed_bytes);
	}
	
	/**
	 Reads a @c F64 from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c F64 represented by the little endian byte array 
					@a bytes.
	 */
	inline F64 BytesLittleEndianToF64(const U8 *bytes) noexcept {
		Assert(bytes);
		
		const U8 reversed_bytes[] = { 
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
	 Reads a @c S8 from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 1 byte.
	 @param[in]		bytes
					A pointer to a byte array.
	 @return		The @c S8 represented by the byte array @a bytes.
	 */
	inline S8 BytesToS8(const U8 *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< S8 >(bytes);
	}
	
	/**
	 Reads an @c U8 from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 1 byte.
	 @param[in]		bytes
					A pointer to a byte array.
	 @return		The @c U8 represented by the byte array @a bytes.
	 */
	inline U8 BytesToU8(const U8 *bytes) noexcept {
		Assert(bytes);
		return bytes[0];
	}
	
	/**
	 Reads a @c S16 from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 2 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array should be 
					interpreted as big endian or not (i.e. little endian).
	 @return		The @c S16 represented by the byte array @a bytes.
	*/
	inline S16 BytesToS16(const U8 *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? 
			BytesBigEndianToS16(bytes) : BytesLittleEndianToS16(bytes);
	}
	
	/**
	 Reads an @c U16 from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 2 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array should be 
					interpreted as big endian or not (i.e. little endian).
	 @return		The @c U16 represented by the byte array @a bytes.
	 */
	inline U16 BytesToU16(const U8 *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? 
			BytesBigEndianToU16(bytes) : BytesLittleEndianToU16(bytes);
	}
	
	/**
	 Reads a @c S32 from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array should be 
					interpreted as big endian or not (i.e. little endian).
	 @return		The @c S32 represented by the byte array @a bytes.
	 */
	inline S32 BytesToS32(const U8 *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? 
			BytesBigEndianToS32(bytes) : BytesLittleEndianToS32(bytes);
	}
	
	/**
	 Reads an @c U32 from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array should be 
					interpreted as big endian or not (i.e. little endian).
	 @return		The @c U32 represented by the byte array @a bytes.
	 */
	inline U32 BytesToU32(const U8 *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? 
			BytesBigEndianToU32(bytes) : BytesLittleEndianToU32(bytes);
	}
	
	/**
	 Reads a @c S64 from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array should be 
					interpreted as big endian or not (i.e. little endian).
	 @return		The @c S64 represented by the byte array @a bytes.
	 */
	inline S64 BytesToS64(const U8 *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? 
			BytesBigEndianToS64(bytes) : BytesLittleEndianToS64(bytes);
	}
	
	/**
	 Reads an @c U64 from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array should be 
					interpreted as big endian or not (i.e. little endian).
	 @return		The @c U64 represented by the byte array @a bytes.
	 */
	inline U64 BytesToU64(const U8 *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? 
			BytesBigEndianToU64(bytes) : BytesLittleEndianToU64(bytes);
	}
	
	/**
	 Reads a @c F32 from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array should be 
					interpreted as big endian or not (i.e. little endian).
	 @return		The @c F32 represented by the byte array @a bytes.
	 */
	inline F32 BytesToF32(const U8 *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? 
			BytesBigEndianToF32(bytes) : BytesLittleEndianToF32(bytes);
	}
	
	/**
	 Reads a @c F64 from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array should be 
					interpreted as big endian or not (i.e. little endian).
	 @return		The @c F64 represented by the byte array @a bytes.
	 */
	inline F64 BytesToF64(const U8 *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? 
			BytesBigEndianToF64(bytes) : BytesLittleEndianToF64(bytes);
	}

#pragma endregion
}
