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
	 A class of wireframe passes for rendering models as wireframes.
	 */
	class WireframePass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the wireframe pass associated with the current engine.

		 @pre			The scene renderer associated with the 
						current engine must be loaded.
		 @return		A pointer to the wireframe pass associated
						with the current engine.
		 */
		static WireframePass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a wireframe pass.

		 @pre			The renderer associated with the
						current engine must be loaded.
		 @pre			The resource manager associated with the
						current engine must be loaded.
		 */
		WireframePass();
		
		/**
		 Constructs a wireframe pass from the given wireframe pass.

		 @param[in]		render_pass
						A reference to the wireframe pass to copy.
		 */
		WireframePass(const WireframePass &render_pass) = delete;

		/**
		 Constructs a wireframe pass by moving the given wireframe pass.

		 @param[in]		render_pass
						A reference to the wireframe pass to move.
		 */
		WireframePass(WireframePass &&render_pass);

		/**
		 Destructs this wireframe pass.
		 */
		~WireframePass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given wireframe pass to this wireframe pass.

		 @param[in]		render_pass
						A reference to the wireframe pass to copy.
		 @return		A reference to the copy of the given wireframe pass
						(i.e. this wireframe pass).
		 */
		WireframePass &operator=(const WireframePass &render_pass) = delete;

		/**
		 Moves the given wireframe pass to this wireframe pass.

		 @param[in]		render_pass
						A reference to the wireframe pass to move.
		 @return		A reference to the moved wireframe pass
						(i.e. this wireframe pass).
		 */
		WireframePass &operator=(WireframePass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this wireframe pass.

		 @throws		FormattedException
						Failed to bind the fixed state of this wireframe pass.
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
		 Binds the color data of this wireframe pass.

		 @throws		FormattedException
						Failed to bind the color data 
						of this wireframe pass.
		 */
		void BindColorData();

		/**
		 Binds the projection data of this wireframe pass.

		 @param[in]		view_to_projection
						The view-to-projection transformation matrix used for
						transforming vertices.
		 @throws		FormattedException
						Failed to bind the projection data 
						of this wireframe pass.
		 */
		void XM_CALLCONV BindProjectionData(FXMMATRIX view_to_projection);

		/**
		 Binds the model data of this wireframe pass.

		 @param[in]		object_to_view
						The object-to-view transformation matrix used for
						transforming vertices.
		 @throws		FormattedException
						Failed to bind the model data 
						of this wireframe pass.
		 */
		void XM_CALLCONV BindModelData(FXMMATRIX object_to_view);

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
		 A pointer to the device context of this wireframe pass.
		 */
		ID3D11DeviceContext2 * const m_device_context;
		
		/**
		 A pointer to the vertex shader of this wireframe pass.
		 */
		const SharedPtr< const VertexShader > m_vs;

		/**
		 A pointer to the pixel shader of this wireframe pass.
		 */
		const SharedPtr< const PixelShader > m_ps;

		/**
		 The color buffer of this wireframe pass.
		 */
		ConstantBuffer< RGBASpectrum > m_color_buffer;

		/**
		 The projection buffer of this wireframe pass.
		 */
		ConstantBuffer< XMMATRIX > m_projection_buffer;

		/**
		 The model buffer of this wireframe pass.
		 */
		ConstantBuffer< ModelTransformBuffer > m_model_buffer;
	};
}