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

	class WireframePass final {

	public:

		WireframePass();
		WireframePass(const WireframePass &render_pass) = delete;
		WireframePass(WireframePass &&render_pass);
		~WireframePass();

		WireframePass &operator=(const WireframePass &render_pass) = delete;
		WireframePass &operator=(WireframePass &&render_pass) = delete;

		void Render(const PassBuffer *scene, const CameraNode *node);

	private:

		void XM_CALLCONV ProcessScene(
			FXMMATRIX world_to_view, FXMMATRIX view_to_projection);
		void XM_CALLCONV ProcessModels(
			const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection, FXMMATRIX view_to_world);

		ID3D11DeviceContext2 * const m_device_context;
		
		SharedPtr< const VertexShader > m_vs;
		SharedPtr< const PixelShader > m_ps;

		ConstantBuffer< ModelTransformBuffer > m_model_buffer;
		ConstantBuffer< SceneTransformBuffer > m_scene_buffer;
		ConstantBuffer< RGBASpectrum > m_color_buffer;
	};
}