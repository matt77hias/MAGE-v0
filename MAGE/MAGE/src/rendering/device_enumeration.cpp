//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\device_enumeration.hpp"
#include "rendering\graphics_settings.hpp"
#include "ui\combo_box.hpp"
#include "file\file_utils.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_DISPLAY_SETTINGS_FILE L"./DisplaySettings.vs"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	//-------------------------------------------------------------------------
	// Globals
	//-------------------------------------------------------------------------
	DeviceEnumeration *g_device_enumeration = nullptr;

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
	 @return		@c true if @a uMsg is processed.
					@c false otherwise.
	 */
	INT_PTR CALLBACK SettingsDialogProcDelegate(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		return g_device_enumeration->SettingsDialogProc(hwndDlg, uMsg, wParam, lParam);
	}

	//-------------------------------------------------------------------------
	// DeviceEnumeration
	//-------------------------------------------------------------------------

	/**
	 Checks whether the given display mode needs to be rejected for the engine.

	 @param[in]		display_mode_desc
					A reference to a display mode descriptor.
	 @return		@c true if the given display mode needs to be rejected for the engine.
					@c false otherwise.
	 */
	inline bool RejectDisplayMode(const DXGI_MODE_DESC1 &display_mode_desc) {
		return display_mode_desc.Height < 480;
	}

	DeviceEnumeration::DeviceEnumeration() 
		: m_adapter(), m_output(), m_settings_script(),
		m_display_modes(), m_selected_diplay_mode(nullptr),
		m_windowed(false), m_vsync(false) {}

	DeviceEnumeration::DeviceEnumeration(DeviceEnumeration &&device_enumeration) = default;

	DeviceEnumeration::~DeviceEnumeration() = default;

	void DeviceEnumeration::InitializeAdapterAndOutput() {
		// Get the IDXGIFactory3.
		ComPtr< IDXGIFactory3 > factory;
		const HRESULT result_factory = CreateDXGIFactory1(__uuidof(IDXGIFactory3), (void**)factory.GetAddressOf());
		if (FAILED(result_factory)) {
			throw FormattedException("IDXGIFactory3 creation failed: %08X.", result_factory);
		}

		// Get the IDXGIAdapter1 and its primary IDXGIOutput.
		// The IDXGIAdapter represents a display subsystem (including one or more GPUs, DACs and video memory).
		// The IDXGIOutput represents an adapter output (such as a monitor).
		ComPtr< IDXGIAdapter1 > adapter1;
		ComPtr< IDXGIOutput > output;
		SIZE_T max_vram = 0;
		for (UINT i = 0; factory->EnumAdapters1(i, adapter1.GetAddressOf()) != DXGI_ERROR_NOT_FOUND; ++i) {

			// Get the IDXGIAdapter2.
			ComPtr< IDXGIAdapter2 > adapter2;
			const HRESULT result_adapter2 = adapter1.As(&adapter2);
			if (FAILED(result_adapter2)) {
				throw FormattedException("IDXGIAdapter2 creation failed: %08X.", result_adapter2);
			}

			// Get the primary IDXGIOutput.
			const HRESULT result_output = adapter2->EnumOutputs(0, output.GetAddressOf());
			if (FAILED(result_output)) {
				continue;
			}
			// Get the IDXGIOutput2.
			ComPtr< IDXGIOutput2 > output2;
			const HRESULT result_output2 = output.As(&output2);
			if (FAILED(result_output2)) {
				throw FormattedException("IDXGIOutput2 creation failed: %08X.", result_output2);
			}

			// Get the DXGI_ADAPTER_DESC2.
			DXGI_ADAPTER_DESC2 desc;
			const HRESULT result_adapter_desc = adapter2->GetDesc2(&desc);
			if (FAILED(result_adapter_desc)) {
				throw FormattedException("DXGI_ADAPTER_DESC2 retrieval failed: %08X.", result_adapter_desc);
			}

			const SIZE_T vram = desc.DedicatedVideoMemory;
			if (vram <= max_vram) {
				continue;
			}

			m_adapter = adapter2;
			m_output = output2;
			max_vram = vram;
		}
	}

	void DeviceEnumeration::InitializeDisplayModes() {
		// Create the display modes linked list.
		m_display_modes = list< DXGI_MODE_DESC1 >();
		m_selected_diplay_mode = nullptr;
		
		// Get the DXGI_MODE_DESCs. 
		for (size_t i = 0; i < _countof(g_pixel_formats); ++i) {

			// The DXGI_MODE_DESC describes a display mode and whether the display mode supports stereo.
			const UINT flags = DXGI_ENUM_MODES_INTERLACED;
			UINT nb_display_modes;
			// Get the number of display modes that match the requested format and other input options.
			const HRESULT result1 = m_output->GetDisplayModeList1(g_pixel_formats[i], flags, &nb_display_modes, nullptr);
			if (FAILED(result1)) {
				throw FormattedException("Failed to get the number of display modes: %08X.", result1);
			}
			UniquePtr< DXGI_MODE_DESC1[] >dxgi_mode_descs(new DXGI_MODE_DESC1[nb_display_modes]);
			// Get the display modes that match the requested format and other input options.
			const HRESULT result2 = m_output->GetDisplayModeList1(g_pixel_formats[i], flags, &nb_display_modes, dxgi_mode_descs.get());
			if (FAILED(result2)) {
				throw FormattedException("Failed to get the display modes: %08X.", result2);
			}

			// Enumerate the DXGI_MODE_DESCs.
			for (UINT mode = 0; mode < nb_display_modes; ++mode) {
				// Reject small display modes.
				if (RejectDisplayMode(dxgi_mode_descs.get()[mode])) {
					continue;
				}

				// Add the display mode to the list.
				m_display_modes.push_back(dxgi_mode_descs.get()[mode]);
			}
		}
	}

	HRESULT DeviceEnumeration::Enumerate() {
		// Load the settings script.
		if (FileExists(MAGE_DEFAULT_DISPLAY_SETTINGS_FILE)) {
			m_settings_script.reset(new VariableScript(MAGE_DEFAULT_DISPLAY_SETTINGS_FILE));
		}
		else {
			m_settings_script.reset(new VariableScript(MAGE_DEFAULT_DISPLAY_SETTINGS_FILE, false));
		}

		// Initialize the adapter and output.
		InitializeAdapterAndOutput();
		// Initialize the display modes.
		InitializeDisplayModes();

		// Creates a modal dialog box from a dialog box template resource.
		// 1. A handle to the module which contains the dialog box template. If this parameter is nullptr, then the current executable is used.
		// 2. The dialog box template.
		// 3. A handle to the window that owns the dialog box.
		// 4. A pointer to the dialog box procedure.
		const INT_PTR result_dialog = DialogBox(nullptr, MAKEINTRESOURCE(IDD_GRAPHICS_SETTINGS), nullptr, SettingsDialogProcDelegate);
		return (result_dialog == IDOK) ? S_OK : E_FAIL;
	}

	INT_PTR DeviceEnumeration::SettingsDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		UNUSED(lParam);

		// Window mode affects color depth (format) affects resolution affects refresh rate.

		switch (uMsg) {
		case WM_INITDIALOG: {
			// Sent to the dialog box procedure immediately before a dialog box is displayed.
			// Dialog box procedures typically use this message to initialize controls and 
			// carry out any other initialization tasks that affect the appearance of the dialog box.

			// Display the adapter details and its driver version.
			DXGI_ADAPTER_DESC2 desc;
			m_adapter->GetDesc2(&desc);
			Edit_SetText(GetDlgItem(hwndDlg, IDC_DISPLAY_ADAPTER), desc.Description);

			if (m_settings_script->IsEmpty()) {
				m_settings_script->AddVariable(VariableType_Bool, "windowed",   true);
				m_settings_script->AddVariable(VariableType_Bool, "vsync",      false);
				m_settings_script->AddVariable(VariableType_Int,  "bpp",        0);
				m_settings_script->AddVariable(VariableType_Int,  "resolution", 0);
				m_settings_script->AddVariable(VariableType_Int,  "refresh",	0);
			}

			// Load the windowed state.
			m_windowed = *m_settings_script->GetValueOfVariable< bool >("windowed");
			
			// Change the check state of a button control.
			// 1. A handle to the dialog box that contains the button.
			// 2. The identifier of the button to modify.
			// 3. The check state of the button.
			CheckDlgButton(hwndDlg, IDC_WINDOWED, m_windowed);
			CheckDlgButton(hwndDlg, IDC_FULLSCREEN, !m_windowed);

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
#ifdef MAGE_X86
				swprintf_s(bpp_buffer, _countof(bpp_buffer), L"%u bbp", BitsPerPixel(it->Format));
#else
				swprintf_s(bpp_buffer, _countof(bpp_buffer), L"%llu bbp", BitsPerPixel(it->Format));
#endif
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
					swprintf_s(buffer, _countof(buffer), L"%u x %u", it->Width, it->Height);
					if (!ComboBoxContains(hwndDlg, IDC_RESOLUTION, buffer)) {
						ComboBoxAdd(hwndDlg, IDC_RESOLUTION, (void*)(static_cast< size_t >(MAKELONG(it->Width, it->Height))), buffer);
					}
				}
			}
			const int resolution = *m_settings_script->GetValueOfVariable< int >("resolution");
			ComboBoxSelect(hwndDlg, IDC_RESOLUTION, resolution);

			// Fill in the refresh rates combo box associated with the current resolution.
			// Remove all items from the list box and edit control of a combo box.
			ComboBox_ResetContent(GetDlgItem(hwndDlg, IDC_REFRESH_RATE));
			for (list< DXGI_MODE_DESC1 >::const_iterator it = m_display_modes.cbegin(); it != m_display_modes.cend(); ++it) {
				if (static_cast< size_t >(MAKELONG(it->Width, it->Height)) == static_cast< size_t >(PtrToUlong(ComboBoxSelected(hwndDlg, IDC_RESOLUTION)))) {
					const UINT refresh_rate = static_cast< UINT >(round(it->RefreshRate.Numerator / static_cast< float >(it->RefreshRate.Denominator)));
					swprintf_s(buffer, _countof(buffer), L"%u Hz", refresh_rate);
					if (!ComboBoxContains(hwndDlg, IDC_REFRESH_RATE, buffer)) {
						ComboBoxAdd(hwndDlg, IDC_REFRESH_RATE, (void*)(static_cast< size_t >(MAKELONG(it->RefreshRate.Numerator, it->RefreshRate.Denominator))), buffer);
					}
				}
			}
			const int refresh = *m_settings_script->GetValueOfVariable< int >("refresh");
			ComboBoxSelect(hwndDlg, IDC_REFRESH_RATE, refresh);

			return true;
		}
		case WM_COMMAND: {
			// Sent when the user selects a command item from a menu, when a control sends a notification message to its parent window.
			switch (LOWORD(wParam)) {
			case IDOK: {
				// Store the details of the selected display mode.
				const size_t resolution   = static_cast< size_t >(PtrToUlong(ComboBoxSelected(hwndDlg, IDC_RESOLUTION)));
				const size_t refresh_rate = static_cast< size_t >(PtrToUlong(ComboBoxSelected(hwndDlg, IDC_REFRESH_RATE)));
				const DXGI_FORMAT format  = (DXGI_FORMAT)PtrToUlong(ComboBoxSelected(hwndDlg, IDC_DISPLAY_FORMAT));
				for (list< DXGI_MODE_DESC1 >::const_iterator it = m_display_modes.cbegin(); it != m_display_modes.cend(); ++it) {
					if (static_cast< size_t >(MAKELONG(it->Width, it->Height)) != resolution) {
						continue;
					}
					if (static_cast< size_t >(MAKELONG(it->RefreshRate.Numerator, it->RefreshRate.Denominator)) != refresh_rate) {
						continue;
					}
					if (it->Format != format) {
						continue;
					}
					m_selected_diplay_mode = &(*it);
					break;
				}
				if (!m_selected_diplay_mode) {
					Error("Selected display mode retrieval failed.");

					// Close the hwndDlg.
					EndDialog(hwndDlg, IDCANCEL);

					return true;
				}
				m_windowed = IsDlgButtonChecked(hwndDlg, IDC_WINDOWED) ? true : false;
				m_vsync	   = IsDlgButtonChecked(hwndDlg, IDC_VSYNC)    ? true : false;

				// Get the selected index from each combo box.
				const int bpp_index			 = ComboBox_GetCurSel(GetDlgItem(hwndDlg, IDC_DISPLAY_FORMAT));
				const int resolution_index	 = ComboBox_GetCurSel(GetDlgItem(hwndDlg, IDC_RESOLUTION));
				const int refresh_rate_index = ComboBox_GetCurSel(GetDlgItem(hwndDlg, IDC_REFRESH_RATE));

				// Set all the settings in the script.
				m_settings_script->SetValueOfVariable("windowed",	m_windowed);
				m_settings_script->SetValueOfVariable("vsync",		m_vsync);
				m_settings_script->SetValueOfVariable("bpp",		bpp_index);
				m_settings_script->SetValueOfVariable("resolution", resolution_index);
				m_settings_script->SetValueOfVariable("refresh",	refresh_rate_index);
				// Save all the settings out to the settings script.
				m_settings_script->ExportScript();

				// Close the hwndDlg.
				EndDialog(hwndDlg, IDOK);

				return true;
			}
			case IDCANCEL: {
				// Close the hwndDlg.
				EndDialog(hwndDlg, IDCANCEL);

				return true;
			}
			case IDC_COLOUR_DEPTH: {
				if (CBN_SELCHANGE == HIWORD(wParam)) {
					wchar_t buffer[16];
					const size_t selected_resolution = static_cast< size_t >(PtrToUlong(ComboBoxSelected(hwndDlg, IDC_RESOLUTION)));

					// Update the resolution combo box.
					// Remove all items from the list box and edit control of a combo box.
					ComboBox_ResetContent(GetDlgItem(hwndDlg, IDC_RESOLUTION));
					for (list< DXGI_MODE_DESC1 >::const_iterator it = m_display_modes.cbegin(); it != m_display_modes.cend(); ++it) {
						if (it->Format == (DXGI_FORMAT)PtrToUlong(ComboBoxSelected(hwndDlg, IDC_COLOUR_DEPTH))) {
							swprintf_s(buffer, _countof(buffer), L"%u x %u", it->Width, it->Height);
							if (!ComboBoxContains(hwndDlg, IDC_RESOLUTION, buffer)) {
								ComboBoxAdd(hwndDlg, IDC_RESOLUTION, (void*)(static_cast< size_t >(MAKELONG(it->Width, it->Height))), buffer);
								if (selected_resolution == static_cast< size_t >(MAKELONG(it->Width, it->Height))) {
									ComboBoxSelect(hwndDlg, IDC_RESOLUTION, (void*)(static_cast< size_t >(selected_resolution)));
								}
							}
						}
					}
					if (ComboBoxSelected(hwndDlg, IDC_RESOLUTION) == nullptr) {
						ComboBoxSelect(hwndDlg, IDC_RESOLUTION, 0);
					}
				}
				return true;
			}
			case IDC_RESOLUTION: {
				if (CBN_SELCHANGE == HIWORD(wParam)) {
					wchar_t buffer[16];
					const size_t selected_refresh_rate = static_cast< size_t >(PtrToUlong(ComboBoxSelected(hwndDlg, IDC_REFRESH_RATE)));

					// Update the refresh rate combo box.
					// Remove all items from the list box and edit control of a combo box.
					ComboBox_ResetContent(GetDlgItem(hwndDlg, IDC_REFRESH_RATE));
					for (list< DXGI_MODE_DESC1 >::const_iterator it = m_display_modes.cbegin(); it != m_display_modes.cend(); ++it) {
						if ((size_t)MAKELONG(it->Width, it->Height) == static_cast< size_t >(PtrToUlong(ComboBoxSelected(hwndDlg, IDC_RESOLUTION)))) {
							const UINT refresh_rate = static_cast< UINT >(round(it->RefreshRate.Numerator / static_cast< float >(it->RefreshRate.Denominator)));
							swprintf_s(buffer, _countof(buffer), L"%u Hz", refresh_rate);
							if (!ComboBoxContains(hwndDlg, IDC_REFRESH_RATE, buffer)) {
								ComboBoxAdd(hwndDlg, IDC_REFRESH_RATE, (void*)(static_cast< size_t >(MAKELONG(it->RefreshRate.Numerator, it->RefreshRate.Denominator))), buffer);
								if (selected_refresh_rate == static_cast< size_t >(MAKELONG(it->RefreshRate.Numerator, it->RefreshRate.Denominator))) {
									ComboBoxSelect(hwndDlg, IDC_REFRESH_RATE, (void*)(static_cast< size_t >(selected_refresh_rate)));
								}
							}
						}
					}
					if (ComboBoxSelected(hwndDlg, IDC_REFRESH_RATE) == nullptr) {
						ComboBoxSelect(hwndDlg, IDC_REFRESH_RATE, 0);
					}
				}
				return true;
			}
			case IDC_WINDOWED:
			case IDC_FULLSCREEN: {
				return true;
			}
			}
		}
		}
		return false;
	}
}