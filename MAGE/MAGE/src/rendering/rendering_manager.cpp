//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const RenderingManager *RenderingManager::Get() noexcept {
		Assert(Engine::Get());

		return Engine::Get()->GetRenderingManager();
	}

	RenderingManager::RenderingManager(HWND hwindow, 
		const DisplayConfiguration *display_configuration) :
		m_hwindow(hwindow), 
		m_fullscreen(false),
		m_in_begin_end_pair(false), 
		m_display_configuration(
			MakeUnique< DisplayConfiguration >(*display_configuration)),
		m_device(), 
		m_device_context(), 
		m_swap_chain(), 
		m_back_buffer_rtv(),
		m_renderer(), 
		m_rendering_output_manager(), 
		m_rendering_state_manager() {

		Assert(m_hwindow);
		Assert(m_display_configuration);

		InitializeSystems();
	}

	RenderingManager::RenderingManager(
		RenderingManager &&rendering_manager) = default;

	RenderingManager::~RenderingManager() {
		UninitializeSystems();
	}

	void RenderingManager::InitializeSystems() {
		// Setup the device and device context.
		SetupDevice();
		// Setup the swap chain.
		SetupSwapChain();

		// Setup the rendering output manager.
		m_rendering_output_manager = MakeUnique< RenderingOutputManager >(
			                         m_device.Get(), GetWidth(), GetHeight());
		// Setup the rendering state manager.
		m_rendering_state_manager = MakeUnique< RenderingStateManager >(
			                        m_device.Get());
		// Setup the renderer.
		const Viewport viewport(GetWidth(), GetHeight());
		m_renderer = MakeUnique< Renderer >(
			         m_device.Get(), m_device_context.Get(), viewport);
	}

	void RenderingManager::UninitializeSystems() noexcept {
		// Switch to windowed mode since Direct3D is incapable to clear its 
		// state properly when in fullscreen mode due to certain threading 
		// issues that occur behind the scenes.
		if (m_swap_chain) {
			m_swap_chain->SetFullscreenState(FALSE, nullptr);
		}

		// Reset any device context to the default settings. 
		if (m_device_context) {
			m_device_context->ClearState();
		}
	}

	//-------------------------------------------------------------------------
	// RenderingManager: D3D11 Device and Device Context
	//-------------------------------------------------------------------------

	void RenderingManager::SetupDevice() {
		// Set the runtime layers to enable.
		U32 create_device_flags = 0u;
#ifdef _DEBUG
		create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		// Get the ID3D11Device and ID3D11DeviceContext.
		ComPtr< ID3D11Device > device;
		ComPtr< ID3D11DeviceContext > device_context;
		const HRESULT result_device = D3D11CreateDevice(
			GetAdapter(),
			D3D_DRIVER_TYPE_UNKNOWN,
			nullptr,
			create_device_flags,
			Pipeline::s_feature_levels,
			_countof(Pipeline::s_feature_levels),
			D3D11_SDK_VERSION,
			device.GetAddressOf(),
			&m_feature_level,
			device_context.GetAddressOf());
		ThrowIfFailed(result_device, 
			"ID3D11Device creation failed: %08X.", result_device);

		// Get the ID3D11Device2.
		const HRESULT result_device2 = device.As(&m_device);
		ThrowIfFailed(result_device2,
			"ID3D11Device2 creation failed: %08X.", result_device2);
		// Get the ID3D11DeviceContext2.
		const HRESULT result_device_context2 = device_context.As(&m_device_context);
		ThrowIfFailed(result_device_context2, 
			"ID3D11DeviceContext2 creation failed: %08X.", result_device_context2);
	}

	//-------------------------------------------------------------------------
	// RenderingManager: Swap Chain
	//-------------------------------------------------------------------------

	void RenderingManager::SetupSwapChain() {
		// Create the swap chain.
		CreateSwapChain();
		// Create the back buffer RTV.
		CreateBackBufferRTV();
	}

	void RenderingManager::ResetSwapChain() {
		// Recreate the swap chain buffers.
		m_swap_chain->ResizeBuffers(0u, 0u, 0u, 
			DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
		// Create the back buffer RTV.
		CreateBackBufferRTV();
	}

	void RenderingManager::CreateSwapChain() {
		// Get the IDXGIFactory3.
		ComPtr< IDXGIFactory3 > dxgi_factory3;
		const HRESULT result_dxgi_factory3 = GetAdapter()->GetParent(
			__uuidof(IDXGIFactory3), (void **)dxgi_factory3.GetAddressOf());
		ThrowIfFailed(result_dxgi_factory3, 
			"IDXGIFactory3 creation failed: %08X.", result_dxgi_factory3);
	
		// DXGI_MWA_NO_WINDOW_CHANGES: Prevent DXGI from monitoring an applications message queue; 
		//                             this makes DXGI unable to respond to mode changes.
		// DXGI_MWA_NO_ALT_ENTER:      Prevent DXGI from responding to an alt-enter sequence.
		// DXGI_MWA_NO_PRINT_SCREEN:   Prevent DXGI from responding to a print-screen key.
		dxgi_factory3->MakeWindowAssociation(m_hwindow, 
			DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER | DXGI_MWA_NO_PRINT_SCREEN);

		// Create a DXGI_SWAP_CHAIN_DESC1.
		DXGI_SWAP_CHAIN_DESC1 swap_chain_desc = {};
		swap_chain_desc.Width       = GetWidth();
		swap_chain_desc.Height      = GetHeight();
		swap_chain_desc.Format      = m_display_configuration->GetDisplayFormat();
		swap_chain_desc.SampleDesc.Count = 1u;
		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.BufferCount = 1u;
		swap_chain_desc.Flags       = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		// Create a DXGI_SWAP_CHAIN_FULLSCREEN_DESC.
		DXGI_SWAP_CHAIN_FULLSCREEN_DESC swap_chain_fullscreen_desc = {};
		swap_chain_fullscreen_desc.RefreshRate = m_display_configuration->GetDisplayRefreshRate();
		swap_chain_fullscreen_desc.Windowed    = TRUE;

		// Get the IDXGISwapChain1.
		ComPtr< IDXGISwapChain1 > swap_chain1;
		const HRESULT result_swap_chain1 = dxgi_factory3->CreateSwapChainForHwnd(
			m_device.Get(), m_hwindow, 
			&swap_chain_desc, &swap_chain_fullscreen_desc, nullptr, 
			swap_chain1.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_swap_chain1, 
			"IDXGISwapChain1 creation failed: %08X.", result_swap_chain1);
		// Get the IDXGISwapChain2.
		const HRESULT result_swap_chain2 = swap_chain1.As(&m_swap_chain);
		ThrowIfFailed(result_swap_chain2, 
			"IDXGISwapChain2 creation failed: %08X.", result_swap_chain2);

		// Set to windowed mode.
		m_swap_chain->SetFullscreenState(FALSE, nullptr);
	}

	void RenderingManager::CreateBackBufferRTV() {
		ComPtr< ID3D11Texture2D > back_buffer;

		{
			// Access the only back buffer of the swap-chain.
			const HRESULT result = m_swap_chain->GetBuffer(
				0u, __uuidof(ID3D11Texture2D), (void **)back_buffer.GetAddressOf());
			ThrowIfFailed(result, 
				"Back buffer texture creation failed: %08X.", result);
		}
		
		{
			// Create the RTV.
			const HRESULT result = m_device->CreateRenderTargetView(
				back_buffer.Get(), nullptr,
				m_back_buffer_rtv.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "RTV creation failed: %08X.", result);
		}
	}

	//-------------------------------------------------------------------------
	// RenderingManager: Rendering
	//-------------------------------------------------------------------------

	void RenderingManager::BindPersistentState() {
		m_rendering_state_manager->BindPersistentState();
		m_renderer->BindPersistentState();
	}

	void RenderingManager::BeginFrame() noexcept {
		Assert(!m_in_begin_end_pair);

		// Clear the back buffer.
		Pipeline::OM::ClearRTV(m_device_context.Get(), 
			m_back_buffer_rtv.Get());

		m_in_begin_end_pair = true;
	}

	void RenderingManager::EndFrame() noexcept {
		Assert(m_in_begin_end_pair);

		// Present the back buffer to the front buffer.
		const U32 sync_interval = (m_display_configuration->IsVSynced()) 
								? 1u : 0u;
		m_swap_chain->Present(sync_interval, 0u);

		m_in_begin_end_pair = false;
	}

	//-------------------------------------------------------------------------
	// RenderingManager: Display Configuration
	//-------------------------------------------------------------------------

	void RenderingManager::SwitchMode(bool toggle) {
		// Release the swap chain buffers.
		m_back_buffer_rtv.Reset();

		BOOL current = false;
		if (toggle) {
			m_swap_chain->GetFullscreenState(&current, nullptr);
			current = !current;
			m_swap_chain->SetFullscreenState(current, nullptr);
		}

		ResetSwapChain();

		m_swap_chain->GetFullscreenState(&current, nullptr);
		m_fullscreen = (current != FALSE);
	}
}