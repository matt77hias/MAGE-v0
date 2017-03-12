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

	template< typename ValueT >
	const ValueT &BigEndianBinaryReader::ReadValue() {
		return *ReadValueArray< ValueT >(1);
	}

	template< typename ValueT >
	const ValueT *BigEndianBinaryReader::ReadValueArray(size_t size) {
		const uint8_t *new_pos = m_pos + sizeof(ValueT) * size;
		if (new_pos < m_pos) {
			Error("%ls: overflow: no %llu values found.", GetFilename().c_str(), size);
			return nullptr;
		}
		if (m_end < new_pos) {
			Error("%ls: end of file: no %llu values found.", GetFilename().c_str(), size);
			return nullptr;
		}

		const ValueT *result = BytesBigEndianToValue< ValueT >(m_pos);
		m_pos = new_pos;
		return result;
	}
}