#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\pass_buffer.hpp"
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

		 @pre			The scene renderer associated with the 
						current engine must be loaded.
		 @return		A pointer to the sky pass associated
						with the current engine.
		 */
		static SkyPass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a Image pass.

		 @pre			The renderer associated with the
						current engine must be loaded.
		 @pre			The resource manager associated with the
						current engine must be loaded.
		 */
		SkyPass();

		/**
		 Constructs a Image pass from the given Image pass.

		 @param[in]		render_pass
						A reference to the Image pass to copy.
		 */
		SkyPass(const SkyPass &render_pass) = delete;

		/**
		 Constructs a Image pass by moving the given Image pass.

		 @param[in]		render_pass
						A reference to the Image pass to move.
		 */
		SkyPass(SkyPass &&render_pass);

		/**
		 Destructs this Image pass.
		 */
		~SkyPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given Image pass to this Image pass.

		 @param[in]		render_pass
						A reference to the Image pass to copy.
		 @return		A reference to the copy of the given Image pass
						(i.e. this Image pass).
		 */
		SkyPass &operator=(const SkyPass &render_pass) = delete;

		/**
		 Moves the given Image pass to this Image pass.

		 @param[in]		render_pass
						A reference to the Image pass to move.
		 @return		A reference to the moved Image pass
						(i.e. this Image pass).
		 */
		SkyPass &operator=(SkyPass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this sky pass.

		 @param[in]		view_to_world
						The view-to-world transformation matrix.
		 @param[in]		view_to_projection
						The view-to-projection transformation matrix.
		 @throws		FormattedException
						Failed to bind the fixed state of this sky pass.
		 */
		void XM_CALLCONV BindFixedState(
			const PassBuffer *scene,
			FXMMATRIX view_to_world,
			CXMMATRIX view_to_projection);

		/**
		 Render.
		 */
		void Render() const noexcept;
		
	private:

		//---------------------------------------------------------------------
		// Bind Variables
		//---------------------------------------------------------------------



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
		const SharedPtr< const VertexShader > m_vs;

		/**
		 A pointer to the pixel shader of this sky pass.
		 */
		const SharedPtr< const PixelShader > m_sky_ps;
	};
}