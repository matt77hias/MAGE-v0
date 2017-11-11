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
		const DisplayConfiguration *display_configuration) 
		: m_hwindow(hwindow),
		m_display_configuration(
			MakeUnique< DisplayConfiguration >(*display_configuration)),
		m_feature_level(),
		m_device(), 
		m_device_context(), 
		m_swap_chain(), 
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
		m_swap_chain = MakeUnique< SwapChain >(
			           m_device.Get(), m_hwindow, 
			           m_display_configuration.get());

		// Setup the rendering output manager.
		m_rendering_output_manager = MakeUnique< RenderingOutputManager >(
			                         m_device.Get(), 
			                         m_display_configuration->GetDisplayWidth(),
			                         m_display_configuration->GetDisplayHeight(),
									 m_display_configuration->GetAADescriptor());
		
		// Setup the rendering state manager.
		m_rendering_state_manager = MakeUnique< RenderingStateManager >(
			                        m_device.Get());
		// Setup the renderer.
		m_renderer = MakeUnique< Renderer >(
			         m_device.Get(), 
			         m_device_context.Get(), 
			         m_display_configuration->GetDisplayWidth(),
			         m_display_configuration->GetDisplayHeight());
	}

	void RenderingManager::UninitializeSystems() noexcept {
		// Uninitialize the swap chain.
		m_swap_chain.reset();

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

		ComPtr< ID3D11Device > device;
		ComPtr< ID3D11DeviceContext > device_context;
		{
			// Get the ID3D11Device and ID3D11DeviceContext.
			const HRESULT result = D3D11CreateDevice(
				m_display_configuration->GetAdapter(),
				D3D_DRIVER_TYPE_UNKNOWN,
				nullptr,
				create_device_flags,
				Pipeline::s_feature_levels,
				_countof(Pipeline::s_feature_levels),
				D3D11_SDK_VERSION,
				device.GetAddressOf(),
				&m_feature_level,
				device_context.GetAddressOf());
			ThrowIfFailed(result,
				"ID3D11Device creation failed: %08X.", result);
		}

		{
			// Get the ID3D11Device5.
			const HRESULT result = device.As(&m_device);
			ThrowIfFailed(result, 
				"ID3D11Device2 creation failed: %08X.", result);
		}
		{
			// Get the ID3D11DeviceContext4.
			const HRESULT result = device_context.As(&m_device_context);
			ThrowIfFailed(result,
				"ID3D11DeviceContext2 creation failed: %08X.", result);
		}
	}

	//-------------------------------------------------------------------------
	// RenderingManager: Rendering
	//-------------------------------------------------------------------------

	void RenderingManager::BindPersistentState() {
		m_rendering_state_manager->BindPersistentState();
		m_renderer->BindPersistentState();
	}
}