#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\static_mesh.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT StaticMesh::SetupIndexBuffer(const uint32_t *indices, size_t nb_indices) {
		const HRESULT result_index_buffer = CreateIndexBuffer< uint32_t >(*m_device.Get(), m_index_buffer.ReleaseAndGetAddressOf(), indices, nb_indices);
		if (FAILED(result_index_buffer)) {
			Error("Index buffer creation failed: %08X.", result_index_buffer);
			return result_index_buffer;
		}

		SetNumberOfIndices(nb_indices);

		return S_OK;
	}
}