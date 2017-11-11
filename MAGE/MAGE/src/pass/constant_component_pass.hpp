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
	 A class of constant component passes for rendering a constant (material 
	 independent) component of models.
	 */
	class ConstantComponentPass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the constant component pass associated with the current engine.

		 @pre			The scene renderer associated with the current engine 
						must be loaded.
		 @return		A pointer to the constant component pass associated 
						with the current engine.
		 */
		static ConstantComponentPass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a constant component pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		ConstantComponentPass();
		
		/**
		 Constructs a constant component pass from the given constant component 
		 pass.

		 @param[in]		render_pass
						A reference to the constant component pass to copy.
		 */
		ConstantComponentPass(
			const ConstantComponentPass &render_pass) = delete;
		
		/**
		 Constructs a constant component pass by moving the given constant 
		 component pass.

		 @param[in]		render_pass
						A reference to the constant component pass to move.
		 */
		ConstantComponentPass(
			ConstantComponentPass &&render_pass);
		
		/**
		 Destructs this constant component pass.
		 */
		~ConstantComponentPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given constant component pass to this constant component 
		 pass.

		 @param[in]		render_pass
						A reference to the constant component pass to copy.
		 @return		A reference to the copy of the given constant component 
						pass (i.e. this constant component pass).
		 */
		ConstantComponentPass &operator=(
			const ConstantComponentPass &render_pass) = delete;
		
		/**
		 Moves the given constant component pass to this constant component pass.

		 @param[in]		render_pass
						A reference to the constant component pass to move.
		 @return		A reference to the moved constant component pass (i.e. 
						this constant component pass).
		 */
		ConstantComponentPass &operator=(
			ConstantComponentPass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this constant component pass.

		 @param[in]		render_mode
						The render mode.
		 @throws		FormattedException
						Failed to bind the fixed state of this constant 
						component pass.
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
		 @throws		FormattedException
						Failed to render the scene.
		 */
		void XM_CALLCONV Render(
			const PassBuffer *scene,
			FXMMATRIX world_to_projection,
			CXMMATRIX world_to_view,
			CXMMATRIX view_to_world);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 An enumeration of the different pixel shader indices for constant 
		 component passes.

		 This contains:
		 @c UVTexture and
		 @c Distance.
		 */
		enum struct PSIndex {
			UVTexture = 0,
			Distance  = 1,
			Count     = 2
		};

		/**
		 Binds the pixel shader (and pixel shader related data) associated with 
		 the given render mode.

		 @param[in]		render_mode
						The render mode.
		 @throws		FormattedException
						Failed to bind the pixel shader related data of this 
						constant component pass.
		 */
		void BindPS(RenderMode render_mode);
		
		/**
		 Binds the model data of this constant component pass.

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
						Failed to bind the model data of this constant 
						component pass.
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
						The world-to-projection transformation matrix. This 
						transformation matrix will be used for culling.
		 @param[in]		world_to_view
						The world-to-view transformation matrix. This 
						transformation matrix will be chained with the 
						object-to-view transformation matrix for transforming 
						vertices.
		 @param[in]		view_to_world
						The view-to-world transformation matrix. This 
						transformation matrix will be chained with the 
						world-to-object transformation matrix for transforming 
						normals.
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
		 A pointer to the device context of this constant component pass. 
		 */
		ID3D11DeviceContext4 * const m_device_context;

		/**
		 A pointer to the vertex shader of this constant component pass.
		 */
		const SharedPtr< const VertexShader > m_vs;

		/**
		 An array containing pointers to the pixel shaders of this constant 
		 component pass.
		 */
		const SharedPtr< const PixelShader > m_ps[static_cast< size_t >(PSIndex::Count)];

		/**
		 The color buffer of this constant component pass.
		 */
		ConstantBuffer< RGBASpectrum > m_color_buffer;

		/**
		 The model buffer of this constant component pass.
		 */
		ConstantBuffer< ModelNormalTextureTransformBuffer > m_model_buffer;

		/**
		 A pointer to the UV reference texture of this constant component pass.
		 */
		const SharedPtr< const Texture > m_uv;
	};
}