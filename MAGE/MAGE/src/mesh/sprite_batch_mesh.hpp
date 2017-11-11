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

		/**
		 The minimum number of sprites to draw per batch for sprite batch 
		 meshes.
		 */
		static const size_t s_min_sprites_per_batch = 128;

		/**
		 The maximum number of sprites to draw per batch (i.e. the maximum 
		 number of sprites that can be represented by a single sprite batch 
		 mesh) for sprite batch meshes.
		 */
		static const size_t s_max_sprites_per_batch = 2048;
		
		/**
		 The number of vertices per sprite.
		 */
		static const size_t s_vertices_per_sprite = 4; // quad = 2 triangles
		
		/**
		 The number of indices per sprite.
		 */
		static const size_t s_indices_per_sprite = 6; // quad = 2 triangles

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the minimum number of vertices to draw per batch for sprite 
		 batch meshes.

		 @return		The minimum number of vertices to draw per batch for 
						sprite batch meshes.
		 */
		static constexpr size_t MinVerticesPerBatch() noexcept {
			return s_vertices_per_sprite * s_min_sprites_per_batch;
		}

		/**
		 Returns the maximum number of vertices to draw per batch for sprite 
		 batch meshes.

		 @return		The maximum number of vertices to draw per batch for 
						sprite batch meshes.
		 */
		static constexpr size_t MaxVerticesPerBatch() noexcept {
			return s_vertices_per_sprite * s_max_sprites_per_batch;
		}

		/**
		 Returns the minimum number of indices to draw per batch for sprite 
		 batch meshes.

		 @return		The minimum number of indices to draw per batch for 
						sprite batch meshes.
		 */
		static constexpr size_t MinIndicesPerBatch() noexcept {
			return s_indices_per_sprite * s_min_sprites_per_batch;
		}

		/**
		 Returns the maximum number of indices to draw per batch for sprite 
		 batch meshes.

		 @return		The maximum number of indices to draw per batch for 
						sprite batch meshes.
		 */
		static constexpr size_t MaxIndicesPerBatch() noexcept {
			return s_indices_per_sprite * s_max_sprites_per_batch;
		}

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite batch mesh.

		 @pre			The device associated with the current engine must be 
						loaded.
		 @throws		FormattedException
						Failed to setup the vertex buffer of the sprite batch 
						mesh.
		 @throws		FormattedException
						Failed to setup the index buffer of the sprite batch 
						mesh.
		 */
		SpriteBatchMesh();

		/**
		 Constructs a sprite batch mesh.

		 @pre			@a device is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @throws		FormattedException
						Failed to setup the vertex buffer of the sprite batch 
						mesh.
		 @throws		FormattedException
						Failed to setup the index buffer of the sprite batch 
						mesh.
		 */
		explicit SpriteBatchMesh(ID3D11Device5 *device);

		/**
		 Constructs a sprite batch mesh from the given sprite batch mesh.

		 @param[in]		sprite_batch_mesh
						A reference to the sprite batch mesh to copy.
		 */
		SpriteBatchMesh(const SpriteBatchMesh &sprite_batch_mesh) = delete;

		/**
		 Constructs a sprite batch mesh by moving the given sprite batch mesh.

		 @param[in]		sprite_batch_mesh
						A reference to the sprite batch mesh to move.
		 */
		SpriteBatchMesh(SpriteBatchMesh &&sprite_batch_mesh);

		/**
		 Destructs this sprite batch mesh.
		 */
		virtual ~SpriteBatchMesh();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sprite batch mesh to this sprite batch mesh.

		 @param[in]		sprite_batch_mesh
						A reference to the sprite batch mesh to copy.
		 @return		A reference to the copy of the given sprite batch mesh 
						(i.e. this sprite batch mesh).
		 */
		SpriteBatchMesh &operator=(
			const SpriteBatchMesh &sprite_batch_mesh) = delete;

		/**
		 Moves the given sprite batch mesh to this sprite batch mesh.

		 @param[in]		sprite_batch_mesh
						A reference to the sprite batch mesh to move.
		 @return		A reference to the moved sprite batch mesh (i.e. this 
						sprite batch mesh).
		 */
		SpriteBatchMesh &operator=(
			SpriteBatchMesh &&sprite_batch_mesh) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Maps the vertex buffer of this this sprite batch mesh.

		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a mapped_buffer is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		map_type
						The map type specifying the CPU's read and write 
						permissions for the vertex buffer of this this sprite 
						batch mesh.
		 @param[out]	mapped_buffer
						A pointer to the map the vertex buffer of this this 
						sprite batch mesh to.
		 @return		A success/error value.
		 */
		HRESULT MapVertexBuffer(ID3D11DeviceContext4 *device_context,
			D3D11_MAP map_type, D3D11_MAPPED_SUBRESOURCE *mapped_buffer);
		
		/**
		 Unmaps the vertex buffer of this this sprite batch mesh.

		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			The vertex buffer of this this sprite batch mesh
						must be mapped with 
						{@link mage::SpriteBatchMesh::MapVertexBuffer(ID3D11DeviceContext4 *, D3D11_MAP, D3D11_MAPPED_SUBRESOURCE *)} 
						before it can be unmapped.
		 @param[in]		device_context
						A pointer to the device context.
		 */
		void UnmapVertexBuffer(ID3D11DeviceContext4 *device_context);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets up the vertex buffer of this sprite batch mesh.

		 @pre			@a device is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 */
		void SetupVertexBuffer(ID3D11Device5 *device);

		/**
		 Sets up the index buffer of this sprite batch mesh.

		 @pre			@a device is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 */
		void SetupIndexBuffer(ID3D11Device5 *device);
	};
}