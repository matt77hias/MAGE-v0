#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\primitive_batch_mesh.hpp"
#include "mesh\vertex.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of indexed sprite batch meshes.
	 */
	class SpriteBatchMesh : 
		public PrimitiveBatchMesh< VertexPositionColorTexture, U16 > {

	public:

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The minimum number of sprites to draw per batch for sprite batch 
		 meshes.
		 */
		static constexpr size_t s_min_sprites_per_batch = 128;

		/**
		 The maximum number of sprites to draw per batch (i.e. the maximum 
		 number of sprites that can be represented by a single sprite batch 
		 mesh) for sprite batch meshes.
		 */
		static constexpr size_t s_max_sprites_per_batch = 2048;
		
		/**
		 The number of vertices per sprite.
		 */
		static constexpr size_t s_vertices_per_sprite = 4; // quad = 2 triangles
		
		/**
		 The number of indices per sprite.
		 */
		static constexpr size_t s_indices_per_sprite = 6; // quad = 2 triangles

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
		 @throws		Exception
						Failed to setup the vertex buffer of the sprite batch 
						mesh.
		 @throws		Exception
						Failed to setup the index buffer of the sprite batch 
						mesh.
		 */
		SpriteBatchMesh();

		/**
		 Constructs a sprite batch mesh.

		 @pre			@a device is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @throws		Exception
						Failed to setup the vertex buffer of the sprite batch 
						mesh.
		 @throws		Exception
						Failed to setup the index buffer of the sprite batch 
						mesh.
		 */
		explicit SpriteBatchMesh(ID3D11Device5 *device);

		/**
		 Constructs a sprite batch mesh from the given sprite batch mesh.

		 @param[in]		mesh
						A reference to the sprite batch mesh to copy.
		 */
		SpriteBatchMesh(const SpriteBatchMesh &mesh) = delete;

		/**
		 Constructs a sprite batch mesh by moving the given sprite batch mesh.

		 @param[in]		mesh
						A reference to the sprite batch mesh to move.
		 */
		SpriteBatchMesh(SpriteBatchMesh &&mesh) noexcept;

		/**
		 Destructs this sprite batch mesh.
		 */
		virtual ~SpriteBatchMesh();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sprite batch mesh to this sprite batch mesh.

		 @param[in]		mesh
						A reference to the sprite batch mesh to copy.
		 @return		A reference to the copy of the given sprite batch mesh 
						(i.e. this sprite batch mesh).
		 */
		SpriteBatchMesh &operator=(const SpriteBatchMesh &mesh) = delete;

		/**
		 Moves the given sprite batch mesh to this sprite batch mesh.

		 @param[in]		mesh
						A reference to the sprite batch mesh to move.
		 @return		A reference to the moved sprite batch mesh (i.e. this 
						sprite batch mesh).
		 */
		SpriteBatchMesh &operator=(SpriteBatchMesh &&mesh) noexcept;

	private:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Generates the indices of a sprite batch mesh.

		 @return		A vector containing the indices of a sprite batch mesh.
		 */
		static std::vector< U16 > GenerateIndices();
	};
}