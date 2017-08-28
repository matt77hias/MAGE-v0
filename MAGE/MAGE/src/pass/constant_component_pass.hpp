#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\pass_buffer.hpp"
#include "buffer\scene_buffer.hpp"
#include "buffer\model_buffer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class ConstantComponentPass final {

	public:

		ConstantComponentPass();
		ConstantComponentPass(const ConstantComponentPass &render_pass) = delete;
		ConstantComponentPass(ConstantComponentPass &&render_pass);
		~ConstantComponentPass();

		ConstantComponentPass &operator=(const ConstantComponentPass &render_pass) = delete;
		ConstantComponentPass &operator=(ConstantComponentPass &&render_pass) = delete;

		void Render(const PassBuffer *scene, const CameraNode *node);

	private:

		enum struct PSIndex {
			UVTexture = 0,
			Distance  = 1,
			Count     = 2
		};

		void BindPS(RenderMode render_mode) noexcept;

		void XM_CALLCONV ProcessScene(
			FXMMATRIX world_to_view, FXMMATRIX view_to_projection);
		void XM_CALLCONV ProcessModels(
			const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection, FXMMATRIX view_to_world);

		ID3D11DeviceContext2 * const m_device_context;
		
		SharedPtr< const VertexShader > m_vs;
		SharedPtr< const PixelShader > m_ps[static_cast< size_t >(PSIndex::Count)];

		ConstantBuffer< ModelTransformBuffer > m_model_buffer;
		ConstantBuffer< SceneTransformBuffer > m_scene_buffer;
		ConstantBuffer< RGBASpectrum > m_color_buffer;
		const SharedPtr< const Texture > m_uv;
	};
}