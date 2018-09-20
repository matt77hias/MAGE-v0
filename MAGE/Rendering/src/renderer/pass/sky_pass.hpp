#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\state_manager.hpp"
#include "resource\rendering_resource_manager.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	/**
	 A class of sky passes for rendering sky domes to screen.
	 */
	class SkyPass {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sky pass.

		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		state_manager
						A reference to the state manager.
		 @param[in]		resource_manager
						A reference to the resource manager.
		 */
		explicit SkyPass(ID3D11DeviceContext& device_context,
						 StateManager& state_manager,
						 ResourceManager& resource_manager);

		/**
		 Constructs a sky pass from the given sky pass.

		 @param[in]		pass
						A reference to the sky pass to copy.
		 */
		SkyPass(const SkyPass& pass) = delete;

		/**
		 Constructs a sky pass by moving the given sky pass.

		 @param[in]		pass
						A reference to the sky pass to move.
		 */
		SkyPass(SkyPass&& pass) noexcept;

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
		SkyPass& operator=(const SkyPass& pass) = delete;

		/**
		 Moves the given sky pass to this sky pass.

		 @param[in]		pass
						A reference to the sky pass to move.
		 @return		A reference to the moved sky pass (i.e. this sky pass).
		 */
		SkyPass& operator=(SkyPass&& pass) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Renders the given world.

		 @param[in]		sky
						A pointer to the SRV of the sky.
		 */
		void Render(ID3D11ShaderResourceView* sky) const noexcept;

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
		 A reference to the device context of this sky pass.
		 */
		std::reference_wrapper< ID3D11DeviceContext > m_device_context;

		/**
		 A reference to the state manager of this sky pass.
		 */
		std::reference_wrapper< StateManager > m_state_manager;

		/**
		 A pointer to the vertex shader of this sky pass.
		 */
		VertexShaderPtr m_vs;

		/**
		 A pointer to the pixel shader of this sky pass.
		 */
		PixelShaderPtr m_ps;
	};
}