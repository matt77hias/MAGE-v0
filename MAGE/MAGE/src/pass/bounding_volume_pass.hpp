#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\pass_buffer.hpp"
#include "buffer\constant_buffer.hpp"
#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of bounding volume passes for rendering model and finite light 
	 volumes.
	 */
	class BoundingVolumePass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the bounding volume pass associated with the current engine.

		 @pre			The scene renderer associated with the current engine 
						must be loaded.
		 @return		A pointer to the bounding volume pass associated with 
						the current engine.
		 */
		static BoundingVolumePass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a bounding volume pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		BoundingVolumePass();

		/**
		 Constructs a bounding volume pass from the given bounding volume pass.

		 @param[in]		render_pass
						A reference to the bounding volume pass to copy.
		 */
		BoundingVolumePass(const BoundingVolumePass &render_pass) = delete;

		/**
		 Constructs a bounding volume pass by moving the given bounding volume 
		 pass.

		 @param[in]		render_pass
						A reference to the bounding volume pass to move.
		 */
		BoundingVolumePass(BoundingVolumePass &&render_pass);

		/**
		 Destructs this bounding volume pass.
		 */
		~BoundingVolumePass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given bounding volume pass to this bounding volume pass.

		 @param[in]		render_pass
						A reference to the bounding volume pass to copy.
		 @return		A reference to the copy of the given bounding volume 
						pass (i.e. this bounding volume pass).
		 */
		BoundingVolumePass &operator=(
			const BoundingVolumePass &render_pass) = delete;

		/**
		 Moves the given bounding volume pass to this bounding volume pass.

		 @param[in]		render_pass
						A reference to the bounding volume pass to move.
		 @return		A reference to the moved bounding volume pass (i.e. 
						this bounding volume pass).
		 */
		BoundingVolumePass &operator=(
			BoundingVolumePass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this bounding volume pass.

		 @throws		FormattedException
						Failed to bind the fixed state of this bounding volume 
						pass.
		 */
		void BindFixedState();

		/**
		 Renders the scene.

		 @pre			@a scene is not equal to @c nullptr.
		 @param[in]		scene
						A pointer to the scene.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix.
		 @throws		FormattedException
						Failed to render the scene.
		 */
		void XM_CALLCONV Render(
			const PassBuffer *scene,
			FXMMATRIX world_to_projection);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the color data of this bounding volume pass.

		 @param[in]		color
						A reference to the color.
		 @throws		FormattedException
						Failed to bind the light color data of this bounding 
						volume pass.
		 */
		void BindColorData(const RGBASpectrum &color);

		/**
		 Binds the light color data of this bounding volume pass.

		 @throws		FormattedException
						Failed to bind the light color data of this bounding 
						volume pass.
		 */
		void BindLightColorData();

		/**
		 Binds the model color data of this bounding volume pass.
		 
		 @throws		FormattedException
						Failed to bind the model color data of this bounding 
						volume pass.
		 */
		void BindModelColorData();

		/**
		 Binds the model data of this bounding volume pass.

		 @param[in]		box_to_projection
						The box-to-projection transformation matrix used for
						transforming box vertices.
		 @throws		FormattedException
						Failed to bind the model data of this bounding volume 
						pass.
		 */
		void XM_CALLCONV BindModelData(FXMMATRIX box_to_projection);
		
		/**
		 Process the given omni lights.

		 @param[in]		lights
						A reference to a vector containing the light pointers
						to process.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix. This 
						transformation matrix will be used for culling and 
						transforming box vertices.
		 @throws		FormattedException
						Failed to process the lights.
		 */
		void XM_CALLCONV ProcessLights(
			const vector< const OmniLightNode * > &lights,
			FXMMATRIX world_to_projection);
		
		/**
		 Process the given spotlights.

		 @param[in]		lights
						A reference to a vector containing the light pointers
						to process.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix. This 
						transformation matrix will be used for culling and 
						transforming box vertices.
		 @throws		FormattedException
						Failed to process the lights.
		 */
		void XM_CALLCONV ProcessLights(
			const vector< const SpotLightNode * > &lights,
			FXMMATRIX world_to_projection);
		
		/**
		 Process the given models.

		 @param[in]		models
						A reference to a vector containing the model pointers
						to process.
		 @param[in]		world_to_projection
						The world-to-projection transformation matrix. This 
						transformation matrix will be used for culling and 
						transforming box vertices.
		 @throws		FormattedException
						Failed to process the models.
		 */
		void XM_CALLCONV ProcessModels(
			const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this bounding volume pass.
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 A pointer to the vertex shader of this bounding volume pass.
		 */
		const SharedPtr< const VertexShader > m_vs;

		/**
		 A pointer to the pixel shader of this bounding volume pass.
		 */
		const SharedPtr< const PixelShader > m_ps;

		/**
		 The color buffer of this bounding volume pass.
		 */
		ConstantBuffer< RGBASpectrum > m_color_buffer;

		/**
		 The model buffer of this bounding volume pass.
		 */
		ConstantBuffer< XMMATRIX > m_model_buffer;
	};
}
