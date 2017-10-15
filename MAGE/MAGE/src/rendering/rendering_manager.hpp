#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

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
		// Member Methods
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
		
		/**
		 Returns the back buffer SRV of this rendering manager.

		 @return		A pointer to the back buffer SRV of this rendering 
						manager.
		 @note			The back buffer RTV and SRV cannot both be bound at the 
						same time.
		 */
		ID3D11ShaderResourceView *GetBackBufferSRV() const noexcept {
			return m_back_buffer_srv.Get();
		}
		
		/**
		 Returns the depth buffer DSV of this rendering manager.

		 @return		A pointer to the depth buffer DSV of this rendering 
						manager.
		 @note			The depth buffer DSV and SRV cannot both be bound at 
						the same time.
		 */
		ID3D11DepthStencilView *GetDepthBufferDSV() const noexcept {
			return m_depth_buffer_dsv.Get();
		}
		
		/**
		 Returns the depth buffer SRV of this rendering manager.

		 @return		A pointer to the depth buffer SRV of this rendering 
						manager.
		 @note			The depth buffer DSV and SRV cannot both be bound at 
						the same time.
		 */
		ID3D11ShaderResourceView *GetDepthBufferSRV() const noexcept {
			return m_depth_buffer_srv.Get();
		}

		/**
		 Returns the rendering state manager of this rendering manager.

		 @return		A pointer to the rendering state manager of this 
						rendering manager.
		 */
		const RenderingStateManager *GetRenderingStateManager() const noexcept {
			return m_rendering_state_manager.get();
		}

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
		 Binds the RTV and DSV of this rendering manager.
		 */
		void BindRTVAndDSV() const noexcept;

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
		 Initializes this rendering manager.

		 @throws		FormattedException
						Failed to initialize this rendering manager.
		 */
		void InitializeRenderingManager();

		/**
		 Uninitializes this rendering manager.
		 */
		void UninitializeRenderingManager() noexcept;

		/**
		 Sets up the D3D11 device and context of this rendering manager.

		 @throws		FormattedException
						Failed to set up the device and device context of this 
						rendering manager.
		 */
		void SetupDevice();
		
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
		 Creates the render target view, shader resource view of the back 
		 buffer of this rendering manager.

		 @throws		FormattedException
						Failed to obtain the back buffer resource of this 
						rendering manager.
		 @throws		FormattedException
						Failed to create the render target view of the back 
						buffer of this rendering manager.
		 @throws		FormattedException
						Failed to create the shader resource view of the back 
						buffer of this rendering manager.
		 */
		void CreateBackBufferRTVandSRV();
		
		/**
		 Creates the depth stencil view and shader resource view of the depth 
		 buffer of this rendering manager.

		 @throws		FormattedException
						Failed to create the depth buffer resource of this 
						rendering manager.
		 @throws		FormattedException
						Failed to create the depth stencil view of the depth 
						buffer of this rendering manager.
		 @throws		FormattedException
						Failed to create the shader resource view of the depth 
						buffer of this rendering manager.
		 */
		void CreateDepthBufferDSVandSRV();

		//---------------------------------------------------------------------
		// Member Variables
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

		/**
		 A pointer to the swap chain of this rendering manager.
		 */
		ComPtr< IDXGISwapChain2 > m_swap_chain;
		
		/**
		 A pointer to the render target view of the back buffer of this 
		 rendering manager.
		 */
		ComPtr< ID3D11RenderTargetView > m_back_buffer_rtv;

		/**
		 A pointer to the shader resource view of the back buffer of this 
		 rendering manager.
		 */
		ComPtr< ID3D11ShaderResourceView > m_back_buffer_srv;

		/**
		 A pointer to the depth stencil view of the depth buffer of this 
		 rendering manager.
		 */
		ComPtr< ID3D11DepthStencilView > m_depth_buffer_dsv;

		/**
		 A pointer to the shader resource view of the depth buffer of this 
		 rendering manager.
		 */
		ComPtr< ID3D11ShaderResourceView > m_depth_buffer_srv;

		/**
		 A pointer to the rendering state manager of this rendering manager.
		 */
		UniquePtr< RenderingStateManager > m_rendering_state_manager;
	};
}