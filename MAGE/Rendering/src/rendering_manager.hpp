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
	 A class of rendering managers.
	 */
	class Manager final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a rendering manager.

		 @param[in]		window
						The main window handle.
		 @param[in]		configuration
						The display configuration.
		 */
		explicit Manager(NotNull< HWND > window, 
						 DisplayConfiguration configuration);

		/**
		 Constructs a rendering manager from the given rendering manager.

		 @param[in]		manager
						A reference to a rendering manager to copy.
		 */
		Manager(const Manager& manager) = delete;

		/**
		 Constructs a rendering manager by moving the given rendering manager.

		 @param[in]		manager
						A reference to a rendering manager to move.
		 */
		Manager(Manager&& manager) noexcept;

		/**
		 Destructs this rendering manager.
		 */
		~Manager();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given rendering manager to this rendering manager.

		 @param[in]		manager
						A reference to a rendering manager to copy.
		 @return		A reference to the copy of the given rendering manager 
						(i.e. this rendering manager).
		 */
		Manager& operator=(const Manager& manager) = delete;

		/**
		 Moves the given rendering manager to this rendering manager.

		 @param[in]		manager
						A reference to a rendering manager to move.
		 @return		A reference to the moved rendering manager (i.e. this 
						rendering manager).
		 */
		Manager& operator=(Manager&& manager) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the display configuration of this rendering manager.

		 @return		A reference to the display configuration of this 
						rendering manager.
		 */
		[[nodiscard]]
		const DisplayConfiguration& GetDisplayConfiguration() const noexcept;

		/**
		 Returns the swap chain of this rendering manager.

		 @return		A reference to the swap chain of this rendering manager.
		 */
		[[nodiscard]]
		SwapChain& GetSwapChain() noexcept;

		/**
		 Returns the swap chain of this rendering manager.

		 @return		A reference to the swap chain of this rendering manager.
		 */
		[[nodiscard]]
		const SwapChain& GetSwapChain() const noexcept;

		/**
		 Returns the resource manager of this rendering manager.

		 @return		A reference to the state manager of this 
						rendering manager.
		 */
		[[nodiscard]]
		ResourceManager& GetResourceManager() const noexcept;

		/**
		 Returns the world of this rendering manager.

		 @return		A reference to the world of this rendering manager.
		 */
		[[nodiscard]]
		World& GetWorld() const noexcept;

		/**
		 Binds the persistent state of this rendering manager.

		 @throws		Exception
						Failed to bind the persistent state of this rendering 
						manager.
		 @throws		Exception
						Failed to bind the persistent state of this rendering 
						manager.
		 */
		void BindPersistentState();

		/**
		 Updates this rendering manager.
		 */
		void Update();

		/**
		 Renders.

		 @param[in]		time
						A reference to the game time.
		 @throws		Exception
						Failed to render the world of this rendering manager.
		 */
		void Render(const GameTime& time);

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		class Impl;

		/**
		 A pointer to the implementation of this rendering manager.
		 */
		UniquePtr< Impl > m_impl;
	};
}