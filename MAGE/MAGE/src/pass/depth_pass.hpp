#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\pass_buffer.hpp"
#include "buffer\constant_buffer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class DepthPass final {

	public:

		DepthPass();
		DepthPass(const DepthPass &render_pass) = delete;
		DepthPass(DepthPass &&render_pass);
		~DepthPass();

		DepthPass &operator=(const DepthPass &render_pass) = delete;
		DepthPass &operator=(DepthPass &&render_pass) = delete;

		void Render(const PassBuffer *scene, const CameraNode *node);
		
	private:

		void XM_CALLCONV BindModelData(
			FXMMATRIX object_to_view) noexcept;
		void XM_CALLCONV BindProjectionData(
			FXMMATRIX view_to_projection) noexcept;

		void XM_CALLCONV ProcessModels(
			const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection,
			FXMMATRIX world_to_view) noexcept;

		ID3D11DeviceContext2 * const m_device_context;

		SharedPtr< const VertexShader > m_vs;

		ConstantBuffer< XMMATRIX > m_projection_buffer;
		ConstantBuffer< XMMATRIX > m_model_buffer;
	};
}