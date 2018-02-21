#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "rendering\buffer\constant_buffer.hpp"
#include "rendering\buffer\model_buffer.hpp"
#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of shading normal passes for rendering world-space shading normals 
	 of models.
	 */
	class ShadingNormalPass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the shading normal pass associated with the current engine.

		 @pre			The scene renderer associated with the  current engine 
						must be loaded.
		 @return		A pointer to the shading normal pass associated with 
						the current engine.
		 */
		static ShadingNormalPass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a shading normal pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		ShadingNormalPass();

		/**
		 Constructs a shading normal pass from the given shading normal pass.

		 @param[in]		pass
						A reference to the shading normal pass to copy.
		 */
		ShadingNormalPass(const ShadingNormalPass &pass) = delete;

		/**
		 Constructs a shading normal pass by moving the given shading normal 
		 pass.

		 @param[in]		pass
						A reference to the shading normal pass to move.
		 */
		ShadingNormalPass(ShadingNormalPass &&pass) noexcept;

		/**
		 Destructs this shading normal pass.
		 */
		~ShadingNormalPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given shading normal pass to this shading normal pass.

		 @param[in]		pass
						A reference to the shading normal pass to copy.
		 @return		A reference to the copy of the given shading normal 
						pass (i.e. this shading normal pass).
		 */
		ShadingNormalPass &operator=(const ShadingNormalPass &pass) = delete;

		/**
		 Moves the given shading normal pass to this shading normal pass.

		 @param[in]		pass
						A reference to the shading normal pass to move.
		 @return		A reference to the moved shading normal pass (i.e. 
						this shading normal pass).
		 */
		ShadingNormalPass &operator=(ShadingNormalPass &&pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Renders the scene.

		 @param[in]		scene
						A reference to the scene.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @param[in]		world_to_view
						The world-to-view transformation matrix.
		 @param[in]		render_mode
						The render mode.
		 @throws		Exception
						Failed to render the scene.
		 */
		void XM_CALLCONV Render(const Scene &scene,
			                    FXMMATRIX world_to_projection,
			                    CXMMATRIX world_to_view,
								RenderMode render_mode);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this shading normal pass.
		 */
		void BindFixedState() const noexcept;

		/**
		 An enumeration of the different pixel shader indices for shading 
		 normal passes.

		 This contains:
		 @c ShadingNormal and
		 @c TSNMShadingNormal.
		 */
		enum class PSIndex : U8 {
			Default = 0,
			TSNM    = 1,
			Count   = 2
		};

		/**
		 Binds the pixel shader of this shading normal pass associated with the 
		 given pixel shader index.

		 @param[in]		index
						The pixel shader index.
		 */
		void BindPS(PSIndex index) noexcept;
		
		/**
		 Binds the pixel shader of this shading normal pass associated with the 
		 given material and the current render mode of this shading normal 
		 pass.

		 @param[in]		material
						A reference to the material.
		 */
		void BindPS(const Material &material) noexcept;
		
		/**
		 Binds the model data of this shading normal pass.

		 @param[in]		object_to_view
						The object-to-view transformation matrix used for 
						transforming vertices.
		 @param[in]		world_to_object
						The world-to-object transformation matrix used for
						transforming normals.
		 @throws		Exception
						Failed to bind the model data of this shading normal 
						pass.
		 */
		void XM_CALLCONV BindModelData(FXMMATRIX object_to_view, 
			                           CXMMATRIX world_to_object);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this shading normal pass. 
		 */
		ID3D11DeviceContext * const m_device_context;

		/**
		 The current render mode of this shading normal pass.
		 */
		RenderMode m_render_mode;
		
		/**
		 A pointer to the vertex shader of this shading normal pass.
		 */
		const VertexShaderPtr m_vs;
		
		/**
		 An array containing pointers to the pixel shaders of this shading 
		 normal pass.
		 */
		const PixelShaderPtr m_ps[static_cast< size_t >(PSIndex::Count)];
		
		/**
		 The pixel shader index of the bound pixel shader of this shading 
		 normal pass.
		 */
		PSIndex m_bound_ps;

		/**
		 The model buffer of this shading normal pass.
		 */
		ConstantBuffer< ModelNormalTransformBuffer > m_model_buffer;
	};
}