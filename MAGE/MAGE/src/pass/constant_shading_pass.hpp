#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\pass_buffer.hpp"
#include "buffer\constant_buffer.hpp"
#include "buffer\model_buffer.hpp"
#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of constant shading passes for rendering
	 models using a constant (material independent) shading.
	 */
	class ConstantShadingPass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the constant shading pass associated with the current engine.

		 @pre			The constant shading pass associated with the 
						current engine must be loaded.
		 @return		A pointer to the constant shading pass associated
						with the current engine.
		 */
		static ConstantShadingPass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a constant shading pass.

		 @pre			The renderer associated with the
						current engine must be loaded.
		 @pre			The resource manager associated with the
						current engine must be loaded.
		 */
		ConstantShadingPass();

		/**
		 Constructs a constant shading pass from the given constant shading pass.

		 @param[in]		render_pass
						A reference to the constant shading pass to copy.
		 */
		ConstantShadingPass(const ConstantShadingPass &render_pass) = delete;

		/**
		 Constructs a constant shading pass by moving the given constant shading pass.

		 @param[in]		render_pass
						A reference to the constant shading pass to move.
		 */
		ConstantShadingPass(ConstantShadingPass &&render_pass);

		/**
		 Destructs this constant shading pass.
		 */
		~ConstantShadingPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given constant shading pass to this constant shading pass.

		 @param[in]		render_pass
						A reference to the constant shading pass to copy.
		 @return		A reference to the copy of the given constant shading pass
						(i.e. this constant shading pass).
		 */
		ConstantShadingPass &operator=(const ConstantShadingPass &render_pass) = delete;

		/**
		 Moves the given constant shading pass to this constant shading pass.

		 @param[in]		render_pass
						A reference to the constant shading pass to move.
		 @return		A reference to the moved constant shading pass
						(i.e. this constant shading pass).
		 */
		ConstantShadingPass &operator=(ConstantShadingPass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this constant shading pass.

		 @throws		FormattedException
						Failed to bind the fixed state 
						of this constant shading pass.
		 */
		void BindFixedState();

		/**
		 Renders the scene.

		 @pre			@a scene is not equal to @c nullptr.
		 @param[in]		scene
						A pointer to the scene.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @param[in]		world_to_view
						The world-to-view transformation matrix.
		 @param[in]		view_to_world
						The view-to-world transformation matrix.
		 @param[in]		view_to_projection
						The view-to-projection transformation matrix.
		 @throws		FormattedException
						Failed to render the scene.
		 */
		void XM_CALLCONV Render(
			const PassBuffer *scene,
			FXMMATRIX world_to_projection,
			CXMMATRIX world_to_view,
			CXMMATRIX view_to_world,
			CXMMATRIX view_to_projection);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the projection data of this constant shading pass.

		 @param[in]		view_to_projection
						The view-to-projection transformation matrix used for
						transforming vertices.
		 @throws		FormattedException
						Failed to bind the projection data 
						of this constant shading pass.
		 */
		void XM_CALLCONV BindProjectionData(
			FXMMATRIX view_to_projection);
		
		/**
		 Binds the model data of this constant shading pass.

		 @param[in]		object_to_view
						The object-to-view transformation matrix used for
						transforming vertices.
		 @param[in]		view_to_object
						The view-to-object transformation matrix used for
						transforming normals.
		 @param[in]		texture_transform
						The texture transformation matrix used for
						transforming texture coordinates.
		 @throws		FormattedException
						Failed to bind the model data 
						of this constant shading pass.
		 */
		void XM_CALLCONV BindModelData(
			FXMMATRIX object_to_view, 
			CXMMATRIX view_to_object,
			CXMMATRIX texture_transform);
		
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
		 @param[in]		view_to_world
						The view-to-world transformation matrix.
						This transformation matrix will be chained with
						the world-to-object transformation matrix for
						transforming normals.
		 @throws		FormattedException
						Failed to process the models.
		 */
		void XM_CALLCONV ProcessModels(
			const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection, 
			CXMMATRIX world_to_view, 
			CXMMATRIX view_to_world);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this constant shading pass.
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 A pointer to the vertex shader of this constant shading pass.
		 */
		const SharedPtr< const VertexShader > m_vs;
		
		/**
		 A pointer to the pixel shader of this constant shading pass.
		 */
		const SharedPtr< const PixelShader > m_ps;

		/**
		 The projection buffer of this constant shading pass.
		 */
		ConstantBuffer< XMMATRIX > m_projection_buffer;
		
		/**
		 The model buffer of this constant shading pass.
		 */
		ConstantBuffer< ModelBuffer > m_model_buffer;
		
		/**
		 A pointer to the white texture of this constant shading pass.
		 */
		const SharedPtr< const Texture > m_white;
	};
}
