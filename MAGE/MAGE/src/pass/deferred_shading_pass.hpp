#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\pass_buffer.hpp"
#include "buffer\constant_buffer.hpp"
#include "buffer\deferred_buffer.hpp"
#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of deferred shading passes for unpacking GBuffers and performing 
	 light calculations using the compute pipeline.
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
		 @throws		FormattedException
						Failed to bind the fixed state of this deferred 
						shading pass.
		 */
		void BindFixedState(BRDFType brdf);

		/**
		 Renders the scene.

		 @pre			@a scene is not equal to @c nullptr.
		 @param[in]		scene
						A pointer to the scene.
		 @param[in]		view_to_projection
						The view-to-projection transformation matrix.
		 @throws		FormattedException
						Failed to render the scene.
		 */
		void XM_CALLCONV Render(
			const PassBuffer *scene,
			FXMMATRIX view_to_projection);
		
	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Updates the compute shader of this deferred shading pass for the given 
		 BRDF.

		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 @param[in]		brdf
						The BRDF.
		 @throws		FormattedException
						Failed to update the compute shader of this deferred 
						shading pass.
		 */
		void UpdateCS(BRDFType brdf);
		
		/**
		 Binds the GBuffer unpacking data of this deferred shading pass.

		 @pre			@a scene is not equal to @c nullptr.
		 @param[in]		view_to_projection
						The view-to-projection transformation matrix used for
						transforming vertices.
		 @param[in]		scene
						A pointer to the scene.
		 @throws		FormattedException
						Failed to bind the projection data of this deferred 
						shading pass.
		 */
		void XM_CALLCONV BindUnpackData(
			FXMMATRIX view_to_projection,
			const PassBuffer *scene);
	
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
		 The current BRDF of this deferred shading pass.
		 */
		BRDFType m_brdf;

		/**
		 The deferred buffer of this deferred shading pass.
		 */
		ConstantBuffer< DeferredBuffer > m_deferred_buffer;
	};
}