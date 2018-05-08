#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename DataT >
	inline void BigEndianBinaryWriter::Write(const DataT& data) {
		WriteArray(gsl::make_span< const DataT >(&data, size_t(1)));
	}

	template< typename DataT >
	void BigEndianBinaryWriter::WriteArray(gsl::span< const DataT > data) {
		const size_t count         = data.size();
		const size_t count_written = fwrite(data.data(), 
											sizeof(DataT), 
											count,
											m_file_stream.get());
		ThrowIfFailed((count_written == count),
					  "%ls: could not write all data to file.", 
					  GetPath().c_str());
	}
}