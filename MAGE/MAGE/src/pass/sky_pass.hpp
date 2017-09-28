#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\pass_buffer.hpp"
#include "buffer\constant_buffer.hpp"
#include "buffer\sky_buffer.hpp"
#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of sky passes for rendering sky domes to screen.
	 */
	class SkyPass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the sky pass associated with the current engine.

		 @pre			The scene renderer associated with the current engine 
						must be loaded.
		 @return		A pointer to the sky pass associated with the current 
						engine.
		 */
		static SkyPass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sky pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		SkyPass();

		/**
		 Constructs a sky pass from the given sky pass.

		 @param[in]		render_pass
						A reference to the sky pass to copy.
		 */
		SkyPass(const SkyPass &render_pass) = delete;

		/**
		 Constructs a sky pass by moving the given sky pass.

		 @param[in]		render_pass
						A reference to the sky pass to move.
		 */
		SkyPass(SkyPass &&render_pass);

		/**
		 Destructs this sky pass.
		 */
		~SkyPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sky pass to this sky pass.

		 @param[in]		render_pass
						A reference to the sky pass to copy.
		 @return		A reference to the copy of the given sky pass (i.e. 
						this sky pass).
		 */
		SkyPass &operator=(const SkyPass &render_pass) = delete;

		/**
		 Moves the given sky pass to this sky pass.

		 @param[in]		render_pass
						A reference to the sky pass to move.
		 @return		A reference to the moved sky pass (i.e. this sky pass).
		 */
		SkyPass &operator=(SkyPass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this sky pass.
		 */
		void BindFixedState() const noexcept;

		/**
		 Renders the given scene.

		 @pre			@a scene is not equal to @c nullptr.
		 @param[in]		scene
						A pointer to the scene.
		 @param[in]		view_to_world
						The view-to-world transformation matrix.
		 @param[in]		view_to_projection
						The view-to-projection transformation matrix.
		 @throws		FormattedException
						Failed to render the scene.
		 */
		void XM_CALLCONV Render(const PassBuffer *scene,
			FXMMATRIX view_to_world,
			CXMMATRIX view_to_projection);
		
	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the transform data of this sky pass.

		 @param[in]		view_to_world
						The view-to-world transformation matrix.
		 @param[in]		view_to_projection
						The view-to-projection transformation matrix.
		 @throws		FormattedException
						Failed to bind the transform data of this sky.
		 */
		void XM_CALLCONV BindTransformData(
			FXMMATRIX view_to_world,
			CXMMATRIX view_to_projection);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this sky pass.
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 A pointer to the vertex shader of this sky pass.
		 */
		const SharedPtr< const VertexShader > m_sky_vs;

		/**
		 A pointer to the pixel shader of this sky pass.
		 */
		const SharedPtr< const PixelShader > m_sky_ps;

		/**
		 The transform buffer of this sky pass.
		 */
		ConstantBuffer< SkyBuffer > m_transform_buffer;
	};
}