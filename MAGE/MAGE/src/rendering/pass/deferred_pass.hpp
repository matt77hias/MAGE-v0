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
	 A class of deferred passes for unpacking GBuffers and performing light 
	 calculations using the rendering or compute pipeline.
	 */
	class DeferredPass final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a deferred pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		DeferredPass();

		/**
		 Constructs a deferred pass from the given deferred shading pass.

		 @param[in]		pass
						A reference to the deferred pass to copy.
		 */
		DeferredPass(const DeferredPass &pass) = delete;

		/**
		 Constructs a deferred pass by moving the given deferred pass.

		 @param[in]		pass
						A reference to the deferred pass to move.
		 */
		DeferredPass(DeferredPass &&pass) noexcept;

		/**
		 Destructs this deferred pass.
		 */
		~DeferredPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given deferred pass to this deferred pass.

		 @param[in]		pass
						A reference to the deferred pass to copy.
		 @return		A reference to the copy of the given deferred shading 
						pass (i.e. this deferred pass).
		 */
		DeferredPass &operator=(const DeferredPass &pass) = delete;

		/**
		 Moves the given deferred pass to this deferred pass.

		 @param[in]		pass
						A reference to the deferred pass to move.
		 @return		A reference to the moved deferred pass (i.e. this 
						deferred pass).
		 */
		DeferredPass &operator=(DeferredPass &&pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Renders.

		 @param[in]		brdf
						The BRDF.
		 @param[in]		vct
						@c true if voxel cone tracing should be enabled. @c false 
						otherwise.
		 @throws		Exception
						Failed to render the scene.
		 */
		void Render(BRDFType brdf, bool vct);

		/**
		 Dispatches.

		 @param[in]		viewport
						A reference to the viewport.
		 @param[in]		brdf
						The BRDF.
		 @param[in]		vct
						@c true if voxel cone tracing should be enabled. @c false 
						otherwise.
		 @throws		Exception
						Failed to dispatch.
		 */
		void Dispatch(const Viewport &viewport, BRDFType brdf, bool vct);
		
	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this deferred pass.
		 */
		void BindFixedState() const noexcept;

		/**
		 Updates the compute and pixel shader of this deferred pass for 
		 the given BRDF.

		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 @param[in]		brdf
						The BRDF.
		 @param[in]		vct
						@c true if voxel cone tracing should be enabled. @c false 
						otherwise.
		 @throws		Exception
						Failed to update the compute shader of this deferred 
						pass.
		 @throws		Exception
						Failed to update the pixel shader of this deferred 
						pass.
		 */
		void UpdateShaders(BRDFType brdf, bool vct);
		
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this deferred pass.
		 */
		ID3D11DeviceContext * const m_device_context;

		/**
		 A pointer to the compute shader of this deferred pass.
		 */
		ComputeShaderPtr m_cs;

		/**
		 A pointer to the vertex shader of this deferred pass.
		 */
		const VertexShaderPtr m_msaa_vs;

		/**
		 A pointer to the pixel shader of this deferred pass.
		 */
		PixelShaderPtr m_msaa_ps;
		
		/**
		 The current BRDF of this deferred pass.
		 */
		BRDFType m_brdf;

		/**
		 A flag indicating whether or not voxel cone tracing should be enabled 
		 for this deferred pass.
		 */
		bool m_vct;
	};
}