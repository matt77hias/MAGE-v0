//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\pass\sprite_batch.hpp"
#include "collection\vector.hpp"
#include "resource\mesh\sprite_batch_mesh.hpp"
#include "resource\mesh\vertex.hpp"
#include "resource\texture\texture.hpp"
#include "logging\error.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// SpriteInfo
	//-------------------------------------------------------------------------
	namespace {

		/**
		 A struct of sprite info for a single sprite.
		 */
		struct alignas(16) SpriteInfo final {

		public:

			//---------------------------------------------------------------------
			// Class Member Variables
			//---------------------------------------------------------------------
		
			// Combine values from SpriteEffect with these internal-only flags.

			/**
			 Mask indicating whether the source region (top left, width and height) 
			 of sprite info structures is expressed in texels.
			 */
			static constexpr U32 s_source_in_texels = 4u;

			/**
			 Mask indicating whether the destination size (width and height) of 
			 sprite info structures is expressed in pixels.
			 */
			static constexpr U32 s_destination_size_in_pixels = 8u;

			static_assert(((s_source_in_texels | s_destination_size_in_pixels)
						  & static_cast< U32 >(SpriteEffect::MirrorXY)) == 0, 
						  "Flag bits must not overlap");
		
			//---------------------------------------------------------------------
			// Constructors and Destructors
			//---------------------------------------------------------------------

			/**
			 Constructs a sprite info.
			 */
			SpriteInfo() noexcept
				: m_source{}, 
				m_destination{}, 
				m_color{}, 
				m_origin_rotation_depth{}, 
				m_texture(nullptr), 
				m_flags(0u) {}

			/**
			 Constructs a sprite info from the given sprite info.

			 @param[in]		sprite_info
							A reference to the sprite info to copy.
			 */
			SpriteInfo(const SpriteInfo& sprite_info) noexcept = default;

			/**
			 Constructs a sprite info by moving the given sprite info.

			 @param[in]		sprite_info
							A reference to the sprite info to move.
			 */
			SpriteInfo(SpriteInfo&& sprite_info) noexcept = default;

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
			 @return		A reference to the copy of the given sprite info (i.e. 
							this sprite info).
			 */
			SpriteInfo& operator=(const SpriteInfo& sprite_info) noexcept = default;

			/**
			 Moves the given sprite info to this sprite info.

			 @param[in]		sprite_info
							A reference to the sprite info to move.
			 @return		A reference to the moved sprite info (i.e. this sprite 
							info).
			 */
			SpriteInfo& operator=(SpriteInfo&& sprite_info) noexcept = default;

			//---------------------------------------------------------------------
			// Member Variables
			//---------------------------------------------------------------------

			/**
			 The texture source region (Left Top Width Height) of the sprite 
			 associated with this sprite info.
			 */
			F32x4A m_source;

			/**
			 The translation and scale (Tx Ty Sx Sy) of the sprite associated with 
			 this sprite info.
			 */
			F32x4A m_destination;

			/**
			 The (linear) RGBA color of the sprite associated with this sprite 
			 info.
			 */
			F32x4A m_color;

			/**
			 The origin, rotation and depth (Ox Oy R D) of the sprite associated 
			 with this sprite info.
			 */
			F32x4A m_origin_rotation_depth;

			/**
			 A pointer to the shader resource view of the texture associated 
			 with this sprite info.
			 */
			ID3D11ShaderResourceView* m_texture;

			/**
			 The flags of the sprite associated with this sprite info.
			 */
			U32 m_flags;
		};
	}

	//-------------------------------------------------------------------------
	// SpriteBatch::Impl
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of sprite batches.
	 */
	class SpriteBatch::Impl final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite batch.

		 @param[in]		device
						A reference to the device.
		 @param[in]		device_context
						A reference to the device context.
		 */
		Impl(ID3D11Device& device, ID3D11DeviceContext& device_context);

		/**
		 Constructs a sprite batch from the given sprite batch.

		 @param[in]		sprite_batch
						A reference to the sprite batch to copy.
		 */
		Impl(const Impl& sprite_batch) = delete;

		/**
		 Constructs a sprite batch by moving the given sprite batch.

		 @param[in]		sprite_batch
						A reference to the sprite batch to move.
		 */
		Impl(Impl&& sprite_batch) noexcept;
		
		/**
		 Destructs this sprite batch.
		 */
		~Impl();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sprite batch to this sprite batch.

		 @param[in]		sprite_batch
						A reference to the sprite batch to copy.
		 @return		A reference to the copy of the given sprite batch (i.e. 
						this sprite batch).
		 */
		Impl& operator=(const Impl& sprite_batch) = delete;

		/**
		 Moves the given sprite batch to this sprite batch.

		 @param[in]		sprite_batch
						A reference to the sprite batch to move.
		 @return		A reference to the moved sprite batch (i.e. this sprite 
						batch).
		 */
		Impl& operator=(Impl&& sprite_batch) noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Lifecycle
		//---------------------------------------------------------------------

		/**
		 Begins the processing of a batch of sprites.

		 @pre			This sprite batch is not inside a begin/end pair.
		 @param[in]		sort_mode
						A reference to the sprite sorting mode for the whole 
						batch of sprites.
		 */
		void Begin(SpriteSortMode sort_mode = SpriteSortMode::Deferred);
		
		/**
		 Draws a sprite.

		 @pre			This sprite batch is inside a begin/end pair.
		 @param[in]		texture
						A pointer to the shader resource view of the texture to 
						draw.
		 @param[in]		color
						The (linear) RGBA color.
		 @param[in]		effects
						The sprite effects to apply.
		 @param[in]		transform
						A reference to the sprite transform.
		 @param[in]		source
						A pointer the rectangular subregion of the texture.
		 */
		void XM_CALLCONV Draw(ID3D11ShaderResourceView* texture, 
			                  FXMVECTOR color, 
			                  SpriteEffect effects, 
			                  const SpriteTransform& transform, 
			                  const RECT* source = nullptr);
		
		/**
		 Ends the processing of a batch of sprites.

		 @pre			This sprite batch is inside a begin/end pair.
		 */
		void End();

	private:

		//---------------------------------------------------------------------
		// Member Methods: Lifecycle
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this sprite batch.
		 */
		void BindFixedState();
		
		/**
		 Flushes a batch of sprites for rendering if non-immediate rendering is 
		 required for the current batch of sprites. Otherwise, the sprites in 
		 the current batch are rendered immediately.

		 Sprites are sorted based on the sprite sorting mode and adjacent 
		 sprites are grouped for rendering if sharing the same texture.

		 @note		This functionality is only used in case of non-immediate 
					rendering.
		 */
		void FlushBatch();

		/**
		 Sorts the sprites of the current batch according to the sprite sorting 
		 mode of this sprite batch.

		 @note		This functionality is only used in case of non-immediate 
					rendering.
		 */
		void SortSprites();
		
		/**
		 Draws a subbatch of sprites of the current batch of sprites
		 of this sprite batch.

		 @pre			@a sprites is not equal to @c nullptr.
		 @pre			@a sprites points to an array containing at least 
						@a nb_sprites sprite info data pointers which are not 
						equal to @c nullptr.
		 @param[in]		texture
						A pointer to the shader resource view of the texture
						that needs to be rendered.
		 @param[in]		sprites
						A pointer to the sprite info data pointers of the
						sprites which need to be rendered.
		 @param[in]		nb_sprites
						The number of sprites which need to be rendered.
		 */
		void Render(ID3D11ShaderResourceView* texture,
					const SpriteInfo* const* sprites,
					size_t nb_sprites);
		
		/**
		 Prepares a single sprite for rendering.

		 @pre			@a vertices is not equal to @c nullptr.
		 @pre			@a vertices points to an array containing at least 
						{@link mage::rendering::SpriteBatchMesh::s_vertices_per_sprite}.
		 @param[in]		sprite
						A reference to the sprite info data.
		 @param[in]		vertices
						A pointer to the vertices for the sprite.
		 @param[in]		texture_size
						The size of the texture (in the number of texels).
		 @param[in]		inverse_texture_size
						The inverse of @a texture_size.
		 */
		void XM_CALLCONV PrepareSprite(const SpriteInfo& sprite, 
			                           VertexPositionColorTexture* vertices,
			                           FXMVECTOR texture_size, 
			                           FXMVECTOR inverse_texture_size) noexcept;

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The initial capacity of the vector containing the sprites waiting to 
		 be drawn by a sprite batch.
		 */
		static const size_t s_initial_capacity = 64u;

		//---------------------------------------------------------------------
		// Member Variables: Rendering
		//---------------------------------------------------------------------

		/**
		 A reference to the device context of this sprite batch.
		 */
		std::reference_wrapper< ID3D11DeviceContext > m_device_context;

		/**
		 A pointer to the sprite batch mesh used by this sprite batch for 
		 drawing the sprites onto.
		 */
		UniquePtr< SpriteBatchMesh > m_mesh;

		/**
		 The current position in the mesh of this sprite batch for adding sprite 
		 vertices.
		 */
		size_t m_mesh_position;

		/**
		 A flag indicating whether this sprite batch is in a begin/end pair 
		 for processing sprites.
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

		//---------------------------------------------------------------------
		// Member Variables: Sprites
		//---------------------------------------------------------------------

		/**
		 A vector containing the sprites waiting to be drawn by this sprite 
		 batch.
		 */
		AlignedVector< SpriteInfo > m_sprites;
		
		/**
		 A vector containing the pointers to the sorted sprites of this sprite 
		 batch.
		 */
		std::vector< const SpriteInfo* > m_sorted_sprites;
	};

	SpriteBatch::Impl::Impl(ID3D11Device& device, 
							ID3D11DeviceContext& device_context)
		: m_device_context(device_context),
		m_mesh(MakeUnique< SpriteBatchMesh >(device)),
		m_mesh_position(0u),
		m_in_begin_end_pair(false),
		m_sort_mode(SpriteSortMode::Deferred),
		m_sprites(),
		m_sorted_sprites() {

		m_sprites.reserve(s_initial_capacity);
	}

	SpriteBatch::Impl::Impl(Impl&& sprite_batch) noexcept = default;

	SpriteBatch::Impl::~Impl() = default;

	SpriteBatch::Impl& SpriteBatch::Impl
		::operator=(Impl&& sprite_batch) noexcept = default;

	void SpriteBatch::Impl::Begin(SpriteSortMode sort_mode) {
		
		// This SpriteBatch may not already be in a begin/end pair.
		Assert(!m_in_begin_end_pair);

		m_sprites.clear();
		m_sorted_sprites.clear();

		m_sort_mode = sort_mode;

		if (SpriteSortMode::Immediate == m_sort_mode) {
			BindFixedState();
		}

		// Toggle the begin/end pair.
		m_in_begin_end_pair = true;
	}
	
	void XM_CALLCONV SpriteBatch::Impl::Draw(ID3D11ShaderResourceView* texture, 
											 FXMVECTOR color, 
											 SpriteEffect effects, 
											 const SpriteTransform& transform, 
											 const RECT* source) {
		
		// This SpriteBatch must already be in a begin/end pair.
		Assert(m_in_begin_end_pair);

		// destination: [Tx Ty Sx Sy]
		const auto destination = XMVectorSet(transform.GetTranslation().m_x,
										     transform.GetTranslation().m_y,
										     transform.GetScale().m_x,
										     transform.GetScale().m_y);
		// origin_rotation_depth: [ROx ROy R D]
		const auto origin_rotation_depth = XMVectorSet(transform.GetRotationOrigin().m_x, 
										               transform.GetRotationOrigin().m_y, 
										               transform.GetRotation(), 
										               transform.GetDepth());
		auto flags = static_cast< U32 >(effects);
		auto dst   = destination;
		
		SpriteInfo sprite;

		if (source) {
			// If a source is given, the source region is represented in 
			// (absolute) texel coordinates.
			const auto src = XMVectorLeftTopWidthHeight(*source);
			sprite.m_source = XMStore< F32x4A >(src);

			// If the destination size is relative to the texture region
			// (i.e. multiplier), the destination size is represented in 
			// (absolute) pixel coordinates.
			if (false == (flags & SpriteInfo::s_destination_size_in_pixels)) {
				dst = XMVectorPermute< 0, 1, 6, 7 >(dst, dst * src);
			}

			flags |= SpriteInfo::s_source_in_texels 
				  |  SpriteInfo::s_destination_size_in_pixels;

			//-----------------------------------------------------------------
			// Source region    is represented in absolute texel coordinates.
			// Destination size is represented in absolute pixel coordinates.
			// E.g. SpriteText
			//-----------------------------------------------------------------
		}
		else {
			// If no source is given, the source region is represented in 
			// (relative) texel (UV) coordinates.
			static const XMVECTORF32 src = { 0.0f, 0.0f, 1.0f, 1.0f };
			sprite.m_source = XMStore< F32x4A >(src);

			//-----------------------------------------------------------------
			// Source region    is represented in relative texel coordinates.
			// Destination size is represented in relative pixel coordinates.
			// E.g. SpriteImage
			//-----------------------------------------------------------------
		}

		sprite.m_destination           = XMStore< F32x4A >(dst);
		sprite.m_color                 = XMStore< F32x4A >(color);
		sprite.m_origin_rotation_depth = XMStore< F32x4A >(origin_rotation_depth);
		sprite.m_texture               = texture;
		sprite.m_flags                 = flags;

		if (SpriteSortMode::Immediate == m_sort_mode) {
			const auto sprites = &sprite;
			Render(texture, &sprites, 1u);
		}
		else {
			
			if (m_sprites.size() == m_sprites.capacity()) {
				m_sprites.reserve(2 * m_sprites.capacity());
			}

			m_sprites.push_back(std::move(sprite));
		}
	}

	void SpriteBatch::Impl::End() {
		// This SpriteBatch must already be in a begin/end pair.
		Assert(m_in_begin_end_pair);

		if (SpriteSortMode::Immediate != m_sort_mode) {
			// Draw the queued sprites.
			BindFixedState();
			FlushBatch();
		}

		// Untoggle the begin/end pair.
		m_in_begin_end_pair = false;
	}

	void SpriteBatch::Impl::BindFixedState() {
		if (D3D11_DEVICE_CONTEXT_DEFERRED == m_device_context.get().GetType()) {
			m_mesh_position = 0;
		}

		// Binds the mesh.
		m_mesh->BindMesh(m_device_context);
	}

	void SpriteBatch::Impl::FlushBatch() {
		if (0u == m_sprites.size()) {
			return;
		}

		// Sort the sprites of this sprite batch.
		SortSprites();

		// Iterate the sorted sprites of this sprite batch, looking for adjacent 
		// sprites sharing a texture.
		ID3D11ShaderResourceView* batch_texture = nullptr;
		size_t batch_start = 0u;
		for (size_t i = 0; i < m_sprites.size(); ++i) {
			auto sprite_texture = m_sorted_sprites[i]->m_texture;

			if (sprite_texture != batch_texture) {
				
				if (i > batch_start) {
					// Flush the current subbatch.
					const auto nb_sprites_batch = i - batch_start;
					Render(batch_texture, &m_sorted_sprites[batch_start], nb_sprites_batch);
				}
				
				batch_texture = sprite_texture;
				batch_start   = i;
			}
		}
		
		// Flush the final subbatch.
		const auto nb_sprites_batch = m_sprites.size() - batch_start;
		Render(batch_texture, &m_sorted_sprites[batch_start], nb_sprites_batch);
	}

	void SpriteBatch::Impl::SortSprites() {
		m_sorted_sprites.reserve(m_sprites.capacity());
		for (const auto& sprite : m_sprites) {
			m_sorted_sprites.push_back(&sprite);
		}
		
		switch (m_sort_mode) {

		case SpriteSortMode::Texture: {
			
			std::sort(std::begin(m_sorted_sprites), 
				      std::end(m_sorted_sprites), 
				      [](const SpriteInfo *lhs, 
						 const SpriteInfo *rhs) noexcept {
					     return lhs->m_texture < rhs->m_texture;
				      });
			break;
		}
		
		case SpriteSortMode::BackToFront: {
			
			std::sort(std::begin(m_sorted_sprites),
					  std::end(m_sorted_sprites),
				      [](const SpriteInfo *lhs, 
						 const SpriteInfo *rhs) noexcept {
					     return lhs->m_origin_rotation_depth.m_w 
							  > rhs->m_origin_rotation_depth.m_w;
				      });
			break;
		}
		
		case SpriteSortMode::FrontToBack: {
			
			std::sort(std::begin(m_sorted_sprites),
					  std::end(m_sorted_sprites),
				      [](const SpriteInfo *lhs, 
						 const SpriteInfo *rhs) noexcept {
					     return lhs->m_origin_rotation_depth.m_w 
							  < rhs->m_origin_rotation_depth.m_w;
				      });
			break;
		}
		}
	}

	void SpriteBatch::Impl::Render(ID3D11ShaderResourceView* texture,
								   const SpriteInfo* const* sprites,
								   size_t nb_sprites) {

		// Binds the texture.
		Pipeline::PS::BindSRV(m_device_context, SLOT_SRV_SPRITE, texture);

		const auto texture_size         = XMLoad(GetTexture2DSize(*texture));
		const auto inverse_texture_size = XMVectorReciprocal(texture_size);

		while (nb_sprites > 0u) {
			// Number of sprites that must be rendered.
			auto nb_sprites_to_render = nb_sprites;
			// Number of sprites that can fit in the vertex buffer.
			const auto nb_sprites_available = SpriteBatchMesh::s_max_sprites_per_batch
				                            - m_mesh_position;
			
			if (nb_sprites_to_render > nb_sprites_available) {
				// Not all sprites fit in the vertex buffer.
				if (nb_sprites_available < SpriteBatchMesh::s_min_sprites_per_batch) {
					// Wrap back to the start of the vertex buffer in case of a 
					// excessively small batch.
					m_mesh_position = 0;
					nb_sprites_to_render = std::min(nb_sprites,
						                            SpriteBatchMesh::s_max_sprites_per_batch);
				}
				else {
					nb_sprites_to_render = nb_sprites_available;
				}
			}

			// Update the vertex buffer.
			{
				// Map the vertex buffer.
				const D3D11_MAP map_type = (0 == m_mesh_position)
					                       ? D3D11_MAP_WRITE_DISCARD 
					                       : D3D11_MAP_WRITE_NO_OVERWRITE;
				D3D11_MAPPED_SUBRESOURCE mapped_buffer;
				const auto lock = m_mesh->Lock(m_device_context, map_type, mapped_buffer);

				// Update the data.
				auto vertices = static_cast< VertexPositionColorTexture* >(mapped_buffer.pData)
					+ m_mesh_position * SpriteBatchMesh::s_vertices_per_sprite;
				
				for (size_t i = 0; i < nb_sprites_to_render; ++i) {
					PrepareSprite(*sprites[i], vertices, texture_size, inverse_texture_size);
					vertices += SpriteBatchMesh::s_vertices_per_sprite;
				}
			}

			// Draw the mesh.
			const auto start_index = m_mesh_position
				                   * SpriteBatchMesh::s_indices_per_sprite;
			const auto nb_indices  = nb_sprites_to_render
				                   * SpriteBatchMesh::s_indices_per_sprite;
			m_mesh->Draw(m_device_context, start_index, nb_indices);

			// Update the workload.
			m_mesh_position += nb_sprites_to_render;
			sprites += nb_sprites_to_render;
			nb_sprites -= nb_sprites_to_render;
		}
	}

	void XM_CALLCONV SpriteBatch::Impl
		::PrepareSprite(const SpriteInfo& sprite, 
		                VertexPositionColorTexture* vertices,
		                FXMVECTOR texture_size, 
			            FXMVECTOR inverse_texture_size) noexcept {
		
		auto source                      = XMLoad(sprite.m_source);
		const auto destination           = XMLoad(sprite.m_destination);
		const auto color                 = XMLoad(sprite.m_color);
		const auto origin_rotation_depth = XMLoad(sprite.m_origin_rotation_depth);
		const auto rotation              = sprite.m_origin_rotation_depth.m_z;
		const auto depth                 = sprite.m_origin_rotation_depth.m_w;
		const auto flags                 = sprite.m_flags;
		auto source_size                 = XMVectorSwizzle< 2, 3, 2, 3 >(source);
		auto destination_size            = XMVectorSwizzle< 2, 3, 2, 3 >(destination);
		
		const auto is_0_mask         = XMVectorEqual(source_size, XMVectorZero());
		const auto non_0_source_size = XMVectorSelect(source_size, g_XMEpsilon, is_0_mask);
		auto origin                  = XMVectorDivide(origin_rotation_depth, non_0_source_size);

		if (flags & SpriteInfo::s_source_in_texels) {
			source      *= inverse_texture_size;
			source_size *= inverse_texture_size;
		}
		else {
			origin      *= inverse_texture_size;
		}
		
		if (false == (flags & SpriteInfo::s_destination_size_in_pixels)) {
			// The maximum source region is always required in this case.
			destination_size *= texture_size;
		}


		//---------------------------------------------------------------------
		// Source region    is represented in relative texel coordinates.
		// Origin           is represented in relative texel coordinates.
		// Destination size is represented in absolute pixel coordinates.
		//---------------------------------------------------------------------


		// The four normalized corner offsets needed to compute the position 
		// coordinates and UV coordinates of each vertex.
		// [x y _ _]
		static const XMVECTOR 
			corner_offsets[SpriteBatchMesh::s_vertices_per_sprite] = {
			XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
			XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f),
			XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f),
			XMVectorSet(1.0f, 1.0f, 0.0f, 1.0f)
		};
		

		// UV coordinates to vertex mapping:
		//
		//   None      MirrorX     MirrorY     MirrorXY
		// 00 -- 01    01 -- 00    10 -- 11   11 -- 10
		// |     |     |     |     |     |     |     |
		// 10 -- 11    11 -- 10    00 -- 01    01 -- 00
		//
		//                    XOR Index: 00 01 10 11
		// SpriteEffect::None      00    00 01 10 11
		// SpriteEffect::MirrorX   01    01 00 11 10
		// SpriteEffect::MirrorY   10    10 11 00 01
		// SpriteEffect::MirrorXY  11    11 10 01 00
		static_assert(static_cast< U8 >(SpriteEffect::MirrorX) == 1 && 
			          static_cast< U8 >(SpriteEffect::MirrorY) == 2,
			          "The mirroring implementation must be updated to match");
		// Isolate the mirror bits.
		const U32 mirror_mask = flags & 3u;


		// Rotation:
		// 
		// [x, y] [ cos -sin ] = [x cos + y sin, x (-sin) + y cos]
		//		  [ sin  cos ]
		XMVECTOR rotation_x;
		XMVECTOR rotation_y;
		if (0.0f != rotation) {
			F32 sin, cos;
			XMScalarSinCos(&sin, &cos, rotation);
			// [sin _ _ _]
			const auto sin_v = XMLoad(sin);
			// [cos _ _ _]
			const auto cos_v = XMLoad(cos);
			// [cos -sin _ _]
			rotation_x = XMVectorMergeXY(cos_v, -sin_v);
			// [sin cos _ _]
			rotation_y = XMVectorMergeXY(sin_v, cos_v);
		}
		else {
			// [1 0 _ _]
			rotation_x = g_XMIdentityR0;
			// [0 1 _ _]
			rotation_y = g_XMIdentityR1;
		}


		// Generate the four output vertices.
		for (size_t i = 0; i < SpriteBatchMesh::s_vertices_per_sprite; ++i) {
			// Compute the position coordinates.
			const auto p0 = (corner_offsets[i] - origin) * destination_size;
			const auto p1 = XMVectorMultiplyAdd(XMVectorSplatX(p0), rotation_x, destination);
			const auto p2 = XMVectorMultiplyAdd(XMVectorSplatY(p0), rotation_y, p1);
			const auto position = XMVectorSetZ(p2, depth);

			// Write the position as a F32x4.
			vertices[i].m_p = Point3(XMStore< F32x3 >(position));
			// Write the color.
			vertices[i].m_c = RGBA(XMStore< F32x4 >(color));

			// Compute the texture coordinates.
			const auto uv = XMVectorMultiplyAdd(corner_offsets[i ^ mirror_mask], 
												source_size, source);
			
			// Write the texture coordinates.
			vertices[i].m_tex = UV(XMStore< F32x2 >(uv));
		}
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// SpriteBatch
	//-------------------------------------------------------------------------
	#pragma region

	SpriteBatch::SpriteBatch(ID3D11Device& device,
							 ID3D11DeviceContext& device_context)
		: m_impl(MakeUnique< Impl >(device, device_context)) {}

	SpriteBatch::SpriteBatch(SpriteBatch&& sprite_batch) noexcept = default;

	SpriteBatch::~SpriteBatch() = default;

	SpriteBatch& SpriteBatch
		::operator=(SpriteBatch&& sprite_batch) noexcept = default;

	void SpriteBatch::Begin(SpriteSortMode sort_mode) {
		m_impl->Begin(sort_mode);
	}

	void XM_CALLCONV SpriteBatch::Draw(ID3D11ShaderResourceView* texture,
									   FXMVECTOR color,
									   SpriteEffect effects,
									   const SpriteTransform& transform,
									   const RECT* source) {
		
		m_impl->Draw(texture, color, effects, transform, source);
	}

	void SpriteBatch::End() {
		m_impl->End();
	}

	#pragma endregion
}