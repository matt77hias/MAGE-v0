//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering_manager.hpp"
#include "renderer\renderer.hpp"
#include "imgui_impl_dx11.hpp"

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
namespace mage::rendering {

	U32 Pipeline::s_nb_draws = 0u;

	//-------------------------------------------------------------------------
	// Manager::Impl
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of rendering managers.
	 */
	class Manager::Impl final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a rendering manager.

		 @param[in]		window
						The main window handle.
		 @param[in]		display_configuration
						The display configuration.
		 */
		explicit Impl(NotNull< HWND > window, 
					  DisplayConfiguration display_configuration);

		/**
		 Constructs a rendering manager from the given rendering manager.

		 @param[in]		manager
						A reference to a rendering manager to copy.
		 */
		Impl(const Impl& manager) = delete;

		/**
		 Constructs a rendering manager by moving the given rendering manager.

		 @param[in]		manager
						A reference to a rendering manager to move.
		 */
		Impl(Impl&& manager) noexcept;

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
		Impl& operator=(const Impl& manager) = delete;

		/**
		 Moves the given rendering manager to this rendering manager.

		 @param[in]		manager
						A reference to a rendering manager to move.
		 @return		A reference to the moved rendering manager (i.e. this 
						rendering manager).
		 */
		Impl& operator=(Impl&& manager) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the display configuration of this rendering manager.

		 @return		A reference to the display configuration of this 
						rendering manager.
		 */
		[[nodiscard]]
		const DisplayConfiguration& GetDisplayConfiguration() const noexcept {
			return *m_display_configuration;
		}

		/**
		 Returns the swap chain of this rendering manager.

		 @return		A reference to the swap chain of this rendering 
						manager.
		 */
		[[nodiscard]]
		SwapChain& GetSwapChain() noexcept {
			return *m_swap_chain;
		}

		/**
		 Returns the swap chain of this rendering manager.

		 @return		A reference to the swap chain of this rendering 
						manager.
		 */
		[[nodiscard]]
		const SwapChain& GetSwapChain() const noexcept {
			return *m_swap_chain;
		}

		/**
		 Returns the resource manager of this rendering manager.

		 @return		A reference to the resource manager of this 
						rendering manager.
		 */
		[[nodiscard]]
		ResourceManager& GetResourceManager() const noexcept {
			return *m_resource_manager;
		}

		/**
		 Returns the world of this rendering manager.

		 @return		A reference to the world of this rendering manager.
		 */
		[[nodiscard]]
		World& GetWorld() const noexcept {
			return *m_world;
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
		 Updates this rendering manager.
		 */
		void Update();

		/**
		 Renders.

		 @throws		Exception
						Failed to render the world of this rendering manager.
		 */
		void Render();
		
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
		NotNull< HWND > m_window;

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
		 A pointer to the resource manager of this rendering manager.
		 */
		UniquePtr< ResourceManager > m_resource_manager;

		/**
		 A pointer to the world of this rendering manager.
		 */
		UniquePtr< World > m_world;

		/**
		 A pointer to the renderer of this rendering manager.
		 */
		UniquePtr< Renderer > m_renderer;
	};

	Manager::Impl::Impl(NotNull< HWND > window, 
						DisplayConfiguration configuration)
		: m_window(std::move(window)),
		m_display_configuration(
			MakeUnique< DisplayConfiguration >(std::move(configuration))),
		m_feature_level(),
		m_device(), 
		m_device_context(), 
		m_swap_chain(), 
		m_resource_manager(), 
		m_world(), 
		m_renderer() {

		InitializeSystems();
	}

	Manager::Impl::Impl(Manager::Impl&& manager) noexcept = default;

	Manager::Impl::~Impl() {
		UninitializeSystems();
	}

	void Manager::Impl::InitializeSystems() {
		// Setup the device and device context.
		SetupDevice();
		
		// Setup the swap chain.
		m_swap_chain = MakeUnique< SwapChain >(*m_device.Get(), 
											   *m_device_context.Get(),
				                               m_window, 
			                                   *m_display_configuration);

		// Setup the resource manager.
		m_resource_manager = MakeUnique< ResourceManager >(*m_device.Get());

		// Setup the world.
		m_world = MakeUnique< World >(*m_device.Get(), 
									  *m_display_configuration,
									  *m_resource_manager);
		
		// Setup the renderer.
		m_renderer = MakeUnique< Renderer >(*m_device.Get(), 
											*m_device_context.Get(), 
											*m_display_configuration, 
											*m_swap_chain, 
											*m_resource_manager);

		// Setup ImGui.
		ImGui::CreateContext();
		ImGui_ImplDX11_Init(m_window, m_device.Get(), m_device_context.Get());
	}

	void Manager::Impl::UninitializeSystems() noexcept {
		// Uninitialize ImGui.
		ImGui_ImplDX11_Shutdown();
		ImGui::DestroyContext();

		// Uninitialize the swap chain.
		m_swap_chain.reset();

		// Reset any device context to the default settings. 
		if (m_device_context) {
			m_device_context->ClearState();
		}
	}

	void Manager::Impl::SetupDevice() {
		#ifdef NDEBUG
		constexpr U32 create_device_flags = 0u;
		#else  // NDEBUG
		constexpr U32 create_device_flags = D3D11_CREATE_DEVICE_DEBUG;
		#endif // NDEBUG

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

	void Manager::Impl::BindPersistentState() {
		m_renderer->BindPersistentState();
	}

	void Manager::Impl::Update() {
		ImGui_ImplDX11_NewFrame();
	}

	void Manager::Impl::Render() {
		m_swap_chain->Clear();

		Pipeline::s_nb_draws = 0u;
		
		m_renderer->Render(GetWorld());

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		m_swap_chain->Present();
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Manager
	//-------------------------------------------------------------------------
	#pragma region

	Manager::Manager(NotNull< HWND > window, 
					 DisplayConfiguration configuration) 
		: m_impl(MakeUnique< Impl >(std::move(window), 
									std::move(configuration))) {}

	Manager::Manager(Manager&& manager) noexcept = default;

	Manager::~Manager() = default;

	[[nodiscard]]
	const DisplayConfiguration& 
		Manager::GetDisplayConfiguration() const noexcept {

		return m_impl->GetDisplayConfiguration();
	}
	
	[[nodiscard]]
	SwapChain& Manager::GetSwapChain() noexcept {
		return m_impl->GetSwapChain();
	}

	[[nodiscard]]
	const SwapChain& Manager::GetSwapChain() const noexcept {
		return m_impl->GetSwapChain();
	}
	
	[[nodiscard]]
	ResourceManager& Manager::GetResourceManager() const noexcept {
		return m_impl->GetResourceManager();
	}

	[[nodiscard]]
	World& Manager::GetWorld() const noexcept {
		return m_impl->GetWorld();
	}

	void Manager::BindPersistentState() {
		m_impl->BindPersistentState();
	}

	void Manager::Update() {
		m_impl->Update();
	}

	void Manager::Render() {
		m_impl->Render();
	}

	#pragma endregion
}