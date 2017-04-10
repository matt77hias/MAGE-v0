#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\allocation.hpp"
#include "math\sprite_transform.hpp"
#include "mesh\sprite_batch_mesh.hpp"
#include "mesh\vertex.hpp"
#include "shader\shader.hpp"
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

	__declspec(align(16)) struct SpriteInfo : public AlignedData< SpriteInfo > {
		
		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------
		
		// Combine values from SpriteEffect with these internal-only flags.
		static const int source_in_texels = 4;
		static const int destination_size_in_pixels = 8;

		static_assert((SpriteEffect_FlipBoth & (source_in_texels | destination_size_in_pixels)) == 0, 
			"Flag bits must not overlap");
		
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		XMFLOAT4A source;
		XMFLOAT4A destination;
		XMFLOAT4A color;
		XMFLOAT4A origin_rotation_depth;
		ID3D11ShaderResourceView *texture;
		int flags;
	};

	class SpriteBatch {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		SpriteBatch(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const CombinedShader &shader = CreateSpriteShader());
		SpriteBatch(const SpriteBatch &sprite_batch) = delete;
		SpriteBatch(SpriteBatch &&sprite_batch) = default;
		virtual ~SpriteBatch() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		SpriteBatch &operator=(const SpriteBatch &sprite_batch) = delete;
		SpriteBatch &operator=(SpriteBatch &&sprite_batch) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void Begin(SpriteSortMode sort_mode = SpriteSortMode_Deferred, XMMATRIX transform = XMMatrixIdentity());
		void Draw(ID3D11ShaderResourceView *texture, const XMVECTOR &color, SpriteEffect effects,
			const SpriteTransform &transform, const RECT *source = nullptr);
		void End();

		void SetRotationMode(DXGI_MODE_ROTATION rotation_mode) {
			m_rotation_mode = rotation_mode;
		}
		DXGI_MODE_ROTATION GetRotationMode() const {
			return m_rotation_mode;
		}
		void SetViewport(const D3D11_VIEWPORT &viewport) {
			m_viewport_set = true;
			m_viewport = viewport;
		}
		const D3D11_VIEWPORT &GetViewport() const {
			return m_viewport;
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void GrowSpriteQueue();
		void PrepareDrawing();
		void FlushBatch();
		void SortSprites();
		void GrowSortedSprites();
		void RenderBatch(ID3D11ShaderResourceView *texture,
			const SpriteInfo * const * sprites, size_t nb_sprites);
		void RenderSprite(const SpriteInfo *sprite, VertexPositionColorTexture *vertices,
			const XMVECTOR &texture_size, const XMVECTOR &inverse_texture_size);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		ID3D11Device2 * const m_device;
		ID3D11DeviceContext2 * const m_device_context;
		UniquePtr< SpriteBatchMesh > m_mesh;
		size_t m_vertex_buffer_position;
		UniquePtr< CombinedShader > m_shader;

		/**
		 A flag indicating how the back buffers should be rotated
		 to fit the physical rotation of a monitor.
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

		bool m_in_begin_end_pair;
		SpriteSortMode m_sort_mode;
		XMMATRIX m_transform;

		// Queue of sprites waiting to be drawn.
		UniquePtr< SpriteInfo[] > m_sprite_queue;
		size_t m_sprite_queue_size;
		size_t m_sprite_queue_array_size;
		vector< const SpriteInfo * > m_sorted_sprites;
		vector< ComPtr< ID3D11ShaderResourceView > > m_sprite_texture_references;

		static const size_t initial_queue_size = 64;
	};

	SharedPtr< SpriteBatch > CreateSpriteBatch();
}