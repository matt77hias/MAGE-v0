//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\swap_chain.hpp"
#include "loaders\texture_loader.hpp"
#include "logging\error.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// SwapChain::Impl
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of swap chains.
	 */
	class SwapChain::Impl final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a swap chain.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a window is not equal to @c nullptr.
		 @pre			@a display_configuration is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		window
						The main window handle.
		 @param[in]		display_configuration
						A pointer to the display configuration.
		 */
		explicit Impl(ID3D11Device *device, 
					  HWND window, 
					  DisplayConfiguration *display_configuration);

		/**
		 Constructs a swap chain from the given swap chain.

		 @param[in]		swap_chain
						A reference to a swap chain to copy.
		 */
		Impl(const Impl &swap_chain) = delete;

		/**
		 Constructs a swap chain by moving the given swap chain.

		 @param[in]		swap_chain
						A reference to a swap chain to move.
		 */
		Impl(Impl &&swap_chain) noexcept;

		/**
		 Destructs this swap chain.
		 */
		~Impl();

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
		Impl &operator=(const Impl &swap_chain) = delete;

		/**
		 Moves the given swap chain to this swap chain.

		 @param[in]		swap_chain
						A reference to a swap chain to move.
		 @return		A reference to the moved swap chain (i.e. this swap 
						chain).
		 */
		Impl &operator=(Impl &&swap_chain) = delete;

		//---------------------------------------------------------------------
		// Member Methods: Display Configuration
		//---------------------------------------------------------------------

		/**
		 Returns the window handle of this swap chain.

		 @return		The window handle of this swap chain.
		 */
		[[nodiscard]]HWND GetWindow() noexcept {
			return m_window;
		}

		/**
		 Checks whether this swap chain displays in windowed mode.

		 @return		@c true if this swap chain displays in windowed mode. 
						@c false otherwise.
		*/
		[[nodiscard]]bool IsWindowed() const noexcept {
			return !IsFullScreen();
		}
		
		/**
		 Checks whether this swap chain displays in full screen mode.

		 @return		@c true if this swap chain displays in full screen mode. 
						@c false otherwise.
		 */
		[[nodiscard]]bool IsFullScreen() const noexcept {
			BOOL current = FALSE;
			m_swap_chain->GetFullscreenState(&current, nullptr);
			return current == TRUE;
		}
		
		/**
		 Checks whether this swap chain lost its mode, i.e. the tracked mode of 
		 this swap chain differs from its actual mode (e.g. ALT + TAB).

		 @return		@c true if this swap chain lost its mode. @c false 
						otherwise.
		 */
		[[nodiscard]]bool LostMode() const noexcept {
			return IsTrackedFullScreen() == IsWindowed();
		}

		/**
		 Sets the initial mode of this swap chain.
		 
		 Call this method before starting the game loop.

		 @throws		Exception
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
		[[nodiscard]]ID3D11RenderTargetView *GetRTV() const noexcept {
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

		 @param[in]		fname
						A reference to the filename.
		 @throws		Exception
						Failed to take a screenshot of the current back buffer 
						of this swap chain. 
		 */
		void TakeScreenShot(const wstring &fname) const;

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
		[[nodiscard]]bool IsTrackedFullScreen() const noexcept {
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

		 @throws		Exception
						Failed to set up the swap chain.
		 */
		void SetupSwapChain();
		
		/**
		 Resets the swap chain.

		 @throws		Exception
						Failed to reset up the swap chain.
		 */
		void ResetSwapChain();

		/**
		 Creates the swap chain.

		 @throws		Exception
						Failed to create the swap chain.
		 */
		void CreateSwapChain();
		
		/**
		 Creates the render target view of the back buffer of this swap chain.

		 @throws		Exception
						Failed to obtain the back buffer resource of this swap 
						chain.
		 @throws		Exception
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
		HWND m_window;

		/**
		 A pointer to the display configuration of this swap chain.
		 */
		DisplayConfiguration * const m_display_configuration;

		//---------------------------------------------------------------------
		// Member Variables: Swap Chain
		//---------------------------------------------------------------------

		ID3D11Device * const m_device;

		/**
		 A pointer to the swap chain.
		 */
		ComPtr< DXGISwapChain > m_swap_chain;
		
		/**
		 A pointer to the render target view of the back buffer of this swap 
		 chain.
		 */
		ComPtr< ID3D11RenderTargetView > m_rtv;
	};

	SwapChain::Impl::Impl(ID3D11Device *device, 
						  HWND window, 
						  DisplayConfiguration *display_configuration)
		: m_window(window), 
		m_display_configuration(display_configuration),
		m_device(device), 
		m_swap_chain(), 
		m_rtv() {

		Assert(m_window);
		Assert(m_display_configuration);
		Assert(m_device);

		// Setup the swap chain.
		SetupSwapChain();
	}

	SwapChain::Impl::Impl(Impl &&swap_chain) noexcept = default;

	SwapChain::Impl::~Impl() {
		// Switch to windowed mode since Direct3D is incapable to clear its 
		// state properly when in fullscreen mode due to certain threading 
		// issues that occur behind the scenes.
		if (m_swap_chain) {
			m_swap_chain->SetFullscreenState(FALSE, nullptr);
		}
	}

	void SwapChain::Impl::SetupSwapChain() {
		// Create the swap chain.
		CreateSwapChain();
		// Create the back buffer RTV.
		CreateRTV();
	}

	void SwapChain::Impl::ResetSwapChain() {
		// Recreate the swap chain buffers.
		m_swap_chain->ResizeBuffers(0u, 0u, 0u,
			                        DXGI_FORMAT_UNKNOWN, 
			                        DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
		// Create the back buffer RTV.
		CreateRTV();
	}

	void SwapChain::Impl::CreateSwapChain() {
		ComPtr< IDXGIFactory2 > dxgi_factory;
		{
			const HRESULT result 
				= m_display_configuration->GetAdapter()->GetParent(
					__uuidof(IDXGIFactory2), 
					(void **)dxgi_factory.GetAddressOf());
			ThrowIfFailed(result, "IDXGIFactory2 creation failed: %08X.", result);
		}
	
		// DXGI_MWA_NO_WINDOW_CHANGES: 
		// Prevent DXGI from monitoring an applications message queue; this 
		// makes DXGI unable to respond to mode changes.
		//
		// DXGI_MWA_NO_ALT_ENTER: 
		// Prevent DXGI from responding to an alt-enter sequence.
		//
		// DXGI_MWA_NO_PRINT_SCREEN: 
		// Prevent DXGI from responding to a print-screen key.
		dxgi_factory->MakeWindowAssociation(m_window, 
			                                DXGI_MWA_NO_WINDOW_CHANGES 
			                              | DXGI_MWA_NO_ALT_ENTER 
			                              | DXGI_MWA_NO_PRINT_SCREEN);

		// Create a swap chain descriptor.
		DXGI_SWAP_CHAIN_DESC1 swap_chain_desc = {};
		swap_chain_desc.Width       = m_display_configuration->GetDisplayWidth();
		swap_chain_desc.Height      = m_display_configuration->GetDisplayHeight();
		swap_chain_desc.Format      = m_display_configuration->GetDisplayFormat();
		swap_chain_desc.SampleDesc.Count = 1u;
		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.BufferCount = 1u;
		swap_chain_desc.Flags       = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		// Create a fullscreen swap chain descriptor.
		DXGI_SWAP_CHAIN_FULLSCREEN_DESC swap_chain_fullscreen_desc = {};
		swap_chain_fullscreen_desc.RefreshRate = m_display_configuration->GetDisplayRefreshRate();
		swap_chain_fullscreen_desc.Windowed    = TRUE;

		ComPtr< IDXGISwapChain1 > swap_chain;
		{
			// Get the IDXGISwapChain1.
			const HRESULT result = dxgi_factory->CreateSwapChainForHwnd(
				m_device, m_window, &swap_chain_desc, &swap_chain_fullscreen_desc, 
				nullptr, swap_chain.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "IDXGISwapChain1 creation failed: %08X.", result);
		}
		{
			// Get the DXGISwapChain.
			const HRESULT result = swap_chain.As(&m_swap_chain);
			ThrowIfFailed(result, "DXGISwapChain creation failed: %08X.", result);
		}

		// Set to windowed mode.
		m_swap_chain->SetFullscreenState(FALSE, nullptr);
	}

	void SwapChain::Impl::CreateRTV() {
		ComPtr< ID3D11Texture2D > back_buffer;
		{
			// Access the only back buffer of the swap-chain.
			const HRESULT result 
				= m_swap_chain->GetBuffer(0u, 
					                      __uuidof(ID3D11Texture2D), 
				                          (void **)back_buffer.GetAddressOf());
			ThrowIfFailed(result,
				"Back buffer texture creation failed: %08X.", result);
		}

		{
			// Create the RTV.
			const HRESULT result 
				= m_device->CreateRenderTargetView(back_buffer.Get(), 
					                               nullptr, 
					                               m_rtv.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, 
				"Back buffer RTV creation failed: %08X.", result);
		}
	}

	void SwapChain::Impl::Clear() const noexcept {
		// Clear the back buffer.
		Pipeline::OM::ClearRTV(Pipeline::GetImmediateDeviceContext(), m_rtv.Get());
	}

	void SwapChain::Impl::Present() const noexcept {
		// Present the back buffer to the front buffer.
		const U32 sync_interval = (m_display_configuration->IsVSynced()) 
			                      ? 1u : 0u;
		m_swap_chain->Present(sync_interval, 0u);
	}

	void SwapChain::Impl::TakeScreenShot(const wstring &fname) const {
		ComPtr< ID3D11Texture2D > back_buffer;
		{
			// Access the only back buffer of the swap-chain.
			const HRESULT result 
				= m_swap_chain->GetBuffer(0u, __uuidof(ID3D11Texture2D),
				                          (void **)back_buffer.GetAddressOf());
			ThrowIfFailed(result,
				"Back buffer texture creation failed: %08X.", result);
		}
		
		loader::ExportTextureToFile(fname,
			                        Pipeline::GetImmediateDeviceContext(), 
			                        back_buffer.Get());
	}

	void SwapChain::Impl::SwitchMode(bool toggle) {
		// Release the swap chain buffers.
		m_rtv.Reset();

		BOOL current = FALSE;
		if (toggle) {
			m_swap_chain->GetFullscreenState(&current, nullptr);
			current = !current;
			m_swap_chain->SetFullscreenState(current, nullptr);
		}

		ResetSwapChain();

		m_swap_chain->GetFullscreenState(&current, nullptr);
		const auto fullscreen = (current == TRUE);
		SetTrackedFullScreen(fullscreen);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// SwapChain
	//-------------------------------------------------------------------------
	#pragma region

	SwapChain::SwapChain(ID3D11Device *device,
						 HWND window,
						 DisplayConfiguration *display_configuration)
		: m_impl(MakeUnique< Impl >(device, window, display_configuration)) {}

	SwapChain::SwapChain(SwapChain &&swap_chain) noexcept = default;

	SwapChain::~SwapChain() = default;

	[[nodiscard]]HWND SwapChain::GetWindow() noexcept {
		return m_impl->GetWindow();
	}

	[[nodiscard]]bool SwapChain::IsWindowed() const noexcept {
		return m_impl->IsWindowed();
	}

	[[nodiscard]]bool SwapChain::IsFullScreen() const noexcept {
		return m_impl->IsFullScreen();
	}

	[[nodiscard]]bool SwapChain::LostMode() const noexcept {
		return m_impl->LostMode();
	}

	void SwapChain::SetInitialMode() {
		m_impl->SetInitialMode;
	}

	void SwapChain::SwitchMode(bool toggle) {
		m_impl->SwitchMode(toggle);
	}

	[[nodiscard]]ID3D11RenderTargetView *SwapChain::GetRTV() const noexcept {
		return m_impl->GetRTV();
	}

	void SwapChain::Clear() const noexcept {
		m_impl->Clear();
	}

	void SwapChain::Present() const noexcept {
		m_impl->Present();
	}

	void SwapChain::TakeScreenShot(const wstring &fname) const {
		m_impl->TakeScreenShot(fname);
	}

	#pragma endregion
}