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

	class VariableShadingPass final {

	public:

		VariableShadingPass();
		VariableShadingPass(const VariableShadingPass &render_pass) = delete;
		VariableShadingPass(VariableShadingPass &&render_pass);
		~VariableShadingPass();

		VariableShadingPass &operator=(const VariableShadingPass &render_pass) = delete;
		VariableShadingPass &operator=(VariableShadingPass &&render_pass) = delete;

		void Render(const PassBuffer *scene, const CameraNode *node);
		
	private:

		enum struct PSIndex {
			Emissive  = 0,
			BRDF      = 1,
			BRDF_TSNM = 2,
			Count     = 3
		};

		void UpdatePSs(BRDFType brdf);
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
		BRDFType m_brdf;

		ConstantBuffer< ModelBuffer > m_model_buffer;
		ConstantBuffer< XMMATRIX > m_projection_buffer;
	};
}