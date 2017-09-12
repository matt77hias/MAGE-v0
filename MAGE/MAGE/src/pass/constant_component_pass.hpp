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

	class ConstantComponentPass final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		ConstantComponentPass();
		ConstantComponentPass(const ConstantComponentPass &render_pass) = delete;
		ConstantComponentPass(ConstantComponentPass &&render_pass);
		~ConstantComponentPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		ConstantComponentPass &operator=(const ConstantComponentPass &render_pass) = delete;
		ConstantComponentPass &operator=(ConstantComponentPass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void BindFixedState(RenderMode render_mode);

		void XM_CALLCONV Render(
			const PassBuffer *scene,
			FXMMATRIX world_to_projection,
			CXMMATRIX world_to_view,
			CXMMATRIX view_to_world,
			CXMMATRIX view_to_projection);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		enum struct PSIndex {
			UVTexture = 0,
			Distance  = 1,
			Count     = 2
		};

		void BindPS(RenderMode render_mode);
		
		void XM_CALLCONV BindModelData(
			FXMMATRIX object_to_view,
			CXMMATRIX view_to_object,
			CXMMATRIX texture_transform);
		
		void XM_CALLCONV BindSceneData(
			FXMMATRIX view_to_projection);
		
		void XM_CALLCONV ProcessModels(
			const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection, 
			CXMMATRIX world_to_view, 
			CXMMATRIX view_to_world);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		ID3D11DeviceContext2 * const m_device_context;

		SharedPtr< const VertexShader > m_vs;
		SharedPtr< const PixelShader > m_ps[static_cast< size_t >(PSIndex::Count)];

		ConstantBuffer< ModelTransformBuffer > m_model_buffer;
		ConstantBuffer< XMMATRIX > m_scene_buffer;
		ConstantBuffer< RGBASpectrum > m_color_buffer;
		const SharedPtr< const Texture > m_uv;
	};
}