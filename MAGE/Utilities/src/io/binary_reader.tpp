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
	const T BinaryReader::Read() {
		const auto old_pos = m_pos;
		const auto new_pos = m_pos + sizeof(T);
		
		ThrowIfFailed((m_pos <= new_pos), 
					  "{}: overflow: no value found.", GetPath());
		ThrowIfFailed((new_pos <= m_end), 
					  "{}: end of file: no value found.", GetPath());

		m_pos = new_pos;
		return BytesTo< T >(old_pos, m_big_endian);
	}

	template< typename T >
	inline const T BigEndianBinaryReader::Read() {
		return *ReadArray< T >(1u);
	}

	template< typename T >
	const T* BigEndianBinaryReader::ReadArray(std::size_t count) {
		const auto old_pos = m_pos;
		const auto new_pos = m_pos + sizeof(T) * count;
		
		ThrowIfFailed((m_pos <= new_pos), 
					  "{}: overflow: no {} values found.", GetPath(), count);
		ThrowIfFailed((new_pos <= m_end), 
					  "{}: end of file: no {} values found.", GetPath(), count);

		m_pos = new_pos;
		return reinterpret_cast< const T* >(old_pos);
	}
}