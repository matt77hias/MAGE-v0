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

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		static const size_t min_sprites_per_batch = 128;
		static const size_t max_sprites_per_batch = 2048;
		static const size_t vertices_per_sprite   = 4; // quad = 2 triangles
		static const size_t indices_per_sprite    = 6; // quad = 2 triangles

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		static constexpr size_t MinVerticesPerBatch() {
			return vertices_per_sprite * min_sprites_per_batch;
		}
		static constexpr size_t MaxVerticesPerBatch() {
			return vertices_per_sprite * max_sprites_per_batch;
		}
		static constexpr size_t MinIndicesPerBatch() {
			return indices_per_sprite * min_sprites_per_batch;
		}
		static constexpr size_t MaxIndicesPerBatch() {
			return indices_per_sprite * max_sprites_per_batch;
		}

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite batch mesh.
		 */
		explicit SpriteBatchMesh(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);

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
		SpriteBatchMesh(SpriteBatchMesh &&sprite_batch_mesh) = default;

		/**
		 Destructs this sprite batch mesh.
		 */
		virtual ~SpriteBatchMesh() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

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

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		HRESULT MapVertexBuffer(D3D11_MAP map_type, D3D11_MAPPED_SUBRESOURCE *mapped_buffer) const {
			return m_device_context->Map(m_vertex_buffer.Get(), 0, map_type, 0, mapped_buffer);
		}
		void UnmapVertexBuffer() {
			m_device_context->Unmap(m_vertex_buffer.Get(), 0);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

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