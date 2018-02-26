#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\renderer.hpp"
#include "rendering\rendering_output_manager.hpp"
#include "rendering\rendering_state_manager.hpp"
#include "rendering\resource_manager.hpp"
#include "rendering\swap_chain.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
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
		 @param[in]		display_configuration
						A pointer to the display configuration.
		 */
		explicit RenderingManager(HWND window, 
			const DisplayConfiguration *display_configuration);

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
		// Member Methods: Display Configuration
		//---------------------------------------------------------------------

		/**
		 Returns the display configuration of this rendering manager.

		 @return		A pointer to the display configuration of this 
						rendering manager.
		 */
		[[nodiscard]] const DisplayConfiguration *
			GetDisplayConfiguration() const noexcept {

			return m_display_configuration.get();
		}

		//---------------------------------------------------------------------
		// Member Methods: Rendering
		//---------------------------------------------------------------------

		/**
		 Returns the device of this rendering manager.

		 @return		A pointer to the device of this rendering manager.
		 */
		[[nodiscard]] D3D11Device *GetDevice() const noexcept {
			return m_device.Get();
		}

		/**
		 Returns the device context of this rendering manager.

		 @return		A pointer to the device context of this rendering 
						manager.
		 */
		[[nodiscard]] D3D11DeviceContext *GetDeviceContext() const noexcept {
			return m_device_context.Get();
		}

		/**
		 Returns the swap chain of this rendering manager.

		 @return		A pointer to the swap chain of this rendering manager.
		 */
		[[nodiscard]] SwapChain *GetSwapChain() const noexcept {
			return m_swap_chain.get();
		}

		/**
		 Returns the rendering output manager of this rendering manager.

		 @return		A pointer to the rendering output manager of this 
						rendering manager.
		 */
		[[nodiscard]] Renderer *GetRenderer() const noexcept {
			return m_renderer.get();
		}

		/**
		 Returns the rendering output manager of this rendering manager.

		 @return		A pointer to the rendering output manager of this 
						rendering manager.
		 */
		[[nodiscard]] const OutputManager *
			GetOutputManager() const noexcept {

			return m_rendering_output_manager.get();
		}

		/**
		 Returns the rendering state manager of this rendering manager.

		 @return		A pointer to the rendering state manager of this 
						rendering manager.
		 */
		[[nodiscard]] const StateManager *
			GetStateManager() const noexcept {

			return m_rendering_state_manager.get();
		}

		/**
		 Begins a frame.
		 */
		void BeginFrame() const;
		
		/**
		 Ends a frame.
		 */
		void EndFrame() const;

		/**
		 Binds the persistent state of this rendering manager.

		 @throws		Exception
						Failed to bind the persistent state of the rendering
						output manager of this rendering manager.
		 @throws		Exception
						Failed to bind the persistent state of the rendering
						state manager of this rendering manager.
		 */
		void BindPersistentState();

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Initializes the different rendering systems of this rendering manager.

		 @throws		Exception
						Failed to initialize at least one of the different 
						rendering systems of this rendering manager.
		 */
		void InitializeSystems();

		/**
		 Uninitializes the different rendering systems of this rendering 
		 manager.
		 */
		void UninitializeSystems() noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Rendering
		//---------------------------------------------------------------------

		/**
		 Sets up the D3D11 device and context of this rendering manager.

		 @throws		Exception
						Failed to set up the device and device context of this 
						rendering manager.
		 */
		void SetupDevice();

		//---------------------------------------------------------------------
		// Member Variables: Display Configration
		//---------------------------------------------------------------------

		/**
		 The handle of the parent window of this rendering manager.
		 */
		const HWND m_window;

		/**
		 A pointer to the display configuration of this rendering manager.
		 */
		UniquePtr< DisplayConfiguration > m_display_configuration;

		//---------------------------------------------------------------------
		// Member Variables: Rendering
		//---------------------------------------------------------------------

		/**
		 A pointer to the feature level of this rendering manager.
		 */
		D3D_FEATURE_LEVEL m_feature_level;

		/**
		 A pointer to the device of this rendering manager.
		 */
		ComPtr< D3D11Device > m_device;

		/**
		 A pointer to the device context of this rendering manager.
		 */
		ComPtr< D3D11DeviceContext > m_device_context;

		/**
		 A pointer to the swap chain of this rendering manager.
		 */
		UniquePtr< SwapChain > m_swap_chain;

		/**
		 A pointer to the renderer of this rendering manager.
		 */
		UniquePtr< Renderer > m_renderer;

		/**
		 A pointer to the rendering output manager of this rendering manager.
		 */
		UniquePtr< OutputManager > m_rendering_output_manager;

		/**
		 A pointer to the rendering state manager of this rendering manager.
		 */
		UniquePtr< StateManager > m_rendering_state_manager;
	};
}