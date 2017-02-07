#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename Vertex >
	HRESULT LoadMeshFromFile(const wstring &fname,
		vector< Vertex > &vertex_buffer, vector< uint32_t > &index_buffer,
		bool invert_handedness, bool clockwise_order) {

		const wstring extension = GetFileExtension(fname);

		if (extension == L"obj" || extension == L"OBJ") {
			return LoadOBJMeshFromFile< Vertex >(fname, vertex_buffer, index_buffer, invert_handedness, clockwise_order);
		}

		Warning("Unknown model file extension: %ls", fname.c_str());
		return E_FAIL;
	}

	template < typename Vertex >
	HRESULT LoadMeshFromFile(const wstring &fname,
		vector< Vertex > &vertex_buffer,
		bool invert_handedness, bool clockwise_order) {

		const wstring extension = GetFileExtension(fname);

		if (extension == L"obj" || extension == L"OBJ") {
			return LoadOBJMeshFromFile< Vertex >(fname, vertex_buffer, invert_handedness, clockwise_order);
		}

		Warning("Unknown model file extension: %ls", fname.c_str());
		return E_FAIL;
	}
}