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

	class ShadingNormalPass final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		ShadingNormalPass();
		ShadingNormalPass(const ShadingNormalPass &render_pass) = delete;
		ShadingNormalPass(ShadingNormalPass &&render_pass);
		~ShadingNormalPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		ShadingNormalPass &operator=(const ShadingNormalPass &render_pass) = delete;
		ShadingNormalPass &operator=(ShadingNormalPass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void BindFixedState(RenderMode render_mode);

		void XM_CALLCONV Render(
			const PassBuffer *scene,
			FXMMATRIX world_to_projection,
			FXMMATRIX world_to_view,
			FXMMATRIX view_to_projection);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		enum struct PSIndex {
			ShadingNormal     = 0,
			TSNMShadingNormal = 1,
			Count             = 2
		};

		void BindPS(PSIndex index) noexcept;
		
		void BindPS(const Material *material) noexcept;
		
		void XM_CALLCONV BindModelData(
			FXMMATRIX object_to_view, 
			FXMMATRIX world_to_object);
		
		void XM_CALLCONV BindSceneData(
			FXMMATRIX view_to_projection);

		void XM_CALLCONV ProcessModels(
			const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection, 
			FXMMATRIX world_to_view);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		ID3D11DeviceContext2 * const m_device_context;
		RenderMode m_render_mode;
		
		SharedPtr< const VertexShader > m_vs;
		SharedPtr< const PixelShader > m_ps[static_cast< size_t >(PSIndex::Count)];
		PSIndex m_bound_ps;

		ConstantBuffer< ModelTransformBuffer > m_model_buffer;
		ConstantBuffer< XMMATRIX > m_scene_buffer;
	};
}