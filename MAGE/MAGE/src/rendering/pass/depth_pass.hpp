#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "rendering\buffer\constant_buffer.hpp"
#include "rendering\buffer\camera_buffer.hpp"
#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of depth passes for rendering models to a depth buffer only.
	 */
	class DepthPass final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a depth pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		DepthPass();

		/**
		 Constructs a depth pass from the given depth pass.

		 @param[in]		pass
						A reference to the depth pass to copy.
		 */
		DepthPass(const DepthPass &pass) = delete;

		/**
		 Constructs a depth pass by moving the given depth pass.

		 @param[in]		pass
						A reference to the depth pass to move.
		 */
		DepthPass(DepthPass &&pass) noexcept;

		/**
		 Destructs this depth pass.
		 */
		~DepthPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given depth pass to this depth pass.

		 @param[in]		pass
						A reference to the depth pass to copy.
		 @return		A reference to the copy of the given depth pass (i.e. 
						this depth pass).
		 */
		DepthPass &operator=(const DepthPass &pass) = delete;

		/**
		 Moves the given depth pass to this depth pass.

		 @param[in]		pass
						A reference to the depth pass to move.
		 @return		A reference to the moved depth pass (i.e. this depth 
						pass).
		 */
		DepthPass &operator=(DepthPass &&pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------
		
		/**
		 Binds the fixed state of this depth pass.

		 @throws		Exception
						Failed to bind the fixed state of this depth pass.
		 */
		void BindFixedState() const noexcept;

		/**
		 Renders the scene.

		 @param[in]		scene
						A reference to the scene.
		 @param[in]		world_to_camera
						The world-to-camera transformation matrix.
		 @param[in]		camera_to_projection
						The camera-to-projection transformation matrix.
		 @throws		Exception
						Failed to render the scene.
		 */
		void XM_CALLCONV Render(const Scene &scene,
								FXMMATRIX world_to_camera,
								CXMMATRIX camera_to_projection);

		/**
		 Renders the occluders of the scene.

		 @param[in]		scene
						A reference to the scene.
		 @param[in]		world_to_camera
						The world-to-camera transformation matrix.
		 @param[in]		camera_to_projection
						The camera-to-projection transformation matrix.
		 @throws		Exception
						Failed to render the scene.
		 */
		void XM_CALLCONV RenderOccluders(const Scene &scene,
										 FXMMATRIX world_to_camera,
										 CXMMATRIX camera_to_projection);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the shaders for opaque models.
		 */
		void BindOpaqueShaders() const noexcept;
		
		/**
		 Binds the shaders for transparent models.
		 */
		void BindTransparentShaders() const noexcept;

		/**
		 Binds the camera of this depth pass.

		 @param[in]		world_to_camera
						The world-to-camera transformation matrix.
		 @param[in]		camera_to_projection
						The camera-to-projection transformation matrix.
		 @throws		Exception
						Failed to bind the camera of this depth pass.
		 */
		void XM_CALLCONV BindCamera(FXMMATRIX world_to_camera, 
									CXMMATRIX camera_to_projection);

		/**
		 Renders the given opaque model.

		 @param[in]		model
						A reference to the opaque model.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 */
		void XM_CALLCONV RenderOpaque(const Model &model, 
									  FXMMATRIX world_to_projection) const noexcept;

		/**
		 Renders the given transparent model.

		 @param[in]		model
						A reference to the transparent model.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 */
		void XM_CALLCONV RenderTransparent(const Model &model, 
										   FXMMATRIX world_to_projection) const noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this depth pass.
		 */
		ID3D11DeviceContext * const m_device_context;

		/**
		 A pointer to the vertex shader of this depth pass.
		 */
		const VertexShaderPtr m_opaque_vs;

		/**
		 A pointer to the vertex shader for transparent models
		 of this depth pass.
		 */
		const VertexShaderPtr m_transparent_vs;

		/**
		 A pointer to the pixel shader for transparent models
		 of this depth pass.
		 */
		const PixelShaderPtr m_transparent_ps;

		/**
		 The camera buffer of this depth pass.
		 */
		ConstantBuffer< SecondaryCameraBuffer > m_camera_buffer;
	};
}