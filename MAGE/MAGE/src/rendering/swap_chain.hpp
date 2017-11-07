#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\display_configuration.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of swap chains.
	 */
	class SwapChain final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the swap chain of the rendering manager associated with the 
		 current engine.

		 @pre			The rendering manager associated with the current 
						engine must be loaded.
		 @return		A pointer to the swap chain of the rendering manager 
						associated with the current engine.
		 */
		static SwapChain *Get() noexcept;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a swap chain.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a hwindow is not equal to @c nullptr.
		 @pre			@a display_configuration is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		hwindow
						The main window handle.
		 @param[in]		display_configuration
						A pointer to the display configuration.
		 */
		explicit SwapChain(ID3D11Device2 *device, HWND hwindow,
			DisplayConfiguration *display_configuration);

		/**
		 Constructs a swap chain from the given swap chain.

		 @param[in]		swap_chain
						A reference to a swap chain to copy.
		 */
		SwapChain(const SwapChain &swap_chain) = delete;

		/**
		 Constructs a swap chain by moving the given swap chain.

		 @param[in]		swap_chain
						A reference to a swap chain to move.
		 */
		SwapChain(SwapChain &&swap_chain);

		/**
		 Destructs this swap chain.
		 */
		~SwapChain();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given swap chain to this swap chain.

		 @param[in]		swap_chain
						A reference to a swap chain to copy.
		 @return		A reference to the copy of the given swap chain (i.e. 
						this swap chain).
		 */
		SwapChain &operator=(const SwapChain &swap_chain) = delete;

		/**
		 Moves the given swap chain to this swap chain.

		 @param[in]		swap_chain
						A reference to a swap chain to move.
		 @return		A reference to the moved swap chain (i.e. this swap 
						chain).
		 */
		SwapChain &operator=(SwapChain &&swap_chain) = delete;

		//---------------------------------------------------------------------
		// Member Methods: Display Configuration
		//---------------------------------------------------------------------

		/**
		 Returns the display configuration of this swap chain.

		 @return		A pointer to the display configuration of this swap 
						chain.
		 */
		const DisplayConfiguration *GetDisplayConfiguration() const noexcept {
			return m_display_configuration;
		}

		/**
		 Checks whether this swap chain displays in windowed mode.

		 @return		@c true if this swap chain displays in windowed mode. 
						@c false otherwise.
		*/
		bool IsWindowed() const noexcept {
			return !IsFullScreen();
		}
		
		/**
		 Checks whether this swap chain displays in full screen mode.

		 @return		@c true if this swap chain displays in full screen mode. 
						@c false otherwise.
		 */
		bool IsFullScreen() const noexcept {
			BOOL current = false;
			m_swap_chain->GetFullscreenState(&current, nullptr);
			return current == TRUE;
		}
		
		/**
		 Checks whether this swap chain lost its mode, i.e. the tracked mode of 
		 this swap chain differs from its actual mode (e.g. ALT + TAB).

		 @return		@c true if this swap chain lost its mode. @c false 
						otherwise.
		 */
		bool LostMode() const noexcept {
			return IsTrackedFullScreen() == IsWindowed();
		}

		/**
		 Sets the initial mode of this swap chain.
		 
		 Call this method before starting the game loop.

		 @throws		FormattedException
						Failed to reset up the swap chain.
		 */
		void SetInitialMode() {
			if (m_display_configuration->IsFullScreen()) {
				SwitchMode(true);
			}
		}
		
		/**
		 Recreates the swap chain buffers and switches the mode of this swap 
		 chain. Windowed mode is switched to full screen mode and vice versa.

		 @param[in]		toggle
						If @c true, then only the swap chain buffers will be 
						recreated to match the current mode of this swap chain 
						and no mode switch will occurs. If @c false, then the 
						swap chain buffers will be recreated and a mode switch 
						will occur.
		 @throws		FormattedException
						Failed to reset up the swap chain.
		 */
		void SwitchMode(bool toggle);

		//---------------------------------------------------------------------
		// Member Methods: Swap Chain
		//---------------------------------------------------------------------

		/**
		 Returns the render target view of the back buffer of this swap chain.

		 @return		A pointer to the render target view of the back buffer 
						of this swap chain.
		 */
		ID3D11RenderTargetView *GetRTV() const noexcept {
			return m_rtv.Get();
		}

		/**
		 Clears the render target view of the back buffer of this swap chain.
		 */
		void Clear() const noexcept;

		/**
		 Presents the back buffer of this swap chain.
		 */
		void Present() const noexcept;

		/**
		 Takes a screenshot of the current back buffer of this swap chain.

		 @throws		FormattedException
						Failed to take a screenshot of the current back buffer 
						of this swap chain. 
		 */
		void TakeScreenShot() const;

	private:

		//---------------------------------------------------------------------
		// Member Methods: Display Configuration
		//---------------------------------------------------------------------

		/**
		 Checks whether the tracked mode of this swap chain corresponds to
		 fullscreen mode.

		 @return		@c true if the tracked mode of this swap chain 
						corresponds to fullscreen mode.
						@c false otherwise.
		 */
		bool IsTrackedFullScreen() const noexcept {
			return m_display_configuration->IsFullScreen();
		}

		/**
		 Sets the tracked mode of this swap chain.

		 @param[in]		fullscreen
						@c true if the tracked mode corresponds to fullscreen 
						mode. @c false otherwise.
		 */
		void SetTrackedFullScreen(bool fullscreen) noexcept {
			m_display_configuration->SetFullScreen(fullscreen);
		}

		//---------------------------------------------------------------------
		// Member Methods: Swap Chain
		//---------------------------------------------------------------------
		
		/**
		 Sets up the swap chain.

		 @throws		FormattedException
						Failed to set up the swap chain.
		 */
		void SetupSwapChain();
		
		/**
		 Resets the swap chain.

		 @throws		FormattedException
						Failed to reset up the swap chain.
		 */
		void ResetSwapChain();

		/**
		 Creates the swap chain.

		 @throws		FormattedException
						Failed to create the swap chain.
		 */
		void CreateSwapChain();
		
		/**
		 Creates the render target view of the back buffer of this swap chain.

		 @throws		FormattedException
						Failed to obtain the back buffer resource of this swap 
						chain.
		 @throws		FormattedException
						Failed to create the render target view of the back 
						buffer of this swap chain.
		 */
		void CreateRTV();

		//---------------------------------------------------------------------
		// Member Variables: Display Configuration
		//---------------------------------------------------------------------

		/**
		 The handle of the parent window of this swap chain.
		 */
		const HWND m_hwindow;

		/**
		 A pointer to the display configuration of this swap chain.
		 */
		DisplayConfiguration * const m_display_configuration;

		//---------------------------------------------------------------------
		// Member Variables: Swap Chain
		//---------------------------------------------------------------------

		ID3D11Device2 * const m_device;

		/**
		 A pointer to the swap chain.
		 */
		ComPtr< IDXGISwapChain2 > m_swap_chain;
		
		/**
		 A pointer to the render target view of the back buffer of this swap 
		 chain.
		 */
		ComPtr< ID3D11RenderTargetView > m_rtv;
	};
}