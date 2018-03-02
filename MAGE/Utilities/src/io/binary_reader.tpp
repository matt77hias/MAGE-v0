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
	const DataT BinaryReader::Read() {
		const auto old_pos = m_pos;
		const auto new_pos = m_pos + sizeof(DataT);
		
		ThrowIfFailed((m_pos <= new_pos), 
					  "%ls: overflow: no value found.", 
					  GetFilename().c_str());
		ThrowIfFailed((new_pos <= m_end), 
					  "%ls: end of file: no value found.", 
					  GetFilename().c_str());

		m_pos = new_pos;
		return BytesTo< DataT >(old_pos, m_big_endian);
	}

	template< typename DataT >
	inline const DataT BigEndianBinaryReader::Read() {
		return *ReadArray< DataT >(1);
	}

	template< typename DataT >
	const DataT* BigEndianBinaryReader::ReadArray(size_t count) {
		const auto old_pos = m_pos;
		const auto new_pos = m_pos + sizeof(DataT) * count;
		
		ThrowIfFailed((m_pos <= new_pos), 
					  "%ls: overflow: no %llu values found.", 
					  GetFilename().c_str(), 
					  static_cast< U64 >(count));
		ThrowIfFailed((new_pos <= m_end), 
					  "%ls: end of file: no %llu values found.", 
					  GetFilename().c_str(), 
					  static_cast< U64 >(count));

		m_pos = new_pos;
		return reinterpret_cast< const DataT * >(old_pos);
	}
}