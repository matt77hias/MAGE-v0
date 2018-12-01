#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\swap_chain.hpp"
#include "resource\rendering_resource_manager.hpp"
#include "scene\rendering_world.hpp"
#include "system\game_timer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::rendering {

	/**
	 A class of renderers.
	 */
	class Renderer {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a renderer.

		 @param[in,out]	device
						A reference to the device.
		 @param[in,out]	device_context
						A reference to the device context.
		 @param[in,out]	display_configuration
						A reference to the display configuration.
		 @param[in,out]	swap_chain
						A reference to the swap chain.
		 @param[in,out]	resource_manager
						A pointer to the resource manager.
		 */
		explicit Renderer(ID3D11Device& device,
						  ID3D11DeviceContext& device_context,
						  DisplayConfiguration& display_configuration,
						  SwapChain& swap_chain,
						  ResourceManager& resource_manager);

		/**
		 Constructs a renderer from the given renderer.

		 @param[in]		renderer
						A reference to the renderer to copy.
		 */
		Renderer(const Renderer& renderer) = delete;

		/**
		 Constructs a renderer by moving the given renderer.

		 @param[in]		renderer
						A reference to the renderer to move.
		 */
		Renderer(Renderer&& renderer) noexcept;

		/**
		 Destructs this renderer.
		 */
		~Renderer();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given renderer to this renderer.

		 @param[in]		renderer
						A reference to the renderer to copy.
		 @return		A reference to the copy of the given renderer (i.e.
						this renderer).
		 */
		Renderer& operator=(const Renderer& renderer) = delete;

		/**
		 Moves the given renderer to this renderer.

		 @param[in]		renderer
						A reference to the renderer to move.
		 @return		A reference to the moved renderer (i.e. this renderer).
		 */
		Renderer& operator=(Renderer&& renderer) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the persistent state of this renderer.

		 @throws		Exception
						Failed to bind the persistent state of this renderer.
		 */
		void BindPersistentState();

		/**
		 Renders the given world.

		 @param[in]		world
						A reference to the world.
		 @param[in]		time
						A reference to the game time.
		 @throws		Exception
						Failed to render the world.
		 */
		void Render(const World& world, const GameTime& time);

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		class Impl;

		/**
		 A pointer to the implementation of this renderer.
		 */
		UniquePtr< Impl > m_impl;
	};
}