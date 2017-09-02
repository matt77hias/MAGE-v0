#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\pass_buffer.hpp"
#include "buffer\constant_buffer.hpp"
#include "buffer\model_buffer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class ConstantShadingPass final {

	public:

		ConstantShadingPass();
		ConstantShadingPass(const ConstantShadingPass &render_pass) = delete;
		ConstantShadingPass(ConstantShadingPass &&render_pass);
		~ConstantShadingPass();

		ConstantShadingPass &operator=(const ConstantShadingPass &render_pass) = delete;
		ConstantShadingPass &operator=(ConstantShadingPass &&render_pass) = delete;

		void Render(const PassBuffer *scene, const CameraNode *node);

	private:

		void XM_CALLCONV BindProjectionData(
			FXMMATRIX view_to_projection) noexcept;
		void XM_CALLCONV BindModelData(
			FXMMATRIX object_to_view, 
			FXMMATRIX view_to_object,
			FXMMATRIX texture_transform) noexcept;
		
		void XM_CALLCONV ProcessModels(
			const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection, 
			FXMMATRIX world_to_view, 
			FXMMATRIX view_to_world) noexcept;

		ID3D11DeviceContext2 * const m_device_context;

		SharedPtr< const VertexShader > m_vs;
		SharedPtr< const PixelShader > m_ps;

		ConstantBuffer< ModelBuffer > m_model_buffer;
		ConstantBuffer< XMMATRIX > m_projection_buffer;
		const SharedPtr< const Texture > m_white;
	};
}
