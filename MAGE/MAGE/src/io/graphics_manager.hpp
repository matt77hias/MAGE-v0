#pragma once

namespace mage {

	const D3D_FEATURE_LEVEL feature_levels[] = {
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

	class GraphicsManager {

	public:

		GraphicsManager() {
			if (g_device_enumeration) {
				delete g_device_enumeration;
			}
			g_device_enumeration = new DeviceEnumeration();
		}

		virtual ~GraphicsManager() {}

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