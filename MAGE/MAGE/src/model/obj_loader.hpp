#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void LoadOBJModelFromFile(const string &fname,
		vector< Vertex > &vertex_buffer, vector< uint32_t > &index_buffer);
}
