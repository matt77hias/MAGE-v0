#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename DataT >
	void Writer::WriteValue(const DataT &data) {
		WriteData(&data, 1);
	}

	template< typename DataT >
	void Writer::WriteValueArray(const DataT *data, size_t count) {
		fwrite(data, sizeof(DataT), count, m_file);
	}
}