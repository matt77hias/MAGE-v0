#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\depth_pass.hpp"
#include "pass\gbuffer_pass.hpp"
#include "pass\deferred_shading_pass.hpp"
#include "pass\variable_shading_pass.hpp"
#include "pass\sprite_pass.hpp"
#include "pass\image_pass.hpp"

#include "pass\constant_shading_pass.hpp"
#include "pass\constant_component_pass.hpp"
#include "pass\variable_component_pass.hpp"
#include "pass\shading_normal_pass.hpp"
#include "pass\wireframe_pass.hpp"
#include "pass\bounding_volume_pass.hpp"

#include "buffer\gbuffer.hpp"
#include "buffer\lbuffer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of scene renderers.
	 */
	class SceneRenderer final {

	public:

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 Returns the scene renderer associated with the current engine.

		 @pre			The scene manager associated with the 
						current engine must be loaded.
		 @return		A pointer to the scene renderer associated
						with the current engine.
		 */
		static SceneRenderer *Get() noexcept;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a scene renderer.
		 */
		SceneRenderer();

		/**
		 Constructs a scene renderer from the given scene renderer.

		 @param[in]		scene_renderer
						A reference to the scene renderer to copy.
		 */
		SceneRenderer(const SceneRenderer &scene_renderer) = delete;

		/**
		 Constructs a scene renderer by moving the given scene renderer.

		 @param[in]		scene_renderer
						A reference to the scene renderer to move.
		 */
		SceneRenderer(SceneRenderer &&scene_renderer);

		/**
		 Destructs this scene renderer.
		 */
		~SceneRenderer();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given scene renderer to this scene renderer.

		 @param[in]		scene_renderer
						A reference to the scene renderer to copy.
		 @return		A reference to the copy of the given scene renderer
						(i.e. this scene renderer).
		 */
		SceneRenderer &operator=(const SceneRenderer &scene_renderer) = delete;

		/**
		 Moves the given scene renderer to this scene renderer.

		 @param[in]		scene_renderer
						A reference to the scene renderer to move.
		 @return		A reference to the moved scene renderer
						(i.e. this scene renderer).
		 */
		SceneRenderer &operator=(SceneRenderer &&scene_renderer) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Renders the given scene.

		 @pre			@a scene is not equal to @c nullptr.
		 @param[in]		scene
						A pointer to the scene.
		 @throws		FormattedException
						Failed to render the scene.
		 */
		void Render(const Scene *scene);

		//---------------------------------------------------------------------
		// Member Methods: Render Passes
		//---------------------------------------------------------------------

		/**
		 Returns the depth pass of this scene renderer.

		 @pre			The renderer associated with the
						current engine must be loaded.
		 @pre			The resource manager associated with the
						current engine must be loaded.
		 @return		A pointer to the depth pass 
						of this scene renderer.
		 */
		DepthPass *GetDepthPass() {
			if (!m_depth_pass) {
				m_depth_pass = MakeUnique< DepthPass >();
			}
			return m_depth_pass.get();
		}

		/**
		 Returns the GBuffer pass of this scene renderer.

		 @pre			The renderer associated with the
						current engine must be loaded.
		 @pre			The resource manager associated with the
						current engine must be loaded.
		 @return		A pointer to the GBuffer pass 
						of this scene renderer.
		 */
		GBufferPass *GetGBufferPass() {
			if (!m_gbuffer_pass) {
				m_gbuffer_pass = MakeUnique< GBufferPass >();
			}
			return m_gbuffer_pass.get();
		}

		/**
		 Returns the deferred shading pass of this scene renderer.

		 @pre			The renderer associated with the
						current engine must be loaded.
		 @pre			The resource manager associated with the
						current engine must be loaded.
		 @return		A pointer to the deferred shading pass 
						of this scene renderer.
		 */
		DeferredShadingPass *GetDeferredShadingPass() {
			if (!m_deferred_shading_pass) {
				m_deferred_shading_pass = MakeUnique< DeferredShadingPass >();
			}
			return m_deferred_shading_pass.get();
		}

		/**
		 Returns the variable shading pass of this scene renderer.

		 @pre			The renderer associated with the
						current engine must be loaded.
		 @pre			The resource manager associated with the
						current engine must be loaded.
		 @return		A pointer to the variable shading pass 
						of this scene renderer.
		 */
		VariableShadingPass *GetVariableShadingPass() {
			if (!m_variable_shading_pass) {
				m_variable_shading_pass = MakeUnique< VariableShadingPass >();
			}
			return m_variable_shading_pass.get();
		}

		/**
		 Returns the sprite pass of this scene renderer.

		 @pre			The renderer associated with the
						current engine must be loaded.
		 @pre			The resource manager associated with the
						current engine must be loaded.
		 @return		A pointer to the sprite pass 
						of this scene renderer.
		 */
		SpritePass *GetSpritePass() {
			if (!m_sprite_pass) {
				m_sprite_pass = MakeUnique< SpritePass >();
			}
			return m_sprite_pass.get();
		}

		/**
		 Returns the image pass of this scene renderer.

		 @pre			The renderer associated with the
						current engine must be loaded.
		 @pre			The resource manager associated with the
						current engine must be loaded.
		 @return		A pointer to the image pass 
						of this scene renderer.
		 */
		ImagePass *GetImagePass() {
			if (!m_image_pass) {
				m_image_pass = MakeUnique< ImagePass >();
			}
			return m_image_pass.get();
		}

		/**
		 Returns the constant shading pass of this scene renderer.

		 @pre			The renderer associated with the
						current engine must be loaded.
		 @pre			The resource manager associated with the
						current engine must be loaded.
		 @return		A pointer to the constant shading pass 
						of this scene renderer.
		 */
		ConstantShadingPass *GetConstantShadingPass() {
			if (!m_constant_shading_pass) {
				m_constant_shading_pass = MakeUnique< ConstantShadingPass >();
			}
			return m_constant_shading_pass.get();
		}

		/**
		 Returns the constant component pass of this scene renderer.

		 @pre			The renderer associated with the
						current engine must be loaded.
		 @pre			The resource manager associated with the
						current engine must be loaded.
		 @return		A pointer to the constant component pass 
						of this scene renderer.
		 */
		ConstantComponentPass *GetConstantComponentPass() {
			if (!m_constant_component_pass) {
				m_constant_component_pass = MakeUnique< ConstantComponentPass >();
			}
			return m_constant_component_pass.get();
		}

		/**
		 Returns the variable component pass of this scene renderer.

		 @pre			The renderer associated with the
						current engine must be loaded.
		 @pre			The resource manager associated with the
						current engine must be loaded.
		 @return		A pointer to the variable component pass 
						of this scene renderer.
		 */
		VariableComponentPass *GetVariableComponentPass() {
			if (!m_variable_component_pass) {
				m_variable_component_pass = MakeUnique< VariableComponentPass >();
			}
			return m_variable_component_pass.get();
		}

		/**
		 Returns the shading normal pass of this scene renderer.

		 @pre			The renderer associated with the
						current engine must be loaded.
		 @pre			The resource manager associated with the
						current engine must be loaded.
		 @return		A pointer to the shading normal pass 
						of this scene renderer.
		 */
		ShadingNormalPass *GetShadingNormalPass() {
			if (!m_shading_normal_pass) {
				m_shading_normal_pass = MakeUnique< ShadingNormalPass >();
			}
			return m_shading_normal_pass.get();
		}

		/**
		 Returns the wireframe pass of this scene renderer.

		 @pre			The renderer associated with the
						current engine must be loaded.
		 @pre			The resource manager associated with the
						current engine must be loaded.
		 @return		A pointer to the wireframe pass 
						of this scene renderer.
		 */
		WireframePass *GetWireframePass() {
			if (!m_wireframe_pass) {
				m_wireframe_pass = MakeUnique< WireframePass >();
			}
			return m_wireframe_pass.get();
		}

		/**
		 Returns the bounding volume pass of this scene renderer.

		 @pre			The renderer associated with the
						current engine must be loaded.
		 @pre			The resource manager associated with the
						current engine must be loaded.
		 @return		A pointer to the bounding volume pass 
						of this scene renderer.
		 */
		BoundingVolumePass *GetBoundingVolumePass() {
			if (!m_bounding_volume_pass) {
				m_bounding_volume_pass = MakeUnique< BoundingVolumePass >();
			}
			return m_bounding_volume_pass.get();
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void ExecuteDepthPass(
			FXMMATRIX world_to_projection,
			CXMMATRIX world_to_view, 
			CXMMATRIX view_to_projection);

		void ExecuteSolidForwardPipeline(
			const Viewport &viewport,
			FXMMATRIX world_to_projection,
			CXMMATRIX world_to_view,
			CXMMATRIX view_to_world,
			CXMMATRIX view_to_projection);

		void ExecuteForwardPipeline(
			const Viewport &viewport,
			FXMMATRIX world_to_projection,
			CXMMATRIX world_to_view,
			CXMMATRIX view_to_world,
			CXMMATRIX view_to_projection,
			BRDFType brdf);

		void ExecuteDeferredPipeline(
			const Viewport &viewport,
			FXMMATRIX world_to_projection,
			CXMMATRIX world_to_view,
			CXMMATRIX view_to_world,
			CXMMATRIX view_to_projection,
			BRDFType brdf);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this scene renderer.
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 The maximum viewport of this scene renderer.
		 */
		Viewport m_maximum_viewport;

		/**
		 A pointer to the pass buffer of this scene renderer.
		 */
		UniquePtr< PassBuffer > m_pass_buffer;
		
		/**
		 A pointer to the Gbuffer of this scene renderer.
		 */
		UniquePtr< GBuffer > m_gbuffer;
		
		/**
		 A pointer to the Lbuffer of this scene renderer.
		 */
		UniquePtr< LBuffer > m_lbuffer;

		//---------------------------------------------------------------------
		// Member Variables: Render Passes
		//---------------------------------------------------------------------

		/**
		 A pointer to the depth pass of this scene renderer.
		 */
		UniquePtr< DepthPass > m_depth_pass;

		/**
		 A pointer to the GBuffer pass of this scene renderer.
		 */
		UniquePtr< GBufferPass >  m_gbuffer_pass;

		/**
		 A pointer to the deferred shading pass of this scene renderer.
		 */
		UniquePtr< DeferredShadingPass > m_deferred_shading_pass;

		/**
		 A pointer to the variable shading pass of this scene renderer.
		 */
		UniquePtr< VariableShadingPass > m_variable_shading_pass;

		/**
		 A pointer to the sprite pass of this scene renderer.
		 */
		UniquePtr< SpritePass > m_sprite_pass;

		/**
		 A pointer to the image pass of this scene renderer.
		 */
		UniquePtr< ImagePass > m_image_pass;
		
		/**
		 A pointer to the constant shading pass of this scene renderer.
		 */
		UniquePtr< ConstantShadingPass > m_constant_shading_pass;

		/**
		 A pointer to the constant component pass of this scene renderer.
		 */
		UniquePtr< ConstantComponentPass > m_constant_component_pass;

		/**
		 A pointer to the variable component pass of this scene renderer.
		 */
		UniquePtr< VariableComponentPass > m_variable_component_pass;

		/**
		 A pointer to the shading normal pass of this scene renderer.
		 */
		UniquePtr< ShadingNormalPass > m_shading_normal_pass;
		
		/**
		 A pointer to the wireframe pass of this scene renderer.
		 */
		UniquePtr< WireframePass > m_wireframe_pass;

		/**
		 A pointer to the bounding volume pass of this scene renderer.
		 */
		UniquePtr< BoundingVolumePass > m_bounding_volume_pass;
	};
}