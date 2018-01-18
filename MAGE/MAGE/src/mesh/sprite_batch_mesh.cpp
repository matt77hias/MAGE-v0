//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\sprite_batch_mesh.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <limits>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpriteBatchMesh::SpriteBatchMesh()
		: SpriteBatchMesh(Pipeline::GetDevice()) {}

	SpriteBatchMesh::SpriteBatchMesh(ID3D11Device5 *device) 
		: PrimitiveBatchMesh(device,
		                     MaxVerticesPerBatch(),
		                     GenerateIndices()) {}

	SpriteBatchMesh::SpriteBatchMesh(SpriteBatchMesh &&mesh) noexcept = default;

	SpriteBatchMesh::~SpriteBatchMesh() = default;

	SpriteBatchMesh &SpriteBatchMesh
		::operator=(SpriteBatchMesh &&mesh) noexcept = default;

	[[nodiscard]] const std::vector< U16 > SpriteBatchMesh::GenerateIndices() {
		static_assert(MaxVerticesPerBatch() < std::numeric_limits< U16 >::max(),
			"s_max_sprites_per_batch too large for 16-bit indices.");

		// Create indices.
		std::vector< U16 > indices;
		indices.reserve(MaxIndicesPerBatch());
		for (U16 i = 0; i < MaxVerticesPerBatch(); i += s_vertices_per_sprite) {
			// First triangle
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i + 2);
			// Second triangle
			indices.push_back(i + 1);
			indices.push_back(i + 3);
			indices.push_back(i + 2);
		}
		return indices;
	}
}