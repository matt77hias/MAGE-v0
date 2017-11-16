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
	 A class of back buffer passes for tone mapping and gamma correcting HDR 
	 images.
	 */
	class BackBufferPass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the back buffer pass associated with the current engine.

		 @pre			The scene renderer associated with the current engine 
						must be loaded.
		 @return		A pointer to the back buffer pass associated with the 
						current engine.
		 */
		static BackBufferPass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an back buffer pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		BackBufferPass();

		/**
		 Constructs an back buffer pass from the given back buffer pass.

		 @param[in]		render_pass
						A reference to the back buffer pass to copy.
		 */
		BackBufferPass(const BackBufferPass &render_pass) = delete;

		/**
		 Constructs an back buffer pass by moving the given back buffer pass.

		 @param[in]		render_pass
						A reference to the Image pass to move.
		 */
		BackBufferPass(BackBufferPass &&render_pass);

		/**
		 Destructs this back buffer pass.
		 */
		~BackBufferPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given back buffer pass to this back buffer pass.

		 @param[in]		render_pass
						A reference to the back buffer pass to copy.
		 @return		A reference to the copy of the given back buffer pass 
						(i.e. this back buffer pass).
		 */
		BackBufferPass &operator=(const BackBufferPass &render_pass) = delete;

		/**
		 Moves the given back buffer pass to this back buffer pass.

		 @param[in]		render_pass
						A reference to the back buffer pass to move.
		 @return		A reference to the moved back buffer pass (i.e. this 
						back buffer pass).
		 */
		BackBufferPass &operator=(BackBufferPass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this back buffer pass.

		 @throws		FormattedException
						Failed to bind the fixed state of this back buffer 
						pass.
		 */
		void BindFixedState();

		/**
		 Renders.
		 */
		void Render() const noexcept;
		
	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this back buffer pass.
		 */
		ID3D11DeviceContext4 * const m_device_context;

		/**
		 A pointer to the vertex shader of this back buffer pass.
		 */
		const SharedPtr< const VertexShader > m_vs;

		/**
		 A pointer to the pixel shader of this back buffer pass.
		 */
		const SharedPtr< const PixelShader > m_ps;
	};
}