#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\logging\error.hpp"
#include "utils\exception\exception.hpp"

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
	inline void BigEndianBinaryWriter::WriteValueArray(const DataT *data, 
		size_t count) {
		
		Assert(data);
		
		const size_t count_written = fwrite(
			data, sizeof(DataT), count, m_file_stream.get());
		ThrowIfFailed((count_written == count),
			"%ls: could not write all data to file.", GetFilename().c_str());
	}
}