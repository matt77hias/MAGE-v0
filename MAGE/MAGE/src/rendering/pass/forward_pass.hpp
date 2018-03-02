#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "rendering\false_color.hpp"
#include "rendering\state_manager.hpp"
#include "rendering\resource_manager.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of forward passes for performing light calculations.
	 */
	class ForwardPass final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a forward pass.

		 @param[in]		device
						A reference to the device.
		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		state_manager
						A reference to the state manager.
		 @param[in]		resource_manager
						A reference to the resource manager.
		 */
		explicit ForwardPass(ID3D11Device& device, 
							 ID3D11DeviceContext& device_context, 
							 StateManager& state_manager, 
							 ResourceManager& resource_manager);

		/**
		 Constructs a forward pass from the given variable shading 
		 pass.

		 @param[in]		pass
						A reference to the forward pass to copy.
		 */
		ForwardPass(const ForwardPass& pass) = delete;

		/**
		 Constructs a forward pass by moving the given variable 
		 pass.

		 @param[in]		pass
						A reference to the forward pass to move.
		 */
		ForwardPass(ForwardPass&& pass) noexcept;

		/**
		 Destructs this forward pass.
		 */
		~ForwardPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given forward pass to this forward pass.

		 @param[in]		pass
						A reference to the forward pass to copy.
		 @return		A reference to the copy of the given variable shading 
						pass (i.e. this forward pass).
		 */
		ForwardPass& operator=(const ForwardPass& pass) = delete;

		/**
		 Moves the given forward pass to this forward pass.

		 @param[in]		pass
						A reference to the forward pass to move.
		 @return		A reference to the moved forward pass (i.e. this 
						forward pass).
		 */
		ForwardPass& operator=(ForwardPass&& pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Renders the given scene.

		 @param[in]		scene
						A reference to the scene.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @param[in]		brdf
						The BRDF.
		 @param[in]		vct
						@c true if voxel cone tracing should be enabled. @c false 
						otherwise.
		 @throws		Exception
						Failed to render the scene.
		 */
		void XM_CALLCONV Render(const Scene& scene,
								FXMMATRIX world_to_projection,
								BRDFType brdf, bool vct) const;

		/**
		 Renders the given scene as solid.

		 @param[in]		scene
						A reference to the scene.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @throws		Exception
						Failed to render the scene.
		 */
		void XM_CALLCONV RenderSolid(const Scene& scene, 
									 FXMMATRIX world_to_projection) const;

		/**
		 Renders the given scene to a GBuffer.

		 @param[in]		scene
						A reference to the scene.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @throws		Exception
						Failed to render the scene.
		 */
		void XM_CALLCONV RenderGBuffer(const Scene& scene, 
									   FXMMATRIX world_to_projection) const;

		/**
		 Renders the emissive models of the given scene.

		 @param[in]		scene
						A reference to the scene.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @throws		Exception
						Failed to render the scene.
		 */
		void XM_CALLCONV RenderEmissive(const Scene& scene,
										FXMMATRIX world_to_projection) const;

		/**
		 Renders the transparent models of the given scene.

		 @param[in]		scene
						A reference to the scene.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @param[in]		brdf
						The BRDF.
		 @param[in]		vct
						@c true if voxel cone tracing should be enabled. @c false 
						otherwise.
		 @throws		Exception
						Failed to render the scene.
		 */
		void XM_CALLCONV RenderTransparent(const Scene& scene,
										   FXMMATRIX world_to_projection,
										   BRDFType brdf, bool vct) const;
		
		/**
		 Renders the given scene as a false color.

		 @param[in]		scene
						A reference to the scene.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @param[in]		false_color
						The false color.
		 @throws		Exception
						Failed to render the scene.
		 */
		void XM_CALLCONV RenderFalseColor(const Scene& scene,
										  FXMMATRIX world_to_projection,
										  FalseColor false_color) const;

		/**
		 Renders the given scene as a wireframe.

		 @param[in]		scene
						A reference to the scene.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @throws		Exception
						Failed to render the scene.
		 */
		void XM_CALLCONV RenderWireframe(const Scene& scene, 
										 FXMMATRIX world_to_projection);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed opaque state of this forward pass.
		 */
		void BindFixedOpaqueState() const noexcept;

		/**
		 Binds the fixed transparent state of this forward pass.
		 */
		void BindFixedTransparentState() const noexcept;

		/**
		 Binds the fixed wireframe state of this forward pass.
		 */
		void BindFixedWireframeState() const noexcept;

		/**
		 Binds the color data of this forward pass.

		 @param[in]		color
						A reference to the color (in in linear space).
		 @throws		Exception
						Failed to bind the color data of this forward pass.
		 */
		void BindColor(const RGBA& color);

		/**
		 Renders the given model.

		 @param[in]		model
						A reference to the model.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 */
		void XM_CALLCONV Render(const Model& model,
								FXMMATRIX world_to_projection) const noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to the device context of this forward pass.
		 */
		std::reference_wrapper< ID3D11DeviceContext > m_device_context;

		/**
		 A reference to the state manager of this forward pass.
		 */
		std::reference_wrapper< StateManager > m_state_manager;

		/**
		 A reference to the resource manager of this forward pass.
		 */
		std::reference_wrapper< ResourceManager > m_resource_manager;

		/**
		 A pointer to the vertex shader of this forward pass.
		 */
		VertexShaderPtr m_vs;

		/**
		 A pointer to the UV reference texture of this forward pass. 
		 */
		TexturePtr m_uv;

		/**
		 The color buffer of this forward pass.
		 */
		ConstantBuffer< RGBA > m_color_buffer;
	};
}