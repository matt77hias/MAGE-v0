#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\pass_buffer.hpp"
#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of deferred shading passes for unpacking GBuffers and performing 
	 light calculations using the rendering or compute pipeline.
	 */
	class DeferredShadingPass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the deferred shading pass associated with the current engine.

		 @pre			The scene renderer associated with the current engine 
						must be loaded.
		 @return		A pointer to the deferred shading pass associated with 
						the current engine.
		 */
		static DeferredShadingPass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a deferred shading pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		DeferredShadingPass();

		/**
		 Constructs a deferred shading pass from the given deferred shading 
		 pass.

		 @param[in]		render_pass
						A reference to the deferred shading pass to copy.
		 */
		DeferredShadingPass(const DeferredShadingPass &render_pass) = delete;

		/**
		 Constructs a deferred shading pass by moving the given deferred 
		 shading pass.

		 @param[in]		render_pass
						A reference to the deferred shading pass to move.
		 */
		DeferredShadingPass(DeferredShadingPass &&render_pass);

		/**
		 Destructs this deferred shading pass.
		 */
		~DeferredShadingPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given deferred shading pass to this deferred shading pass.

		 @param[in]		render_pass
						A reference to the deferred shading pass to copy.
		 @return		A reference to the copy of the given deferred shading 
						pass (i.e. this deferred shading pass).
		 */
		DeferredShadingPass &operator=(
			const DeferredShadingPass &render_pass) = delete;

		/**
		 Moves the given deferred shading pass to this deferred shading pass.

		 @param[in]		render_pass
						A reference to the deferred shading pass to move.
		 @return		A reference to the moved deferred shading pass (i.e. 
						this deferred shading pass).
		 */
		DeferredShadingPass &operator=(
			DeferredShadingPass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this deferred shading pass.

		 @param[in]		brdf
						The BRDF.
	     @param[in]		use_compute
						If @c true, the compute pipeline is used.
						Otherwise, the rendering pipeline is used.
		 @throws		FormattedException
						Failed to bind the fixed state of this deferred 
						shading pass.
		 */
		void BindFixedState(BRDFType brdf, bool use_compute);

		/**
		 Renders.
		 */
		void Render() const noexcept;

		/**
		 Dispatches.

		 @param[in]		viewport
						A reference to the viewport.
		 */
		void Dispatch(const Viewport &viewport) const noexcept;
		
	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Updates the compute and pixel shader of this deferred shading pass for 
		 the given BRDF.

		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 @param[in]		brdf
						The BRDF.
		 @throws		FormattedException
						Failed to update the compute shader of this deferred 
						shading pass.
		 @throws		FormattedException
						Failed to update the pixel shader of this deferred 
						shading pass.
		 */
		void UpdateShaders(BRDFType brdf);
		
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this deferred shading pass.
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 A pointer to the compute shader of this deferred shading pass.
		 */
		SharedPtr< const ComputeShader > m_cs;

		/**
		 A pointer to the vertex shader of this deferred shading pass.
		 */
		SharedPtr< const VertexShader > m_vs;

		/**
		 A pointer to the pixel shader of this deferred shading pass.
		 */
		SharedPtr< const PixelShader > m_ps;
		
		/**
		 The current BRDF of this deferred shading pass.
		 */
		BRDFType m_brdf;
	};
}