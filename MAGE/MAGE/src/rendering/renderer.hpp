#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\pass\aa_pass.hpp"
#include "rendering\pass\back_buffer_pass.hpp"
#include "rendering\pass\bounding_volume_pass.hpp"
#include "rendering\pass\deferred_pass.hpp"
#include "rendering\pass\depth_pass.hpp"
#include "rendering\pass\dof_pass.hpp"
#include "rendering\pass\forward_pass.hpp"
#include "rendering\pass\gbuffer_pass.hpp"
#include "rendering\pass\lbuffer_pass.hpp"
#include "rendering\pass\sky_pass.hpp"
#include "rendering\pass\solid_pass.hpp"
#include "rendering\pass\sprite_pass.hpp"
#include "rendering\pass\voxelization_pass.hpp"
#include "rendering\pass\wireframe_pass.hpp"
#include "rendering\buffer\game_buffer.hpp"
#include "rendering\buffer\camera_buffer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of renderers.
	 */
	class Renderer final {

	public:

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 Returns the renderer of the rendering manager associated with the 
		 current engine.

		 @pre			The rendering manager associated with the current 
						engine must be loaded.
		 @return		A pointer to the renderer of the rendering manager 
						associated with the current engine.
		 */
		[[nodiscard]] static Renderer *Get() noexcept;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a renderer.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 */
		explicit Renderer(ID3D11Device *device, 
			              ID3D11DeviceContext *device_context);

		/**
		 Constructs a renderer from the given renderer.

		 @param[in]		renderer
						A reference to the renderer to copy.
		 */
		Renderer(const Renderer &renderer) = delete;

		/**
		 Constructs a renderer by moving the given renderer.

		 @param[in]		renderer
						A reference to the renderer to move.
		 */
		Renderer(Renderer &&renderer) noexcept;

		/**
		 Destructs this renderer.
		 */
		~Renderer();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given renderer to this renderer.

		 @param[in]		renderer
						A reference to the renderer to copy.
		 @return		A reference to the copy of the given renderer (i.e. 
						this renderer).
		 */
		Renderer &operator=(const Renderer &renderer) = delete;

		/**
		 Moves the given renderer to this renderer.

		 @param[in]		renderer
						A reference to the renderer to move.
		 @return		A reference to the moved renderer (i.e. this renderer).
		 */
		Renderer &operator=(Renderer &&renderer) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the persistent state of this renderer.

		 @throws		Exception
						Failed to bind the persistent state of this renderer.
		 */
		void BindPersistentState();

		/**
		 Renders the given scene.

		 @param[in]		scene
						A reference to the scene.
		 @throws		Exception
						Failed to render the scene.
		 */
		void Render(const Scene &scene);

		//---------------------------------------------------------------------
		// Member Methods: Render Passes
		//---------------------------------------------------------------------

		/**
		 Returns the AA pass of this renderer.

		 @pre			The rendering manager associated with the current 
						engine must be loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 @return		A pointer to the AA pass of this renderer.
		 */
		AAPass *GetAAPass() {
			if (!m_aa_pass) {
				m_aa_pass = MakeUnique< AAPass >();
			}
			return m_aa_pass.get();
		}

		/**
		 Returns the back buffer pass of this renderer.

		 @pre			The rendering manager associated with the current 
						engine must be loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 @return		A pointer to the back buffer pass of this renderer.
		 */
		BackBufferPass *GetBackBufferPass() {
			if (!m_back_buffer_pass) {
				m_back_buffer_pass = MakeUnique< BackBufferPass >();
			}
			return m_back_buffer_pass.get();
		}

		/**
		 Returns the bounding volume pass of this renderer.

		 @pre			The rendering manager associated with the current 
						engine must be loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 @return		A pointer to the bounding volume pass of this scene 
						renderer.
		 */
		BoundingVolumePass *GetBoundingVolumePass() {
			if (!m_bounding_volume_pass) {
				m_bounding_volume_pass = MakeUnique< BoundingVolumePass >();
			}
			return m_bounding_volume_pass.get();
		}

		/**
		 Returns the deferred pass of this renderer.

		 @pre			The rendering manager associated with the current 
						engine must be loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 @return		A pointer to the deferred pass of this renderer.
		 */
		DeferredShadingPass *GetDeferredPass() {
			if (!m_deferred_shading_pass) {
				m_deferred_shading_pass = MakeUnique< DeferredShadingPass >();
			}
			return m_deferred_shading_pass.get();
		}

		/**
		 Returns the depth pass of this renderer.

		 @pre			The rendering manager associated with the current 
						engine must be loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 @return		A pointer to the depth pass of this renderer.
		 */
		DepthPass *GetDepthPass() {
			if (!m_depth_pass) {
				m_depth_pass = MakeUnique< DepthPass >();
			}
			return m_depth_pass.get();
		}

		/**
		 Returns the depth-of-field pass of this renderer.

		 @pre			The rendering manager associated with the current 
						engine must be loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 @return		A pointer to the depth-of-field pass of this renderer.
		 */
		DOFPass *GetDOFPass() {
			if (!m_dof_pass) {
				m_dof_pass = MakeUnique< DOFPass >();
			}
			return m_dof_pass.get();
		}

		/**
		 Returns the forward pass of this renderer.

		 @pre			The rendering manager associated with the current 
						engine must be loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 @return		A pointer to the forward pass of this renderer.
		 */
		ForwardPass *GetForwardPass() {
			if (!m_forward_pass) {
				m_forward_pass = MakeUnique< ForwardPass >();
			}
			return m_forward_pass.get();
		}

		/**
		 Returns the GBuffer pass of this renderer.

		 @pre			The rendering manager associated with the current 
						engine must be loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 @return		A pointer to the GBuffer pass of this renderer.
		 */
		GBufferPass *GetGBufferPass() {
			if (!m_gbuffer_pass) {
				m_gbuffer_pass = MakeUnique< GBufferPass >();
			}
			return m_gbuffer_pass.get();
		}

		/**
		 Returns the LBuffer pass of this renderer.

		 @pre			The rendering manager associated with the current 
						engine must be loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 @return		A pointer to the LBuffer pass of this renderer.
		 */
		LBufferPass *GetLBufferPass() {
			if (!m_lbuffer_pass) {
				m_lbuffer_pass = MakeUnique< LBufferPass >();
			}
			return m_lbuffer_pass.get();
		}

		/**
		 Returns the sky pass of this renderer.

		 @pre			The rendering manager associated with the current 
						engine must be loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 @return		A pointer to the sky pass of this renderer.
		 */
		SkyPass *GetSkyPass() {
			if (!m_sky_pass) {
				m_sky_pass = MakeUnique< SkyPass >();
			}
			return m_sky_pass.get();
		}

		/**
		 Returns the solid pass of this renderer.

		 @pre			The rendering manager associated with the current 
						engine must be loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 @return		A pointer to the solid pass of this renderer.
		 */
		SolidPass *GetSolidPass() {
			if (!m_solid_pass) {
				m_solid_pass = MakeUnique< SolidPass >();
			}
			return m_solid_pass.get();
		}

		/**
		 Returns the sprite pass of this renderer.

		 @pre			The rendering manager associated with the current 
						engine must be loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 @return		A pointer to the sprite pass of this renderer.
		 */
		SpritePass *GetSpritePass() {
			if (!m_sprite_pass) {
				m_sprite_pass = MakeUnique< SpritePass >();
			}
			return m_sprite_pass.get();
		}

		/**
		 Returns the voxelization pass of this renderer.

		 @pre			The rendering manager associated with the current 
						engine must be loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 @return		A pointer to the voxelization pass of this renderer.
		 */
		VoxelizationPass *GetVoxelizationPass() {
			if (!m_voxelization_pass) {
				m_voxelization_pass = MakeUnique< VoxelizationPass >();
			}
			return m_voxelization_pass.get();
		}

		/**
		 Returns the wireframe pass of this renderer.

		 @pre			The rendering manager associated with the current 
						engine must be loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 @return		A pointer to the wireframe pass of this renderer.
		 */
		WireframePass *GetWireframePass() {
			if (!m_wireframe_pass) {
				m_wireframe_pass = MakeUnique< WireframePass >();
			}
			return m_wireframe_pass.get();
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void UpdateBuffers(const Scene &scene) const;
		
		void Render(const Scene &scene, const Camera &camera);
		
		void XM_CALLCONV RenderForward(const Scene &scene, 
									   const Camera &camera, 
									   FXMMATRIX world_to_projection);
		
		void XM_CALLCONV RenderDeferred(const Scene &scene, 
										const Camera &camera, 
										FXMMATRIX world_to_projection);
		
		void XM_CALLCONV RenderSolid(const Scene &scene, 
									 const Camera &camera, 
									 FXMMATRIX world_to_projection);
		
		void XM_CALLCONV RenderVoxelization(const Scene &scene, 
											const Camera &camera, 
											FXMMATRIX world_to_projection);
		
		void XM_CALLCONV RenderFalseColor(const Scene &scene, 
										  const Camera &camera, 
										  FXMMATRIX world_to_projection);
		
		void RenderAA(const Camera &camera);
		
		void RenderPostProcessing(const Camera &camera);
		
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this renderer.
		 */
		ID3D11DeviceContext * const m_device_context;

		/**
		 A pointer to the game buffer of this renderer.
		 */
		ConstantBuffer< GameBuffer > m_game_buffer;

		//---------------------------------------------------------------------
		// Member Variables: Render Passes
		//---------------------------------------------------------------------

		/**
		 A pointer to the AA pass of this renderer.
		 */
		UniquePtr< AAPass > m_aa_pass;

		/**
		 A pointer to the back buffer pass of this renderer.
		 */
		UniquePtr< BackBufferPass > m_back_buffer_pass;

		/**
		 A pointer to the bounding volume pass of this renderer.
		 */
		UniquePtr< BoundingVolumePass > m_bounding_volume_pass;

		/**
		 A pointer to the deferred pass of this renderer.
		 */
		UniquePtr< DeferredPass > m_deferred_pass;

		/**
		 A pointer to the depth pass of this renderer.
		 */
		UniquePtr< DepthPass > m_depth_pass;

		/**
		 A pointer to the depth-of-field pass of this renderer.
		 */
		UniquePtr< DOFPass > m_dof_pass;

		/**
		 A pointer to the forward pass of this renderer.
		 */
		UniquePtr< ForwardPass > m_forward_pass;

		/**
		 A pointer to the GBuffer pass of this renderer.
		 */
		UniquePtr< GBufferPass >  m_gbuffer_pass;

		/**
		 A pointer to the LBuffer pass of this renderer.
		 */
		UniquePtr< LBufferPass >  m_lbuffer_pass;

		/**
		 A pointer to the sky pass of this renderer.
		 */
		UniquePtr< SkyPass > m_sky_pass;

		/**
		 A pointer to the solid pass of this renderer.
		 */
		UniquePtr< SolidPass > m_solid_pass;

		/**
		 A pointer to the sprite pass of this renderer.
		 */
		UniquePtr< SpritePass > m_sprite_pass;

		/**
		 A pointer to the voxelization pass of this renderer.
		 */
		UniquePtr< VoxelizationPass > m_voxelization_pass;

		/**
		 A pointer to the wireframe pass of this renderer.
		 */
		UniquePtr< WireframePass > m_wireframe_pass;
	};
}