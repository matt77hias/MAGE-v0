#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename DataT >
	void Writer::Write(const DataT *data, size_t count) {
		fwrite(data, sizeof(DataT), count, m_file);
	}
}