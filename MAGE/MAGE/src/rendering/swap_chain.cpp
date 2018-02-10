//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_manager.hpp"
#include "loaders\texture_loader.hpp"
#include "system\system_time.hpp"
#include "logging\error.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	[[nodiscard]] SwapChain *SwapChain::Get() noexcept {
		Assert(RenderingManager::Get());

		return RenderingManager::Get()->GetSwapChain();
	}

	SwapChain::SwapChain(ID3D11Device5 *device, 
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

	SwapChain::SwapChain(SwapChain &&swap_chain) noexcept = default;

	SwapChain::~SwapChain() {
		// Switch to windowed mode since Direct3D is incapable to clear its 
		// state properly when in fullscreen mode due to certain threading 
		// issues that occur behind the scenes.
		if (m_swap_chain) {
			m_swap_chain->SetFullscreenState(FALSE, nullptr);
		}
	}

	//-------------------------------------------------------------------------
	// Member Methods: Swap Chain
	//-------------------------------------------------------------------------

	void SwapChain::SetupSwapChain() {
		// Create the swap chain.
		CreateSwapChain();
		// Create the back buffer RTV.
		CreateRTV();
	}

	void SwapChain::ResetSwapChain() {
		// Recreate the swap chain buffers.
		m_swap_chain->ResizeBuffers(0u, 0u, 0u,
			                        DXGI_FORMAT_UNKNOWN, 
			                        DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
		// Create the back buffer RTV.
		CreateRTV();
	}

	void SwapChain::CreateSwapChain() {
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

	void SwapChain::CreateRTV() {
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

	void SwapChain::Clear() const noexcept {
		// Clear the back buffer.
		Pipeline::OM::ClearRTV(Pipeline::GetImmediateDeviceContext(), m_rtv.Get());
	}

	void SwapChain::Present() const noexcept {
		// Present the back buffer to the front buffer.
		const U32 sync_interval = (m_display_configuration->IsVSynced()) 
			                      ? 1u : 0u;
		m_swap_chain->Present(sync_interval, 0u);
	}

	void SwapChain::TakeScreenShot() const {
		ComPtr< ID3D11Texture2D > back_buffer;
		{
			// Access the only back buffer of the swap-chain.
			const HRESULT result 
				= m_swap_chain->GetBuffer(0u, __uuidof(ID3D11Texture2D),
				                          (void **)back_buffer.GetAddressOf());
			ThrowIfFailed(result,
				"Back buffer texture creation failed: %08X.", result);
		}
		
		const auto fname = L"screenshot-" 
			             + GetLocalSystemDateAndTimeAsString() 
			             + L".png";
		
		loader::ExportTextureToFile(fname,
			                        Pipeline::GetImmediateDeviceContext(), 
			                        back_buffer.Get());
	}

	//-------------------------------------------------------------------------
	// Member Methods: Display Configuration
	//-------------------------------------------------------------------------

	void SwapChain::SwitchMode(bool toggle) {
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
}