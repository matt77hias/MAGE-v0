#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

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
	 @pre			The given byte array must contain at least @c sizeof(DataT) bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		A pointer to a @c DataT element represented
					by the big endian byte array @a bytes.
	 */
	template < typename DataT >
	inline const DataT *BytesBigEndianToValue(const uint8_t *bytes) noexcept {
		Assert(bytes);
		return reinterpret_cast< const DataT * >(bytes);
	}
	
	/**
	 Reads an int8_t from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 1 byte.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c int8_t represented 
					by the big endian byte array @a bytes.
	 */
	inline int8_t BytesBigEndianToInt8(const uint8_t *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< int8_t >(bytes);
	}
	
	/**
	 Reads an uint8_t from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 1 byte.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c uint8_t represented
					by the big endian byte array @a bytes.
	 */
	inline uint8_t BytesBigEndianToUInt8(const uint8_t *bytes) noexcept {
		Assert(bytes);
		return bytes[0];
	}
	
	/**
	 Reads an int16_t from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 2 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c int16_t represented
					by the big endian byte array @a bytes.
	 */
	inline int16_t BytesBigEndianToInt16(const uint8_t *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< int16_t >(bytes);
	}
	
	/**
	 Reads an uint16_t from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 2 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c uint16_t represented
					by the big endian byte array @a bytes.
	 */
	inline uint16_t BytesBigEndianToUInt16(const uint8_t *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< uint16_t >(bytes);
	}
	
	/**
	 Reads an int32_t from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c int32_t represented
					by the big endian byte array @a bytes.
	 */
	inline int32_t BytesBigEndianToInt32(const uint8_t *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< int32_t >(bytes);
	}
	
	/**
	 Reads an uint32_t from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c uint32_t represented
					by the big endian byte array @a bytes.
	 */
	inline uint32_t BytesBigEndianToUInt32(const uint8_t *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< uint32_t >(bytes);
	}
	
	/**
	 Reads an int64_t from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c int64_t represented
					by the big endian byte array @a bytes.
	 */
	inline int64_t BytesBigEndianToInt64(const uint8_t *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< int64_t >(bytes);
	}
	
	/**
	 Reads an uint64_t from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c uint64_t represented
					by the big endian byte array @a bytes.
	 */
	inline uint64_t BytesBigEndianToUInt64(const uint8_t *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< uint64_t >(bytes);
	}
	
	/**
	 Reads an float from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least @c sizeof(float) bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c float represented
					by the big endian byte array @a bytes.
	 */
	inline float BytesBigEndianToFloat(const uint8_t *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< float >(bytes);
	}
	
	/**
	 Reads an double from the given big endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least @c sizeof(double) bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c double represented
					by the big endian byte array @a bytes.
	 */
	inline double BytesBigEndianToDouble(const uint8_t *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< double >(bytes);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Binary Conversion Utilities: Little Endian
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Reads an int8_t from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 1 byte.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c int8_t represented
					by the little endian byte array @a bytes.
	 */
	inline int8_t BytesLittleEndianToInt8(const uint8_t *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< int8_t >(bytes);
	}
	
	/**
	 Reads an uint8_t from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 1 byte.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c uint8_t represented
					by the little endian byte array @a bytes.
	 */
	inline uint8_t BytesLittleEndianToUInt8(const uint8_t *bytes) noexcept {
		Assert(bytes);
		return bytes[0];
	}
	
	/**
	 Reads an int16_t from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 2 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c int16_t represented
					by the little endian byte array @a bytes.
	 */
	inline int16_t BytesLittleEndianToInt16(const uint8_t *bytes) noexcept {
		Assert(bytes);
		const uint8_t reversed_bytes[] = { bytes[1], bytes[0] };
		return BytesBigEndianToInt16(reversed_bytes);
	}
	
	/**
	 Reads an uint16_t from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 2 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c uint16_t represented
					by the little endian byte array @a bytes.
	 */
	inline uint16_t BytesLittleEndianToUInt16(const uint8_t *bytes) noexcept {
		Assert(bytes);
		const uint8_t reversed_bytes[] = { bytes[1], bytes[0] };
		return BytesBigEndianToUInt16(reversed_bytes);
	}
	
	/**
	 Reads an int32_t from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c int32_t represented
					by the little endian byte array @a bytes.
	 */
	inline int32_t BytesLittleEndianToInt32(const uint8_t *bytes) noexcept {
		Assert(bytes);
		const uint8_t reversed_bytes[] = { bytes[3], bytes[2], bytes[1], bytes[0] };
		return BytesBigEndianToInt32(reversed_bytes);
	}
	
	/**
	 Reads an uint32_t from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c uint32_t represented
					by the little endian byte array @a bytes.
	 */
	inline uint32_t BytesLittleEndianToUInt32(const uint8_t *bytes) noexcept {
		Assert(bytes);
		const uint8_t reversed_bytes[] = { bytes[3], bytes[2], bytes[1], bytes[0] };
		return BytesBigEndianToUInt32(reversed_bytes);
	}
	
	/**
	 Reads an int64_t from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c int64_t represented
					by the little endian byte array @a bytes.
	 */
	inline int64_t BytesLittleEndianToInt64(const uint8_t *bytes) noexcept {
		Assert(bytes);
		const uint8_t reversed_bytes[] = { bytes[7], bytes[6], bytes[5], bytes[4], bytes[3], bytes[2], bytes[1], bytes[0] };
		return BytesBigEndianToInt64(reversed_bytes);
	}
	
	/**
	 Reads an uint64_t from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c uint64_t represented
					by the little endian byte array @a bytes.
	 */
	inline uint64_t BytesLittleEndianToUInt64(const uint8_t *bytes) noexcept {
		Assert(bytes);
		const uint8_t reversed_bytes[] = { bytes[7], bytes[6], bytes[5], bytes[4], bytes[3], bytes[2], bytes[1], bytes[0] };
		return BytesBigEndianToUInt64(reversed_bytes);
	}
	
	/**
	 Reads an float from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least @c sizeof(float) bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c float represented
					by the little endian byte array @a bytes.
	 */
	inline float BytesLittleEndianToFloat(const uint8_t *bytes) noexcept {
		Assert(bytes);
		const uint8_t reversed_bytes[] = { bytes[3], bytes[2], bytes[1], bytes[0] };
		return BytesBigEndianToFloat(reversed_bytes);
	}
	
	/**
	 Reads an double from the given little endian byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least @c sizeof(double) bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c double represented
					by the little endian byte array @a bytes.
	 */
	inline double BytesLittleEndianToDouble(const uint8_t *bytes) noexcept {
		Assert(bytes);
		const uint8_t reversed_bytes[] = { bytes[7], bytes[6], bytes[5], bytes[4], bytes[3], bytes[2], bytes[1], bytes[0] };
		return BytesBigEndianToDouble(reversed_bytes);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Binary Conversion Utilities
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Reads an int8_t from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 1 byte.
	 @param[in]		bytes
					A pointer to a byte array.
	 @return		The @c int8_t represented
					by the byte array @a bytes.
	 */
	inline int8_t BytesToInt8(const uint8_t *bytes) noexcept {
		Assert(bytes);
		return *BytesBigEndianToValue< int8_t >(bytes);
	}
	
	/**
	 Reads an uint8_t from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 1 byte.
	 @param[in]		bytes
					A pointer to a byte array.
	 @return		The @c uint8_t represented
					by the byte array @a bytes.
	 */
	inline uint8_t BytesToUInt8(const uint8_t *bytes) noexcept {
		Assert(bytes);
		return bytes[0];
	}
	
	/**
	 Reads an int16_t from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 2 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array
					should be interpreted as big endian or not (i.e. little endian).
	 @return		The @c int16_t represented
					by the byte array @a bytes.
	*/
	inline int16_t BytesToInt16(const uint8_t *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? BytesBigEndianToInt16(bytes) : BytesLittleEndianToInt16(bytes);
	}
	
	/**
	 Reads an uint16_t from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 2 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array
					should be interpreted as big endian or not (i.e. little endian).
	 @return		The @c uint16_t represented
					by the byte array @a bytes.
	 */
	inline uint16_t BytesToUInt16(const uint8_t *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? BytesBigEndianToUInt16(bytes) : BytesLittleEndianToUInt16(bytes);
	}
	
	/**
	 Reads an int32_t from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array
					should be interpreted as big endian or not (i.e. little endian).
	 @return		The @c int32_t represented
					by the byte array @a bytes.
	 */
	inline int32_t BytesToInt32(const uint8_t *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? BytesBigEndianToInt32(bytes) : BytesLittleEndianToInt32(bytes);
	}
	
	/**
	 Reads an uint32_t from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 4 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array
					should be interpreted as big endian or not (i.e. little endian).
	 @return		The @c uint32_t represented
					by the byte array @a bytes.
	 */
	inline uint32_t BytesToUInt32(const uint8_t *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? BytesBigEndianToUInt32(bytes) : BytesLittleEndianToUInt32(bytes);
	}
	
	/**
	 Reads an int64_t from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array
					should be interpreted as big endian or not (i.e. little endian).
	 @return		The @c int64_t represented
					by the byte array @a bytes.
	 */
	inline int64_t BytesToInt64(const uint8_t *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? BytesBigEndianToInt64(bytes) : BytesLittleEndianToInt64(bytes);
	}
	
	/**
	 Reads an uint64_t from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least 8 bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array
					should be interpreted as big endian or not (i.e. little endian).
	 @return		The @c uint64_t represented
					by the byte array @a bytes.
	 */
	inline uint64_t BytesToUInt64(const uint8_t *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? BytesBigEndianToUInt64(bytes) : BytesLittleEndianToUInt64(bytes);
	}
	
	/**
	 Reads an float from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least @c sizeof(float) bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array
					should be interpreted as big endian or not (i.e. little endian).
	 @return		The @c float represented
					by the byte array @a bytes.
	 */
	inline float BytesToFloat(const uint8_t *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? BytesBigEndianToFloat(bytes) : BytesLittleEndianToFloat(bytes);
	}
	
	/**
	 Reads an double from the given byte array.

	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least @c sizeof(double) bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					Flag indicating whether the given byte array
					should be interpreted as big endian or not (i.e. little endian).
	 @return		The @c double represented
					by the byte array @a bytes.
	 */
	inline double BytesToDouble(const uint8_t *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? BytesBigEndianToDouble(bytes) : BytesLittleEndianToDouble(bytes);
	}

#pragma endregion
}
