#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\mesh.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of indexed sprite batch meshes.
	 */
	class SpriteBatchMesh : public Mesh {

	public:

		static const size_t SpriteBatchMesh::min_sprites_per_batch = 128;
		static const size_t SpriteBatchMesh::max_sprites_per_batch = 2048;
		static const size_t SpriteBatchMesh::vertices_per_sprite   = 4; // quad = 2 triangles
		static const size_t SpriteBatchMesh::indices_per_sprite    = 6; // quad = 2 triangles

		static constexpr size_t MinVerticesPerSprite() {
			return min_sprites_per_batch * vertices_per_sprite;
		}
		static constexpr size_t MaxVerticesPerSprite() {
			return max_sprites_per_batch * vertices_per_sprite;
		}
		static constexpr size_t MinIndicesPerSprite() {
			return min_sprites_per_batch * indices_per_sprite;
		}
		static constexpr size_t MaxIndicesPerSprite() {
			return max_sprites_per_batch * indices_per_sprite;
		}

		/**
		 Constructs a sprite batch mesh.
		 */
		SpriteBatchMesh(ComPtr< ID3D11Device2 > device, ComPtr< ID3D11DeviceContext2 > device_context);

		/**
		 Destructs this sprite batch mesh.
		 */
		virtual ~SpriteBatchMesh() = default;

	private:

		/**
		 Constructs a sprite batch mesh from the given sprite batch mesh.

		 @param[in]		sprite_batch_mesh
						A reference to the sprite batch mesh.
		 */
		SpriteBatchMesh(const SpriteBatchMesh &sprite_batch_mesh) = delete;

		/**
		 Constructs a sprite batch mesh from the given sprite batch mesh.

		 @param[in]		sprite_batch_mesh
						A reference to the sprite batch mesh.
		 */
		SpriteBatchMesh(SpriteBatchMesh &&sprite_batch_mesh) = delete;

		/**
		 Copies the given sprite batch mesh to this sprite batch mesh.

		 @param[in]		sprite_batch_mesh
						A reference to the sprite batch mesh to copy from.
		 @return		A reference to the copy of the given sprite batch mesh
						(i.e. this sprite batch mesh).
		*/
		SpriteBatchMesh &operator=(const SpriteBatchMesh &sprite_batch_mesh) = delete;

		/**
		 Copies the given sprite batch mesh to this sprite batch mesh.

		 @param[in]		sprite_batch_mesh
						A reference to the sprite batch mesh to copy from.
		 @return		A reference to the copy of the given sprite batch mesh
						(i.e. this sprite batch mesh).
		 */
		SpriteBatchMesh &operator=(SpriteBatchMesh &&sprite_batch_mesh) = delete;

		/**
		 Sets up the vertex buffer of this sprite batch mesh.
		 */
		HRESULT SetupVertexBuffer();

		/**
		 Sets up the index buffer of this sprite batch mesh.
		 */
		HRESULT SetupIndexBuffer();
	};
}