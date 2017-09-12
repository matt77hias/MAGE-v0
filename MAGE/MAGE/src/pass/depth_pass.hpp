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

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		DepthPass();
		DepthPass(const DepthPass &render_pass) = delete;
		DepthPass(DepthPass &&render_pass);
		~DepthPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		DepthPass &operator=(const DepthPass &render_pass) = delete;
		DepthPass &operator=(DepthPass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------
		
		void BindFixedState();

		void XM_CALLCONV Render(
			const PassBuffer *scene,
			FXMMATRIX world_to_projection,
			CXMMATRIX world_to_view,
			CXMMATRIX view_to_projection);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void XM_CALLCONV BindModelData(
			FXMMATRIX object_to_view);
		
		void XM_CALLCONV BindProjectionData(
			FXMMATRIX view_to_projection);

		void XM_CALLCONV ProcessModels(
			const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection,
			CXMMATRIX world_to_view);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		ID3D11DeviceContext2 * const m_device_context;

		SharedPtr< const VertexShader > m_vs;

		ConstantBuffer< XMMATRIX > m_projection_buffer;
		ConstantBuffer< XMMATRIX > m_model_buffer;
	};
}