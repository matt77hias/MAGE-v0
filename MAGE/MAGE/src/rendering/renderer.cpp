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

	const Renderer *Renderer::Get() noexcept {
		Assert(Engine::Get());

		return Engine::Get()->GetRenderer();
	}

	Renderer::Renderer(HWND hwindow, 
		const DisplayConfiguration *display_configuration) :
		m_hwindow(hwindow), m_fullscreen(false),
		m_in_begin_end_pair(false), 
		m_display_configuration(MakeUnique< DisplayConfiguration >(*display_configuration)),
		m_device(), m_device_context(), m_swap_chain(), m_rtv(), m_dsv(),
		m_rendering_state_cache() {

		Assert(m_hwindow);
		Assert(m_display_configuration);

		InitializeRenderer();
	}

	Renderer::Renderer(Renderer &&renderer) = default;

	Renderer::~Renderer() {
		UninitializeRenderer();
	}

	void Renderer::InitializeRenderer() {
		// Setup the device and device context.
		SetupDevice();
		// Setup the swap chain.
		SetupSwapChain();

		// Setup the rendering states.
		m_rendering_state_cache = MakeUnique< RenderingStateCache >(m_device.Get());
	}

	void Renderer::UninitializeRenderer() noexcept {
		// Switch to windowed mode since Direct3D is incapable 
		// to clear its state properly when in fullscreen mode
		// due to certain threading issues that occur behind the scenes.
		if (m_swap_chain) {
			m_swap_chain->SetFullscreenState(FALSE, nullptr);
		}

		// Reset any device context to the default settings. 
		if (m_device_context) {
			m_device_context->ClearState();
		}
	}

	void Renderer::SetupDevice() {
		// Set the runtime layers to enable.
		UINT create_device_flags = 0;
#ifdef _DEBUG
		create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		// Get the ID3D11Device and ID3D11DeviceContext.
		ComPtr< ID3D11Device > device;
		ComPtr< ID3D11DeviceContext > device_context;
		HRESULT result_device = D3D11CreateDevice(
			GetAdapter(),			      // Adapter.
			D3D_DRIVER_TYPE_UNKNOWN,	  // Driver type.
			nullptr,					  // A handle to a DLL that implements a software rasterizer.
			create_device_flags,		  // The runtime layers to enable.
			g_feature_levels,			  // The order of feature levels to attempt to create.
			_countof(g_feature_levels),	  // The number of feature levels.
			D3D11_SDK_VERSION,			  // The SDK version.
			device.GetAddressOf(),		  // The address of a pointer to the ID3D11Device that represents the device created.
			&m_feature_level,			  // The address of a pointer to the supported feature level.
			device_context.GetAddressOf() // The address of a pointer to the ID3D11DeviceContext.
		);
		if (FAILED(result_device)) {
			throw FormattedException("ID3D11Device creation failed: %08X.", result_device);
		}

		// Get the ID3D11Device2.
		const HRESULT result_device2 = device.As(&m_device);
		if (FAILED(result_device2)) {
			throw FormattedException("ID3D11Device2 creation failed: %08X.", result_device2);
		}
		// Get the ID3D11DeviceContext2.
		const HRESULT result_device_context2 = device_context.As(&m_device_context);
		if (FAILED(result_device_context2)) {
			throw FormattedException("ID3D11DeviceContext2 creation failed: %08X.", result_device_context2);
		}
	}

	void Renderer::SetupSwapChain() {
		m_display_configuration->UpdateMSAASampleDesc(GetDevice());

		// Create the swap chain.
		CreateSwapChain();
		// Create and binds the RTV and DSV.
		CreateRTV();
		CreateDSV();
		OM::BindRTVAndDSV(m_device_context.Get(), m_rtv.Get(), m_dsv.Get());
	}

	void Renderer::ResetSwapChain() {
		// Recreate the swap chain buffers.
		m_swap_chain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
		// Create and binds the RTV and DSV.
		CreateRTV();
		CreateDSV();
		OM::BindRTVAndDSV(m_device_context.Get(), m_rtv.Get(), m_dsv.Get());
	}

	void Renderer::CreateSwapChain() {
		// Get the IDXGIFactory3.
		ComPtr< IDXGIFactory3 > dxgi_factory3;
		const HRESULT result_dxgi_factory3 = GetAdapter()->GetParent(__uuidof(IDXGIFactory3), (void **)dxgi_factory3.GetAddressOf());
		if (FAILED(result_dxgi_factory3)) {
			throw FormattedException("IDXGIFactory3 creation failed: %08X.", result_dxgi_factory3);
		}

		// DXGI_MWA_NO_WINDOW_CHANGES: Prevent DXGI from monitoring an applications message queue; this makes DXGI unable to respond to mode changes.
		// DXGI_MWA_NO_ALT_ENTER:      Prevent DXGI from responding to an alt-enter sequence.
		// DXGI_MWA_NO_PRINT_SCREEN:   Prevent DXGI from responding to a print-screen key.
		dxgi_factory3->MakeWindowAssociation(m_hwindow, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER | DXGI_MWA_NO_PRINT_SCREEN);

		// Create a DXGI_SWAP_CHAIN_DESC1.
		DXGI_SWAP_CHAIN_DESC1 swap_chain_desc = {};
		swap_chain_desc.Width       = static_cast< UINT >(GetWidth());
		swap_chain_desc.Height      = static_cast< UINT >(GetHeight());
		swap_chain_desc.Format      = m_display_configuration->GetDisplayFormat();
		swap_chain_desc.SampleDesc  = m_display_configuration->GetMSAASampleDesc();
		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.BufferCount = 1;
		swap_chain_desc.Flags       = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		// Create a DXGI_SWAP_CHAIN_FULLSCREEN_DESC.
		DXGI_SWAP_CHAIN_FULLSCREEN_DESC swap_chain_fullscreen_desc = {};
		swap_chain_fullscreen_desc.RefreshRate = m_display_configuration->GetDisplayRefreshRate();
		swap_chain_fullscreen_desc.Windowed    = TRUE;

		// Get the IDXGISwapChain1.
		ComPtr< IDXGISwapChain1 > swap_chain1;
		const HRESULT result_swap_chain1 = dxgi_factory3->CreateSwapChainForHwnd(
			m_device.Get(), m_hwindow, &swap_chain_desc, &swap_chain_fullscreen_desc, nullptr, swap_chain1.ReleaseAndGetAddressOf());
		if (FAILED(result_swap_chain1)) {
			throw FormattedException("IDXGISwapChain1 creation failed: %08X.", result_swap_chain1);
		}
		// Get the IDXGISwapChain2.
		const HRESULT result_swap_chain2 = swap_chain1.As(&m_swap_chain);
		if (FAILED(result_swap_chain2)) {
			throw FormattedException("IDXGISwapChain2 creation failed: %08X.", result_swap_chain2);
		}

		// Set to windowed mode.
		m_swap_chain->SetFullscreenState(FALSE, nullptr);
	}

	void Renderer::CreateRTV() {
		// Access the only back buffer of the swap-chain.
		ComPtr< ID3D11Texture2D > back_buffer;
		const HRESULT result_back_buffer = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)back_buffer.GetAddressOf());
		if (FAILED(result_back_buffer)) {
			throw FormattedException("Back buffer texture creation failed: %08X.", result_back_buffer);
		}
		
		// Create the render target view.
		const HRESULT result_render_target_view = m_device->CreateRenderTargetView(back_buffer.Get(), nullptr, m_rtv.ReleaseAndGetAddressOf());
		if (FAILED(result_render_target_view)) {
			throw FormattedException("ID3D11RenderTargetView creation failed: %08X.", result_render_target_view);
		}
	}

	void Renderer::CreateDSV() {
		// Create the depth stencil texture descriptor.
		D3D11_TEXTURE2D_DESC depth_stencil_desc = {};
		depth_stencil_desc.Width              = static_cast< UINT >(GetWidth());
		depth_stencil_desc.Height             = static_cast< UINT >(GetHeight());
		depth_stencil_desc.MipLevels          = 1;
		depth_stencil_desc.ArraySize          = 1;
		depth_stencil_desc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_stencil_desc.SampleDesc         = m_display_configuration->GetMSAASampleDesc();
		depth_stencil_desc.Usage              = D3D11_USAGE_DEFAULT;
		depth_stencil_desc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
		depth_stencil_desc.CPUAccessFlags     = 0;
		depth_stencil_desc.MiscFlags          = 0;
		
		// Create the depth stencil texture.
		ComPtr< ID3D11Texture2D > depth_stencil;
		const HRESULT result_depth_stencil = m_device->CreateTexture2D(&depth_stencil_desc, nullptr, depth_stencil.ReleaseAndGetAddressOf());
		if (FAILED(result_depth_stencil)) {
			throw FormattedException("Depth-stencil texture creation failed: %08X.", result_depth_stencil);
		}

		// Create the depth stencil view descriptor.
		D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc = {};
		dsv_desc.Format             = depth_stencil_desc.Format;
		dsv_desc.ViewDimension      = m_display_configuration->UseMSAA() ? 
										D3D11_DSV_DIMENSION_TEXTURE2DMS : 
										D3D11_DSV_DIMENSION_TEXTURE2D;
		dsv_desc.Texture2D.MipSlice = 0;
		
		// Create a depth stencil view.
		const HRESULT result_dsv = m_device->CreateDepthStencilView(depth_stencil.Get(), &dsv_desc, m_dsv.ReleaseAndGetAddressOf());
		if (FAILED(result_dsv)) {
			throw FormattedException("Depth-stencil view creation failed: %08X.", result_dsv);
		}
	}

	void Renderer::BeginFrame() {
		Assert(!m_in_begin_end_pair);

		static const XMVECTORF32 background_color = { 0.0f, 0.117647058f, 0.149019608f, 1.000000000f };

		// Clear the back buffer.
		m_device_context->ClearRenderTargetView(m_rtv.Get(), background_color);
		// Clear the depth buffer to 1.0 (i.e. max depth).
		// Clear the stencil buffer to 0.
		m_device_context->ClearDepthStencilView(m_dsv.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		m_in_begin_end_pair = true;
	}

	void Renderer::EndFrame() {
		Assert(m_in_begin_end_pair);

		// Present the back buffer to the front buffer.
		const UINT sync_interval = (m_display_configuration->IsVSynced()) ? 1 : 0;
		m_swap_chain->Present(sync_interval, 0);

		m_in_begin_end_pair = false;
	}

	void Renderer::BeginTextures(UINT nb_rtvs, 
		ID3D11RenderTargetView * const *rtvs, ID3D11DepthStencilView *dsv) {
		Assert(!m_in_begin_end_pair);

		OM::BindRTVsAndDSV(m_device_context.Get(), nb_rtvs, rtvs, dsv);

		m_in_begin_end_pair = true;
	}

	void Renderer::EndTextures() {
		Assert(m_in_begin_end_pair);

		OM::BindRTVAndDSV(m_device_context.Get(), m_rtv.Get(), m_dsv.Get());

		m_in_begin_end_pair = false;
	}

	void Renderer::SwitchMode(bool toggle) {
		// Release the swap chain buffers.
		m_rtv.Reset();
		m_dsv.Reset();

		BOOL current = false;
		if (toggle) {
			m_swap_chain->GetFullscreenState(&current, nullptr);
			current = !current;
			m_swap_chain->SetFullscreenState(current, nullptr);
		}

		ResetSwapChain();

		m_swap_chain->GetFullscreenState(&current, nullptr);
		m_fullscreen = (current != 0);
	}
}