#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_state.hpp"

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
	class Renderer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a renderer.


		 @param[in]		hwindow
						The main window handle.
		 */
		explicit Renderer(HWND hwindow);

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
		 Returns the width in pixels of the display of this renderer.

		 @return		The width in pixels of the display of this renderer.
		 */
		uint32_t GetWidth() const noexcept {
			return static_cast< uint32_t >(m_display_mode.Width);
		}

		/**
		 Returns the height in pixels of the display of this renderer.

		 @return		The height in pixels of the display of this renderer.
		 */
		uint32_t GetHeight() const noexcept {
			return static_cast< uint32_t >(m_display_mode.Height);
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
		 Returns the 2D rendering state of this renderer.

		 @return		A pointer to the 2D rendering state of this renderer.
		 */
		RenderingState *GetRenderingState2D() const noexcept {
			return m_rendering_state_2d.get();
		}

		/**
		 Returns the 3D rendering state of this renderer.

		 @return		A pointer to the 3D rendering state of this renderer.
		 */
		RenderingState *GetRenderingState3D() const noexcept {
			return m_rendering_state_3d.get();
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

		/**
		 Begins the rendering of the current frame.

		 @pre			This renderer is not inside a begin/end pair.
		 */
		void BeginFrame();

		/**
		 Ends the rendering of the current frame.

		 @pre			This renderer is inside a begin/end pair.
		 */
		void EndFrame();

		/**
		 Prepares the 2D rendering of the current frame.
		 */
		void PrepareRendering2D() {
			m_rendering_state_2d->PrepareRendering();
		}

		/**
		 Prepares the 3D rendering of the current frame.
		 */
		void PrepareRendering3D() {
			m_rendering_state_3d->PrepareRendering();
		}

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
		 Sets up the swap chain of this renderer.

		 @throws		FormattedException
						Failed to set up the swap chain of this renderer.
		 */
		void SetupSwapChain();

		/**
		 Sets up the render target view of this renderer.

		 @throws		FormattedException
						Failed to set up the render target view
						of this renderer.
		 */
		void SetupRTV();

		/**
		 Sets up the depth stencil view of this renderer.

		 @throws		FormattedException
						Failed to set up the depth stencil view
						of this renderer.
		 */
		void SetupDSV();

		/**
		 Sets up the rendering states of this renderer.

		 @throws		FormattedException
						Failed to set up the rendering states
						this renderer.
		 */
		void SetupRenderingStates();

		/**
		 Sets up and binds the viewport of this renderer
		 to the graphics pipeline.
		 */
		void SetupViewPort() const;

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
		 A pointer to the display mode of this renderer.
		 */
		DXGI_MODE_DESC1	m_display_mode;

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
		 A pointer to the render target view of this renderer.
		 */
		ComPtr< ID3D11RenderTargetView > m_rtv;

		/**
		 A pointer to the depth stencil view of this renderer.
		 */
		ComPtr< ID3D11DepthStencilView > m_dsv;

		/**
		 A pointer to the 2D rendering state of this renderer.
		 */
		UniquePtr< RenderingState > m_rendering_state_2d;

		/**
		 A pointer to the 3D rendering state of this renderer.
		 */
		UniquePtr< RenderingState >  m_rendering_state_3d;

		/**
		 A pointer to the rendering state cache of this renderer.
		 */
		UniquePtr< RenderingStateCache > m_rendering_state_cache;
	};
}