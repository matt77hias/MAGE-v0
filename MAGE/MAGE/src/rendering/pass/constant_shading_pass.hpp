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
	 A class of constant shading passes for rendering models using a constant 
	 (material independent) shading.
	 */
	class ConstantShadingPass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the constant shading pass associated with the current engine.

		 @pre			The scene renderer associated with the current engine 
						must be loaded.
		 @return		A pointer to the constant shading pass associated with 
						the current engine.
		 */
		static ConstantShadingPass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a constant shading pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		ConstantShadingPass();

		/**
		 Constructs a constant shading pass from the given constant shading 
		 pass.

		 @param[in]		pass
						A reference to the constant shading pass to copy.
		 */
		ConstantShadingPass(const ConstantShadingPass &pass) = delete;

		/**
		 Constructs a constant shading pass by moving the given constant 
		 shading pass.

		 @param[in]		pass
						A reference to the constant shading pass to move.
		 */
		ConstantShadingPass(ConstantShadingPass &&pass) noexcept;

		/**
		 Destructs this constant shading pass.
		 */
		~ConstantShadingPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given constant shading pass to this constant shading pass.

		 @param[in]		pass
						A reference to the constant shading pass to copy.
		 @return		A reference to the copy of the given constant shading 
						pass (i.e. this constant shading pass).
		 */
		ConstantShadingPass &operator=(const ConstantShadingPass &pass) = delete;

		/**
		 Moves the given constant shading pass to this constant shading pass.

		 @param[in]		pass
						A reference to the constant shading pass to move.
		 @return		A reference to the moved constant shading pass (i.e. 
						this constant shading pass).
		 */
		ConstantShadingPass &operator=(ConstantShadingPass &&pass) = delete;

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
		 @throws		Exception
						Failed to render the scene.
		 */
		void XM_CALLCONV Render(const Scene &scene,
			                    FXMMATRIX world_to_projection,
			                    CXMMATRIX world_to_view,
			                    CXMMATRIX view_to_world);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this constant shading pass.

		 @throws		Exception
						Failed to bind the fixed state of this constant shading 
						pass.
		 */
		void BindFixedState() const noexcept;

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
		 @throws		Exception
						Failed to bind the model data 
						of this constant shading pass.
		 */
		void XM_CALLCONV BindModelData(FXMMATRIX object_to_view, 
			                           CXMMATRIX view_to_object,
			                           CXMMATRIX texture_transform);
		
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this constant shading pass.
		 */
		ID3D11DeviceContext4 * const m_device_context;

		/**
		 A pointer to the vertex shader of this constant shading pass.
		 */
		const VertexShaderPtr m_vs;
		
		/**
		 A pointer to the pixel shader of this constant shading pass.
		 */
		const PixelShaderPtr m_ps;

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
