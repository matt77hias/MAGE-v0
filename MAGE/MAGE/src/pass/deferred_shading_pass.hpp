#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\pass_buffer.hpp"
#include "buffer\constant_buffer.hpp"
#include "buffer\deferred_buffer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class DeferredShadingPass final {

	public:

		DeferredShadingPass();
		DeferredShadingPass(const DeferredShadingPass &render_pass) = delete;
		DeferredShadingPass(DeferredShadingPass &&render_pass);
		~DeferredShadingPass();

		DeferredShadingPass &operator=(const DeferredShadingPass &render_pass) = delete;
		DeferredShadingPass &operator=(DeferredShadingPass &&render_pass) = delete;

		void Render(const PassBuffer *scene, const CameraNode *node);
		
	private:

		void UpdatePS(BRDFType brdf);
		void XM_CALLCONV BindUnpackData(
			FXMMATRIX view_to_projection,
			const PassBuffer *scene) noexcept;
	
		ID3D11DeviceContext2 * const m_device_context;

		SharedPtr< const VertexShader > m_vs;
		SharedPtr< const PixelShader > m_ps;
		BRDFType m_brdf;

		ConstantBuffer< DeferredBuffer > m_deferred_buffer;
	};
}