//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Renderer::Renderer(HWND hwindow) : 
		Loadable(), m_hwindow(hwindow), m_fullscreen(g_device_enumeration->IsFullScreen()),
		m_render_target_view(nullptr), m_swap_chain2(nullptr), m_device_context2(nullptr), m_device2(nullptr) {

		const HRESULT result_renderer = InitializeRenderer();
		if (FAILED(result_renderer)) {
			Error("Renderer intialization failed: %ld.", result_renderer);
			return;
		}

		SetLoaded();
	}

	Renderer::~Renderer() {

		const HRESULT result_renderer = UnitializeRenderer();
		if (FAILED(result_renderer)) {
			Error("Renderer unintialization failed: %ld.", result_renderer);
		}
		
	}

	HRESULT Renderer::InitializeRenderer() {
		// Setup the ID3D11Device2 and ID3D11DeviceContext2.
		const HRESULT result_device = SetupDevice();
		if (FAILED(result_device)) {
			Error("Device setup failed: %ld.", result_device);
			return result_device;
		}
		// Setup the IDXGISwapChain2.
		const HRESULT result_swapchain = SetupSwapChain();
		if (FAILED(result_swapchain)) {
			Error("Swap chain setup failed: %ld.", result_swapchain);
			return result_swapchain;
		}
		
		m_swap_chain2->SetFullscreenState(m_fullscreen, nullptr);

		// Setup the ID3D11RenderTargetView
		const HRESULT result_render_target_view = SetupRenderTargetView();
		if (FAILED(result_render_target_view)) {
			Error("Target render view setup failed: %ld.", result_render_target_view);
			return result_render_target_view;
		}
		// Setup the ID3D11DepthStencilView.
		const HRESULT result_depth_stencil_view = SetupDepthStencilView();
		if (FAILED(result_depth_stencil_view)) {
			Error("Depth stencil view setup failed: %ld.", result_depth_stencil_view);
			return result_depth_stencil_view;
		}
		// Bind one or more render targets atomically and 
		// the depth-stencil buffer to the output-merger stage.
		// 1. Number of render targets to bind.
		// 2. Pointer to an array of ID3D11RenderTargetViews
		// 3. The depth-stencil state.
		m_device_context2->OMSetRenderTargets(1, &m_render_target_view, m_depth_stencil_view);

		// Setup the D3D11_VIEWPORT.
		const HRESULT result_view_port = SetupViewPort();
		if (FAILED(result_view_port)) {
			Error("Viewport setup failed: %ld.", result_view_port);
			return result_view_port;
		}

		return S_OK;
	}

	HRESULT Renderer::UnitializeRenderer() {
		// Switch to windowed mode since Direct3D is incapable of when in fullscreen mode
		// due to certain threading issues that occur behind the scenes.
		if (m_swap_chain2) {
			m_swap_chain2->SetFullscreenState(FALSE, nullptr);
		}

		// Reset any device context to the default settings. 
		if (m_device_context2) {
			m_device_context2->ClearState();
		}

		// Release D3D11 components.
		SAFE_RELEASE(m_depth_stencil);
		SAFE_RELEASE(m_depth_stencil_view);
		SAFE_RELEASE(m_render_target_view);
		SAFE_RELEASE(m_swap_chain2);
		SAFE_RELEASE(m_device_context2);
		SAFE_RELEASE(m_device2);

		return S_OK;
	}

	HRESULT Renderer::SetupDevice() {
		// Set the runtime layers to enable.
		UINT create_device_flags = 0;
#ifdef _DEBUG
		create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		// Get the ID3D11Device and ID3D11DeviceContext.
		ID3D11Device *device = nullptr;
		ID3D11DeviceContext *device_context = nullptr;
		HRESULT result_device = S_OK;
		for (UINT i = 0; i < _countof(g_driver_types); ++i) {
			m_driver_type = g_driver_types[i];
			result_device = D3D11CreateDevice(
				nullptr,							// Adapter.
				m_driver_type,						// Driver type.
				nullptr,							// A handle to a DLL that implements a software rasterizer.
				create_device_flags,				// The runtime layers to enable.
				g_feature_levels,					// The order of feature levels to attempt to create.
				_countof(g_feature_levels),			// The number of feature levels.
				D3D11_SDK_VERSION,					// The SDK version.
				&device,							// The address of a pointer to the ID3D11Device that represents the device created.
				&m_feature_level,					// The address of a pointer to the supported feature level.
				&device_context						// The address of a pointer to the ID3D11DeviceContext.
			);
			if (SUCCEEDED(result_device)) {
				break;
			}
		}
		if (FAILED(result_device)) {
			Error("ID3D11Device creation failed: %ld.", result_device);
			return result_device;
		}

		// Get the ID3D11Device2.
		const HRESULT result_device2 = device->QueryInterface(__uuidof(ID3D11Device2), (void **)&m_device2);
		// Release the ID3D11Device.
		device->Release();
		if (FAILED(result_device2)) {
			Error("ID3D11Device2 creation failed: %ld.", result_device2);
			return result_device2;
		}
		// Get the ID3D11DeviceContext2.
		const HRESULT result_device_context2 = device_context->QueryInterface(__uuidof(ID3D11DeviceContext2), (void **)&m_device_context2);
		// Release the ID3D11DeviceContext.
		device_context->Release();
		if (FAILED(result_device_context2)) {
			Error("ID3D11DeviceContext2 creation failed: %ld.", result_device_context2);
			return result_device_context2;
		}
	}

	HRESULT Renderer::SetupSwapChain() {
		// Get the IDXGIDevice3.
		IDXGIDevice3 *dxgi_device3 = nullptr;
		const HRESULT result_dxgi_device3 = m_device2->QueryInterface(__uuidof(IDXGIDevice3), (void **)&dxgi_device3);
		if (FAILED(result_dxgi_device3)) {
			Error("IDXGIDevice3 creation failed: %ld.", result_dxgi_device3);
			return result_dxgi_device3;
		}
		// Get the IDXGIAdapter.
		IDXGIAdapter *dxgi_adapter = nullptr;
		const HRESULT result_dxgi_adapter = dxgi_device3->GetAdapter(&dxgi_adapter);
		// Release the IDXGIDevice3.
		dxgi_device3->Release();
		if (FAILED(result_dxgi_adapter)) {
			Error("IDXGIAdapter creation failed: %ld.", result_dxgi_adapter);
			return result_dxgi_adapter;
		}
		// Get the IDXGIFactory3.
		IDXGIFactory3* dxgi_factory3 = nullptr;
		const HRESULT result_dxgi_factory3 = dxgi_adapter->GetParent(__uuidof(IDXGIFactory3), (void **)&dxgi_factory3);
		// Release the IDXGIAdapter.
		dxgi_adapter->Release();
		if (FAILED(result_dxgi_factory3)) {
			Error("IDXGIFactory3 creation failed: %ld.", result_dxgi_factory3);
			return result_dxgi_factory3;
		}

		// DXGI_MWA_NO_WINDOW_CHANGES: Prevent DXGI from monitoring an applications message queue; this makes DXGI unable to respond to mode changes.
		// DXGI_MWA_NO_ALT_ENTER:      Prevent DXGI from responding to an alt-enter sequence.
		// DXGI_MWA_NO_PRINT_SCREEN:   Prevent DXGI from responding to a print-screen key.
		dxgi_factory3->MakeWindowAssociation(m_hwindow, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER | DXGI_MWA_NO_PRINT_SCREEN);

		// Create a DXGI_SWAP_CHAIN_DESC1.
		DXGI_SWAP_CHAIN_DESC1 swap_chain_desc;
		ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));
		swap_chain_desc.Width              = g_device_enumeration->GetDisplayMode()->Width;	// The resolution width.
		swap_chain_desc.Height             = g_device_enumeration->GetDisplayMode()->Height;// The resolution height.
		swap_chain_desc.Format             = g_device_enumeration->GetDisplayMode()->Format;// The display format.
		swap_chain_desc.SampleDesc.Count   = 1;												// The number of multisamples per pixel.
		swap_chain_desc.SampleDesc.Quality = 0;												// The image quality level. (lowest)
		swap_chain_desc.BufferUsage        = DXGI_USAGE_RENDER_TARGET_OUTPUT;				// Use the surface or resource as an output render target.
		swap_chain_desc.BufferCount        = 1;												// The number of buffers in the swap chain.
		swap_chain_desc.Flags              = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		// Get the IDXGISwapChain1.
		IDXGISwapChain1 *swap_chain1;
		const HRESULT result_swap_chain1 = dxgi_factory3->CreateSwapChainForHwnd(m_device2, m_hwindow, &swap_chain_desc, nullptr, nullptr, &swap_chain1);
		// Release the IDXGIFactory3.
		dxgi_factory3->Release();
		if (FAILED(result_swap_chain1)) {
			Error("IDXGISwapChain1 creation failed: %ld.", result_swap_chain1);
			return result_swap_chain1;
		}
		// Get the IDXGISwapChain2.
		const HRESULT result_swap_chain2 = swap_chain1->QueryInterface(__uuidof(IDXGISwapChain2), (void **)&m_swap_chain2);
		// Release the IDXGISwapChain1.
		swap_chain1->Release();
		if (FAILED(result_swap_chain2)) {
			Error("IDXGISwapChain2 creation failed: %ld.", result_swap_chain2);
			return result_swap_chain2;
		}

		return S_OK;
	}

	HRESULT Renderer::SetupRenderTargetView() {
		// Access the only back buffer of the swap-chain.
		ID3D11Texture2D *back_buffer = nullptr;
		const HRESULT result_back_buffer = m_swap_chain2->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&back_buffer);
		if (FAILED(result_back_buffer)) {
			Error("Back buffer texture creation failed: %ld.", result_back_buffer);
			return result_back_buffer;
		}
		// Create a ID3D11RenderTargetView.
		const HRESULT result_render_target_view = m_device2->CreateRenderTargetView(back_buffer, nullptr, &m_render_target_view);
		// Release the back buffer.
		back_buffer->Release();
		if (FAILED(result_render_target_view)) {
			Error("ID3D11RenderTargetView creation failed: %ld.", result_render_target_view);
			return result_render_target_view;
		}

		return S_OK;
	}

	HRESULT Renderer::SetupDepthStencilView() {
		// Create the depth stencil texture.
		D3D11_TEXTURE2D_DESC depth_stencil_desc;
		ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc));
		depth_stencil_desc.Width              = g_device_enumeration->GetDisplayMode()->Width;	// Texture width (in texels).
		depth_stencil_desc.Height             = g_device_enumeration->GetDisplayMode()->Height;	// Texture height (in texels).
		depth_stencil_desc.MipLevels          = 1;                                              // The maximum number of mipmap levels in the texture.
		depth_stencil_desc.ArraySize          = 1;							                    // Number of textures in the texture array.
		depth_stencil_desc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;                  // Texture format.
		depth_stencil_desc.SampleDesc.Count   = 1;							                    // The number of multisamples per pixel.
		depth_stencil_desc.SampleDesc.Quality = 0;							                    // The image quality level. (lowest)
		depth_stencil_desc.Usage              = D3D11_USAGE_DEFAULT;			                // Value that identifies how the texture is to be read from and written to.
		depth_stencil_desc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;		                // Flags for binding to pipeline stages. 
		depth_stencil_desc.CPUAccessFlags     = 0;							                    // No CPU access is necessary.
		depth_stencil_desc.MiscFlags          = 0;							                    // Flags that identify other, less common resource options.
		const HRESULT result_depth_stencil    = m_device2->CreateTexture2D(&depth_stencil_desc, nullptr, &m_depth_stencil);
		if (FAILED(result_depth_stencil)) {
			Error("Depth-stencil texture creation failed: %ld.", result_depth_stencil);
			return result_depth_stencil;
		}

		// Create the depth stencil view.
		D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
		ZeroMemory(&depth_stencil_view_desc, sizeof(depth_stencil_view_desc));
		depth_stencil_view_desc.Format             = depth_stencil_desc.Format;
		depth_stencil_view_desc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
		depth_stencil_view_desc.Texture2D.MipSlice = 0;
		const HRESULT result_depth_stencil_view    = m_device2->CreateDepthStencilView(m_depth_stencil, &depth_stencil_view_desc, &m_depth_stencil_view);
		if (FAILED(result_depth_stencil_view)) {
			Error("Depth-stencil view creation failed: %ld.", result_depth_stencil_view);
			return result_depth_stencil_view;
		}

		return S_OK;
	}

	HRESULT Renderer::SetupViewPort() {
		// Setup the (default) viewport
		D3D11_VIEWPORT viewport;
		viewport.TopLeftX = 0;			// x position of the left hand side of the viewport.
		viewport.TopLeftY = 0;			// y position of the top of the viewport.
		viewport.Width    = (FLOAT)g_device_enumeration->GetDisplayMode()->Width; // Width of the viewport.
		viewport.Height   = (FLOAT)g_device_enumeration->GetDisplayMode()->Height;// Height of the viewport.
		viewport.MinDepth = 0.0f;		// Minimum depth of the viewport.
		viewport.MaxDepth = 1.0f;		// Maximum depth of the viewport.

		// Bind an array of viewports to the rasterizer stage of the pipeline.
		// 1. Number of viewports to bind.
		// 2. An array of D3D11_VIEWPORT structures to bind to the device.
		m_device_context2->RSSetViewports(1, &viewport);

		return S_OK;
	}

	void Renderer::Render(double elapsed_time) {
		// A solarized dark background color (some basic colors can be found in <directxcolors.h>)
		const XMVECTORF32 background_color = { 0.0f, 0.117647058f, 0.149019608f, 1.000000000f };

		// Clear the back buffer.
		m_device_context2->ClearRenderTargetView(m_render_target_view, background_color);
		// Clear the depth buffer to 1.0 (i.e. max depth).
		m_device_context2->ClearDepthStencilView(m_depth_stencil_view, D3D11_CLEAR_DEPTH, 1.0f, 0);

		// Present the back buffer to the front buffer.
		m_swap_chain2->Present(0, 0);
	}

	void Renderer::SwitchMode(bool toggle) {

		// Release the swap chain buffers.
		m_render_target_view->Release();

		BOOL current = false;
		if (toggle) {
			m_swap_chain2->GetFullscreenState(&current, nullptr);
			current = !current;
			m_swap_chain2->SetFullscreenState(current, nullptr);
		}

		// Recreate the swap chain buffers.
		m_swap_chain2->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
		SetupRenderTargetView();

		m_swap_chain2->GetFullscreenState(&current, nullptr);
		m_fullscreen = (current != 0);
	}
}