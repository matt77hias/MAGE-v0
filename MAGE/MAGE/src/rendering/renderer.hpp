#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "loadable.hpp"
#include "rendering\rendering.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of renderers.
	 */
	class Renderer : public Loadable {

	public:

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
		 Returns the window handle of this renderer.

		 @return		The window handle of this renderer.
		 */
		HWND GetHandle() const {
			return m_hwindow;
		}

		/**
		 Returns the device of this renderer.

		 @return		A pointer to the device of this renderer.
		 */
		ComPtr< ID3D11Device2 > GetDevice() {
			return m_device2;
		}

		/**
		 Returns the device context of this renderer.

		 @return		A pointer to the device context of this renderer.
		 */
		ComPtr< ID3D11DeviceContext2 > GetDeviceContext() {
			return m_device_context2;
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
			m_swap_chain2->GetFullscreenState(&current, nullptr);
			return current != 0;
		}

		/**
		 Checks whether this renderer lost its mode, i.e. the current mode of this renderer
		 differs from the cyrrent mode of its swap chain (due to for example ALT + TAB).
		 */
		bool LostMode() const {
			return m_fullscreen == IsWindowed();
		}

		/**
		 Recreates the swap chain buffers and switches the mode of this renderer.
		 Windowed mode is switched to full screen mode and vice versa.

		 @return		toggle
						If @c true only the swap chain buffers will be recreated
						to match the current mode of the swap chain and no mode switch will occurs.
						If @c false both the swap chain buffers will be replaced
						and a mode switch will occur.
		 */
		void SwitchMode(bool toggle);

		/**
		 Starts the rendering of the current frame.

		 @param[in]		background_color
						A reference to the background color for the current frame.
		 */
		void StartFrame(const XMVECTORF32 &background_color = { 0.0f, 0.117647058f, 0.149019608f, 1.000000000f }) const;

		/**
		 Ends the rendering of the current frame.
		 */
		void EndFrame() const;

	protected:

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
		HRESULT SetupViewPort() const;

		D3D_FEATURE_LEVEL		         m_feature_level;
		ComPtr< ID3D11Device2 >	         m_device2;
		ComPtr< ID3D11DeviceContext2 >   m_device_context2;
		ComPtr< IDXGISwapChain2 >        m_swap_chain2;
		ComPtr< ID3D11RenderTargetView > m_render_target_view;
		ComPtr< ID3D11Texture2D >        m_depth_stencil;
		ComPtr< ID3D11DepthStencilView > m_depth_stencil_view;

	private:

		/**
		 The handle of the parent window.
		 */
		HWND m_hwindow;

		/**
		 A flag indicating whether this renderer uses a full screen mode
		 (if @c true) or a windowed mode (if @c false).
		 */
		bool m_fullscreen;
	};
}