#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\viewport.hpp"
#include "material\brdf.hpp"
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

		 @param[in]		pass
						A reference to the deferred shading pass to copy.
		 */
		DeferredShadingPass(const DeferredShadingPass &pass) = delete;

		/**
		 Constructs a deferred shading pass by moving the given deferred 
		 shading pass.

		 @param[in]		pass
						A reference to the deferred shading pass to move.
		 */
		DeferredShadingPass(DeferredShadingPass &&pass) noexcept;

		/**
		 Destructs this deferred shading pass.
		 */
		~DeferredShadingPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given deferred shading pass to this deferred shading pass.

		 @param[in]		pass
						A reference to the deferred shading pass to copy.
		 @return		A reference to the copy of the given deferred shading 
						pass (i.e. this deferred shading pass).
		 */
		DeferredShadingPass &operator=(const DeferredShadingPass &pass) = delete;

		/**
		 Moves the given deferred shading pass to this deferred shading pass.

		 @param[in]		pass
						A reference to the deferred shading pass to move.
		 @return		A reference to the moved deferred shading pass (i.e. 
						this deferred shading pass).
		 */
		DeferredShadingPass &operator=(DeferredShadingPass &&pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Renders.

		 @param[in]		brdf
						The BRDF.
		 */
		void Render(BRDFType brdf);

		/**
		 Dispatches.

		 @param[in]		viewport
						A reference to the viewport.
		 @param[in]		brdf
						The BRDF.
		 */
		void Dispatch(const Viewport &viewport, BRDFType brdf);
		
	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this deferred shading pass.
		 */
		void BindFixedState() const noexcept;

		/**
		 Updates the compute and pixel shader of this deferred shading pass for 
		 the given BRDF.

		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 @param[in]		brdf
						The BRDF.
		 @throws		Exception
						Failed to update the compute shader of this deferred 
						shading pass.
		 @throws		Exception
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
		ID3D11DeviceContext4 * const m_device_context;

		/**
		 A pointer to the compute shader of this deferred shading pass.
		 */
		ComputeShaderPtr m_cs;

		/**
		 A pointer to the vertex shader of this deferred shading pass.
		 */
		const VertexShaderPtr m_vs;

		/**
		 A pointer to the pixel shader of this deferred shading pass.
		 */
		PixelShaderPtr m_msaa_ps;
		
		/**
		 The current BRDF of this deferred shading pass.
		 */
		BRDFType m_brdf;
	};
}