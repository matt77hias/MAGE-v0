#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loadable.hpp"
#include "memory\memory.hpp"
#include "rendering\rendering.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

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
		 Returns the width in pixels of the display of this renderer.

		 @return		The width in pixels of the display of this renderer.
		 */
		uint32_t GetWidth() const {
			return static_cast< uint32_t >(m_display_mode.Width);
		}

		/**
		 Returns the height in pixels of the display of this renderer.

		 @return		The height in pixels of the display of this renderer.
		 */
		uint32_t GetHeight() const {
			return static_cast< uint32_t >(m_display_mode.Height);
		}

		/**
		 Returns the device of this renderer.

		 @return		A pointer to the device of this renderer.
		 */
		ComPtr< ID3D11Device2 > GetDevice() const {
			return m_device2;
		}

		/**
		 Returns the device context of this renderer.

		 @return		A pointer to the device context of this renderer.
		 */
		ComPtr< ID3D11DeviceContext2 > GetDeviceContext() const {
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
		 Start the solid rasterizer of this renderer.
		 */
		void StartSolidRasterizer();

		/**
		 Start the wireframe rasterizer of this renderer.
		 */
		void StartWireframeRasterizer();

		/**
		 Starts the rendering of the current frame.
		 */
		void StartFrame() const;

		/**
		 Ends the rendering of the current frame.
		 */
		void EndFrame() const;

	private:

		/**
		 Constructs a renderer from the given renderer.

		 @param[in]		renderer
						A reference to a renderer.
		 */
		Renderer(const Renderer &renderer) = delete;

		/**
		 Copies the given renderer to this renderer.

		 @param[in]		renderer
						A reference to a renderer.
		 @return		A reference to the copy of the given renderer
						(i.e. this renderer).
		 */
		Renderer &operator=(const Renderer &renderer) = delete;

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
		 Sets up the rasterizer states of this renderer.

		 @return		A success/error value.
		 */
		HRESULT SetupRasterizerStates();

		/**
		 Sets up and binds the viewport of this renderer
		 to the graphics pipeline.

		 @return		A success/error value.
		 */
		HRESULT SetupViewPort() const;

		/**
		 The handle of the parent window.
		 */
		HWND m_hwindow;

		/**
		 A flag indicating whether this renderer uses a full screen mode
		 (if @c true) or a windowed mode (if @c false).
		 */
		bool m_fullscreen;

		DXGI_MODE_DESC1					 m_display_mode;
		D3D_FEATURE_LEVEL		         m_feature_level;
		ComPtr< ID3D11Device2 >	         m_device2;
		ComPtr< ID3D11DeviceContext2 >   m_device_context2;
		ComPtr< IDXGISwapChain2 >        m_swap_chain2;
		ComPtr< ID3D11RenderTargetView > m_render_target_view;
		ComPtr< ID3D11Texture2D >        m_depth_stencil;
		ComPtr< ID3D11DepthStencilView > m_depth_stencil_view;
		ComPtr< ID3D11RasterizerState1 > m_solid_rasterizer_state;
		ComPtr< ID3D11RasterizerState1 > m_wireframe_rasterizer_state;
	};
}