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

	void StaticMesh::SetupIndexBuffer(const uint32_t *indices, size_t nb_indices) {
		const HRESULT result_index_buffer = CreateStaticIndexBuffer< uint32_t >(m_device, m_index_buffer.ReleaseAndGetAddressOf(), indices, nb_indices);
		if (FAILED(result_index_buffer)) {
			throw FormattedException("Index buffer creation failed: %08X.", result_index_buffer);
		}

		SetNumberOfIndices(nb_indices);
	}
}