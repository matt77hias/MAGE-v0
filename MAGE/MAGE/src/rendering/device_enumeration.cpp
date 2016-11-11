//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	//-------------------------------------------------------------------------
	// Globals
	//-------------------------------------------------------------------------
	DeviceEnumeration *g_device_enumeration = NULL;

	//-------------------------------------------------------------------------
	// WindowProc for handling Windows messages.
	//-------------------------------------------------------------------------

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
	INT_PTR CALLBACK SettingsDialogProcDelegate(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		return g_device_enumeration->SettingsDialogProc(hwndDlg, uMsg, wParam, lParam);
	}

	//-------------------------------------------------------------------------
	// DeviceEnumeration
	//-------------------------------------------------------------------------

	INT_PTR DeviceEnumeration::Enumerate() {
		
		m_adapter = NULL;

		// Create the display modes linked list.
		m_display_modes = list< DXGI_MODE_DESC1 >();

		// Load the settings script.
		m_settings_script = new VariableScript("DisplaySettings.mage");

		// Get the IDXGIFactory.
		IDXGIFactory3 *factory;
		const HRESULT result_factory = CreateDXGIFactory1(__uuidof(IDXGIFactory3), (void**)&factory);
		if (result_factory) {
			Severe("CreateDXGIFactory1: %d", result_factory);
		}

		// Get the IDXGIAdapter.
		// The IDXGIAdapter represents a display subsystem (including one or more GPUs, DACs and video memory).
		IDXGIAdapter1 *adapter1;
		SIZE_T max_vram = 0;
		for (UINT i = 0; factory->EnumAdapters1(i, &adapter1) != DXGI_ERROR_NOT_FOUND; ++i) {
			IDXGIAdapter2 *adapter2;
			const HRESULT result_adapter2 = adapter1->QueryInterface(__uuidof(IDXGIAdapter2), (void **)&adapter2);
			if (result_adapter2) {
				Severe("IDXGIAdapter1::QueryInterface: %d", result_adapter2);
			}
			
			DXGI_ADAPTER_DESC2 desc;
			adapter2->GetDesc2(&desc);
			const SIZE_T vram = desc.DedicatedVideoMemory;

			if (vram >= max_vram) {
				
				if (m_adapter) {
					// Release the IDXGIAdapter2.
					m_adapter->Release();
				}

				max_vram = vram;
				m_adapter = adapter2;
			}
			else {
				// Release the IDXGIAdapter2.
				adapter2->Release();
			}

			// Release the IDXGIAdapter1.
			adapter1->Release();
		}

		// Release the IDXGIFactory.
		factory->Release();

		// Get the primary IDXGIOutput.
		// The IDXGIOutput represents an adapter output (such as a monitor).
		IDXGIOutput *output;
		const HRESULT result_output = m_adapter->EnumOutputs(0, &output);
		if (result_output) {
			Severe("IDXGIAdapter2::EnumOutputs: %d", result_output);
		}
		IDXGIOutput2 *output2;
		const HRESULT result_output2 = output->QueryInterface(__uuidof(IDXGIOutput2), (void **)&output2);
		if (result_output2) {
			Severe("IDXGIOutput::QueryInterface: %d", result_output2);
		}
			
		for (size_t i = 0; i < _countof(g_pixel_formats); ++i) {
			
			// Get the DXGI_MODE_DESCs.
			// The DXGI_MODE_DESC describes a display mode and whether the display mode supports stereo.
			const UINT flags = DXGI_ENUM_MODES_INTERLACED;
			UINT nb_display_modes;
			// Get the number of display modes that match the requested format and other input options.
			output2->GetDisplayModeList1(g_pixel_formats[i], flags, &nb_display_modes, NULL);
			DXGI_MODE_DESC1 *dxgi_mode_descs = new DXGI_MODE_DESC1[nb_display_modes];
			// Get the display modes that match the requested format and other input options.
			output2->GetDisplayModeList1(g_pixel_formats[i], flags, &nb_display_modes, dxgi_mode_descs);

			// Enumerate the DXGI_MODE_DESCs.
			for (UINT mode = 0; mode < nb_display_modes; ++mode) {
					
				// Reject small display modes.
				if (dxgi_mode_descs[mode].Height < 480) {
					continue;
				}

				// Add the display mode to the list.
				m_display_modes.push_back(dxgi_mode_descs[mode]);
			}

			// Delete the DXGI_MODE_DESCs.
			delete[] dxgi_mode_descs;
		}

		// Release the IDXGIOutput.
		output->Release();
		// Release the IDXGIOutput2.
		output2->Release();

		// Creates a modal dialog box from a dialog box template resource.
		// 1. A handle to the module which contains the dialog box template. If this parameter is NULL, then the current executable is used.
		// 2. The dialog box template.
		// 3. A handle to the window that owns the dialog box.
		// 4. A pointer to the dialog box procedure.
		return DialogBox(NULL, MAKEINTRESOURCE(IDD_GRAPHICS_SETTINGS), NULL, SettingsDialogProcDelegate);
	}

	INT_PTR DeviceEnumeration::SettingsDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		(void)lParam;

		// Window mode affects colour depth (format) affects resolution affects refresh rate.

		switch (uMsg) {
		case WM_INITDIALOG: {
			// Sent to the dialog box procedure immediately before a dialog box is displayed.
			// Dialog box procedures typically use this message to initialize controls and 
			// carry out any other initialization tasks that affect the appearance of the dialog box.

			// Display the adapter details and its driver version.
			wchar_t version_buffer[16];
			DXGI_ADAPTER_DESC2 desc;
			m_adapter->GetDesc2(&desc);
			swprintf_s(version_buffer, _countof(version_buffer), L"%d", LOWORD(desc.AdapterLuid.LowPart));
			Edit_SetText(GetDlgItem(hwndDlg, IDC_DISPLAY_ADAPTER), desc.Description);
			Edit_SetText(GetDlgItem(hwndDlg, IDC_DRIVER_VERSION), version_buffer);

			// Check if the content of the settings script.
			const bool *windowed = m_settings_script->GetValueOfVariable< bool >("windowed");
			if (windowed == NULL) {
				m_windowed = true;
				// Change the check state of a button control.
				// 1. A handle to the dialog box that contains the button.
				// 2. The identifier of the button to modify.
				// 3. The check state of the button.
				CheckDlgButton(hwndDlg, IDC_WINDOWED, m_windowed);
			}
			else {
				// Load the window mode state.
				m_windowed = *windowed;
				// Change the check state of a button control.
				// 1. A handle to the dialog box that contains the button.
				// 2. The identifier of the button to modify.
				// 3. The check state of the button.
				CheckDlgButton(hwndDlg, IDC_WINDOWED, m_windowed);
				CheckDlgButton(hwndDlg, IDC_FULLSCREEN, !m_windowed);

				// Check if running in fullscreen mode.
				if (m_windowed == false) {
					// Enable all the fullscreen controls.
					// Enable mouse and keyboard input to the specified window or control.
					EnableWindow(GetDlgItem(hwndDlg, IDC_VSYNC), true);
					EnableWindow(GetDlgItem(hwndDlg, IDC_DISPLAY_FORMAT), true);
					EnableWindow(GetDlgItem(hwndDlg, IDC_RESOLUTION), true);
					EnableWindow(GetDlgItem(hwndDlg, IDC_REFRESH_RATE), true);

					// Load the vsync state.
					m_vsync = *m_settings_script->GetValueOfVariable< bool >("vsync");
					// Change the check state of a button control.
					// 1. A handle to the dialog box that contains the button.
					// 2. The identifier of the button to modify.
					// 3. The check state of the button.
					CheckDlgButton(hwndDlg, IDC_VSYNC, m_vsync);

					// Fill in the display formats combo box.
					// Remove all items from the list box and edit control of a combo box.
					ComboBox_ResetContent(GetDlgItem(hwndDlg, IDC_DISPLAY_FORMAT));
					for (list< DXGI_MODE_DESC1 >::const_iterator it = m_display_modes.cbegin(); it != m_display_modes.cend(); ++it) {
						wchar_t bpp_buffer[8];
						swprintf_s(bpp_buffer, _countof(bpp_buffer), L"%lld bbp", BitsPerPixel(it->Format));
						if (!ComboBoxContains(hwndDlg, IDC_DISPLAY_FORMAT, bpp_buffer)) {
							ComboBoxAdd(hwndDlg, IDC_DISPLAY_FORMAT, (void*)it->Format, bpp_buffer);
						}
					}
					const int bpp = *m_settings_script->GetValueOfVariable< int >("bpp");
					ComboBoxSelect(hwndDlg, IDC_DISPLAY_FORMAT, bpp);

					// Text buffer.
					wchar_t buffer[16];

					// Fill in the resolutions combo box associated with the current format.
					// Remove all items from the list box and edit control of a combo box.
					ComboBox_ResetContent(GetDlgItem(hwndDlg, IDC_RESOLUTION));
					for (list< DXGI_MODE_DESC1 >::const_iterator it = m_display_modes.cbegin(); it != m_display_modes.cend(); ++it) {
						if (it->Format == (DXGI_FORMAT)PtrToUlong(ComboBoxSelected(hwndDlg, IDC_COLOUR_DEPTH))) {
							swprintf_s(buffer, _countof(buffer), L"%d x %d", it->Width, it->Height);
							if (!ComboBoxContains(hwndDlg, IDC_RESOLUTION, buffer)) {
								ComboBoxAdd(hwndDlg, IDC_RESOLUTION, (void*)((size_t)MAKELONG(it->Width, it->Height)), buffer);
							}
						}
					}
					const int resolution = *m_settings_script->GetValueOfVariable< int >("resolution");
					ComboBoxSelect(hwndDlg, IDC_RESOLUTION, resolution);

					// Fill in the refresh rates combo box associated with the current resolution.
					// Remove all items from the list box and edit control of a combo box.
					ComboBox_ResetContent(GetDlgItem(hwndDlg, IDC_REFRESH_RATE));
					for (list< DXGI_MODE_DESC1 >::const_iterator it = m_display_modes.cbegin(); it != m_display_modes.cend(); ++it) {
						if ((DWORD)MAKELONG(it->Width, it->Height) == (DWORD)PtrToUlong(ComboBoxSelected(hwndDlg, IDC_RESOLUTION))) {
							const UINT refresh_rate = (UINT)round(it->RefreshRate.Numerator / (float)it->RefreshRate.Denominator);
							swprintf_s(buffer, _countof(buffer), L"%d Hz", refresh_rate);
							if (!ComboBoxContains(hwndDlg, IDC_REFRESH_RATE, buffer)) {
								ComboBoxAdd(hwndDlg, IDC_REFRESH_RATE, (void*)((size_t)MAKELONG(it->RefreshRate.Numerator, it->RefreshRate.Denominator)), buffer);
							}
						}
					}
					const int refresh = *m_settings_script->GetValueOfVariable< int >("refresh");
					ComboBoxSelect(hwndDlg, IDC_REFRESH_RATE, refresh);
				}
			}
			return true;
		}
		case WM_COMMAND: {
			// Sent when the user selects a command item from a menu, when a control sends a notification message to its parent window.
			switch (LOWORD(wParam)) {
			case IDOK: {
				// Store the details of the selected display mode.
				m_selected_diplay_mode.Width = LOWORD(PtrToUlong(ComboBoxSelected(hwndDlg, IDC_RESOLUTION)));
				m_selected_diplay_mode.Height = HIWORD(PtrToUlong(ComboBoxSelected(hwndDlg, IDC_RESOLUTION)));
				m_selected_diplay_mode.RefreshRate.Numerator = LOWORD(PtrToUlong(ComboBoxSelected(hwndDlg, IDC_REFRESH_RATE)));
				m_selected_diplay_mode.RefreshRate.Denominator = HIWORD(PtrToUlong(ComboBoxSelected(hwndDlg, IDC_REFRESH_RATE)));
				m_selected_diplay_mode.Format = (DXGI_FORMAT)PtrToUlong(ComboBoxSelected(hwndDlg, IDC_DISPLAY_FORMAT));
				m_windowed = IsDlgButtonChecked(hwndDlg, IDC_WINDOWED) ? true : false;
				m_vsync = IsDlgButtonChecked(hwndDlg, IDC_VSYNC) ? true : false;

				// Get the selected index from each combo box.
				const int bpp = ComboBox_GetCurSel(GetDlgItem(hwndDlg, IDC_DISPLAY_FORMAT));
				const int resolution = ComboBox_GetCurSel(GetDlgItem(hwndDlg, IDC_RESOLUTION));
				const int refresh_rate = ComboBox_GetCurSel(GetDlgItem(hwndDlg, IDC_REFRESH_RATE));

				const bool *windowed = m_settings_script->GetValueOfVariable< bool >("windowed");
				if (windowed == NULL) {
					// Add all the settings to the script.
					m_settings_script->AddVariable("windowed", BoolType, new bool(m_windowed));
					m_settings_script->AddVariable("vsync", BoolType, new bool(m_vsync));
					m_settings_script->AddVariable("bpp", IntType, new int(bpp));
					m_settings_script->AddVariable("resolution", IntType, new int(resolution));
					m_settings_script->AddVariable("refresh", IntType, new int(refresh_rate));
				}
				else {
					// Set all the settings.
					m_settings_script->SetValueOfVariable("windowed", new bool(m_windowed));
					m_settings_script->SetValueOfVariable("vsync", new bool(m_vsync));
					m_settings_script->SetValueOfVariable("bpp", new int(bpp));
					m_settings_script->SetValueOfVariable("resolution", new int(resolution));
					m_settings_script->SetValueOfVariable("refresh", new int(refresh_rate));
				}

				// Save all the settings out to the settings script.
				m_settings_script->ExportScript();
				// Destroy the settings script.
				delete m_settings_script;

				// Release the IDXGIAdapter2.
				m_adapter->Release();

				// Close the hwndDlg.
				EndDialog(hwndDlg, IDOK);

				return true;
			}
			case IDCANCEL: {
				// Destroy the settings script.
				delete m_settings_script;

				// Release the IDXGIAdapter2.
				m_adapter->Release();

				EndDialog(hwndDlg, IDCANCEL);

				return true;
			}
			case IDC_COLOUR_DEPTH: {
				if (CBN_SELCHANGE == HIWORD(wParam)) {
					wchar_t buffer[16];
					const DWORD selected_resolution = (DWORD)PtrToUlong(ComboBoxSelected(hwndDlg, IDC_RESOLUTION));

					// Update the resolution combo box.
					// Remove all items from the list box and edit control of a combo box.
					ComboBox_ResetContent(GetDlgItem(hwndDlg, IDC_RESOLUTION));
					for (list< DXGI_MODE_DESC1 >::const_iterator it = m_display_modes.cbegin(); it != m_display_modes.cend(); ++it) {
						if (it->Format == (DXGI_FORMAT)PtrToUlong(ComboBoxSelected(hwndDlg, IDC_COLOUR_DEPTH))) {
							swprintf_s(buffer, _countof(buffer), L"%d x %d", it->Width, it->Height);
							if (!ComboBoxContains(hwndDlg, IDC_RESOLUTION, buffer)) {
								ComboBoxAdd(hwndDlg, IDC_RESOLUTION, (void*)((size_t)MAKELONG(it->Width, it->Height)), buffer);
								if (selected_resolution == (DWORD)MAKELONG(it->Width, it->Height)) {
									ComboBoxSelect(hwndDlg, IDC_RESOLUTION, (void*)((size_t)selected_resolution));
								}
							}
						}
					}
					if (ComboBoxSelected(hwndDlg, IDC_RESOLUTION) == NULL) {
						ComboBoxSelect(hwndDlg, IDC_RESOLUTION, 0);
					}
				}
				return true;
			}
			case IDC_RESOLUTION: {
				if (CBN_SELCHANGE == HIWORD(wParam)) {
					wchar_t buffer[16];
					DWORD selected_refresh_rate = (DWORD)PtrToUlong(ComboBoxSelected(hwndDlg, IDC_REFRESH_RATE));

					// Update the refresh rate combo box.
					// Remove all items from the list box and edit control of a combo box.
					ComboBox_ResetContent(GetDlgItem(hwndDlg, IDC_REFRESH_RATE));
					for (list< DXGI_MODE_DESC1 >::const_iterator it = m_display_modes.cbegin(); it != m_display_modes.cend(); ++it) {
						if ((DWORD)MAKELONG(it->Width, it->Height) == (DWORD)PtrToUlong(ComboBoxSelected(hwndDlg, IDC_RESOLUTION))) {
							const UINT refresh_rate = (UINT)round(it->RefreshRate.Numerator / (float)it->RefreshRate.Denominator);
							swprintf_s(buffer, _countof(buffer), L"%d Hz", refresh_rate);
							if (!ComboBoxContains(hwndDlg, IDC_REFRESH_RATE, buffer)) {
								ComboBoxAdd(hwndDlg, IDC_REFRESH_RATE, (void*)((size_t)MAKELONG(it->RefreshRate.Numerator, it->RefreshRate.Denominator)), buffer);
								if (selected_refresh_rate == (DWORD)MAKELONG(it->RefreshRate.Numerator, it->RefreshRate.Denominator)) {
									ComboBoxSelect(hwndDlg, IDC_REFRESH_RATE, (void*)((size_t)selected_refresh_rate));
								}
							}
						}
					}
					if (ComboBoxSelected(hwndDlg, IDC_REFRESH_RATE) == NULL) {
						ComboBoxSelect(hwndDlg, IDC_REFRESH_RATE, 0);
					}
				}
				return true;
			}
			case IDC_WINDOWED:
			case IDC_FULLSCREEN: {
				// Check if change to windowed or fullscreen mode.
				if (IsDlgButtonChecked(hwndDlg, IDC_WINDOWED)) {
					// Clear and disable all the fullscreen controls.
					// Remove all items from the list box and edit control of a combo box.
					ComboBox_ResetContent(GetDlgItem(hwndDlg, IDC_DISPLAY_FORMAT));
					ComboBox_ResetContent(GetDlgItem(hwndDlg, IDC_RESOLUTION));
					ComboBox_ResetContent(GetDlgItem(hwndDlg, IDC_REFRESH_RATE));
					// Change the check state of a button control.
					// 1. A handle to the dialog box that contains the button.
					// 2. The identifier of the button to modify.
					// 3. The check state of the button.
					CheckDlgButton(hwndDlg, IDC_VSYNC, false);
					EnableWindow(GetDlgItem(hwndDlg, IDC_VSYNC), false);
					EnableWindow(GetDlgItem(hwndDlg, IDC_DISPLAY_FORMAT), false);
					EnableWindow(GetDlgItem(hwndDlg, IDC_RESOLUTION), false);
					EnableWindow(GetDlgItem(hwndDlg, IDC_REFRESH_RATE), false);
				}
				else {
					// Enable all the fullscreen controls.
					EnableWindow(GetDlgItem(hwndDlg, IDC_VSYNC), true);
					EnableWindow(GetDlgItem(hwndDlg, IDC_DISPLAY_FORMAT), true);
					EnableWindow(GetDlgItem(hwndDlg, IDC_RESOLUTION), true);
					EnableWindow(GetDlgItem(hwndDlg, IDC_REFRESH_RATE), true);

					// Fill in the display formats combo box.
					// Remove all items from the list box and edit control of a combo box.
					ComboBox_ResetContent(GetDlgItem(hwndDlg, IDC_DISPLAY_FORMAT));
					for (list< DXGI_MODE_DESC1 >::const_iterator it = m_display_modes.cbegin(); it != m_display_modes.cend(); ++it) {
						wchar_t bpp_buffer[8];
						swprintf_s(bpp_buffer, _countof(bpp_buffer), L"%lld bbp", BitsPerPixel(it->Format));
						if (!ComboBoxContains(hwndDlg, IDC_DISPLAY_FORMAT, bpp_buffer)) {
							ComboBoxAdd(hwndDlg, IDC_DISPLAY_FORMAT, (void*)it->Format, bpp_buffer);
						}
					}
					ComboBoxSelect(hwndDlg, IDC_DISPLAY_FORMAT, 0);
				}
				return true;
			}
			}
		}
		}
		return false;
	}
}