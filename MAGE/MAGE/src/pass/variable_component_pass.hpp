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

	class VariableComponentPass final {

	public:

		VariableComponentPass();
		VariableComponentPass(const VariableComponentPass &render_pass) = delete;
		VariableComponentPass(VariableComponentPass &&render_pass);
		~VariableComponentPass();

		VariableComponentPass &operator=(const VariableComponentPass &render_pass) = delete;
		VariableComponentPass &operator=(VariableComponentPass &&render_pass) = delete;

		void Render(const PassBuffer *scene, const CameraNode *node);

	private:

		void XM_CALLCONV BindModelData(
			FXMMATRIX object_to_view,
			FXMMATRIX view_to_object,
			FXMMATRIX texture_transform,
			const Material *material) noexcept;
		void XM_CALLCONV BindSceneData(
			FXMMATRIX view_to_projection) noexcept;
		
		void XM_CALLCONV ProcessModels(
			const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection, 
			FXMMATRIX world_to_view, 
			FXMMATRIX view_to_world) noexcept;

		ID3D11DeviceContext2 * const m_device_context;
		RenderMode m_render_mode;

		SharedPtr< const VertexShader > m_vs;
		SharedPtr< const PixelShader > m_ps;

		ConstantBuffer< ModelTransformBuffer > m_model_buffer;
		ConstantBuffer< XMMATRIX > m_scene_buffer;
		ConstantBuffer< RGBASpectrum > m_color_buffer;
		const SharedPtr< const Texture > m_white;
	};
}