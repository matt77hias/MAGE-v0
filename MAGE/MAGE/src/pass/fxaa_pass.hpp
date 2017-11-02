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
	 A class of FXAA passes for performing AA.
	 */
	class FXAAPass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the FXAA pass associated with the current engine.

		 @pre			The scene renderer associated with the current engine 
						must be loaded.
		 @return		A pointer to the FXAA pass associated with the current
						engine.
		 */
		static FXAAPass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a FXAA pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		FXAAPass();

		/**
		 Constructs a FXAA pass from the given FXAA 
		 pass.

		 @param[in]		render_pass
						A reference to the FXAA pass to copy.
		 */
		FXAAPass(const FXAAPass &render_pass) = delete;

		/**
		 Constructs a FXAA pass by moving the given FXAA 
		 shading pass.

		 @param[in]		render_pass
						A reference to the FXAA pass to move.
		 */
		FXAAPass(FXAAPass &&render_pass);

		/**
		 Destructs this FXAA pass.
		 */
		~FXAAPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given FXAA pass to this FXAA pass.

		 @param[in]		render_pass
						A reference to the FXAA pass to copy.
		 @return		A reference to the copy of the given FXAA pass (i.e. 
						this FXAA pass).
		 */
		FXAAPass &operator=(const FXAAPass &render_pass) = delete;

		/**
		 Moves the given FXAA pass to this FXAA pass.

		 @param[in]		render_pass
						A reference to the FXAA pass to move.
		 @return		A reference to the moved FXAA pass (i.e. this FXAA 
						pass).
		 */
		FXAAPass &operator=(FXAAPass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this FXAA pass.
		 */
		void BindFixedState() const noexcept;

		/**
		 Render.

		 @param[in]		viewport
						A reference to the viewport.
		 @throws		FormattedException
						Failed to render the scene.
		 */
		void Render(const Viewport &viewport);
		
	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this FXAA pass.
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 A pointer to the compute shader of this FXAA pass.
		 */
		SharedPtr< const ComputeShader > m_cs;
	};
}