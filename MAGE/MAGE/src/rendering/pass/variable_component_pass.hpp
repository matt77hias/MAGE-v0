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
	 A class of variable component passes for rendering a variable (material 
	 dependent) component of models.
	 */
	class VariableComponentPass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the variable component pass associated with the current 
		 engine.

		 @pre			The scene renderer associated with the current engine 
						must be loaded.
		 @return		A pointer to the variable component pass associated
						with the current engine.
		 */
		static VariableComponentPass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a variable component pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		VariableComponentPass();

		/**
		 Constructs a variable component pass from the given variable component 
		 pass.

		 @param[in]		pass
						A reference to the variable component pass to copy.
		 */
		VariableComponentPass(const VariableComponentPass &pass) = delete;

		/**
		 Constructs a variable component pass by moving the given variable 
		 component pass.

		 @param[in]		pass
						A reference to the variable component pass to move.
		 */
		VariableComponentPass(VariableComponentPass &&pass) noexcept;

		/**
		 Destructs this variable component pass.
		 */
		~VariableComponentPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given variable component pass to this variable component 
		 pass.

		 @param[in]		pass
						A reference to the variable component pass to copy.
		 @return		A reference to the copy of the given variable component 
						pass (i.e. this variable component pass).
		 */
		VariableComponentPass &operator=(const VariableComponentPass &pass) = delete;

		/**
		 Moves the given variable component pass to this variable component 
		 pass.

		 @param[in]		pass
						A reference to the variable component pass to move.
		 @return		A reference to the moved variable component pass (i.e. 
						this variable component pass).
		 */
		VariableComponentPass &operator=(VariableComponentPass &&pass) = delete;

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
		 @param[in]		view_to_world
						The view-to-world transformation matrix.
		 @param[in]		render_mode
						The render mode.
		 @throws		Exception
						Failed to render the scene.
		 */
		void XM_CALLCONV Render(const Scene &scene,
			                    FXMMATRIX world_to_projection,
			                    CXMMATRIX world_to_view,
			                    CXMMATRIX view_to_world,
								RenderMode render_mode);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this variable component pass.
		 */
		void BindFixedState() const noexcept;

		/**
		 Binds the model data of this variable component pass.

		 @param[in]		object_to_view
						The object-to-view transformation matrix used for
						transforming vertices.
		 @param[in]		view_to_object
						The view-to-object transformation matrix used for
						transforming normals.
		 @param[in]		texture_transform
						The texture transformation matrix used for transforming 
						texture coordinates.
		 @param[in]		material
						A reference to the material.
		 @throws		Exception
						Failed to bind the model data of this variable 
						component pass.
		 */
		void XM_CALLCONV BindModelData(FXMMATRIX object_to_view,
			                           CXMMATRIX view_to_object,
			                           CXMMATRIX texture_transform,
			                           const Material &material);
		
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this variable component pass.
		 */
		ID3D11DeviceContext * const m_device_context;
		
		/**
		 The current render mode of this variable component pass. 
		 */
		RenderMode m_render_mode;

		/**
		 A pointer to the vertex shader of this variable component pass.
		 */
		const VertexShaderPtr m_vs;

		/**
		 A pointer to the pixel shader of this variable component pass.
		 */
		const PixelShaderPtr m_ps;

		/**
		 The color buffer of this variable component pass.
		 */
		ConstantBuffer< RGBA > m_color_buffer;

		/**
		 The model buffer of this variable component pass.
		 */
		ConstantBuffer< ModelNormalTextureTransformBuffer > m_model_buffer;

		/**
		 A pointer to the with texture of this variable component pass.
		 */
		const SharedPtr< const Texture > m_white;
	};
}