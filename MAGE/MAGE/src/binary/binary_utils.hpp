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
	void BytesLittleEndianToInt8(const char *bytes, int8_t &result);
	void BytesLittleEndianToUInt8(const char *bytes, uint8_t &result);
	void BytesLittleEndianToInt16(const char *bytes, int16_t &result);
	void BytesLittleEndianToUInt16(const char *bytes, uint16_t &result);
	void BytesLittleEndianToInt32(const char *bytes, int32_t &result);
	void BytesLittleEndianToUInt32(const char *bytes, uint32_t &result);
	void BytesLittleEndianToInt64(const char *bytes, int64_t &result);
	void BytesLittleEndianToUInt64(const char *bytes, uint64_t &result);
	void BytesLittleEndianToFloat(const char *bytes, float &result);
	void BytesLittleEndianToDouble(const char *bytes, double &result);

	void BytesBigEndianToInt8(const char *bytes, int8_t &result);
	void BytesBigEndianToUInt8(const char *bytes, uint8_t &result);
	void BytesBigEndianToInt16(const char *bytes, int16_t &result);
	void BytesBigEndianToUInt16(const char *bytes, uint16_t &result);
	void BytesBigEndianToInt32(const char *bytes, int32_t &result);
	void BytesBigEndianToUInt32(const char *bytes, uint32_t &result);
	void BytesBigEndianToInt64(const char *bytes, int64_t &result);
	void BytesBigEndianToUInt64(const char *bytes, uint64_t &result);
	void BytesBigEndianToFloat(const char *bytes, float &result);
	void BytesBigEndianToDouble(const char *bytes, double &result);
}