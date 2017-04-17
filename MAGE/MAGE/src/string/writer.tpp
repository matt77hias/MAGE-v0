#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename DataT >
	inline void Writer::WriteValue(const DataT &data) {
		WriteValueArray(&data, 1);
	}

	template< typename DataT >
	inline void Writer::WriteValueArray(const DataT *data, size_t count) {
		fwrite(data, sizeof(DataT), count, m_file);
	}
}