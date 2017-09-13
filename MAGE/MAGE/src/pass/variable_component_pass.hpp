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
	 A class of variable component passes for rendering 
	 a variable (material dependent) component of models.
	 */
	class VariableComponentPass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the variable component pass associated with the current engine.

		 @pre			The scene renderer associated with the 
						current engine must be loaded.
		 @return		A pointer to the variable component pass associated
						with the current engine.
		 */
		static VariableComponentPass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a variable component pass.

		 @pre			The renderer associated with the
						current engine must be loaded.
		 @pre			The resource manager associated with the
						current engine must be loaded.
		 */
		VariableComponentPass();

		/**
		 Constructs a variable component pass from the given variable component pass.

		 @param[in]		render_pass
						A reference to the variable component pass to copy.
		 */
		VariableComponentPass(const VariableComponentPass &render_pass) = delete;

		/**
		 Constructs a variable component pass by moving the given variable component pass.

		 @param[in]		render_pass
						A reference to the variable component pass to move.
		 */
		VariableComponentPass(VariableComponentPass &&render_pass);

		/**
		 Destructs this variable component pass.
		 */
		~VariableComponentPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given variable component pass to this variable component pass.

		 @param[in]		render_pass
						A reference to the variable component pass to copy.
		 @return		A reference to the copy of the given variable component pass
						(i.e. this variable component pass).
		 */
		VariableComponentPass &operator=(const VariableComponentPass &render_pass) = delete;

		/**
		 Moves the given variable component pass to this variable component pass.

		 @param[in]		render_pass
						A reference to the variable component pass to move.
		 @return		A reference to the moved variable component pass
						(i.e. this variable component pass).
		 */
		VariableComponentPass &operator=(VariableComponentPass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this variable component pass.

		 @param[in]		render_mode
						The render mode.
		 @throws		FormattedException
						Failed to bind the fixed state 
						of this variable component pass.
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
		 Binds the projection data of this variable component pass.

		 @param[in]		view_to_projection
						The view-to-projection transformation matrix used for
						transforming vertices.
		 @throws		FormattedException
						Failed to bind the projection data 
						of this variable component pass.
		 */
		void XM_CALLCONV BindProjectionData(
			FXMMATRIX view_to_projection);

		/**
		 Binds the model data of this variable component pass.

		 @pre			@a material is not equal to @c nullptr.
		 @param[in]		object_to_view
						The object-to-view transformation matrix used for
						transforming vertices.
		 @param[in]		view_to_object
						The view-to-object transformation matrix used for
						transforming normals.
		 @param[in]		texture_transform
						The texture transformation matrix used for
						transforming texture coordinates.
		 @param[in]		material
						A pointer to the material.
		 @throws		FormattedException
						Failed to bind the model data 
						of this variable component pass.
		 */
		void XM_CALLCONV BindModelData(
			FXMMATRIX object_to_view,
			CXMMATRIX view_to_object,
			CXMMATRIX texture_transform,
			const Material *material);
		
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
		 A pointer to the device context of this variable component pass.
		 */
		ID3D11DeviceContext2 * const m_device_context;
		
		/**
		 The current render mode of this variable component pass. 
		 */
		RenderMode m_render_mode;

		/**
		 A pointer to the vertex shader of this variable component pass.
		 */
		const SharedPtr< const VertexShader > m_vs;

		/**
		 A pointer to the pixel shader of this variable component pass.
		 */
		const SharedPtr< const PixelShader > m_ps;

		/**
		 The color buffer of this variable component pass.
		 */
		ConstantBuffer< RGBASpectrum > m_color_buffer;

		/**
		 The projection buffer of this variable component pass.
		 */
		ConstantBuffer< XMMATRIX > m_projection_buffer;

		/**
		 The model buffer of this variable component pass.
		 */
		ConstantBuffer< ModelTransformBuffer > m_model_buffer;

		/**
		 A pointer to the with texture of this variable component pass.
		 */
		const SharedPtr< const Texture > m_white;
	};
}