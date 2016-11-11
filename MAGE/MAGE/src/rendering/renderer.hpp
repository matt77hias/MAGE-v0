#pragma once

namespace mage {

	class Renderer {

	public:

		Renderer() {
			if (g_device_enumeration) {
				delete g_device_enumeration;
			}
			g_device_enumeration = new DeviceEnumeration();
		}

		virtual ~Renderer() {}

		bool StartEnumerate() {
			return (g_device_enumeration->Enumerate() == IDOK);
		}

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