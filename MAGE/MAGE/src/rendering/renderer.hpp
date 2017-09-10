#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_state_cache.hpp"
#include "rendering\display_configuration.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of renderers.
	 */
	class Renderer final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the renderer associated with the current engine.

		 @return		A pointer to the renderer associated
						with the current engine.
		 */
		static const Renderer *Get() noexcept;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a renderer.

		 @pre			@a display_configuration is not equal to @c nullptr.
		 @param[in]		hwindow
						The main window handle.
		 @param[in]		display_configuration
						A pointer to the display configuration.
		 */
		explicit Renderer(HWND hwindow, 
			const DisplayConfiguration *display_configuration);

		/**
		 Constructs a renderer from the given renderer.

		 @param[in]		renderer
						A reference to a renderer to copy.
		 */
		Renderer(const Renderer &renderer) = delete;

		/**
		 Constructs a renderer by moving the given renderer.

		 @param[in]		renderer
						A reference to a renderer to move.
		 */
		Renderer(Renderer &&renderer);

		/**
		 Destructs this renderer.
		 */
		~Renderer();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given renderer to this renderer.

		 @param[in]		renderer
						A reference to a renderer to copy.
		 @return		A reference to the copy of the given renderer
						(i.e. this renderer).
		 */
		Renderer &operator=(const Renderer &renderer) = delete;

		/**
		 Moves the given renderer to this renderer.

		 @param[in]		renderer
						A reference to a renderer to move.
		 @return		A reference to the moved renderer
						(i.e. this renderer).
		 */
		Renderer &operator=(Renderer &&renderer) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the adapter of this renderer.

		 @return		A pointer to the adapter of this renderer.
		 */
		IDXGIAdapter2 *GetAdapter() const noexcept {
			return m_display_configuration->GetAdapter();
		}

		/**
		 Returns the output of this renderer.

		 @return		A pointer to the device context of this renderer.
		 */
		IDXGIOutput2 *GetOutput() const noexcept {
			return m_display_configuration->GetOutput();
		}

		/**
		 Returns the device of this renderer.

		 @return		A pointer to the device of this renderer.
		 */
		ID3D11Device2 *GetDevice() const noexcept {
			return m_device.Get();
		}

		/**
		 Returns the device context of this renderer.

		 @return		A pointer to the device context of this renderer.
		 */
		ID3D11DeviceContext2 *GetDeviceContext() const noexcept {
			return m_device_context.Get();
		}

		/**
		 Returns the back buffer RTV of this renderer.

		 @return		A pointer to the back buffer RTV of this renderer.
		 @note			The back buffer RTV and SRV cannot both be bound 
						at the same time.
		 */
		ID3D11RenderTargetView *GetBackBufferRTV() const noexcept {
			return m_back_buffer_rtv.Get();
		}
		
		/**
		 Returns the back buffer SRV of this renderer.

		 @return		A pointer to the back buffer SRV of this renderer.
		 @note			The back buffer RTV and SRV cannot both be bound 
						at the same time.
		 */
		ID3D11ShaderResourceView *GetBackBufferSRV() const noexcept {
			return m_back_buffer_srv.Get();
		}
		
		/**
		 Returns the depth buffer DSV of this renderer.

		 @return		A pointer to the depth buffer DSV of this renderer.
		 @note			The depth buffer DSV and SRV cannot both be bound
						at the same time.
		 */
		ID3D11DepthStencilView *GetDepthBufferDSV() const noexcept {
			return m_depth_buffer_dsv.Get();
		}
		
		/**
		 Returns the depth buffer SRV of this renderer.

		 @return		A pointer to the depth buffer SRV of this renderer.
		 @note			The depth buffer DSV and SRV cannot both be bound
						at the same time.
		 */
		ID3D11ShaderResourceView *GetDepthBufferSRV() const noexcept {
			return m_depth_buffer_srv.Get();
		}

		/**
		 Returns the rendering state cache of this renderer.

		 @return		A pointer to the rendering state cache of this renderer.
		 */
		RenderingStateCache *GetRenderingStateCache() const noexcept {
			return m_rendering_state_cache.get();
		}

		/**
		 Returns the width in pixels of the display of this renderer.

		 @return		The width in pixels of the display of this renderer.
		 */
		uint32_t GetWidth() const noexcept {
			return m_display_configuration->GetDisplayWidth();
		}

		/**
		 Returns the height in pixels of the display of this renderer.

		 @return		The height in pixels of the display of this renderer.
		 */
		uint32_t GetHeight() const noexcept {
			return m_display_configuration->GetDisplayHeight();
		}

		/**
		 Checks whether MSAA is used by this renderer.

		 @return		@c true if MSAA is used by this renderer.
						@c false otherwise.
		 */
		bool HasMSAA() const noexcept {
			return m_display_configuration->UseMSAA();
		}

		/**
		 Checks whether this renderer renders in windowed mode.

		 @return		@c true if this renderer renders in windowed mode.
						@c false otherwise.
		*/
		bool IsWindowed() const {
			return !IsFullScreen();
		}

		/**
		 Checks whether this renderer renders in full screen mode.

		 @return		@c true if this renderer renders in full screen mode.
						@c false otherwise.
		 */
		bool IsFullScreen() const {
			BOOL current = false;
			m_swap_chain->GetFullscreenState(&current, nullptr);
			return current != 0;
		}

		/**
		 Checks whether this renderer lost its mode, i.e. the current mode of this renderer
		 differs from the current mode of its swap chain (due to for example ALT + TAB).

		 @return		@c true if this renderer lost its mode.
						@c false otherwise.
		 */
		bool LostMode() const {
			return m_fullscreen == IsWindowed();
		}

		/**
		 Sets the initial mode of this renderer.
		 Call this method before starting the game loop.
		 */
		void SetInitialMode() noexcept {
			if (m_display_configuration->IsFullScreen()) {
				SwitchMode(true);
			}
		}

		/**
		 Recreates the swap chain buffers and switches the mode of this renderer.
		 Windowed mode is switched to full screen mode and vice versa.

		 @param[in]		toggle
						If @c true only the swap chain buffers will be recreated
						to match the current mode of the swap chain and no mode 
						switch will occurs.
						If @c false both the swap chain buffers will be replaced
						and a mode switch will occur.
		 */
		void SwitchMode(bool toggle);

		//---------------------------------------------------------------------
		// Member Methods: Rendering
		//---------------------------------------------------------------------

		/**
		 Binds the RTV and DSV of this renderer.
		 */
		void BindRTVAndDSV() const noexcept;

		/**
		 Begins the rendering of the current frame.

		 @pre			This renderer is not inside a begin/end pair.
		 */
		void BeginFrame() noexcept;

		/**
		 Ends the rendering of the current frame.

		 @pre			This renderer is inside a begin/end pair.
		 */
		void EndFrame() noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Initializes this renderer.

		 @throws		FormattedException
						Failed to initialize this renderer.
		 */
		void InitializeRenderer();

		/**
		 Uninitializes this renderer.
		 */
		void UninitializeRenderer() noexcept;

		/**
		 Sets up the D3D11 device and context of this renderer.

		 @throws		FormattedException
						Failed to set up the device and device context
						of this renderer.
		 */
		void SetupDevice();

		/**
		 Sets up the swap chain of this renderer with its render target view
		 and depth stencil view.

		 @throws		FormattedException
						Failed to set up the swap chain of this renderer.
		 */
		void SetupSwapChain();

		/**
		 Resets the swap chain of this renderer with its render target view
		 and depth stencil view.

		 @throws		FormattedException
						Failed to set up the swap chain of this renderer.
		 */
		void ResetSwapChain();

		/**
		 Creates the swap chain of this renderer.

		 @throws		FormattedException
						Failed to create the swap chain of this renderer.
		 */
		void CreateSwapChain();

		/**
		 Creates the render target view, shader resource view 
		 of the back buffer of this renderer.

		 @throws		FormattedException
						Failed to obtain the back buffer resource
						of this renderer.
		 @throws		FormattedException
						Failed to create the render target view 
						of the back buffer of this renderer.
		 @throws		FormattedException
						Failed to create the shader resource view 
						of the back buffer of this renderer.
		 */
		void CreateBackBufferRTVandSRV();

		/**
		 Creates the depth stencil view and shader resource view 
		 of the depth buffer of this renderer.

		 @throws		FormattedException
						Failed to create the depth buffer resource
						of this renderer.
		 @throws		FormattedException
						Failed to create the depth stencil view 
						of the depth buffer of this renderer.
		 @throws		FormattedException
						Failed to create the shader resource view
						of the depth buffer of this renderer.
		 */
		void CreateDepthBufferDSVandSRV();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The handle of the parent window of this renderer.
		 */
		const HWND m_hwindow;

		/**
		 A flag indicating whether this renderer uses a full screen mode
		 or not (i.e. a windowed mode).
		 */
		bool m_fullscreen;

		/**
		 A flag indicating whether this renderer is inside a begin/end pair.
		 */
		bool m_in_begin_end_pair;

		/**
		 A pointer to the display configuration of this renderer.
		 */
		UniquePtr< DisplayConfiguration > m_display_configuration;

		/**
		 A pointer to the feature level of this renderer.
		 */
		D3D_FEATURE_LEVEL m_feature_level;

		/**
		 A pointer to the device of this renderer.
		 */
		ComPtr< ID3D11Device2 >	m_device;

		/**
		 A pointer to the device context of this renderer.
		 */
		ComPtr< ID3D11DeviceContext2 > m_device_context;

		/**
		 A pointer to the swap chain of this renderer.
		 */
		ComPtr< IDXGISwapChain2 > m_swap_chain;

		/**
		 A pointer to the render target view 
		 of the back buffer of this renderer.
		 */
		ComPtr< ID3D11RenderTargetView > m_back_buffer_rtv;

		/**
		 A pointer to the shader resource view 
		 of the back buffer of this renderer.
		 */
		ComPtr< ID3D11ShaderResourceView > m_back_buffer_srv;

		/**
		 A pointer to the depth stencil view 
		 of the depth buffer of this renderer.
		 */
		ComPtr< ID3D11DepthStencilView > m_depth_buffer_dsv;

		/**
		 A pointer to the shader resource view
		 of the depth buffer of this renderer.
		 */
		ComPtr< ID3D11ShaderResourceView > m_depth_buffer_srv;

		/**
		 A pointer to the rendering state cache of this renderer.
		 */
		UniquePtr< RenderingStateCache > m_rendering_state_cache;
	};
}