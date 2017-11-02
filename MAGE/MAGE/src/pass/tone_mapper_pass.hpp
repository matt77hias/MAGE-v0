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
	 A class of tone mapper passes for performing AA.
	 */
	class ToneMapperPass final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the tone mapper pass associated with the current engine.

		 @pre			The scene renderer associated with the current engine 
						must be loaded.
		 @return		A pointer to the tone mapper pass associated with the 
						current engine.
		 */
		static ToneMapperPass *Get();

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a tone mapper pass.

		 @pre			The renderer associated with the current engine must be 
						loaded.
		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		ToneMapperPass();

		/**
		 Constructs a tone mapper pass from the given tone mapper 
		 pass.

		 @param[in]		render_pass
						A reference to the tone mapper pass to copy.
		 */
		ToneMapperPass(const ToneMapperPass &render_pass) = delete;

		/**
		 Constructs a tone mapper pass by moving the given ToneMapper 
		 shading pass.

		 @param[in]		render_pass
						A reference to the tone mapper pass to move.
		 */
		ToneMapperPass(ToneMapperPass &&render_pass);

		/**
		 Destructs this tone mapper pass.
		 */
		~ToneMapperPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given tone mapper pass to this tone mapper pass.

		 @param[in]		render_pass
						A reference to the tone mapper pass to copy.
		 @return		A reference to the copy of the given tone mapper pass 
						(i.e. this tone mapper pass).
		 */
		ToneMapperPass &operator=(const ToneMapperPass &render_pass) = delete;

		/**
		 Moves the given tone mapper pass to this tone mapper pass.

		 @param[in]		render_pass
						A reference to the tone mapper pass to move.
		 @return		A reference to the moved tone mapper pass (i.e. this 
						tone mapper pass).
		 */
		ToneMapperPass &operator=(ToneMapperPass &&render_pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this tone mapper pass.
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
		 A pointer to the device context of this tone mapper pass.
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 A pointer to the compute shader of this tone mapper pass.
		 */
		SharedPtr< const ComputeShader > m_cs;
	};
}