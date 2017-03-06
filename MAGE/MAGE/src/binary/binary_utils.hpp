#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {
	
	//-------------------------------------------------------------------------
	// Binary Conversion Utilities
	//-------------------------------------------------------------------------
	inline int8_t BytesBigEndianToInt8(const uint8_t *bytes) {
		return *reinterpret_cast< const int8_t * >(bytes);
	}
	inline uint8_t BytesBigEndianToUInt8(const uint8_t *bytes) {
		return bytes[0];
	}
	inline int16_t BytesBigEndianToInt16(const uint8_t *bytes) {
		return *reinterpret_cast< const int16_t * >(bytes);
	}
	inline uint16_t BytesBigEndianToUInt16(const uint8_t *bytes) {
		return *reinterpret_cast< const uint16_t * >(bytes);
	}
	inline int32_t BytesBigEndianToInt32(const uint8_t *bytes) {
		return *reinterpret_cast< const int32_t * >(bytes);
	}
	inline uint32_t BytesBigEndianToUInt32(const uint8_t *bytes) {
		return *reinterpret_cast< const uint32_t * >(bytes);
	}
	inline int64_t BytesBigEndianToInt64(const uint8_t *bytes) {
		return *reinterpret_cast< const int64_t * >(bytes);
	}
	inline uint64_t BytesBigEndianToUInt64(const uint8_t *bytes) {
		return *reinterpret_cast< const uint64_t * >(bytes);
	}
	inline float BytesBigEndianToFloat(const uint8_t *bytes) {
		return *reinterpret_cast< const float * >(bytes);
	}
	inline double BytesBigEndianToDouble(const uint8_t *bytes) {
		return *reinterpret_cast< const double * >(bytes);
	}

	inline int8_t BytesLittleEndianToInt8(const uint8_t *bytes) {
		return *reinterpret_cast< const int8_t * >(bytes);
	}
	inline uint8_t BytesLittleEndianToUInt8(const uint8_t *bytes) {
		return bytes[0];
	}
	inline int16_t BytesLittleEndianToInt16(const uint8_t *bytes) {
		const uint8_t reversed_bytes[] = { bytes[1], bytes[0] };
		return BytesBigEndianToInt16(reversed_bytes);
	}
	inline uint16_t BytesLittleEndianToUInt16(const uint8_t *bytes) {
		const uint8_t reversed_bytes[] = { bytes[1], bytes[0] };
		return BytesBigEndianToUInt16(reversed_bytes);
	}
	inline int32_t BytesLittleEndianToInt32(const uint8_t *bytes) {
		const uint8_t reversed_bytes[] = { bytes[3], bytes[2], bytes[1], bytes[0] };
		return BytesBigEndianToInt32(reversed_bytes);
	}
	inline uint32_t BytesLittleEndianToUInt32(const uint8_t *bytes) {
		const uint8_t reversed_bytes[] = { bytes[3], bytes[2], bytes[1], bytes[0] };
		return BytesBigEndianToUInt32(reversed_bytes);
	}
	inline int64_t BytesLittleEndianToInt64(const uint8_t *bytes) {
		const uint8_t reversed_bytes[] = { bytes[7], bytes[6], bytes[5], bytes[4], bytes[3], bytes[2], bytes[1], bytes[0] };
		return BytesBigEndianToInt64(reversed_bytes);
	}
	inline uint64_t BytesLittleEndianToUInt64(const uint8_t *bytes) {
		const uint8_t reversed_bytes[] = { bytes[7], bytes[6], bytes[5], bytes[4], bytes[3], bytes[2], bytes[1], bytes[0] };
		return BytesBigEndianToUInt64(reversed_bytes);
	}
	inline float BytesLittleEndianToFloat(const uint8_t *bytes) {
		const uint8_t reversed_bytes[] = { bytes[3], bytes[2], bytes[1], bytes[0] };
		return BytesBigEndianToFloat(reversed_bytes);
	}
	inline double BytesLittleEndianToDouble(const uint8_t *bytes) {
		const uint8_t reversed_bytes[] = { bytes[7], bytes[6], bytes[5], bytes[4], bytes[3], bytes[2], bytes[1], bytes[0] };
		return BytesBigEndianToDouble(reversed_bytes);
	}

	inline int8_t BytesToInt8(const uint8_t *bytes) {
		return *reinterpret_cast< const int8_t * >(bytes);
	}
	inline uint8_t BytesToUInt8(const uint8_t *bytes) {
		return bytes[0];
	}
	inline int16_t BytesToInt16(const uint8_t *bytes, bool big_endian) {
		return (big_endian) ? BytesBigEndianToInt16(bytes) : BytesLittleEndianToInt16(bytes);
	}
	inline uint16_t BytesToUInt16(const uint8_t *bytes, bool big_endian) {
		return (big_endian) ? BytesBigEndianToUInt16(bytes) : BytesLittleEndianToUInt16(bytes);
	}
	inline int32_t BytesToInt32(const uint8_t *bytes, bool big_endian) {
		return (big_endian) ? BytesBigEndianToInt32(bytes) : BytesLittleEndianToInt32(bytes);
	}
	inline uint32_t BytesToUInt32(const uint8_t *bytes, bool big_endian) {
		return (big_endian) ? BytesBigEndianToUInt32(bytes) : BytesLittleEndianToUInt32(bytes);
	}
	inline int64_t BytesToInt64(const uint8_t *bytes, bool big_endian) {
		return (big_endian) ? BytesBigEndianToInt64(bytes) : BytesLittleEndianToInt64(bytes);
	}
	inline uint64_t BytesToUInt64(const uint8_t *bytes, bool big_endian) {
		return (big_endian) ? BytesBigEndianToUInt64(bytes) : BytesLittleEndianToUInt64(bytes);
	}
	inline float BytesToFloat(const uint8_t *bytes, bool big_endian) {
		return (big_endian) ? BytesBigEndianToFloat(bytes) : BytesLittleEndianToFloat(bytes);
	}
	inline double BytesToDouble(const uint8_t *bytes, bool big_endian) {
		return (big_endian) ? BytesBigEndianToDouble(bytes) : BytesLittleEndianToDouble(bytes);
	}
}