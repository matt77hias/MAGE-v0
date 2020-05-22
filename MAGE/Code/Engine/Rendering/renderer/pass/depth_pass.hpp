#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\state_manager.hpp"
#include "resource\rendering_resource_manager.hpp"
#include "scene\rendering_world.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	/**
	 A class of depth passes for rendering models to a depth buffer only.
	 */
	class DepthPass {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a depth pass.

		 @param[in,out]	device
						A reference to the device.
		 @param[in,out]	device_context
						A reference to the device context.
		 @param[in,out]	state_manager
						A reference to the state manager.
		 @param[in,out]	resource_manager
						A reference to the resource manager.
		 */
		explicit DepthPass(ID3D11Device& device,
						   ID3D11DeviceContext& device_context,
						   StateManager& state_manager,
						   ResourceManager& resource_manager);

		/**
		 Constructs a depth pass from the given depth pass.

		 @param[in]		pass
						A reference to the depth pass to copy.
		 */
		DepthPass(const DepthPass& pass) = delete;

		/**
		 Constructs a depth pass by moving the given depth pass.

		 @param[in]		pass
						A reference to the depth pass to move.
		 */
		DepthPass(DepthPass&& pass) noexcept;

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
		DepthPass& operator=(const DepthPass& pass) = delete;

		/**
		 Moves the given depth pass to this depth pass.

		 @param[in]		pass
						A reference to the depth pass to move.
		 @return		A reference to the moved depth pass (i.e. this depth
						pass).
		 */
		DepthPass& operator=(DepthPass&& pass) noexcept;

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
		 Renders the world.

		 @param[in]		world
						A reference to the world.
		 @param[in]		world_to_camera
						The world-to-camera transformation matrix.
		 @param[in]		camera_to_projection
						The camera-to-projection transformation matrix.
		 @throws		Exception
						Failed to render the world.
		 */
		void XM_CALLCONV Render(const World& world,
								FXMMATRIX world_to_camera,
								CXMMATRIX camera_to_projection);

		/**
		 Renders the occluders of the world.

		 @param[in]		world
						A reference to the world.
		 @param[in]		world_to_camera
						The world-to-camera transformation matrix.
		 @param[in]		camera_to_projection
						The camera-to-projection transformation matrix.
		 @throws		Exception
						Failed to render the world.
		 */
		void XM_CALLCONV RenderOccluders(const World& world,
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
		void XM_CALLCONV RenderOpaque(const Model& model,
									  FXMMATRIX world_to_projection) const noexcept;

		/**
		 Renders the given transparent model.

		 @param[in]		model
						A reference to the transparent model.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 */
		void XM_CALLCONV RenderTransparent(const Model& model,
										   FXMMATRIX world_to_projection) const noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to the device context of this depth pass.
		 */
		std::reference_wrapper< ID3D11DeviceContext > m_device_context;

		/**
		 A reference to the state manager of this depth pass.
		 */
		std::reference_wrapper< StateManager > m_state_manager;

		/**
		 A pointer to the vertex shader of this depth pass.
		 */
		VertexShaderPtr m_opaque_vs;

		/**
		 A pointer to the vertex shader for transparent models
		 of this depth pass.
		 */
		VertexShaderPtr m_transparent_vs;

		/**
		 A pointer to the pixel shader for transparent models
		 of this depth pass.
		 */
		PixelShaderPtr m_transparent_ps;

		/**
		 The camera buffer of this depth pass.
		 */
		ConstantBuffer< SecondaryCameraBuffer > m_camera_buffer;
	};
}