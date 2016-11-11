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
		 Main window handle of this renderer.
		 */
		HWND m_hwindow;

		/**
		 Flag indicating wether this renderer is loaded.
		 */
		bool m_loaded;








		IDXGIDevice3 *m_device;
	};

}