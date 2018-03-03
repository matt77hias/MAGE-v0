#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\display_configuration.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of swap chains.
	 */
	class SwapChain final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a swap chain.

		 @param[in]		device
						A reference to the device.
		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		window
						The main window handle.
		 @param[in]		display_configuration
						A reference to the display configuration.
		 */
		explicit SwapChain(ID3D11Device& device, 
						   ID3D11DeviceContext& device_context,
			               NotNull< HWND > window,
			               DisplayConfiguration& display_configuration);

		/**
		 Constructs a swap chain from the given swap chain.

		 @param[in]		swap_chain
						A reference to a swap chain to copy.
		 */
		SwapChain(const SwapChain& swap_chain) = delete;

		/**
		 Constructs a swap chain by moving the given swap chain.

		 @param[in]		swap_chain
						A reference to a swap chain to move.
		 */
		SwapChain(SwapChain&& swap_chain) noexcept;

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
		SwapChain& operator=(const SwapChain& swap_chain) = delete;

		/**
		 Moves the given swap chain to this swap chain.

		 @param[in]		swap_chain
						A reference to a swap chain to move.
		 @return		A reference to the moved swap chain (i.e. this swap 
						chain).
		 */
		SwapChain& operator=(SwapChain&& swap_chain) = delete;

		//---------------------------------------------------------------------
		// Member Methods: Display Configuration
		//---------------------------------------------------------------------

		/**
		 Returns the window handle of this swap chain.

		 @return		The window handle of this swap chain.
		 */
		[[nodiscard]]
		NotNull< HWND > GetWindow() noexcept;

		/**
		 Checks whether this swap chain displays in windowed mode.

		 @return		@c true if this swap chain displays in windowed mode. 
						@c false otherwise.
		*/
		[[nodiscard]]
		bool IsWindowed() const noexcept;
		
		/**
		 Checks whether this swap chain displays in full screen mode.

		 @return		@c true if this swap chain displays in full screen mode. 
						@c false otherwise.
		 */
		[[nodiscard]]
		bool IsFullScreen() const noexcept;
		
		/**
		 Checks whether this swap chain lost its mode, i.e. the tracked mode of 
		 this swap chain differs from its actual mode (e.g. ALT + TAB).

		 @return		@c true if this swap chain lost its mode. @c false 
						otherwise.
		 */
		[[nodiscard]]
		bool LostMode() const noexcept;

		/**
		 Sets the initial mode of this swap chain.
		 
		 Call this method before starting the game loop.

		 @throws		Exception
						Failed to reset up the swap chain.
		 */
		void SetInitialMode();
		
		/**
		 Recreates the swap chain buffers and switches the mode of this swap 
		 chain. Windowed mode is switched to full screen mode and vice versa.

		 @param[in]		toggle
						If @c true, then only the swap chain buffers will be 
						recreated to match the current mode of this swap chain 
						and no mode switch will occurs. If @c false, then the 
						swap chain buffers will be recreated and a mode switch 
						will occur.
		 @throws		Exception
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
		[[nodiscard]]
		ID3D11RenderTargetView *GetRTV() const noexcept;

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

		 @param[in]		fname
						A reference to the filename.
		 @throws		Exception
						Failed to take a screenshot of the current back buffer 
						of this swap chain. 
		 */
		void TakeScreenShot(const wstring& fname) const;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		class Impl;

		/**
		 A pointer to the implementation of this swap chain.
		 */
		UniquePtr< Impl > m_impl;	
	};
}