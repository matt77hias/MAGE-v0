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

	class GBufferPass final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		GBufferPass();
		GBufferPass(const GBufferPass &render_pass) = delete;
		GBufferPass(GBufferPass &&render_pass);
		~GBufferPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		GBufferPass &operator=(const GBufferPass &render_pass) = delete;
		GBufferPass &operator=(GBufferPass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void BindFixedState();

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

		void UpdateMaterialCoefficientData(
			const PassBuffer *scene) noexcept;
		
		float NormalizeMaterialCoefficient(
			uint8_t index, const Material *material) const noexcept;

		enum struct PSIndex {
			Default = 0,
			TSNM    = 1,
			Count   = 2
		};

		void BindPS(PSIndex index) noexcept;
		
		void BindPS(const Material *material) noexcept;
		
		void XM_CALLCONV BindProjectionData(
			FXMMATRIX view_to_projection);
		
		void XM_CALLCONV BindModelData(
			FXMMATRIX object_to_view, 
			CXMMATRIX view_to_object,
			CXMMATRIX texture_transform,
			const Material *material);
		
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
		PSIndex m_bound_ps;

		ConstantBuffer< DeferredModelBuffer > m_model_buffer;
		ConstantBuffer< XMMATRIX > m_projection_buffer;

		float m_material_coefficient_min[PassBuffer::s_nb_material_coefficients];
		float m_material_coefficient_range[PassBuffer::s_nb_material_coefficients];
	};
}