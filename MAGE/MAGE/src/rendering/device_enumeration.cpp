//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"
#include "rendering\rendering_utils.hpp"
#include "rendering\graphics_settings.hpp"
#include "platform\windows_utils.hpp"
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
	// DeviceEnumeration
	//-------------------------------------------------------------------------

	const DeviceEnumeration *DeviceEnumeration::Get() noexcept {
		Assert(Engine::Get());

		return Engine::Get()->GetDeviceEnumeration();
	}

	INT_PTR CALLBACK DeviceEnumeration::SettingsDialogProcDelegate(
		HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {

		DeviceEnumeration * const device_enumeration 
			= GetDialogCaller< DeviceEnumeration >(hwndDlg, uMsg, wParam, lParam);
		return device_enumeration->SettingsDialogProc(hwndDlg, uMsg, wParam, lParam);
	}

	const DXGI_FORMAT DeviceEnumeration::s_pixel_formats[] = {
		DXGI_FORMAT_B8G8R8X8_UNORM,
		DXGI_FORMAT_B8G8R8A8_UNORM,
		DXGI_FORMAT_R10G10B10A2_UNORM,
	};

	DeviceEnumeration::DeviceEnumeration() 
		: m_adapter(), m_output(), m_settings_script(),
		m_display_modes(), m_selected_diplay_mode(nullptr),
		m_windowed(false), m_vsync(false) {}

	DeviceEnumeration::DeviceEnumeration(DeviceEnumeration &&device_enumeration) = default;

	DeviceEnumeration::~DeviceEnumeration() = default;

	/**
	 Checks whether the given display mode needs to be rejected for the engine.

	 @param[in]		display_mode_desc
					A reference to a display mode descriptor.
	 @return		@c true if the given display mode needs to be rejected for the engine.
					@c false otherwise.
	 */
	inline bool RejectDisplayMode(const DXGI_MODE_DESC1 &display_mode_desc) noexcept {
		return display_mode_desc.Height < 480;
	}

	HRESULT DeviceEnumeration::Enumerate() {
		// Load the settings script.
		const bool file_exists = FileExists(MAGE_DEFAULT_DISPLAY_SETTINGS_FILE);
		m_settings_script.reset(new VariableScript(MAGE_DEFAULT_DISPLAY_SETTINGS_FILE, file_exists));

		// Initialize the adapter and output.
		InitializeAdapterAndOutput();
		// Initialize the display modes.
		InitializeDisplayModes();

		// Creates a modal dialog box from a dialog box template resource.
		// 1. A handle to the module which contains the dialog box template. If this parameter is nullptr, then the current executable is used.
		// 2. The dialog box template.
		// 3. A handle to the window that owns the dialog box.
		// 4. A pointer to the dialog box procedure.
		// 5. The value to pass to the dialog box in the lParam parameter of the WM_INITDIALOG message.
		const INT_PTR result_dialog = DialogBoxParam(nullptr, MAKEINTRESOURCE(IDD_GRAPHICS_SETTINGS), 
			nullptr, SettingsDialogProcDelegate, reinterpret_cast< LPARAM >(this));
		return (result_dialog == IDOK) ? S_OK : E_FAIL;
	}

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
		for (size_t i = 0; i < _countof(s_pixel_formats); ++i) {

			// The DXGI_MODE_DESC describes a display mode and whether the display mode supports stereo.
			const UINT flags = DXGI_ENUM_MODES_INTERLACED;
			UINT nb_display_modes;
			// Get the number of display modes that match the requested format and other input options.
			const HRESULT result1 = m_output->GetDisplayModeList1(s_pixel_formats[i], flags, &nb_display_modes, nullptr);
			if (FAILED(result1)) {
				throw FormattedException("Failed to get the number of display modes: %08X.", result1);
			}
			UniquePtr< DXGI_MODE_DESC1[] >dxgi_mode_descs(new DXGI_MODE_DESC1[nb_display_modes]);
			// Get the display modes that match the requested format and other input options.
			const HRESULT result2 = m_output->GetDisplayModeList1(s_pixel_formats[i], flags, &nb_display_modes, dxgi_mode_descs.get());
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

	/**
	 Converts the resolution of the given display format descriptor to a @c size_t.

	 @param[in]		desc
					A reference to the display format descriptor.
	 @return		A @c size_t value corresponding to the resolution 
					of the given display format descriptor.
	 */
	inline size_t ConvertResolution(const DXGI_MODE_DESC1 &desc) noexcept {
		return static_cast< size_t >(MAKELONG(desc.Width, desc.Height));
	}

	/**
	 Converts the refresh rate of the given display format descriptor to a @c size_t.

	 @param[in]		desc
					A reference to the display format descriptor.
	 @return		A @c size_t value corresponding to the refresh rate
					of the given display format descriptor.
	 */
	inline size_t ConvertRefreshRate(const DXGI_MODE_DESC1 &desc) noexcept {
		return static_cast< size_t >(round(desc.RefreshRate.Numerator / static_cast< float >(desc.RefreshRate.Denominator)));
	}

	INT_PTR DeviceEnumeration::SettingsDialogProc(
		HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		UNUSED(lParam);
		wchar_t buffer[16];

		// color depth (format) affects resolution affects refresh rate.

		switch (uMsg) {
		case WM_INITDIALOG: {
			// Sent to the dialog box procedure immediately before a dialog box is displayed.
			// Dialog box procedures typically use this message to initialize controls and 
			// carry out any other initialization tasks that affect the appearance of the dialog box.

			// Display the adapter details.
			DXGI_ADAPTER_DESC2 desc;
			m_adapter->GetDesc2(&desc);
			Edit_SetText(GetDlgItem(hwndDlg, IDC_DISPLAY_ADAPTER), desc.Description);

			if (m_settings_script->IsEmpty()) {
				m_settings_script->AddVariable(VariableType::Bool, "windowed",   true);
				m_settings_script->AddVariable(VariableType::Bool, "vsync",      false);
				m_settings_script->AddVariable(VariableType::Int,  "bpp",        0);
				m_settings_script->AddVariable(VariableType::Int,  "resolution", 0);
				m_settings_script->AddVariable(VariableType::Int,  "refresh",	 0);
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
			for (auto it = m_display_modes.cbegin(); it != m_display_modes.cend(); ++it) {
#ifdef MAGE_X86
				swprintf_s(buffer, _countof(buffer), L"%u bbp", BitsPerPixel(it->Format));
#else
				swprintf_s(buffer, _countof(buffer), L"%llu bbp", BitsPerPixel(it->Format));
#endif
				if (!ComboBoxContains(hwndDlg, IDC_DISPLAY_FORMAT, buffer)) { 
					ComboBoxAddData(hwndDlg, IDC_DISPLAY_FORMAT, it->Format, buffer);
				}
			}
			const int bpp_index = *m_settings_script->GetValueOfVariable< int >("bpp");
			ComboBoxSelect(hwndDlg, IDC_DISPLAY_FORMAT, bpp_index);

			const DXGI_FORMAT selected_format = ComboBoxSelectedData< DXGI_FORMAT >(hwndDlg, IDC_DISPLAY_FORMAT);
			// Fill in the resolutions combo box associated with the current format.
			// Remove all items from the list box and edit control of a combo box.
			ComboBox_ResetContent(GetDlgItem(hwndDlg, IDC_RESOLUTION));
			for (auto it = m_display_modes.cbegin(); it != m_display_modes.cend(); ++it) {
				if (selected_format == it->Format) {
					
					swprintf_s(buffer, _countof(buffer), L"%u x %u", it->Width, it->Height);
					
					if (!ComboBoxContains(hwndDlg, IDC_RESOLUTION, buffer)) {
						const size_t resolution = ConvertResolution(*it);
						ComboBoxAddData(hwndDlg, IDC_RESOLUTION, resolution, buffer);
					}
				}
			}
			const int resolution_index = *m_settings_script->GetValueOfVariable< int >("resolution");
			ComboBoxSelect(hwndDlg, IDC_RESOLUTION, resolution_index);

			const size_t selected_resolution = ComboBoxSelectedData< size_t >(hwndDlg, IDC_RESOLUTION);
			// Fill in the refresh rates combo box associated with the current resolution.
			// Remove all items from the list box and edit control of a combo box.
			ComboBox_ResetContent(GetDlgItem(hwndDlg, IDC_REFRESH_RATE));
			for (auto it = m_display_modes.cbegin(); it != m_display_modes.cend(); ++it) {
				const size_t resolution = ConvertResolution(*it);
				if (selected_resolution == resolution) {
					
					const size_t refresh_rate = ConvertRefreshRate(*it);
					swprintf_s(buffer, _countof(buffer), L"%u Hz", static_cast< unsigned int >(refresh_rate));
					
					if (!ComboBoxContains(hwndDlg, IDC_REFRESH_RATE, buffer)) {
						ComboBoxAddData(hwndDlg, IDC_REFRESH_RATE, refresh_rate, buffer);
					}
				}
			}
			const int refresh_rate_index = *m_settings_script->GetValueOfVariable< int >("refresh");
			ComboBoxSelect(hwndDlg, IDC_REFRESH_RATE, refresh_rate_index);

			return TRUE;
		}
		case WM_COMMAND: {
			// Sent when the user selects a command item from a menu, when a control sends a notification message to its parent window.
			switch (LOWORD(wParam)) {
			case IDOK: {
				// Store the details of the selected display mode.
				const DXGI_FORMAT selected_format  = ComboBoxSelectedData< DXGI_FORMAT >(hwndDlg, IDC_DISPLAY_FORMAT);
				const size_t selected_resolution   = ComboBoxSelectedData< size_t >(hwndDlg, IDC_RESOLUTION);
				const size_t selected_refresh_rate = ComboBoxSelectedData< size_t >(hwndDlg, IDC_REFRESH_RATE);
				for (auto it = m_display_modes.cbegin(); it != m_display_modes.cend(); ++it) {
					
					const size_t resolution = ConvertResolution(*it);
					if (selected_resolution != resolution) {
						continue;
					}

					const size_t refresh_rate = ConvertRefreshRate(*it);
					if (selected_refresh_rate != refresh_rate) {
						continue;
					}

					if (selected_format != it->Format) {
						continue;
					}

					m_selected_diplay_mode = &(*it);
					break;
				}
				if (!m_selected_diplay_mode) {
					Error("Selected display mode retrieval failed.");

					// Close the hwndDlg.
					EndDialog(hwndDlg, IDCANCEL);

					return TRUE;
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

				return TRUE;
			}
			case IDCANCEL: {
				// Close the hwndDlg.
				EndDialog(hwndDlg, IDCANCEL);

				return TRUE;
			}
			case IDC_DISPLAY_FORMAT: {
				if (CBN_SELCHANGE == HIWORD(wParam)) {
					const DXGI_FORMAT selected_format = ComboBoxSelectedData< DXGI_FORMAT >(hwndDlg, IDC_DISPLAY_FORMAT);
					const size_t selected_resolution  = ComboBoxSelectedData< size_t >(hwndDlg, IDC_RESOLUTION);

					// Update the resolution combo box.
					// Remove all items from the list box and edit control of a combo box.
					ComboBox_ResetContent(GetDlgItem(hwndDlg, IDC_RESOLUTION));
					for (auto it = m_display_modes.cbegin(); it != m_display_modes.cend(); ++it) {
						if (selected_format == it->Format) {
							
							swprintf_s(buffer, _countof(buffer), L"%u x %u", it->Width, it->Height);
							
							if (!ComboBoxContains(hwndDlg, IDC_RESOLUTION, buffer)) {
								const size_t resolution = ConvertResolution(*it);
								ComboBoxAddData(hwndDlg, IDC_RESOLUTION, resolution, buffer);

								if (selected_resolution == resolution) {
									ComboBoxSelectData(hwndDlg, IDC_RESOLUTION, selected_resolution);
								}
							}
						}
					}

					if (ComboBoxSelected(hwndDlg, IDC_RESOLUTION) == nullptr) {
						ComboBoxSelect(hwndDlg, IDC_RESOLUTION, 0);
					}
				}

				return TRUE;
			}
			case IDC_RESOLUTION: {
				if (CBN_SELCHANGE == HIWORD(wParam)) {
					const size_t selected_resolution   = ComboBoxSelectedData< size_t >(hwndDlg, IDC_RESOLUTION);
					const size_t selected_refresh_rate = ComboBoxSelectedData< size_t >(hwndDlg, IDC_REFRESH_RATE);

					// Update the refresh rate combo box.
					// Remove all items from the list box and edit control of a combo box.
					ComboBox_ResetContent(GetDlgItem(hwndDlg, IDC_REFRESH_RATE));
					for (auto it = m_display_modes.cbegin(); it != m_display_modes.cend(); ++it) {
						const size_t resolution = ConvertResolution(*it);
						if (selected_resolution == resolution) {
							
							const size_t refresh_rate = ConvertRefreshRate(*it);
							swprintf_s(buffer, _countof(buffer), L"%u Hz", static_cast< unsigned int >(refresh_rate));
							
							if (!ComboBoxContains(hwndDlg, IDC_REFRESH_RATE, buffer)) {
								ComboBoxAddData(hwndDlg, IDC_REFRESH_RATE, refresh_rate, buffer);
								
								if (selected_refresh_rate == refresh_rate) {
									ComboBoxSelectData(hwndDlg, IDC_REFRESH_RATE, selected_refresh_rate);
								}
							}
						}
					}

					if (ComboBoxSelected(hwndDlg, IDC_REFRESH_RATE) == nullptr) {
						ComboBoxSelect(hwndDlg, IDC_REFRESH_RATE, 0);
					}
				}

				return TRUE;
			}
			case IDC_WINDOWED:
			case IDC_FULLSCREEN: {
				return TRUE;
			}
			}
		}
		}
		return FALSE;
	}
}