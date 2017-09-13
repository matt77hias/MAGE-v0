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

	/**
	 A class of shading normal passes for rendering
	 world-space shading normals of models.
	 */
	class ShadingNormalPass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the shading normal pass associated with the current engine.

		 @pre			The shading normal pass associated with the 
						current engine must be loaded.
		 @return		A pointer to the shading normal pass associated
						with the current engine.
		 */
		static ShadingNormalPass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a shading normal pass.

		 @pre			The renderer associated with the
						current engine must be loaded.
		 @pre			The resource manager associated with the
						current engine must be loaded.
		 */
		ShadingNormalPass();

		/**
		 Constructs a shading normal pass from the given shading normal pass.

		 @param[in]		render_pass
						A reference to the shading normal pass to copy.
		 */
		ShadingNormalPass(const ShadingNormalPass &render_pass) = delete;

		/**
		 Constructs a shading normal pass by moving the given shading normal pass.

		 @param[in]		render_pass
						A reference to the shading normal pass to move.
		 */
		ShadingNormalPass(ShadingNormalPass &&render_pass);

		/**
		 Destructs this shading normal pass.
		 */
		~ShadingNormalPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given shading normal pass to this shading normal pass.

		 @param[in]		render_pass
						A reference to the shading normal pass to copy.
		 @return		A reference to the copy of the given shading normal pass
						(i.e. this shading normal pass).
		 */
		ShadingNormalPass &operator=(const ShadingNormalPass &render_pass) = delete;

		/**
		 Moves the given shading normal pass to this shading normal pass.

		 @param[in]		render_pass
						A reference to the shading normal pass to move.
		 @return		A reference to the moved shading normal pass
						(i.e. this shading normal pass).
		 */
		ShadingNormalPass &operator=(ShadingNormalPass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this shading normal pass.

		 @param[in]		render_mode
						The render mode.
		 @throws		FormattedException
						Failed to bind the fixed state 
						of this shading normal pass.
		 */
		void BindFixedState(RenderMode render_mode);

		/**
		 Renders the scene.

		 @pre			@a scene is not equal to @c nullptr.
		 @param[in]		scene
						A pointer to the scene.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @param[in]		world_to_view
						The world-to-view transformation matrix.
		 @param[in]		view_to_projection
						The view-to-projection transformation matrix.
		 @throws		FormattedException
						Failed to render the scene.
		 */
		void XM_CALLCONV Render(
			const PassBuffer *scene,
			FXMMATRIX world_to_projection,
			CXMMATRIX world_to_view,
			CXMMATRIX view_to_projection);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 An enumeration of the different pixel shader indices 
		 for shading normal passes.

		 This contains:
		 @c ShadingNormal and
		 @c TSNMShadingNormal.
		 */
		enum struct PSIndex {
			ShadingNormal     = 0,
			TSNMShadingNormal = 1,
			Count             = 2
		};

		/**
		 Binds the pixel shader of this shading normal pass
		 associated with the given pixel shader index.

		 @param[in]		index
						The pixel shader index.
		 */
		void BindPS(PSIndex index) noexcept;
		
		/**
		 Binds the pixel shader of this shading normal pass 
		 associated with the given material and the current 
		 render mode of this shading normal pass.

		 @pre			@a material is not equal to @c nullptr.
		 @param[in]		material
						A pointer to the material.
		 */
		void BindPS(const Material *material) noexcept;
		
		/**
		 Binds the projection data of this shading normal pass.

		 @param[in]		view_to_projection
						The view-to-projection transformation matrix used for
						transforming vertices.
		 @throws		FormattedException
						Failed to bind the projection data 
						of this shading normal pass.
		 */
		void XM_CALLCONV BindProjectionData(FXMMATRIX view_to_projection);

		/**
		 Binds the model data of this shading normal pass.

		 @param[in]		object_to_view
						The object-to-view transformation matrix used for
						transforming vertices.
		 @param[in]		world_to_object
						The world-to-object transformation matrix used for
						transforming normals.
		 @throws		FormattedException
						Failed to bind the model data 
						of this shading normal pass.
		 */
		void XM_CALLCONV BindModelData(
			FXMMATRIX object_to_view, 
			CXMMATRIX world_to_object);
		
		/**
		 Process the given models.

		 @param[in]		models
						A reference to a vector containing the model pointers
						to process.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
						This transformation matrix will be used for 
						culling.
		 @param[in]		world_to_view
						The world-to-view transformation matrix.
						This transformation matrix will be chained with
						the object-to-view transformation matrix for
						transforming vertices.
		 @throws		FormattedException
						Failed to process the models.
		 */
		void XM_CALLCONV ProcessModels(
			const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection, 
			CXMMATRIX world_to_view);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this shading normal pass. 
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 The current render mode of this shading normal pass.
		 */
		RenderMode m_render_mode;
		
		/**
		 A pointer to the vertex shader of this shading normal pass.
		 */
		SharedPtr< const VertexShader > m_vs;
		
		/**
		 An array containing pointers to the pixel shaders
		 of this shading normal pass.
		 */
		SharedPtr< const PixelShader > m_ps[static_cast< size_t >(PSIndex::Count)];
		
		/**
		 The pixel shader index of the bound pixel shader
		 of this shading normal pass.
		 */
		PSIndex m_bound_ps;

		/**
		 The projection buffer of this shading normal pass.
		 */
		ConstantBuffer< XMMATRIX > m_projection_buffer;

		/**
		 The model buffer of this shading normal pass.
		 */
		ConstantBuffer< ModelTransformBuffer > m_model_buffer;
	};
}