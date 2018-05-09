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

	template< typename T >
	inline void BigEndianBinaryWriter::Write(const T& data) {
		WriteArray(gsl::make_span< const T >(&data, size_t(1)));
	}

	template< typename T >
	void BigEndianBinaryWriter::WriteArray(gsl::span< const T > data) {
		const size_t count         = data.size();
		const size_t count_written = fwrite(data.data(), sizeof(T), count,
											m_file_stream.get());
		ThrowIfFailed((count_written == count),
					  "%ls: could not write all data to file.", 
					  GetPath().c_str());
	}
}