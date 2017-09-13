#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of image passes for rendering images to screen 
	 (while optionally transferring depth values as well).
	 */
	class ImagePass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the image pass associated with the current engine.

		 @pre			The image pass associated with the 
						current engine must be loaded.
		 @return		A pointer to the image pass associated
						with the current engine.
		 */
		static ImagePass *Get();

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
		ImagePass();

		/**
		 Constructs a Image pass from the given Image pass.

		 @param[in]		render_pass
						A reference to the Image pass to copy.
		 */
		ImagePass(const ImagePass &render_pass) = delete;

		/**
		 Constructs a Image pass by moving the given Image pass.

		 @param[in]		render_pass
						A reference to the Image pass to move.
		 */
		ImagePass(ImagePass &&render_pass);

		/**
		 Destructs this Image pass.
		 */
		~ImagePass();

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
		ImagePass &operator=(const ImagePass &render_pass) = delete;

		/**
		 Moves the given Image pass to this Image pass.

		 @param[in]		render_pass
						A reference to the Image pass to move.
		 @return		A reference to the moved Image pass
						(i.e. this Image pass).
		 */
		ImagePass &operator=(ImagePass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this image pass.

		 @param[in]		transfer_depth
						@c true if the depth values need to be transferred
						as well. @c false otherwise.
		 @throws		FormattedException
						Failed to bind the fixed state of this image pass.
		 */
		void BindFixedState(bool transfer_depth = true);

		/**
		 Render.
		 */
		void Render() const noexcept;
		
	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this image pass.
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 A pointer to the vertex shader of this image pass.
		 */
		const SharedPtr< const VertexShader > m_vs;

		/**
		 A pointer to the pixel shader of this image pass.
		 */
		const SharedPtr< const PixelShader > m_image_ps;

		/**
		 A pointer to the pixel shader of this image pass.
		 */
		const SharedPtr< const PixelShader > m_image_depth_ps;
	};
}