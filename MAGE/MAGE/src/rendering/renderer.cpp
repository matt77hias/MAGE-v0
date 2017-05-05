//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\renderer.hpp"
#include "rendering\device_enumeration.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Renderer::Renderer(HWND hwindow) : 
		m_hwindow(hwindow), m_fullscreen(false),
		m_in_begin_end_pair(false), 
		m_display_mode(*g_device_enumeration->GetDisplayMode()),
		m_device(), m_device_context(), m_swap_chain(), m_rtv(), m_dsv(),
		m_rendering_state_2d(), m_rendering_state_3d(), m_rendering_state_cache() {

		Assert(m_hwindow);

		InitializeRenderer();
	}

	Renderer::Renderer(Renderer &&renderer) = default;

	Renderer::~Renderer() {
		UninitializeRenderer();
	}

	void Renderer::InitializeRenderer() {
		// Setup the ID3D11Device2 and ID3D11DeviceContext2.
		SetupDevice();
		// Setup the IDXGISwapChain2.
		SetupSwapChain();

		// Setup and binds the RTV and DSV.
		SetupRTV();
		SetupDSV();
		m_device_context->OMSetRenderTargets(1, m_rtv.GetAddressOf(), m_dsv.Get());

		// Setup the rendering states.
		SetupRenderingStates();
		// Setup the viewport.
		SetupViewPort();
	}

	void Renderer::UninitializeRenderer() {
		// Switch to windowed mode since Direct3D is incapable of when in fullscreen mode
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
			g_device_enumeration->GetAdapter().Get(),	// Adapter.
			D3D_DRIVER_TYPE_UNKNOWN,					// Driver type.
			nullptr,									// A handle to a DLL that implements a software rasterizer.
			create_device_flags,						// The runtime layers to enable.
			g_feature_levels,							// The order of feature levels to attempt to create.
			_countof(g_feature_levels),					// The number of feature levels.
			D3D11_SDK_VERSION,							// The SDK version.
			device.GetAddressOf(),						// The address of a pointer to the ID3D11Device that represents the device created.
			&m_feature_level,							// The address of a pointer to the supported feature level.
			device_context.GetAddressOf()				// The address of a pointer to the ID3D11DeviceContext.
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
		// Get the IDXGIAdapter2.
		ComPtr< IDXGIAdapter2 > dxgi_adapter2 = g_device_enumeration->GetAdapter();
		// Get the IDXGIFactory3.
		ComPtr< IDXGIFactory3 > dxgi_factory3;
		const HRESULT result_dxgi_factory3 = dxgi_adapter2->GetParent(__uuidof(IDXGIFactory3), (void **)dxgi_factory3.GetAddressOf());
		if (FAILED(result_dxgi_factory3)) {
			throw FormattedException("IDXGIFactory3 creation failed: %08X.", result_dxgi_factory3);
		}

		// DXGI_MWA_NO_WINDOW_CHANGES: Prevent DXGI from monitoring an applications message queue; this makes DXGI unable to respond to mode changes.
		// DXGI_MWA_NO_ALT_ENTER:      Prevent DXGI from responding to an alt-enter sequence.
		// DXGI_MWA_NO_PRINT_SCREEN:   Prevent DXGI from responding to a print-screen key.
		dxgi_factory3->MakeWindowAssociation(m_hwindow, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER | DXGI_MWA_NO_PRINT_SCREEN);

		// Create a DXGI_SWAP_CHAIN_DESC1.
		DXGI_SWAP_CHAIN_DESC1 swap_chain_desc;
		ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));
		swap_chain_desc.Width              = m_display_mode.Width;	                 // The resolution width.
		swap_chain_desc.Height             = m_display_mode.Height;                  // The resolution height.
		swap_chain_desc.Format             = m_display_mode.Format;                  // The display format.
		swap_chain_desc.SampleDesc.Count   = 1;										 // The number of multisamples per pixel.
		swap_chain_desc.SampleDesc.Quality = 0;										 // The image quality level. (lowest)
		swap_chain_desc.BufferUsage        = DXGI_USAGE_RENDER_TARGET_OUTPUT;		 // Use the surface or resource as an output render target.
		swap_chain_desc.BufferCount        = 1;										 // The number of buffers in the swap chain.
		swap_chain_desc.Flags              = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		// Create a DXGI_SWAP_CHAIN_FULLSCREEN_DESC.
		DXGI_SWAP_CHAIN_FULLSCREEN_DESC swap_chain_fullscreen_desc;
		ZeroMemory(&swap_chain_fullscreen_desc, sizeof(swap_chain_fullscreen_desc));
		swap_chain_fullscreen_desc.Windowed = TRUE;

		// Get the IDXGISwapChain1.
		ComPtr< IDXGISwapChain1 > swap_chain1;
		const HRESULT result_swap_chain1 = dxgi_factory3->CreateSwapChainForHwnd(m_device.Get(), m_hwindow, &swap_chain_desc, &swap_chain_fullscreen_desc, nullptr, swap_chain1.ReleaseAndGetAddressOf());
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

	void Renderer::SetupRTV() {
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

	void Renderer::SetupDSV() {
		// Create the depth stencil texture descriptor.
		D3D11_TEXTURE2D_DESC depth_stencil_desc;
		ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc));
		depth_stencil_desc.Width              = m_display_mode.Width;	       // Texture width (in texels).
		depth_stencil_desc.Height             = m_display_mode.Height;	       // Texture height (in texels).
		depth_stencil_desc.MipLevels          = 1;                             // The maximum number of mipmap levels in the texture.
		depth_stencil_desc.ArraySize          = 1;							   // Number of textures in the texture array.
		depth_stencil_desc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT; // Texture format.
		depth_stencil_desc.SampleDesc.Count   = 1;							   // The number of multisamples per pixel.
		depth_stencil_desc.SampleDesc.Quality = 0;							   // The image quality level. (lowest)
		depth_stencil_desc.Usage              = D3D11_USAGE_DEFAULT;		   // Value that identifies how the texture is to be read from and written to.
		depth_stencil_desc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;	   // Flags for binding to pipeline stages. 
		depth_stencil_desc.CPUAccessFlags     = 0;							   // No CPU access is necessary.
		depth_stencil_desc.MiscFlags          = 0;							   // Flags that identify other, less common resource options.
		
		// Create the depth stencil texture.
		ComPtr< ID3D11Texture2D > depth_stencil;
		const HRESULT result_depth_stencil = m_device->CreateTexture2D(&depth_stencil_desc, nullptr, depth_stencil.ReleaseAndGetAddressOf());
		if (FAILED(result_depth_stencil)) {
			throw FormattedException("Depth-stencil texture creation failed: %08X.", result_depth_stencil);
		}

		// Create the depth stencil view descriptor.
		D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc;
		ZeroMemory(&dsv_desc, sizeof(dsv_desc));
		dsv_desc.Format             = depth_stencil_desc.Format;
		dsv_desc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsv_desc.Texture2D.MipSlice = 0;
		
		// Create a depth stencil view.
		const HRESULT result_dsv = m_device->CreateDepthStencilView(depth_stencil.Get(), &dsv_desc, m_dsv.ReleaseAndGetAddressOf());
		if (FAILED(result_dsv)) {
			throw FormattedException("Depth-stencil view creation failed: %08X.", result_dsv);
		}
	}

	void Renderer::SetupRenderingStates() {
		m_rendering_state_cache = make_unique< RenderingStateCache >(m_device.Get());
		m_rendering_state_2d    = make_unique< RenderingState >(m_device.Get(), m_device_context.Get(), m_rendering_state_cache.get());
		m_rendering_state_3d    = make_unique< RenderingState >(m_device.Get(), m_device_context.Get(), m_rendering_state_cache.get());
		m_rendering_state_2d->SetDefaultRenderingState2D();
		m_rendering_state_3d->SetDefaultRenderingState3D();
	}

	void Renderer::SetupViewPort() const {
		// Setup the (default) viewport.
		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(viewport));
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width    = static_cast< FLOAT >(m_display_mode.Width);
		viewport.Height   = static_cast< FLOAT >(m_display_mode.Height);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		// Bind an array of viewports to the rasterizer stage of the pipeline.
		// 1. Number of viewports to bind.
		// 2. An array of D3D11_VIEWPORT structures to bind to the device.
		m_device_context->RSSetViewports(1, &viewport);
	}

	void Renderer::BeginFrame() {
		Assert(!m_in_begin_end_pair);

		//const XMVECTORF32 background_color = { 0.0f, 0.117647058f, 0.149019608f, 1.000000000f };
		const XMVECTORF32 background_color = { 0.0f, 0.0f, 0.0f, 1.000000000f };

		// Clear the back buffer.
		m_device_context->ClearRenderTargetView(m_rtv.Get(), background_color);
		// Clear the depth buffer to 1.0 (i.e. max depth).
		m_device_context->ClearDepthStencilView(m_dsv.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

		m_in_begin_end_pair = true;
	}

	void Renderer::EndFrame() {
		Assert(m_in_begin_end_pair);

		// Present the back buffer to the front buffer.
		m_swap_chain->Present(0, 0);

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

		// Recreate the swap chain buffers.
		m_swap_chain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
		// Setup and binds the RTV and DSV.
		SetupRTV();
		SetupDSV();
		m_device_context->OMSetRenderTargets(1, m_rtv.GetAddressOf(), m_dsv.Get());

		m_swap_chain->GetFullscreenState(&current, nullptr);
		m_fullscreen = (current != 0);
	}
}