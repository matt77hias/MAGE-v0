#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\resource_manager.hpp"
#include "rendering\swap_chain.hpp"
#include "scene\scene.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of rendering managers.
	 */
	class RenderingManager final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the rendering manager associated with the current engine.

		 @pre			The current engine must exist.
		 @return		A pointer to the rendering manager associated with the 
						current engine.
		 */
		[[nodiscard]] static const RenderingManager *Get() noexcept;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a rendering manager.

		 @pre			@a window is not equal to @c nullptr.
		 @pre			@a display_configuration is not equal to @c nullptr.
		 @param[in]		window
						The main window handle.
		 @param[in]		configuration
						A pointer to the display configuration.
		 */
		explicit RenderingManager(HWND window, 
								  const DisplayConfiguration *configuration);

		/**
		 Constructs a rendering manager from the given rendering manager.

		 @param[in]		manager
						A reference to a rendering manager to copy.
		 */
		RenderingManager(const RenderingManager &manager) = delete;

		/**
		 Constructs a rendering manager by moving the given rendering manager.

		 @param[in]		manager
						A reference to a rendering manager to move.
		 */
		RenderingManager(RenderingManager &&manager) noexcept;

		/**
		 Destructs this rendering manager.
		 */
		~RenderingManager();

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
		RenderingManager &operator=(const RenderingManager &manager) = delete;

		/**
		 Moves the given rendering manager to this rendering manager.

		 @param[in]		manager
						A reference to a rendering manager to move.
		 @return		A reference to the moved rendering manager (i.e. this 
						rendering manager).
		 */
		RenderingManager &operator=(RenderingManager &&manager) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the display configuration of this rendering manager.

		 @return		A pointer to the display configuration of this 
						rendering manager.
		 */
		[[nodiscard]] const DisplayConfiguration *
			GetDisplayConfiguration() const noexcept;

		/**
		 Returns the swap chain of this rendering manager.

		 @return		A pointer to the swap chain of this rendering manager.
		 */
		[[nodiscard]] SwapChain *GetSwapChain() const noexcept;

		/**
		 Returns the state manager of this rendering manager.

		 @return		A pointer to the state manager of this 
						rendering manager.
		 */
		[[nodiscard]] ResourceManager *GetResourceManager() const noexcept;

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
		 Renders the given scene.

		 @param[in]		scene
						A reference to the scene.
		 @throws		Exception
						Failed to render the scene.
		 */
		void Render(const Scene &scene);

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