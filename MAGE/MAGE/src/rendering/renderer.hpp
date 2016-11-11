#pragma once

/**
 A class of renderers.
 */
namespace mage {

	class Renderer {

	friend class Engine;

	public:
		
		/**
		 Checks whether this renderer is loaded.

		 @return		@c true if this renderer is loaded.
						@c false otherwise.
		 */
		bool IsLoaded() const {
			return m_loaded;
		}

	protected:

		/**
		 Constructs a renderer.

		 @param[in]		The main window handle.
		 */
		Renderer(HWND hwindow);

		/**
		 Destructs this renderer.
		 */
		virtual ~Renderer();

		/**
		 Initializes the D3D11 device of this renderer.

		 @return		A success/error value.
		 */
		HRESULT InitDevice();

		/**
		 Main window handle of this renderer.
		 */
		HWND m_hwindow;

		/**
		 Flag indicating wether this renderer is loaded.
		 */
		bool m_loaded;

		D3D_DRIVER_TYPE           m_driver_type;
		D3D_FEATURE_LEVEL		  m_feature_level;
		ID3D11Device2            *m_device2;
		ID3D11DeviceContext2     *m_device_context2;
		IDXGISwapChain2          *m_swap_chain2;
		ID3D11RenderTargetView   *m_render_target_view;
		ID3D11Texture2D          *m_depth_stencil;
		ID3D11DepthStencilView   *m_depth_stencil_view;
	};

}