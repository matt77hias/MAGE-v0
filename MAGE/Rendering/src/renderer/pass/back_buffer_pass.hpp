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
	 A class of back buffer passes.
	 */
	class BackBufferPass {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a back buffer pass.

		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		state_manager
						A reference to the state manager.
		 @param[in]		resource_manager
						A reference to the resource manager.
		 */
		explicit BackBufferPass(ID3D11DeviceContext& device_context, 
								StateManager& state_manager, 
								ResourceManager& resource_manager);

		/**
		 Constructs an back buffer pass from the given back buffer pass.

		 @param[in]		pass
						A reference to the back buffer pass to copy.
		 */
		BackBufferPass(const BackBufferPass& pass) = delete;

		/**
		 Constructs an back buffer pass by moving the given back buffer pass.

		 @param[in]		pass
						A reference to the Image pass to move.
		 */
		BackBufferPass(BackBufferPass&& pass) noexcept;

		/**
		 Destructs this back buffer pass.
		 */
		~BackBufferPass();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given back buffer pass to this back buffer pass.

		 @param[in]		pass
						A reference to the back buffer pass to copy.
		 @return		A reference to the copy of the given back buffer pass 
						(i.e. this back buffer pass).
		 */
		BackBufferPass& operator=(const BackBufferPass& pass) = delete;

		/**
		 Moves the given back buffer pass to this back buffer pass.

		 @param[in]		pass
						A reference to the back buffer pass to move.
		 @return		A reference to the moved back buffer pass (i.e. this 
						back buffer pass).
		 */
		BackBufferPass& operator=(BackBufferPass&& pass) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Renders.
		 */
		void Render();
		
	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the fixed state of this back buffer pass.
		 */
		void BindFixedState() const noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to the device context of this back buffer pass.
		 */
		std::reference_wrapper< ID3D11DeviceContext > m_device_context;

		/**
		 A reference to the state manager of this back buffer pass.
		 */
		std::reference_wrapper< StateManager > m_state_manager;

		/**
		 A pointer to the vertex shader of this back buffer pass.
		 */
		VertexShaderPtr m_vs;

		/**
		 A pointer to the pixel shader of this back buffer pass.
		 */
		PixelShaderPtr m_ps;
	};
}