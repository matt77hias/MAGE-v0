//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite_batch.hpp"
#include "texture\texture_utils.hpp"
#include "rendering\rendering_state_manager.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpriteBatch::SpriteBatch()
		: SpriteBatch(Pipeline::GetDevice(), 
			          Pipeline::GetImmediateDeviceContext()) {}

	SpriteBatch::SpriteBatch(ID3D11Device5 *device, 
		                     ID3D11DeviceContext4 *device_context)
		: m_device_context(device_context),
		m_mesh(MakeUnique< SpriteBatchMesh >(device)),
		m_vertex_buffer_position(0u),
		m_rotation_mode(DXGI_MODE_ROTATION_IDENTITY),
		m_viewport_set(false),
		m_viewport{},
		m_in_begin_end_pair(false),
		m_sort_mode(SpriteSortMode::Deferred),
		m_transform(XMMatrixIdentity()),
		m_transform_buffer(device),
		m_sprites(),
		m_nb_sprites(0u),
		m_nb_sprites_max(0u),
		m_sorted_sprites() {}

	SpriteBatch::SpriteBatch(SpriteBatch &&sprite_batch) noexcept = default;

	SpriteBatch::~SpriteBatch() = default;

	void XM_CALLCONV SpriteBatch::Begin(SpriteSortMode sort_mode, 
		                                FXMMATRIX transform) {
		
		// This SpriteBatch may not already be in a begin/end pair.
		Assert(!m_in_begin_end_pair);

		m_sort_mode = sort_mode;
		m_transform = transform;

		if (SpriteSortMode::Immediate == m_sort_mode) {
			BindSpriteBatch();
		}

		// Toggle the begin/end pair.
		m_in_begin_end_pair = true;
	}
	
	void XM_CALLCONV SpriteBatch::Draw(ID3D11ShaderResourceView *texture,
		                               FXMVECTOR color,
		                               SpriteEffect effects,
		                               const SpriteTransform &transform, 
		                               const RECT *source) {
		
		// This SpriteBatch must already be in a begin/end pair.
		Assert(m_in_begin_end_pair);
		Assert(texture);

		if (m_nb_sprites >= m_nb_sprites_max) {
			GrowSpriteQueue();
		}
		
		auto sprite = &m_sprites[m_nb_sprites];

		auto flags = static_cast< U32 >(effects);
		// destination: Tx Ty Sx Sy
		const auto destination = XMVectorSet(transform.GetTranslation().m_x,
										     transform.GetTranslation().m_y,
										     transform.GetScale().m_x,
										     transform.GetScale().m_y);
		// origin_rotation_depth: ROx ROy R D
		const auto origin_rotation_depth = XMVectorSet(transform.GetRotationOrigin().m_x, 
										               transform.GetRotationOrigin().m_y, 
										               transform.GetRotation(), 
										               transform.GetDepth());

		auto dst = destination;
		if (source) {
			const auto src = XMVectorLeftTopWidthHeight(*source);
			XMStoreFloat4A(&sprite->m_source, src);

			// If the destination size is relative to the source region, 
			// convert it to pixels.
			if (!(flags & SpriteInfo::s_destination_size_in_pixels)) {
				dst = XMVectorPermute< 0, 1, 6, 7 >(dst, dst * src);
			}

			flags |= SpriteInfo::s_source_in_texels 
				   | SpriteInfo::s_destination_size_in_pixels;
		}
		else {
			// No explicit source region, so use the entire texture.
			static const XMVECTORF32 max_texture_region = { 0, 0, 1, 1 };
			XMStoreFloat4A(&sprite->m_source, max_texture_region);
		}

		// Store sprite parameters.
		XMStoreFloat4A(&sprite->m_destination, dst);
		XMStoreFloat4A(&sprite->m_color, color);
		XMStoreFloat4A(&sprite->m_origin_rotation_depth, origin_rotation_depth);
		sprite->m_texture = texture;
		sprite->m_flags = flags;

		if (SpriteSortMode::Immediate == m_sort_mode) {
			RenderBatch(texture, &sprite, 1);
		}
		else {
			// Queue this sprite for later sorting and batched rendering.
			++m_nb_sprites;
		}
	}

	void SpriteBatch::End() {
		// This SpriteBatch must already be in a begin/end pair.
		Assert(m_in_begin_end_pair);

		if (SpriteSortMode::Immediate != m_sort_mode) {
			// Draw the queued sprites.
			BindSpriteBatch();
			FlushBatch();
		}

		// Untoggle the begin/end pair.
		m_in_begin_end_pair = false;
	}

	void SpriteBatch::GrowSpriteQueue() {
		m_nb_sprites_max = std::max(SpriteBatch::s_initial_queue_size,
			                        2 * m_nb_sprites_max);
		
		auto sprites = MakeUnique< SpriteInfo[] >(m_nb_sprites_max);
		for (size_t i = 0; i < m_nb_sprites; ++i) {
			sprites[i] = m_sprites[i];
		}
		m_sprites = std::move(sprites);

		// Clear any dangling SpriteInfo pointers left over from previous rendering.
		m_sorted_sprites.clear();
	}

	void SpriteBatch::BindSpriteBatch() {
		if (D3D11_DEVICE_CONTEXT_DEFERRED == m_device_context->GetType()) {
			m_vertex_buffer_position = 0;
		}

		// Apply the rotation mode to the transform of this sprite batch.
		if (DXGI_MODE_ROTATION_UNSPECIFIED != m_rotation_mode) {
			if (m_viewport_set) {
				m_transform *= GetViewportTransform(m_viewport, m_rotation_mode);
			}
			else {
				m_transform *= GetViewportTransform(m_device_context, m_rotation_mode);
			}
		}

		// Updates the transform (for a complete batch).
		m_transform_buffer.UpdateData(m_device_context, XMMatrixTranspose(m_transform));
		// Bind the transform buffer.
		m_transform_buffer.Bind< Pipeline::VS >(m_device_context, 
			SLOT_CBUFFER_SECONDARY_CAMERA);
		// Binds the mesh.
		m_mesh->BindMesh(m_device_context);
	}

	void SpriteBatch::FlushBatch() {
		if (0u == m_nb_sprites) {
			return;
		}
		
		// Sort the sprites of this sprite batch.
		SortSprites();

		// Walk the sorted sprites of this sprite batch, looking for adjacent 
		// sprites sharing a texture.
		ID3D11ShaderResourceView *batch_texture = nullptr;
		size_t batch_start = 0u;
		for (size_t i = 0; i < m_nb_sprites; ++i) {
			
			auto sprite_texture = m_sorted_sprites[i]->m_texture;
			Assert(sprite_texture);
			
			if (sprite_texture != batch_texture) {
				
				if (i > batch_start) {
					// Flush the current subbatch.
					const auto nb_sprites_batch = i - batch_start;
					RenderBatch(batch_texture, &m_sorted_sprites[batch_start], nb_sprites_batch);
				}
				
				batch_texture = sprite_texture;
				batch_start   = i;
			}
		}
		// Flush the final subbatch.
		const auto nb_sprites_batch = m_nb_sprites - batch_start;
		RenderBatch(batch_texture, &m_sorted_sprites[batch_start], nb_sprites_batch);

		// Reset the sprite queue.
		m_nb_sprites = 0;

		// The original ordering will always be re-sorted.
		if (SpriteSortMode::Deferred != m_sort_mode) {
			m_sorted_sprites.clear();
		}
	}

	void SpriteBatch::SortSprites() {
		if (m_sorted_sprites.size() < m_nb_sprites) {
			GrowSortedSprites();
		}

		switch (m_sort_mode) {

		case SpriteSortMode::Texture: {
			
			std::sort(m_sorted_sprites.begin(), 
				      m_sorted_sprites.begin() + m_nb_sprites, 
				      [](const SpriteInfo *lhs, 
						 const SpriteInfo *rhs) noexcept -> bool {
					     return lhs->m_texture < rhs->m_texture;
				      });
			break;
		}
		
		case SpriteSortMode::BackToFront: {
			
			std::sort(m_sorted_sprites.begin(), 
				      m_sorted_sprites.begin() + m_nb_sprites, 
				      [](const SpriteInfo *lhs, 
						 const SpriteInfo *rhs) noexcept -> bool {
					     return lhs->m_origin_rotation_depth.m_w 
							  > rhs->m_origin_rotation_depth.m_w;
				      });
			break;
		}
		
		case SpriteSortMode::FrontToBack: {
			
			std::sort(m_sorted_sprites.begin(), 
				      m_sorted_sprites.begin() + m_nb_sprites, 
				      [](const SpriteInfo *lhs, 
						 const SpriteInfo *rhs) noexcept -> bool {
					     return lhs->m_origin_rotation_depth.m_w 
							  < rhs->m_origin_rotation_depth.m_w;
				      });
			break;
		}
		}
	}

	void SpriteBatch::GrowSortedSprites() {
		// Retrieve the old size of the sorted sprites collection.
		const auto old_size = m_sorted_sprites.size();
		// Resize the sorted sprites collection.
		m_sorted_sprites.resize(m_nb_sprites);
		// Transfer the remaining sprites. 
		for (auto i = old_size; i < m_nb_sprites; ++i) {
			m_sorted_sprites[i] = &m_sprites[i];
		}
	}

	void SpriteBatch::RenderBatch(ID3D11ShaderResourceView *texture,
		                          const SpriteInfo * const *sprites, 
		                          size_t nb_sprites) {

		// Binds the texture.
		Pipeline::PS::BindSRV(m_device_context, SLOT_SRV_SPRITE, texture);

		const auto texture_size = GetTexture2DSize(texture);
		const auto inverse_texture_size = XMVectorReciprocal(texture_size);

		while (nb_sprites > 0u) {
			// Number of sprites that must be rendered.
			auto nb_sprites_to_render = nb_sprites;
			// Number of sprites that can fit in the vertex buffer.
			const auto nb_sprites_available = SpriteBatchMesh::s_max_sprites_per_batch
				                            - m_vertex_buffer_position;
			if (nb_sprites_to_render > nb_sprites_available) {
				// Not all sprites fit in the vertex buffer.
				if (nb_sprites_available < SpriteBatchMesh::s_min_sprites_per_batch) {
					// Wrap back to the start of the vertex buffer in case of a excessively small batch.
					m_vertex_buffer_position = 0;
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
				const D3D11_MAP map_type = (0 == m_vertex_buffer_position)
					                       ? D3D11_MAP_WRITE_DISCARD 
					                       : D3D11_MAP_WRITE_NO_OVERWRITE;
				D3D11_MAPPED_SUBRESOURCE mapped_buffer;
				const auto lock = m_mesh->Lock(m_device_context,
					                           map_type, &mapped_buffer);

				// Update the data.
				auto vertices = static_cast< VertexPositionColorTexture * >(mapped_buffer.pData)
					+ m_vertex_buffer_position * SpriteBatchMesh::s_vertices_per_sprite;
				for (size_t i = 0; i < nb_sprites_to_render; ++i) {
					PrepareSprite(sprites[i], vertices, texture_size, inverse_texture_size);
					vertices += SpriteBatchMesh::s_vertices_per_sprite;
				}
			}

			// Draw the mesh.
			const auto start_index = m_vertex_buffer_position
				                   * SpriteBatchMesh::s_indices_per_sprite;
			const auto nb_indices  = nb_sprites_to_render
				                   * SpriteBatchMesh::s_indices_per_sprite;
			m_mesh->Draw(m_device_context, start_index, nb_indices);

			// Update the workload.
			m_vertex_buffer_position += nb_sprites_to_render;
			sprites += nb_sprites_to_render;
			nb_sprites -= nb_sprites_to_render;
		}
	}

	void XM_CALLCONV SpriteBatch
		::PrepareSprite(const SpriteInfo *sprite, 
		                VertexPositionColorTexture *vertices,
		                FXMVECTOR texture_size, 
			            FXMVECTOR inverse_texture_size) noexcept {
		
		auto source                      = XMLoadFloat4A(&sprite->m_source);
		const auto destination           = XMLoadFloat4A(&sprite->m_destination);
		const auto color                 = XMLoadFloat4A(&sprite->m_color);
		const auto origin_rotation_depth = XMLoadFloat4A(&sprite->m_origin_rotation_depth);
		const auto rotation              = sprite->m_origin_rotation_depth.m_z;
		const auto flags                 = sprite->m_flags;
		auto source_size                 = XMVectorSwizzle< 2, 3, 2, 3 >(source);
		auto destination_size            = XMVectorSwizzle< 2, 3, 2, 3 >(destination);
		
		// Scale the origin offset by source size, taking care to avoid overflow if 
		// the source region is zero
		const auto is_zero_mask          = XMVectorEqual(source_size, XMVectorZero());
		const auto non_zero_source_size  = XMVectorSelect(source_size, g_XMEpsilon, is_zero_mask);
		auto origin                      = XMVectorDivide(origin_rotation_depth, non_zero_source_size);

		// Convert the source region from texels to mod-1 texture coordinate format.
		if (flags & SpriteInfo::s_source_in_texels) {
			source      *= inverse_texture_size;
			source_size *= inverse_texture_size;
		}
		else {
			origin      *= inverse_texture_size;
		}
		// If the destination size is relative to the source region, convert it to pixels.
		if (!(flags & SpriteInfo::s_destination_size_in_pixels)) {
			destination_size *= texture_size;
		}

		// Compute a 2x2 rotation matrix.
		XMVECTOR rotation_matrix1;
		XMVECTOR rotation_matrix2;
		if (0.0f != rotation) {
			F32 sin, cos;
			XMScalarSinCos(&sin, &cos, rotation);
			const auto sin_v = XMLoadFloat(&sin);
			const auto cos_v = XMLoadFloat(&cos);
			rotation_matrix1     = XMVectorMergeXY( cos_v, sin_v);
			rotation_matrix2     = XMVectorMergeXY(-sin_v, cos_v);
		}
		else {
			rotation_matrix1     = g_XMIdentityR0;
			rotation_matrix2     = g_XMIdentityR1;
		}
		
		// The four corner vertices are computed by transforming these unit-square positions.
		static XMVECTORF32 corner_offsets[SpriteBatchMesh::s_vertices_per_sprite] = {
			{ 0, 0 },
			{ 1, 0 },
			{ 0, 1 },
			{ 1, 1 },
		};
		
		// Texture coordinates are computed from the same corner_offsets table as 
		// vertex positions, but if the sprite is mirrored, this table must be indexed 
		// in a different order. This is done as follows:
		//
		//    position = cornerOffsets[i]
		//    texcoord = cornerOffsets[i ^ SpriteEffect]

		static_assert(
			static_cast< U32 >(SpriteEffect::FlipHorizontally) == 1u && 
			static_cast< U32 >(SpriteEffect::FlipVertically)   == 2u,
			"The mirroring implementation must be updated to match");

		const U32 mirror_bits = flags & 3;

		// Generate the four output vertices.
		for (size_t i = 0; i < SpriteBatchMesh::s_vertices_per_sprite; ++i) {
			// Calculate position.
			const auto corner_offset
				= (corner_offsets[i] - origin) * destination_size;
			// Apply 2x2 rotation matrix.
			const auto position1
				= XMVectorMultiplyAdd(XMVectorSplatX(corner_offset), rotation_matrix1, destination);
			const auto position2
				= XMVectorMultiplyAdd(XMVectorSplatY(corner_offset), rotation_matrix2, position1);
			// Set z = depth.
			const auto position
				= XMVectorPermute< 0, 1, 7, 6 >(position2, origin_rotation_depth);
			// Write the position as a F32x4, even though VertexPositionColorTexture::p 
			// is an F32x3. This is faster, and harmless as we are just clobbering the 
			// first element of the following color field, which will immediately be 
			// overwritten with its correct value.
			XMStoreFloat4(reinterpret_cast< F32x4 * >(&vertices[i].m_p), position);

			// Write the color.
			XMStoreFloat4(&vertices[i].m_c, color);

			// Compute and write the texture coordinate.
			const auto texture_coordinate
				= XMVectorMultiplyAdd(corner_offsets[i ^ mirror_bits], source_size, source);
			XMStoreFloat2(&vertices[i].m_tex, texture_coordinate);
		}
	}
}