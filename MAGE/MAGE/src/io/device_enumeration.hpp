#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <DXGI1_3.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io/graphics_settings.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A display mode.
	 */
	struct DisplayMode {

		/**
		 The display mode descriptor of this display mode.
		 */
		DXGI_MODE_DESC1 mode;
		
#define MAGE_DISPLAYMODE_BPP_COUNT 7

		/**
		 The colour depth expressed as a character string for the display mode.
		 */
		wchar_t bpp[MAGE_DISPLAYMODE_BPP_COUNT];
	};

	/**
	 A device enumeration.
	 */
	class DeviceEnumeration {
	
	public:

		/**
		 Constructs a device enumeration.
		 */
		DeviceEnumeration() {}

		/**
		 Destructs this device enumeration.
		 */
		virtual ~DeviceEnumeration() {}

		/**
		 Enumerates the available display modes on the default adapter output of
		 the physical adapter associated with the given device.

		 @param[in]		device
						A pointer to the device.
		 */
		INT_PTR Enumerate(IDXGIDevice3 *device);

		/**
		 Engine-defined callback function used with the CreateDialog
		 for device enumeration.

		 @param[in]		hwndDlg
						A handle to the dialog box.
		 @param[in]		uMsg
						The message.
		 @param[in]		wParam
						Additional message-specific information.
		 @param[in]		lParam
						Additional message-specific information.
		 */
		INT_PTR SettingsDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

		/**
		 Returns the selected display mode by the user.

		 @return		A pointer to the selected display mode.
		 */
		const DXGI_MODE_DESC1 *GetSelectedDisplayMode() const {
			return &m_selected_diplay_mode;
		}
		
		/**
		 Check whether the application should run in windowed mode.

		 @return		@c true if the application should run in windowed mode.
						@c false otherwise.
		 */
		bool IsWindowed() const {
			return m_windowed;
		}

		/**
		 Check whether v-sync should be enabled.

		 @return		@c true if v-sync should be enabled.
						@c false otherwise.
		 */
		bool IsVSynced() const {
			return m_vsync;
		}

	private:
		
		/**
		 The description of the adapter (or video card).
		 */
		DXGI_ADAPTER_DESC2 m_adapter_desc;

		/**
		 A pointer to the script which stores the device configuration.
		 */
		VariableScript *m_settings_script;
		
		/**
		 A pointer to the linked list of enumerated display modes.
		 */
		LinkedList< DisplayMode > *m_display_modes;
		
		/**
		 The selected display mode by the user.
		 */										
		DXGI_MODE_DESC1 m_selected_diplay_mode;
		
		/**
		 Flag indicating whether the application should run in windowed mode.
		 */
		bool m_windowed;
		
		/**
		 Flag indicating whether v-sync should be enabled.
		 */
		bool m_vsync;
	};

	/**
	 A (global) pointer to the device enumeration.
	 */
	extern DeviceEnumeration *g_device_enumeration;
}