//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite_batch.hpp"
#include "sprite\sprite_utils.hpp"
#include "texture\texture_utils.hpp"
#include "rendering\rendering_state_cache.hpp"
#include "logging\error.hpp"

// Include HLSL bindings.
#include "..\..\shaders\hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <algorithm>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpriteBatch::SpriteBatch()
		: SpriteBatch(Pipeline::GetDevice(), Pipeline::GetImmediateDeviceContext()) {}

	SpriteBatch::SpriteBatch(
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context)
		: m_device_context(device_context), 
		m_mesh(MakeUnique< SpriteBatchMesh >(device)), 
		m_vertex_buffer_position(0),
		m_rotation_mode(DXGI_MODE_ROTATION_IDENTITY), m_viewport_set(false), m_viewport{}, 
		m_in_begin_end_pair(false), m_sort_mode(SpriteSortMode::Deferred), 
		m_transform(XMMatrixIdentity()), m_transform_buffer(device),
		m_sprite_queue(), m_sprite_queue_size(0), m_sprite_queue_array_size(0), 
		m_sorted_sprites(), m_sprite_srvs() {}

	SpriteBatch::SpriteBatch(SpriteBatch &&sprite_batch) = default;

	SpriteBatch::~SpriteBatch() = default;

	void XM_CALLCONV SpriteBatch::Begin(
		SpriteSortMode sort_mode, FXMMATRIX transform) {
		
		// This SpriteBatch may not already be in a begin/end pair.
		Assert(!m_in_begin_end_pair);

		m_sort_mode = sort_mode;
		m_transform = transform;

		if (m_sort_mode == SpriteSortMode::Immediate) {
			BindSpriteBatch();
		}

		// Toggle the begin/end pair.
		m_in_begin_end_pair = true;
	}
	
	void XM_CALLCONV SpriteBatch::Draw(ID3D11ShaderResourceView *texture,
		FXMVECTOR color, SpriteEffect effects,
		const SpriteTransform &transform, const RECT *source) {
		
		// This SpriteBatch must already be in a begin/end pair.
		Assert(m_in_begin_end_pair);
		Assert(texture);

		if (m_sprite_queue_size >= m_sprite_queue_array_size) {
			GrowSpriteQueue();
		}
		
		SpriteInfo *sprite = &m_sprite_queue[m_sprite_queue_size];

		unsigned int flags = static_cast< unsigned int >(effects);
		// destination: Tx Ty Sx Sy
		const XMVECTOR destination = XMVectorSet(
										transform.GetTranslation().x,
										transform.GetTranslation().y,
										transform.GetScale().x,
										transform.GetScale().y);
		// origin_rotation_depth: ROx ROy R D
		const XMVECTOR origin_rotation_depth = XMVectorSet(
										transform.GetRotationOrigin().x, 
										transform.GetRotationOrigin().y, 
										transform.GetRotation(), 
										transform.GetDepth());
		
		XMVECTOR dst = destination;
		if (source) {
			const XMVECTOR src = XMVectorLeftTopWidthHeight(*source);
			XMStoreFloat4A(&sprite->m_source, src);

			// If the destination size is relative to the source region, convert it to pixels.
			if (!(flags & SpriteInfo::destination_size_in_pixels)) {
				dst = XMVectorPermute< 0, 1, 6, 7 >(dst, dst * src);
			}

			flags |= SpriteInfo::source_in_texels | SpriteInfo::destination_size_in_pixels;
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

		if (m_sort_mode == SpriteSortMode::Immediate) {
			RenderBatch(texture, &sprite, 1);
		}
		else {
			// Queue this sprite for later sorting and batched rendering.
			++m_sprite_queue_size;

			// Make sure a refcount is hold on this texture until the sprite has been drawn. 
			// Only checking the back of the vector means duplicate references will be added 
			// if the caller switches back and forth between multiple repeated textures, 
			// but calling AddRef more times than strictly necessary hurts nothing, 
			// and is faster than scanning the whole list or using a map to detect all duplicates.
			if (m_sprite_srvs.empty() || texture != m_sprite_srvs.back().Get()) {
				m_sprite_srvs.emplace_back(texture);
			}
		}
	}

	void SpriteBatch::End() {
		
		// This SpriteBatch must already be in a begin/end pair.
		Assert(m_in_begin_end_pair);

		if (m_sort_mode != SpriteSortMode::Immediate) {
			// Draw the queued sprites.
			BindSpriteBatch();
			FlushBatch();
		}

		// Untoggle the begin/end pair.
		m_in_begin_end_pair = false;
	}

	void SpriteBatch::GrowSpriteQueue() {
		const size_t sprite_queue_array_size = 
			std::max(SpriteBatch::s_initial_queue_size, m_sprite_queue_array_size * 2);
		UniquePtr< SpriteInfo[] > sprite_queue(MakeUnique< SpriteInfo[] >(sprite_queue_array_size));
		
		for (size_t i = 0; i < m_sprite_queue_size; ++i) {
			sprite_queue[i] = m_sprite_queue[i];
		}
		
		m_sprite_queue = std::move(sprite_queue);
		m_sprite_queue_array_size = sprite_queue_array_size;

		// Clear any dangling SpriteInfo pointers left over from previous rendering.
		m_sorted_sprites.clear();
	}

	void SpriteBatch::BindSpriteBatch() {
		if (m_device_context->GetType() == D3D11_DEVICE_CONTEXT_DEFERRED) {
			m_vertex_buffer_position = 0;
		}

		// Apply the rotation mode to the transform of this sprite batch.
		if (m_rotation_mode != DXGI_MODE_ROTATION_UNSPECIFIED) {
			if (m_viewport_set) {
				m_transform *= GetViewportTransform(m_viewport, m_rotation_mode);
			}
			else {
				m_transform *= GetViewportTransform(m_device_context, m_rotation_mode);
			}
		}

		// Updates the transform (for a complete batch).
		m_transform_buffer.UpdateData(m_device_context, 
			XMMatrixTranspose(m_transform));
		// Bind the transform buffer.
		m_transform_buffer.Bind< Pipeline::VS >(
			m_device_context, SLOT_CBUFFER_PER_FRAME);
		// Binds the mesh.
		m_mesh->BindMesh(m_device_context);
	}

	void SpriteBatch::FlushBatch() {
		if (m_sprite_queue_size == 0) {
			return;
		}
		
		// Sort the sprites of this sprite batch.
		SortSprites();

		// Walk the sorted sprites of this sprite batch,
		// looking for adjacent sprites sharing a texture.
		ID3D11ShaderResourceView *batch_texture = nullptr;
		size_t batch_start = 0;
		for (size_t i = 0; i < m_sprite_queue_size; ++i) {
			ID3D11ShaderResourceView *sprite_texture = m_sorted_sprites[i]->m_texture;
			Assert(sprite_texture);
			if (sprite_texture != batch_texture) {
				if (i > batch_start) {
					// Flush the current subbatch.
					const size_t nb_sprites = i - batch_start;
					RenderBatch(batch_texture, &m_sorted_sprites[batch_start], nb_sprites);
				}
				batch_texture = sprite_texture;
				batch_start   = i;
			}
		}
		// Flush the final subbatch.
		const size_t nb_sprites = m_sprite_queue_size - batch_start;
		RenderBatch(batch_texture, &m_sorted_sprites[batch_start], nb_sprites);

		// Reset the sprite queue.
		m_sprite_queue_size = 0;
		m_sprite_srvs.clear();

		// We always re-sort the original ordering.
		if (m_sort_mode != SpriteSortMode::Deferred) {
			m_sorted_sprites.clear();
		}
	}

	void SpriteBatch::SortSprites() {
		if (m_sorted_sprites.size() < m_sprite_queue_size) {
			GrowSortedSprites();
		}

		switch (m_sort_mode) {

		case SpriteSortMode::Texture: {
			std::sort(m_sorted_sprites.begin(), m_sorted_sprites.begin() + m_sprite_queue_size, 
				[](const SpriteInfo *lhs, const SpriteInfo *rhs) -> bool {
				return lhs->m_texture < rhs->m_texture;
			});
			break;
		}
		case SpriteSortMode::BackToFront: {
			std::sort(m_sorted_sprites.begin(), m_sorted_sprites.begin() + m_sprite_queue_size, 
				[](const SpriteInfo *lhs, const SpriteInfo *rhs) -> bool {
				return lhs->m_origin_rotation_depth.w > rhs->m_origin_rotation_depth.w;
			});
			break;
		}
		case SpriteSortMode::FrontToBack: {
			std::sort(m_sorted_sprites.begin(), m_sorted_sprites.begin() + m_sprite_queue_size, 
				[](const SpriteInfo *lhs, const SpriteInfo *rhs) -> bool {
				return lhs->m_origin_rotation_depth.w < rhs->m_origin_rotation_depth.w;
			});
			break;
		}
		}
	}

	void SpriteBatch::GrowSortedSprites() {
		// Retrieve the old size of the sorted sprites collection.
		const size_t old_size = m_sorted_sprites.size();
		// Resize the sorted sprites collection.
		m_sorted_sprites.resize(m_sprite_queue_size);
		// Transfer the remaining sprites. 
		for (size_t i = old_size; i < m_sprite_queue_size; ++i) {
			m_sorted_sprites[i] = &m_sprite_queue[i];
		}
	}

	void SpriteBatch::RenderBatch(ID3D11ShaderResourceView *texture,
		const SpriteInfo * const *sprites, size_t nb_sprites) {

		// Binds the texture.
		Pipeline::PS::BindSRV(m_device_context, 
			SLOT_SRV_SPRITE, texture);

		const XMVECTOR texture_size = GetTexture2DSize(texture);
		const XMVECTOR inverse_texture_size = XMVectorReciprocal(texture_size);

		while (nb_sprites > 0) {
			// Number of sprites that must be rendered.
			size_t nb_sprites_to_render = nb_sprites;
			// Number of sprites that can fit in the vertex buffer.
			const size_t nb_sprites_available = SpriteBatchMesh::s_max_sprites_per_batch - m_vertex_buffer_position;
			if (nb_sprites_to_render > nb_sprites_available) {
				// Not all sprites fit in the vertex buffer.
				if (nb_sprites_available < SpriteBatchMesh::s_min_sprites_per_batch) {
					// Wrap back to the start of the vertex buffer in case of a excessively small batch.
					m_vertex_buffer_position = 0;
					nb_sprites_to_render = std::min(nb_sprites, SpriteBatchMesh::s_max_sprites_per_batch);
				}
				else {
					nb_sprites_to_render = nb_sprites_available;
				}
			}
				
			// Map vertex buffer
			const D3D11_MAP map_type = (m_vertex_buffer_position == 0) 
				? D3D11_MAP_WRITE_DISCARD : D3D11_MAP_WRITE_NO_OVERWRITE;
			D3D11_MAPPED_SUBRESOURCE mapped_buffer;
			const HRESULT result_map = m_mesh->MapVertexBuffer(m_device_context, map_type, &mapped_buffer);
			if (FAILED(result_map)) {
				Error("Vertex buffer mapping failed: %08X.", result_map);
				return;
			}

			// Update vertex buffer
			VertexPositionColorTexture *vertices = 
				static_cast< VertexPositionColorTexture * >(mapped_buffer.pData) 
				+ m_vertex_buffer_position * SpriteBatchMesh::s_vertices_per_sprite;
			for (size_t i = 0; i < nb_sprites_to_render; ++i) {
				PrepareSprite(sprites[i], vertices, texture_size, inverse_texture_size);
				vertices += SpriteBatchMesh::s_vertices_per_sprite;
			}
			
			// Unmap vertex buffer
			m_mesh->UnmapVertexBuffer(m_device_context);

			// Draw mesh
			const size_t start_index = m_vertex_buffer_position * SpriteBatchMesh::s_indices_per_sprite;
			const size_t nb_indices  = nb_sprites_to_render * SpriteBatchMesh::s_indices_per_sprite;
			m_mesh->Draw(m_device_context, start_index, nb_indices);

			// Update workload
			m_vertex_buffer_position += nb_sprites_to_render;
			sprites += nb_sprites_to_render;
			nb_sprites -= nb_sprites_to_render;
		}
	}

	void XM_CALLCONV SpriteBatch::PrepareSprite(
		const SpriteInfo *sprite, VertexPositionColorTexture *vertices,
		FXMVECTOR texture_size, FXMVECTOR inverse_texture_size) noexcept {
		
		XMVECTOR source                      = XMLoadFloat4A(&sprite->m_source);
		const XMVECTOR destination           = XMLoadFloat4A(&sprite->m_destination);
		const XMVECTOR color                 = XMLoadFloat4A(&sprite->m_color);
		const XMVECTOR origin_rotation_depth = XMLoadFloat4A(&sprite->m_origin_rotation_depth);
		const float rotation                 = sprite->m_origin_rotation_depth.z;
		const int flags                      = sprite->m_flags;
		XMVECTOR source_size                 = XMVectorSwizzle< 2, 3, 2, 3 >(source);
		XMVECTOR destination_size            = XMVectorSwizzle< 2, 3, 2, 3 >(destination);

		// Scale the origin offset by source size, 
		// taking care to avoid overflow if the source region is zero
		const XMVECTOR is_zero_mask          = XMVectorEqual(source_size, XMVectorZero());
		const XMVECTOR non_zero_source_size  = XMVectorSelect(source_size, g_XMEpsilon, is_zero_mask);
		XMVECTOR origin                      = XMVectorDivide(origin_rotation_depth, non_zero_source_size);

		// Convert the source region from texels to mod-1 texture coordinate format.
		if (flags & SpriteInfo::source_in_texels) {
			source      *= inverse_texture_size;
			source_size *= inverse_texture_size;
		}
		else {
			origin      *= inverse_texture_size;
		}
		// If the destination size is relative to the source region, convert it to pixels.
		if (!(flags & SpriteInfo::destination_size_in_pixels)) {
			destination_size *= texture_size;
		}

		// Compute a 2x2 rotation matrix.
		XMVECTOR rotation_matrix1;
		XMVECTOR rotation_matrix2;
		if (rotation != 0) {
			float sin, cos;
			XMScalarSinCos(&sin, &cos, rotation);
			const XMVECTOR sin_v = XMLoadFloat(&sin);
			const XMVECTOR cos_v = XMLoadFloat(&cos);
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

		// Texture coordinates are computed from the same corner_offsets
		// table as vertex positions, but if the sprite is mirrored, this table
		// must be indexed in a different order. This is done as follows:
		//
		//    position = cornerOffsets[i]
		//    texcoord = cornerOffsets[i ^ SpriteEffect]

		static_assert(
			static_cast< unsigned int >(SpriteEffect::FlipHorizontally) == 1u && 
			static_cast< unsigned int >(SpriteEffect::FlipVertically)   == 2u,
			"The mirroring implementation must be updated to match");

		const int mirror_bits = flags & 3;

		// Generate the four output vertices.
		for (size_t i = 0; i < SpriteBatchMesh::s_vertices_per_sprite; ++i) {
			// Calculate position.
			const XMVECTOR corner_offset = (corner_offsets[i] - origin) * destination_size;
			// Apply 2x2 rotation matrix.
			const XMVECTOR position1 = XMVectorMultiplyAdd(XMVectorSplatX(corner_offset), rotation_matrix1, destination);
			const XMVECTOR position2 = XMVectorMultiplyAdd(XMVectorSplatY(corner_offset), rotation_matrix2, position1);
			// Set z = depth.
			const XMVECTOR position = XMVectorPermute< 0, 1, 7, 6 >(position2, origin_rotation_depth);

			// Write the position as a XMFLOAT4, even though VertexPositionColorTexture::p is an XMFLOAT3.
			// This is faster, and harmless as we are just clobbering the first element of the
			// following color field, which will immediately be overwritten with its correct value.
			XMStoreFloat4(reinterpret_cast< XMFLOAT4 * >(&vertices[i].p), position);

			// Write the color.
			XMStoreFloat4(&vertices[i].c, color);

			// Compute and write the texture coordinate.
			const XMVECTOR texture_coordinate = XMVectorMultiplyAdd(corner_offsets[i ^ mirror_bits], source_size, source);
			XMStoreFloat2(&vertices[i].tex, texture_coordinate);
		}
	}
}