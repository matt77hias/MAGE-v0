#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\error.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename DataT >
	inline void BigEndianBinaryWriter::Write(const DataT &data) {
		WriteArray(&data, 1);
	}

	template< typename DataT >
	inline void BigEndianBinaryWriter::WriteArray(const DataT *data, 
		                                          size_t count) {
		Assert(data);
		
		const size_t count_written 
			= fwrite(data, sizeof(DataT), count, m_file_stream.get());
		ThrowIfFailed((count_written == count),
			"%ls: could not write all data to file.", GetFilename().c_str());
	}
}