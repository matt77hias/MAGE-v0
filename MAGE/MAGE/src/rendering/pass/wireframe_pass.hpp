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
	 A class of wireframe passes for rendering models as wireframes.
	 */
	class WireframePass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the wireframe pass associated with the current engine.

		 @pre			The scene renderer associated with the current engine 
						must be loaded.
		 @return		A pointer to the wireframe pass associated with the 
						current engine.
		 */
		static WireframePass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a wireframe pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		WireframePass();
		
		/**
		 Constructs a wireframe pass from the given wireframe pass.

		 @param[in]		pass
						A reference to the wireframe pass to copy.
		 */
		WireframePass(const WireframePass &pass) = delete;

		/**
		 Constructs a wireframe pass by moving the given wireframe pass.

		 @param[in]		pass
						A reference to the wireframe pass to move.
		 */
		WireframePass(WireframePass &&pass) noexcept;

		/**
		 Destructs this wireframe pass.
		 */
		~WireframePass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given wireframe pass to this wireframe pass.

		 @param[in]		pass
						A reference to the wireframe pass to copy.
		 @return		A reference to the copy of the given wireframe pass 
						(i.e. this wireframe pass).
		 */
		WireframePass &operator=(const WireframePass &pass) = delete;

		/**
		 Moves the given wireframe pass to this wireframe pass.

		 @param[in]		pass
						A reference to the wireframe pass to move.
		 @return		A reference to the moved wireframe pass (i.e. this 
						wireframe pass).
		 */
		WireframePass &operator=(WireframePass &&pass) = delete;

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
		 @param[in]		color
						A reference to the color (in in linear space).
		 @throws		Exception
						Failed to render the scene.
		 */
		void XM_CALLCONV Render(const Scene &scene,
			                    FXMMATRIX world_to_projection,
			                    CXMMATRIX world_to_view,
								const RGBA &color = { 0.0f, 0.0f, 1.0f, 1.0f });

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this wireframe pass.
		 */
		void BindFixedState() const noexcept;

		/**
		 Binds the color data of this wireframe pass.

		 @param[in]		color
						A reference to the color (in in linear space).
		 @throws		Exception
						Failed to bind the color data of this wireframe pass.
		 */
		void BindColorData(const RGBA &color);

		/**
		 Binds the model data of this wireframe pass.

		 @param[in]		object_to_view
						The object-to-view transformation matrix used for
						transforming vertices.
		 @throws		Exception
						Failed to bind the model data 
						of this wireframe pass.
		 */
		void XM_CALLCONV BindModelData(FXMMATRIX object_to_view);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this wireframe pass.
		 */
		D3D11DeviceContext * const m_device_context;
		
		/**
		 A pointer to the vertex shader of this wireframe pass.
		 */
		const VertexShaderPtr m_vs;

		/**
		 A pointer to the pixel shader of this wireframe pass.
		 */
		const PixelShaderPtr m_ps;

		/**
		 The color buffer of this wireframe pass.
		 */
		ConstantBuffer< RGBA > m_color_buffer;

		/**
		 The model buffer of this wireframe pass.
		 */
		ConstantBuffer< ModelNormalTextureTransformBuffer > m_model_buffer;
	};
}