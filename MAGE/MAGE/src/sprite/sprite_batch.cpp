//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite_batch.hpp"
#include "rendering\state_manager.hpp"

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

	SpriteBatch::SpriteBatch(ID3D11Device *device, 
		                     ID3D11DeviceContext *device_context)
		: m_device_context(device_context),
		m_mesh(MakeUnique< SpriteBatchMesh >(device)),
		m_mesh_position(0u),
		m_in_begin_end_pair(false),
		m_sort_mode(SpriteSortMode::Deferred),
		m_transform(XMMatrixIdentity()),
		m_transform_buffer(device),
		m_sprites(),
		m_sorted_sprites() {

		m_sprites.reserve(s_initial_capacity);
		m_sorted_sprites.reserve(m_sprites.capacity());
	}

	SpriteBatch::SpriteBatch(SpriteBatch &&sprite_batch) noexcept = default;

	SpriteBatch::~SpriteBatch() = default;

	void XM_CALLCONV SpriteBatch::Begin(SpriteSortMode sort_mode, 
		                                FXMMATRIX transform) {
		
		// This SpriteBatch may not already be in a begin/end pair.
		Assert(!m_in_begin_end_pair);

		m_sprites.clear();
		m_sorted_sprites.clear();

		m_sort_mode = sort_mode;
		m_transform = transform;

		if (SpriteSortMode::Immediate == m_sort_mode) {
			BindFixedState();
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

		if (m_sprites.size() == m_sprites.capacity()) {
			m_sprites.reserve(2 * m_sprites.capacity());
			m_sorted_sprites.clear();
			m_sorted_sprites.reserve(m_sprites.capacity());
		}
		
		// Create a sprite.
		auto &sprite = m_sprites.emplace_back();

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

		// Store sprite parameters.
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
			m_sorted_sprites.push_back(&sprite);
		}
	}

	void SpriteBatch::End() {
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

	void SpriteBatch::BindFixedState() {
		if (D3D11_DEVICE_CONTEXT_DEFERRED == m_device_context->GetType()) {
			m_mesh_position = 0;
		}

		m_transform *= GetViewportTransform();

		// Updates the transform (for a complete batch).
		m_transform_buffer.UpdateData(m_device_context, XMMatrixTranspose(m_transform));
		// Bind the transform buffer.
		m_transform_buffer.Bind< Pipeline::VS >(m_device_context, 
			                                    SLOT_CBUFFER_SECONDARY_CAMERA);
		
		// Binds the mesh.
		m_mesh->BindMesh(m_device_context);
	}

	void SpriteBatch::FlushBatch() {
		if (0u == m_sprites.size()) {
			return;
		}
		
		// Sort the sprites of this sprite batch.
		SortSprites();

		// Iterate the sorted sprites of this sprite batch, looking for adjacent 
		// sprites sharing a texture.
		ID3D11ShaderResourceView *batch_texture = nullptr;
		size_t batch_start = 0u;
		for (size_t i = 0; i < m_sprites.size(); ++i) {
			
			auto sprite_texture = m_sorted_sprites[i]->m_texture;
			Assert(sprite_texture);
			
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

	void SpriteBatch::SortSprites() {
		switch (m_sort_mode) {

		case SpriteSortMode::Texture: {
			
			std::sort(m_sorted_sprites.begin(), 
				      m_sorted_sprites.end(), 
				      [](const SpriteInfo *lhs, 
						 const SpriteInfo *rhs) noexcept {
					     return lhs->m_texture < rhs->m_texture;
				      });
			break;
		}
		
		case SpriteSortMode::BackToFront: {
			
			std::sort(m_sorted_sprites.begin(), 
				      m_sorted_sprites.end(), 
				      [](const SpriteInfo *lhs, 
						 const SpriteInfo *rhs) noexcept {
					     return lhs->m_origin_rotation_depth.m_w 
							  > rhs->m_origin_rotation_depth.m_w;
				      });
			break;
		}
		
		case SpriteSortMode::FrontToBack: {
			
			std::sort(m_sorted_sprites.begin(), 
				      m_sorted_sprites.end(), 
				      [](const SpriteInfo *lhs, 
						 const SpriteInfo *rhs) noexcept {
					     return lhs->m_origin_rotation_depth.m_w 
							  < rhs->m_origin_rotation_depth.m_w;
				      });
			break;
		}
		}
	}

	void SpriteBatch::Render(ID3D11ShaderResourceView *texture,
		                     const SpriteInfo * const *sprites, 
		                     size_t nb_sprites) {

		// Binds the texture.
		Pipeline::PS::BindSRV(m_device_context, SLOT_SRV_SPRITE, texture);

		const auto texture_size         = GetTexture2DSize(texture);
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
				const auto lock = m_mesh->Lock(m_device_context, map_type, &mapped_buffer);

				// Update the data.
				auto vertices = static_cast< VertexPositionColorTexture * >(mapped_buffer.pData)
					+ m_mesh_position * SpriteBatchMesh::s_vertices_per_sprite;
				
				for (size_t i = 0; i < nb_sprites_to_render; ++i) {
					PrepareSprite(sprites[i], vertices, texture_size, inverse_texture_size);
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

	void XM_CALLCONV SpriteBatch
		::PrepareSprite(const SpriteInfo *sprite, 
		                VertexPositionColorTexture *vertices,
		                FXMVECTOR texture_size, 
			            FXMVECTOR inverse_texture_size) noexcept {
		
		auto source                      = XMLoad(sprite->m_source);
		const auto destination           = XMLoad(sprite->m_destination);
		const auto color                 = XMLoad(sprite->m_color);
		const auto origin_rotation_depth = XMLoad(sprite->m_origin_rotation_depth);
		const auto rotation              = sprite->m_origin_rotation_depth.m_z;
		const auto depth                 = sprite->m_origin_rotation_depth.m_w;
		const auto flags                 = sprite->m_flags;
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
			vertices[i].m_c = SRGBA(XMStore< F32x4 >(color));

			// Compute the texture coordinates.
			const auto uv = XMVectorMultiplyAdd(corner_offsets[i ^ mirror_mask], source_size, source);
			
			// Write the texture coordinates.
			vertices[i].m_tex = UV(XMStore< F32x2 >(uv));
		}
	}
}