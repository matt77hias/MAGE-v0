//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"
#include "rendering\renderer.hpp"
#include "imgui\imgui_impl_dx11.hpp"
#include "logging\error.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <iterator>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// RenderingManager::Impl
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of rendering managers.
	 */
	class RenderingManager::Impl final {

	public:

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
		explicit Impl(HWND window, 
					  const DisplayConfiguration *display_configuration);

		/**
		 Constructs a rendering manager from the given rendering manager.

		 @param[in]		manager
						A reference to a rendering manager to copy.
		 */
		Impl(const Impl &manager) = delete;

		/**
		 Constructs a rendering manager by moving the given rendering manager.

		 @param[in]		manager
						A reference to a rendering manager to move.
		 */
		Impl(Impl &&manager) noexcept;

		/**
		 Destructs this rendering manager.
		 */
		~Impl();

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
		Impl &operator=(const Impl &manager) = delete;

		/**
		 Moves the given rendering manager to this rendering manager.

		 @param[in]		manager
						A reference to a rendering manager to move.
		 @return		A reference to the moved rendering manager (i.e. this 
						rendering manager).
		 */
		Impl &operator=(Impl &&manager) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the display configuration of this rendering manager.

		 @return		A pointer to the display configuration of this 
						rendering manager.
		 */
		[[nodiscard]]const DisplayConfiguration *
			GetDisplayConfiguration() const noexcept {

			return m_display_configuration.get();
		}

		/**
		 Returns the swap chain of this rendering manager.

		 @return		A pointer to the swap chain of this rendering manager.
		 */
		[[nodiscard]]SwapChain *GetSwapChain() const noexcept {
			return m_swap_chain.get();
		}

		/**
		 Returns the resource manager of this rendering manager.

		 @return		A pointer to the resource manager of this 
						rendering manager.
		 */
		[[nodiscard]]ResourceManager *GetResourceManager() const noexcept {
			return m_resource_manager.get();
		}

		/**
		 Binds the persistent state of this rendering manager.

		 @throws		Exception
						Failed to bind the persistent state of this rendering 
						manager.
		 @throws		Exception
						Failed to bind the persistent state of this rendering 
						manager.
		 */
		void BindPersistentState();

		/**
		 Renders the given scene.

		 @param[in]		scene
						A reference to the scene.
		 @throws		Exception
						Failed to render the scene.
		 */
		void Render(const Scene &scene);
		
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

		/**
		 Sets up the D3D11 device and context of this rendering manager.

		 @throws		Exception
						Failed to set up the device and device context of this 
						rendering manager.
		 */
		void SetupDevice();

		//---------------------------------------------------------------------
		// Member Variables: Display Configuration
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
		 A pointer to the resource manager of this rendering manager.
		 */
		UniquePtr< ResourceManager > m_resource_manager;
	};

	RenderingManager::Impl::Impl(HWND window, 
								 const DisplayConfiguration *configuration)
		: m_window(window),
		m_display_configuration(
			MakeUnique< DisplayConfiguration >(*configuration)),
		m_feature_level(),
		m_device(), 
		m_device_context(), 
		m_swap_chain(), 
		m_renderer(),
		m_resource_manager() {

		Assert(m_window);
		Assert(m_display_configuration);

		InitializeSystems();
	}

	RenderingManager::Impl::Impl(RenderingManager::Impl &&manager) noexcept = default;

	RenderingManager::Impl::~Impl() {
		UninitializeSystems();
	}

	void RenderingManager::Impl::InitializeSystems() {
		// Setup the device and device context.
		SetupDevice();
		
		// Setup the swap chain.
		m_swap_chain = MakeUnique< SwapChain >(m_device.Get(), 
				                               m_window, 
			                                   m_display_configuration.get());

		// Setup the output manager.
		// Setup the resource manager.
		m_resource_manager = MakeUnique< ResourceManager >(m_device.Get());
		// Setup the renderer.
		m_renderer         = MakeUnique< Renderer >(m_device.Get(),
													m_device_context.Get(), 
													m_display_configuration.get(),
													m_swap_chain.get(), 
													m_resource_manager.get());

		// Setup ImGui.
		ImGui_ImplDX11_Init(m_window, m_device.Get(), m_device_context.Get());
	}

	void RenderingManager::Impl::UninitializeSystems() noexcept {
		// Uninitialize ImGui.
		ImGui_ImplDX11_Shutdown();

		// Uninitialize the swap chain.
		m_swap_chain.reset();

		// Reset any device context to the default settings. 
		if (m_device_context) {
			m_device_context->ClearState();
		}
	}

	void RenderingManager::Impl::SetupDevice() {
		// Set the runtime layers to enable.
		U32 create_device_flags = 0u;
		#ifdef _DEBUG
		create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
		#endif

		ComPtr< ID3D11Device > device;
		ComPtr< ID3D11DeviceContext > device_context;
		{
			// Get the ID3D11Device and ID3D11DeviceContext.
			const HRESULT result 
				= D3D11CreateDevice(m_display_configuration->GetAdapter(),
				                    D3D_DRIVER_TYPE_UNKNOWN,
				                    nullptr,
				                    create_device_flags,
				                    Pipeline::s_feature_levels,
				                    static_cast< U32 >(std::size(Pipeline::s_feature_levels)),
				                    D3D11_SDK_VERSION,
				                    device.GetAddressOf(),
				                    &m_feature_level,
				                    device_context.GetAddressOf());
			ThrowIfFailed(result, "ID3D11Device creation failed: %08X.", result);
		}

		{
			// Get the D3D11Device.
			const HRESULT result = device.As(&m_device);
			ThrowIfFailed(result, 
				"D3D11Device creation failed: %08X.", result);
		}
		{
			// Get the D3D11DeviceContext.
			const HRESULT result = device_context.As(&m_device_context);
			ThrowIfFailed(result,
				"D3D11DeviceContext creation failed: %08X.", result);
		}
	}

	void RenderingManager::Impl::BindPersistentState() {
		m_renderer->BindPersistentState();
	}

	void RenderingManager::Impl::Render(const Scene &scene) {
		m_swap_chain->Clear();

		ImGui_ImplDX11_NewFrame();
		
		m_renderer->Render(scene);

		ImGui::Render();

		m_swap_chain->Present();
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// RenderingManager
	//-------------------------------------------------------------------------
	#pragma region

	[[nodiscard]]const RenderingManager *RenderingManager::Get() noexcept {
		Assert(Engine::Get());

		return Engine::Get()->GetRenderingManager();
	}

	RenderingManager::RenderingManager(HWND window, 
									   const DisplayConfiguration *configuration) 
		: m_impl(MakeUnique< Impl >(window, configuration)) {}

	RenderingManager::RenderingManager(RenderingManager &&manager) noexcept = default;

	RenderingManager::~RenderingManager() = default;

	[[nodiscard]]const DisplayConfiguration *
		RenderingManager::GetDisplayConfiguration() const noexcept {

		return m_impl->GetDisplayConfiguration();
	}
	
	[[nodiscard]]SwapChain *RenderingManager::GetSwapChain() const noexcept {
		return m_impl->GetSwapChain();
	}
	
	[[nodiscard]]ResourceManager *
		RenderingManager::GetResourceManager() const noexcept {

		return m_impl->GetResourceManager();
	}

	void RenderingManager::BindPersistentState() {
		m_impl->BindPersistentState();
	}

	void RenderingManager::Render(const Scene &scene) {
		m_impl->Render(scene);
	}

	#pragma endregion
}