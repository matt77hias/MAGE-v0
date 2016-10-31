#pragma once

namespace mage {

	class GraphicsManager {

	public:

		GraphicsManager();

		virtual ~GraphicsManager() {}

		IDXGIDevice3 *GetDevice() const {
			return m_device;
		}

		DXGI_MODE_DESC1 GetDisplayMode() const {
			return m_display_mode;
		}

	private:

		IDXGIDevice3 *m_device;

		DXGI_MODE_DESC1 m_display_mode;
	};

}