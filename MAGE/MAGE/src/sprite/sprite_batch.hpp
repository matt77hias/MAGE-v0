#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "collection\collection.hpp"
#include "math\sprite_transform.hpp"
#include "mesh\sprite_batch_mesh.hpp"
#include "mesh\vertex.hpp"
#include "rendering\constant_buffer.hpp"
#include "shader\sprite_shader.hpp"
#include "sprite\sprite_utils.hpp"
#include "sprite\sprite_sort_mode.hpp"
#include "sprite\sprite_effects.hpp"
#include "material\color.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// SpriteInfo
	//-------------------------------------------------------------------------

	/**
	 A struct of sprite info for a single sprite.
	 */
	__declspec(align(16)) struct SpriteInfo final : public AlignedData< SpriteInfo > {

	public:

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------
		
		// Combine values from SpriteEffect with these internal-only flags.

		/**
		 Mask indicating whether the source region of sprite info structures
		 is expressed in texels.
		 */
		static const unsigned int source_in_texels = 4;

		/**
		 Mask indicating whether the destination of sprite info structures
		 is expressed in pixels.
		 */
		static const unsigned int destination_size_in_pixels = 8;

		static_assert(
			(static_cast< unsigned int >(SpriteEffect::FlipBoth) & (source_in_texels | destination_size_in_pixels)) == 0, 
			"Flag bits must not overlap");
		
		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite info.
		 */
		SpriteInfo()
			: m_source{}, m_destination{},
			m_color{}, m_origin_rotation_depth{},
			m_texture(nullptr), m_flags(0) {}

		/**
		 Constructs a sprite info from the given sprite info.

		 @param[in]		sprite_info
						A reference to the sprite info to copy.
		 */
		SpriteInfo(const SpriteInfo &sprite_info) = default;

		/**
		 Constructs a sprite info by moving the given sprite info.

		 @param[in]		sprite_info
						A reference to the sprite info to move.
		 */
		SpriteInfo(SpriteInfo &&sprite_info) = default;

		/**
		 Destructs this sprite info.
		 */
		~SpriteInfo() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sprite info to this sprite info.

		 @param[in]		sprite_info
						A reference to the sprite info to copy.
		 @return		A reference to the copy of the given sprite info
						(i.e. this sprite info).
		 */
		SpriteInfo &operator=(const SpriteInfo &sprite_info) = default;

		/**
		 Moves the given sprite info to this sprite info.

		 @param[in]		sprite_info
						A reference to the sprite info to move.
		 @return		A reference to the moved sprite info
						(i.e. this sprite info).
		 */
		SpriteInfo &operator=(SpriteInfo &&sprite_info) = default;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The texture source region (Left Top Width Height) of the sprite
		 associated with this sprite info.
		 */
		XMFLOAT4A m_source;

		/**
		 The translation and scale (Tx Ty Sx Sy) of the sprite
		 associated with this sprite info.
		 */
		XMFLOAT4A m_destination;

		/**
		 The color of the sprite associated with this sprite info.
		 */
		XMFLOAT4A m_color;

		/**
		 The origin, rotation and depth (Ox Oy R D) of the sprite 
		 associated with this sprite info.
		 */
		XMFLOAT4A m_origin_rotation_depth;

		/**
		 A pointer to the shader resource view of the texture
		 associated with this sprite info.
		 */
		ID3D11ShaderResourceView *m_texture;

		/**
		 The flags of the sprite associated with this sprite info.
		 */
		unsigned int m_flags;
	};

	//-------------------------------------------------------------------------
	// SpriteBatch
	//-------------------------------------------------------------------------

	/**
	 A class of sprite batches.
	 */
	__declspec(align(16)) class SpriteBatch final : public AlignedData< SpriteBatch > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite batch.

		 @pre			The current engine must be loaded.
		 @param[in]		shader
						A reference to the shader.
		 */
		SpriteBatch(const CombinedShader &shader = CreateSpriteShader());

		/**
		 Constructs a sprite batch.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		shader
						A reference to the shader.
		 */
		SpriteBatch(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const CombinedShader &shader = CreateSpriteShader());

		/**
		 Constructs a sprite batch from the given sprite batch.

		 @param[in]		sprite_batch
						A reference to the sprite batch to copy.
		 */
		SpriteBatch(const SpriteBatch &sprite_batch) = delete;

		/**
		 Constructs a sprite batch by moving the given sprite batch.

		 @param[in]		sprite_batch
						A reference to the sprite batch to move.
		 */
		SpriteBatch(SpriteBatch &&sprite_batch);
		
		/**
		 Destructs this sprite batch.
		 */
		~SpriteBatch();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sprite batch to this sprite batch.

		 @param[in]		sprite_batch
						A reference to the sprite batch to copy.
		 @return		A reference to the copy of the given sprite batch
						(i.e. this sprite batch).
		 */
		SpriteBatch &operator=(const SpriteBatch &sprite_batch) = delete;

		/**
		 Moves the given sprite batch to this sprite batch.

		 @param[in]		sprite_batch
						A reference to the sprite batch to move.
		 @return		A reference to the moved sprite batch
						(i.e. this sprite batch).
		 */
		SpriteBatch &operator=(SpriteBatch &&sprite_batch) = delete;

		//---------------------------------------------------------------------
		// Member Methods: Lifecycle
		//---------------------------------------------------------------------

		/**
		 Begins the processing of a batch of sprites.

		 @pre			This sprite batch is not inside a begin/end pair.
		 @param[in]		sort_mode
						A reference to the sprite sorting mode for the whole batch of sprites.
		 @param[in]		transform
						A reference to the transform for the whole batch of sprites.
		 */
		void Begin(SpriteSortMode sort_mode = SpriteSortMode::Deferred, const XMMATRIX &transform = XMMatrixIdentity());
		
		/**
		 Draws a sprite.

		 @pre			This sprite batch is inside a begin/end pair.
		 @pre			@a texture is not equal to @c nullptr.
		 @param[in]		texture
						A pointer to the shader resource view of the texture to draw.
		 @param[in]		color
						A reference to the color (multiplier).
		 @param[in]		effects
						The sprite effects to apply.
		 @param[in]		transform
						A reference to the sprite transform.
		 @param[in]		source
						A pointer the rectangular subregion of the texture.
		 */
		void Draw(ID3D11ShaderResourceView *texture, const XMVECTOR &color, SpriteEffect effects,
			const SpriteTransform &transform, const RECT *source = nullptr);
		
		/**
		 Ends the processing of a batch of sprites.

		 @pre			This sprite batch is inside a begin/end pair.
		 */
		void End();

		//---------------------------------------------------------------------
		// Member Methods: Batch-Independent Data
		//---------------------------------------------------------------------

		/**
		 Returns the rotation mode of this sprite batch 
		 to fit the physical rotation of a monitor.

		 @return		The rotation mode of this sprite batch .
		 */
		DXGI_MODE_ROTATION GetRotationMode() const noexcept {
			return m_rotation_mode;
		}

		/**
		 Sets the rotation mode of this sprite batch
		 to fit the physical rotation of a monitor
		 to the given rotation mode.

		 @param[in]		rotation_mode
						The rotation mode.
		 */
		void SetRotationMode(DXGI_MODE_ROTATION rotation_mode) noexcept {
			m_rotation_mode = rotation_mode;
		}

		/**
		 Returns the viewport of this sprite batch.

		 @return		A reference to the viewport of this sprite batch.
		 */
		const D3D11_VIEWPORT &GetViewport() const noexcept {
			return m_viewport;
		}

		/**
		 Sets the viewport of this sprite batch to the given viewport.

		 @param[in]		viewport
						A reference to the viewport.
		 */
		void SetViewport(const D3D11_VIEWPORT &viewport) noexcept {
			m_viewport_set = true;
			m_viewport = viewport;
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods: Lifecycle
		//---------------------------------------------------------------------

		/**
		 Grows the sprite queue of this sprite batch. 
		 
		 This effectively replaces the current sprite queue
		 with a new sprite queue having a capacity equal
		 to two times the capacity of the current sprite queue
		 of this sprite batch.
		 */
		void GrowSpriteQueue();
		
		/**
		 Prepares the drawing of the mesh of this sprite batch.
		 */
		void PrepareDrawing();

		/**
		 Flushes a batch of sprites for rendering if non-immediate
		 rendering is required for the current batch of sprites.
		 Otherwise, the sprites in the current batch are rendered
		 immediately.

		 Sprites are sorted based on the sprite sorting mode
		 and adjacent sprites are grouped for rendering if sharing
		 the same texture.

		 @note		This functionality is only used if non-immediate 
					rendering is required.
		 */
		void FlushBatch();

		/**
		 Sorts the sprites of the current batch according to the
		 sprite sorting mode of the current batch of this sprite batch.

		 @note		This functionality is only used if non-immediate 
					rendering is required.
		 */
		void SortSprites();

		/**
		 Grows the vector of sorted sprites of this sprite batch.

		 This effectively replaces the current vector of sorted sprites
		 with a new vector of sorted sprites having a capacity equal
		 to the number of sprites waiting to be drawn in the sprite queue
		 of this sprite batch.

		 @note		This functionality is only used if non-immediate 
					rendering is required.
		 */
		void GrowSortedSprites();
		
		
		/**
		 Draws a subbatch of sprites of the current batch of sprites
		 of this sprite batch.

		 @pre			@a texture is not equal to @c nullptr.
		 @pre			@a sprites is not equal to @c nullptr.
		 @pre			@a sprites points to an array containing
						at least @a nb_sprites sprite info data 
						pointers which are not equal to @c nullptr.
		 @param[in]		texture
						A pointer to the shader resource view of the texture
						that needs to be rendered.
		 @param[in]		sprites
						A pointer to the sprite info data pointers of the
						sprites which need to be rendered.
		 @param[in]		nb_sprites
						The number of sprites which need to be rendered.
		 */
		void RenderBatch(ID3D11ShaderResourceView *texture,
			const SpriteInfo * const * sprites, size_t nb_sprites);

		/**
		 Prepares a single sprite for rendering.

		 @pre			@a sprite is not equal to @c nullptr.
		 @pre			@a vertices is not equal to @c nullptr.
		 @pre			@a vertices points to an array containing
						at least {@link mage::SpriteBatchMesh::s_vertices_per_sprite}.
		 @param[in]		sprite
						A pointer to the sprite info data.
		 @param[in]		vertices
						A pointer to the vertices for the sprite.
		 @param[in]		texture_size
						A reference to the size of the texture.
		 @param[in]		inverse_texture_size
						A reference to the inverse size of the texture.
		 */
		void PrepareSprite(const SpriteInfo *sprite, VertexPositionColorTexture *vertices,
			const XMVECTOR &texture_size, const XMVECTOR &inverse_texture_size) noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device of this sprite batch.
		 */
		ID3D11Device2 * const m_device;

		/**
		 A pointer to the device context of this sprite batch.
		 */
		ID3D11DeviceContext2 * const m_device_context;

		//---------------------------------------------------------------------
		// Member Variables: Model Data
		//---------------------------------------------------------------------

		/**
		 A pointer to the sprite batch mesh used by this sprite batch
		 for drawing the sprites onto.
		 */
		UniquePtr< SpriteBatchMesh > m_mesh;

		/**
		 The current position in the vertex buffer of the mesh
		 of this sprite batch for adding sprite vertices.
		 */
		size_t m_vertex_buffer_position;

		/**
		 A pointer to the shader used by this sprite batch
		 for shading the sprites.
		 */
		UniquePtr< CombinedShader > m_shader;

		//---------------------------------------------------------------------
		// Member Variables: Batch-Independent Data
		//---------------------------------------------------------------------

		/**
		 A flag indicating how the back buffers should be rotated
		 to fit the physical rotation of a monitor for this sprite batch.
		 */
		DXGI_MODE_ROTATION m_rotation_mode;

		/**
		 A flag (indicating whether the viewport of
		 this sprite batch has been set.
		 */
		bool m_viewport_set;

		/**
		 The viewport of this sprite batch.
		 */
		D3D11_VIEWPORT m_viewport;

		/**
		 A flag indicating whether this sprite batch is in
		 a begin/end pair for processing sprites.
		 */
		bool m_in_begin_end_pair;

		//---------------------------------------------------------------------
		// Member Variables: Batch-Dependent Data
		//---------------------------------------------------------------------

		/**
		 The sprite sorting mode used by this sprite batch for
		 deciding on the draw order of sprites in the current
		 btach of sprites.
		 */
		SpriteSortMode m_sort_mode;

		/**
		 The transform of this sprite batch applied to
		 all sprites in the current batch of sprites.
		 */
		XMMATRIX m_transform;

		/**
		 The transform buffer used by this sprite batch for storing
		 a sprite transformation. 
		 */
		ConstantBuffer< XMMATRIX > m_transform_buffer;

		//---------------------------------------------------------------------
		// Member Variables: Queuing Data
		//---------------------------------------------------------------------

		/**
		 A pointer to the queue containing the sprites waiting
		 to be drawn by this sprite batch.
		 */
		UniquePtr< SpriteInfo[] > m_sprite_queue;
		
		/**
		 The number of sprites waiting to be drawn by this sprite batch.
		 */
		size_t m_sprite_queue_size;

		/**
		 The number of sprites that could potentially be waiting to be drawn by 
		 this sprite batch. If the demand exceeds this number, the queue will
		 be enlarged appropriately.
		 */
		size_t m_sprite_queue_array_size;

		/**
		 A vector containing the pointer to the sorted sprites in the queue
		 of this sprite batch.
		 */
		vector< const SpriteInfo * > m_sorted_sprites;

		/**
		 A vector containing the smart pointers of the texture shader resource views.

		 If each {@link mage::SpriteInfo} instance held a refcount on its texture, 
		 this could end up with many redundant @c AddRef and @c Release calls on 
		 the same object, so instead this separate collection is used to hold just 
		 a single refcount each time the associated texture is changed.
		 */
		vector< ComPtr< ID3D11ShaderResourceView > > m_sprite_texture_references;

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The initial size of the queue containing the sprites waiting
		 to be drawn by a sprite batch.
		 */
		static const size_t s_initial_queue_size = 64;
	};
}