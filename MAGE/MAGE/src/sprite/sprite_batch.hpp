#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "rendering\rendering.hpp"
#include "sprite\sprite_sort_mode.hpp"
#include "sprite\sprite_effects.hpp"
#include "sprite\sprite_transform.hpp"
#include "material\color.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <functional>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class SpriteBatch {

	public:

		SpriteBatch();
		virtual ~SpriteBatch() = default;

		void Begin(SpriteSortMode sort_mode, ID3D11BlendState *blend_state, ID3D11SamplerState *sampler_state,
			ID3D11DepthStencilState *depth_stencil_state, ID3D11RasterizerState *rasterizer_state,
			std::function< void() > SetCustomShaders, XMMATRIX transformMatrix = XMMatrixIdentity());
		void Draw(ID3D11ShaderResourceView *texture, const SpriteTransform &transform,
			XMVECTOR color, SpriteEffects effects, float layer_depth);
		void End();

		void SetRotationMode(DXGI_MODE_ROTATION rotation_mode) {
			m_rotation_mode = rotation_mode;
		}
		DXGI_MODE_ROTATION GetRotationMode() const {
			return m_rotation_mode;
		}
		void SetViewport(const D3D11_VIEWPORT &viewport) {
			m_viewport_dirty = true;
			m_viewport = viewport;
		}
		const D3D11_VIEWPORT &GetViewport() const {
			return m_viewport;
		}

	private:

		SpriteBatch(const SpriteBatch &sprite_batch) = delete;
		SpriteBatch &operator=(const SpriteBatch &sprite_batch) = delete;

		HRESULT InitializeIndexBuffer(ComPtr< ID3D11Device2 > device);
		HRESULT InitializeVertexBuffer(ComPtr< ID3D11Device2 > device);
		HRESULT InitializeShaders(ComPtr< ID3D11Device2 > device);

		/**
		 A pointer to the vertex buffer of this sprite batch.
		 */
		ComPtr< ID3D11Buffer > m_vertex_buffer;

		/**
		 A pointer to the index buffer of this sprite batch.
		 */
		ComPtr< ID3D11Buffer > m_index_buffer;

		/**
		 A flag indicating how the back buffers should be rotated 
		 to fit the physical rotation of a monitor.
		 */
		DXGI_MODE_ROTATION m_rotation_mode;

		/**
		 A flag (dirty bit) indicating whether the viewport of
		 this sprite batch has been set.
		 */
		bool m_viewport_dirty;

		/**
		 The viewport of this sprite batch.
		 */
		D3D11_VIEWPORT m_viewport;
	};
}