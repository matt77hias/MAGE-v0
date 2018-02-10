#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\sky.hpp"
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

		 @param[in]		pass
						A reference to the sky pass to copy.
		 */
		SkyPass(const SkyPass &pass) = delete;

		/**
		 Constructs a sky pass by moving the given sky pass.

		 @param[in]		pass
						A reference to the sky pass to move.
		 */
		SkyPass(SkyPass &&pass) noexcept;

		/**
		 Destructs this sky pass.
		 */
		~SkyPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sky pass to this sky pass.

		 @param[in]		pass
						A reference to the sky pass to copy.
		 @return		A reference to the copy of the given sky pass (i.e. 
						this sky pass).
		 */
		SkyPass &operator=(const SkyPass &pass) = delete;

		/**
		 Moves the given sky pass to this sky pass.

		 @param[in]		pass
						A reference to the sky pass to move.
		 @return		A reference to the moved sky pass (i.e. this sky pass).
		 */
		SkyPass &operator=(SkyPass &&pass) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Renders the given scene.

		 @param[in]		sky
						A reference to the sky.
		 */
		void Render(const Sky &sky) const noexcept;
		
	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this sky pass.
		 */
		void BindFixedState() const noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device context of this sky pass.
		 */
		D3D11DeviceContext * const m_device_context;

		/**
		 A pointer to the vertex shader of this sky pass.
		 */
		const VertexShaderPtr m_vs;

		/**
		 A pointer to the pixel shader of this sky pass.
		 */
		const PixelShaderPtr m_ps;
	};
}