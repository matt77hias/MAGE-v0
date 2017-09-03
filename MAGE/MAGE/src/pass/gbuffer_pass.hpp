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

		GBufferPass();
		GBufferPass(const GBufferPass &render_pass) = delete;
		GBufferPass(GBufferPass &&render_pass);
		~GBufferPass();

		GBufferPass &operator=(const GBufferPass &render_pass) = delete;
		GBufferPass &operator=(GBufferPass &&render_pass) = delete;

		void Render(const PassBuffer *scene, const CameraNode *node);
		
	private:

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
			FXMMATRIX view_to_projection) noexcept;
		void XM_CALLCONV BindModelData(
			FXMMATRIX object_to_view, 
			FXMMATRIX view_to_object,
			FXMMATRIX texture_transform,
			const Material *material) noexcept;
		
		void XM_CALLCONV ProcessModels(
			const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection, 
			FXMMATRIX world_to_view, 
			FXMMATRIX view_to_world) noexcept;

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