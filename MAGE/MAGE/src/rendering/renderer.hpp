#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of renderers.
	 */
	class Renderer : private Loadable {

	friend class Engine;

	public:

		/**
		 Recreates the swap chain buffers and switches the mode of this renderer.
		 Windowed mode is switched to full screen mode and vice versa.

		 @return		toggle
						If @c true only the swap chain buffers will be recreated
						and no mode switch will occurs.
						If @c false both the swap chain buffers will be replaced
						and a mode switch will occur.
		 */
		void SwitchMode(bool toggle);

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
			m_swap_chain2->GetFullscreenState(&current, nullptr);
			return current != 0;
		}

		/**
		 Checks whether this renderer lost its full screen mode 
		 (due to for example ALT + TAB).
		 */
		bool LostFullScreen() const {
			return m_fullscreen == IsWindowed();
		}

		HRESULT CreateTexture2D(const D3D11_TEXTURE2D_DESC *desc, const D3D11_SUBRESOURCE_DATA *init_data, ID3D11Texture2D **texture);
		HRESULT CreateBuffer(const D3D11_BUFFER_DESC *buffer_desc, const D3D11_SUBRESOURCE_DATA *init_data, ID3D11Buffer **texture);

	protected:

		/**
		 Constructs a renderer.

		 @param[in]		hwindow
						The main window handle.
		 */
		Renderer(HWND hwindow);

		/**
		 Destructs this renderer.
		 */
		virtual ~Renderer();

		/**
		 Initializes this renderer.

		 @return		A success/error value.
		 */
		HRESULT InitializeRenderer();

		/**
		 Uninitializes this renderer.

		 @return		A success/error value.
		 */
		HRESULT UnitializeRenderer();

		/**
		 Setup the D3D11 device and context of this renderer.

		 @return		A success/error value.
		 */
		HRESULT SetupDevice();

		/**
		 Sets up the swap chain of this renderer.

		 @return		A success/error value.
		 */
		HRESULT SetupSwapChain();

		/**
		 Sets up the render target view of this renderer.

		 @return		A success/error value.
		 */
		HRESULT SetupRenderTargetView();

		/**
		 Sets up the depth stencil view of this renderer.

		 @return		A success/error value.
		 */
		HRESULT SetupDepthStencilView();

		/**
		 Sets up and binds the viewport of this renderer
		 to the graphics pipeline.

		 @return		A success/error value.
		 */
		HRESULT SetupViewPort();

		/**
		 Renders the current frame.

		 @param[in]		elapsed_time
						The elapsed time since the previous frame.
		 */
		void Render(double elapsed_time);

		/**
		 Main window handle of this renderer.
		 */
		HWND m_hwindow;

		/**
		 A flag indicating whether this renderer uses a full screen mode
		 (if @c true) or a windowed mode (if @c false).
		 */
		bool m_fullscreen;

		D3D_FEATURE_LEVEL		  m_feature_level;
		ID3D11Device2            *m_device2;
		ID3D11DeviceContext2     *m_device_context2;
		IDXGISwapChain2          *m_swap_chain2;
		ID3D11RenderTargetView   *m_render_target_view;
		ID3D11Texture2D          *m_depth_stencil;
		ID3D11DepthStencilView   *m_depth_stencil_view;
	};
}