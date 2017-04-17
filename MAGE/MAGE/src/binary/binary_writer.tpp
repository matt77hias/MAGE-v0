#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename DataT >
	inline void BigEndianBinaryWriter::WriteValue(const DataT &data) {
		WriteValueArray(&data, 1);
	}

	template< typename DataT >
	inline void BigEndianBinaryWriter::WriteValueArray(const DataT *data, size_t count) {
		const size_t count_written = fwrite(data, sizeof(DataT), count, m_file);
		Assert(count == count_written);
	}
}