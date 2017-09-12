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

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		DeferredShadingPass();
		DeferredShadingPass(const DeferredShadingPass &render_pass) = delete;
		DeferredShadingPass(DeferredShadingPass &&render_pass);
		~DeferredShadingPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		DeferredShadingPass &operator=(const DeferredShadingPass &render_pass) = delete;
		DeferredShadingPass &operator=(DeferredShadingPass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void BindFixedState(BRDFType brdf);

		void XM_CALLCONV Render(
			const PassBuffer *scene,
			FXMMATRIX view_to_projection);
		
	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void UpdateCS(BRDFType brdf);
		
		void XM_CALLCONV BindUnpackData(
			FXMMATRIX view_to_projection,
			const PassBuffer *scene);
	
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		ID3D11DeviceContext2 * const m_device_context;

		SharedPtr< const ComputeShader > m_cs;
		BRDFType m_brdf;

		ConstantBuffer< DeferredComputeBuffer > m_deferred_buffer;
	};
}