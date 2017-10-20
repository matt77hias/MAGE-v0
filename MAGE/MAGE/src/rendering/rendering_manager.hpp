#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\renderer.hpp"
#include "rendering\rendering_output_manager.hpp"
#include "rendering\rendering_state_manager.hpp"
#include "rendering\display_configuration.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of rendering managers.
	 */
	class RenderingManager final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the rendering manager associated with the current engine.

		 @pre			The current engine must exist.
		 @return		A pointer to the rendering manager associated with the 
						current engine.
		 */
		static const RenderingManager *Get() noexcept;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a rendering manager.

		 @pre			@a display_configuration is not equal to @c nullptr.
		 @param[in]		hwindow
						The main window handle.
		 @param[in]		display_configuration
						A pointer to the display configuration.
		 */
		explicit RenderingManager(HWND hwindow, 
			const DisplayConfiguration *display_configuration);

		/**
		 Constructs a rendering manager from the given rendering manager.

		 @param[in]		rendering_manager
						A reference to a rendering manager to copy.
		 */
		RenderingManager(const RenderingManager &rendering_manager) = delete;

		/**
		 Constructs a rendering manager by moving the given rendering manager.

		 @param[in]		rendering_manager
						A reference to a rendering manager to move.
		 */
		RenderingManager(RenderingManager &&rendering_manager);

		/**
		 Destructs this rendering manager.
		 */
		~RenderingManager();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given rendering manager to this rendering manager.

		 @param[in]		rendering_manager
						A reference to a rendering manager to copy.
		 @return		A reference to the copy of the given rendering manager 
						(i.e. this rendering manager).
		 */
		RenderingManager &operator=(
			const RenderingManager &rendering_manager) = delete;

		/**
		 Moves the given rendering manager to this rendering manager.

		 @param[in]		rendering_manager
						A reference to a rendering manager to move.
		 @return		A reference to the moved rendering manager (i.e. this 
						rendering manager).
		 */
		RenderingManager &operator=(
			RenderingManager &&rendering_manager) = delete;

		//---------------------------------------------------------------------
		// Member Methods: DXGI Adapter and Output
		//---------------------------------------------------------------------

		/**
		 Returns the adapter of this rendering manager.

		 @return		A pointer to the adapter of this rendering manager.
		 */
		IDXGIAdapter2 *GetAdapter() const noexcept {
			return m_display_configuration->GetAdapter();
		}

		/**
		 Returns the output of this rendering manager.

		 @return		A pointer to the device context of this rendering 
						manager.
		 */
		IDXGIOutput2 *GetOutput() const noexcept {
			return m_display_configuration->GetOutput();
		}

		//---------------------------------------------------------------------
		// Member Methods: D3D11 Device and Device Context
		//---------------------------------------------------------------------

		/**
		 Returns the device of this rendering manager.

		 @return		A pointer to the device of this rendering manager.
		 */
		ID3D11Device2 *GetDevice() const noexcept {
			return m_device.Get();
		}

		/**
		 Returns the device context of this rendering manager.

		 @return		A pointer to the device context of this rendering 
						manager.
		 */
		ID3D11DeviceContext2 *GetDeviceContext() const noexcept {
			return m_device_context.Get();
		}
		
		//---------------------------------------------------------------------
		// Member Methods: Swap Chain
		//---------------------------------------------------------------------

		/**
		 Returns the back buffer RTV of this rendering manager.

		 @return		A pointer to the back buffer RTV of this rendering 
						manager.
		 @note			The back buffer RTV and SRV cannot both be bound at the 
						same time.
		 */
		ID3D11RenderTargetView *GetBackBufferRTV() const noexcept {
			return m_back_buffer_rtv.Get();
		}
		
		//---------------------------------------------------------------------
		// Member Methods: Rendering
		//---------------------------------------------------------------------

		/**
		 Returns the rendering output manager of this rendering manager.

		 @return		A pointer to the rendering output manager of this 
						rendering manager.
		 */
		Renderer *GetRenderer() const noexcept {
			return m_renderer.get();
		}

		/**
		 Returns the rendering output manager of this rendering manager.

		 @return		A pointer to the rendering output manager of this 
						rendering manager.
		 */
		const RenderingOutputManager *GetRenderingOutputManager() const noexcept {
			return m_rendering_output_manager.get();
		}

		/**
		 Returns the rendering state manager of this rendering manager.

		 @return		A pointer to the rendering state manager of this 
						rendering manager.
		 */
		const RenderingStateManager *GetRenderingStateManager() const noexcept {
			return m_rendering_state_manager.get();
		}

		//---------------------------------------------------------------------
		// Member Methods: Display Configuration
		//---------------------------------------------------------------------

		/**
		 Returns the width in pixels of the display of this rendering manager.

		 @return		The width in pixels of the display of this rendering 
						manager.
		 */
		U32 GetWidth() const noexcept {
			return m_display_configuration->GetDisplayWidth();
		}

		/**
		 Returns the height in pixels of the display of this rendering manager.

		 @return		The height in pixels of the display of this rendering 
						manager.
		 */
		U32 GetHeight() const noexcept {
			return m_display_configuration->GetDisplayHeight();
		}
		
		/**
		 Checks whether this rendering manager renders in windowed mode.

		 @return		@c true if this rendering manager renders in 
						windowed mode. @c false otherwise.
		*/
		bool IsWindowed() const {
			return !IsFullScreen();
		}
		
		/**
		 Checks whether this rendering manager renders in full screen mode.

		 @return		@c true if this rendering manager renders in full 
						screen mode. @c false otherwise.
		 */
		bool IsFullScreen() const {
			BOOL current = false;
			m_swap_chain->GetFullscreenState(&current, nullptr);
			return current != 0;
		}
		
		/**
		 Checks whether this rendering manager lost its mode, i.e. the current 
		 mode of this rendering manager differs from the current mode of its 
		 swap chain (due to for example ALT + TAB).

		 @return		@c true if this rendering manager lost its mode. 
						@c false otherwise.
		 */
		bool LostMode() const {
			return m_fullscreen == IsWindowed();
		}

		/**
		 Sets the initial mode of this rendering manager.
		 
		 Call this method before starting the game loop.
		 */
		void SetInitialMode() noexcept {
			if (m_display_configuration->IsFullScreen()) {
				SwitchMode(true);
			}
		}
		
		/**
		 Recreates the swap chain buffers and switches the mode of this 
		 rendering manager. Windowed mode is switched to full screen mode and 
		 vice versa.

		 @param[in]		toggle
						If @c true only the swap chain buffers will be 
						recreated to match the current mode of the swap chain 
						and no mode switch will occurs. If @c false both the 
						swap chain buffers will be replaced and a mode switch 
						will occur.
		 */
		void SwitchMode(bool toggle);

		/**
		 Returns the gamma value of this rendering manager used for gamma 
		 correction.

		 @return		The gamma value of this rendering manager used for 
						gamma correction.
		 */
		F32 GetGamma() const noexcept {
			return m_display_configuration->GetGamma();
		}

		//---------------------------------------------------------------------
		// Member Methods: Rendering
		//---------------------------------------------------------------------

		/**
		 Binds the persistent state of this rendering manager.

		 @throws		FormattedException
						Failed to bind the persistent state of this rendering 
						manager.
		 */
		void BindPersistentState();

		/**
		 Begins the rendering of the current frame.

		 @pre			This rendering manager is not inside a begin/end pair.
		 */
		void BeginFrame() noexcept;

		/**
		 Ends the rendering of the current frame.

		 @pre			This rendering manager is inside a begin/end pair.
		 */
		void EndFrame() noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Initializes the different systems of this rendering manager.

		 @throws		FormattedException
						Failed to initialize at least one of the different 
						systems of this rendering manager.
		 */
		void InitializeSystems();

		/**
		 Uninitializes the different systems of this rendering manager.
		 */
		void UninitializeSystems() noexcept;

		//---------------------------------------------------------------------
		// Member Methods: D3D11 Device and Device Context
		//---------------------------------------------------------------------

		/**
		 Sets up the D3D11 device and context of this rendering manager.

		 @throws		FormattedException
						Failed to set up the device and device context of this 
						rendering manager.
		 */
		void SetupDevice();

		//---------------------------------------------------------------------
		// Member Methods: Swap Chain
		//---------------------------------------------------------------------
		
		/**
		 Sets up the swap chain of this rendering manager with its render 
		 target view and depth stencil view.

		 @throws		FormattedException
						Failed to set up the swap chain of this rendering 
						manager.
		 */
		void SetupSwapChain();
		
		/**
		 Resets the swap chain of this rendering manager with its render target
		 view and depth stencil view.

		 @throws		FormattedException
						Failed to set up the swap chain of this rendering 
						manager.
		 */
		void ResetSwapChain();

		/**
		 Creates the swap chain of this rendering manager.

		 @throws		FormattedException
						Failed to create the swap chain of this rendering 
						manager.
		 */
		void CreateSwapChain();
		
		/**
		 Creates the render target view of the back buffer of this rendering 
		 manager.

		 @throws		FormattedException
						Failed to obtain the back buffer resource of this 
						rendering manager.
		 @throws		FormattedException
						Failed to create the render target view of the back 
						buffer of this rendering manager.
		 */
		void CreateBackBufferRTV();

		//---------------------------------------------------------------------
		// Member Variables: Display Configuration
		//---------------------------------------------------------------------

		/**
		 The handle of the parent window of this rendering manager.
		 */
		const HWND m_hwindow;

		/**
		 A flag indicating whether this rendering manager uses a full screen 
		 mode or not (i.e. a windowed mode).
		 */
		bool m_fullscreen;

		/**
		 A flag indicating whether this rendering manager is inside a begin/end 
		 pair.
		 */
		bool m_in_begin_end_pair;

		/**
		 A pointer to the display configuration of this rendering manager.
		 */
		UniquePtr< DisplayConfiguration > m_display_configuration;

		//---------------------------------------------------------------------
		// Member Variables: D3D11 Device and Device Context
		//---------------------------------------------------------------------

		/**
		 A pointer to the feature level of this rendering manager.
		 */
		D3D_FEATURE_LEVEL m_feature_level;

		/**
		 A pointer to the device of this rendering manager.
		 */
		ComPtr< ID3D11Device2 >	m_device;

		/**
		 A pointer to the device context of this rendering manager.
		 */
		ComPtr< ID3D11DeviceContext2 > m_device_context;

		//---------------------------------------------------------------------
		// Member Variables: Swap Chain
		//---------------------------------------------------------------------

		/**
		 A pointer to the swap chain of this rendering manager.
		 */
		ComPtr< IDXGISwapChain2 > m_swap_chain;
		
		/**
		 A pointer to the render target view of the back buffer of this 
		 rendering manager.
		 */
		ComPtr< ID3D11RenderTargetView > m_back_buffer_rtv;

		//---------------------------------------------------------------------
		// Member Variables: Rendering
		//---------------------------------------------------------------------

		/**
		 A pointer to the renderer of this rendering manager.
		 */
		UniquePtr< Renderer > m_renderer;

		/**
		 A pointer to the rendering output manager of this rendering manager.
		 */
		UniquePtr< RenderingOutputManager > m_rendering_output_manager;

		/**
		 A pointer to the rendering state manager of this rendering manager.
		 */
		UniquePtr< RenderingStateManager > m_rendering_state_manager;
	};
}