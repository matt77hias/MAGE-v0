//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\display_configurator.hpp"
#include "rendering\display_settings.hpp"
#include "platform\windows_utils.hpp"
#include "ui\combo_box.hpp"
#include "file\file_utils.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <iterator>
#include <windowsx.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Integrated + Dedicated GPU on notebooks  
//-----------------------------------------------------------------------------
#pragma region

/**
 NVIDIA Optimus enablement

 @pre NVIDIA Control Panel > Preferred graphics processor > "Auto-select"
 */
extern "C" {
	__declspec(dllexport) DWORD NvOptimusEnablement;
}

/**
 AMD "Optimus" enablement
 */
extern "C" {
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance;
}

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DISPLAY_VARIABLE_AA           "anti-aliasing"
#define MAGE_DISPLAY_VARIABLE_REFRESH_RATE "refresh"
#define MAGE_DISPLAY_VARIABLE_RESOLUTION   "resolution"
#define MAGE_DISPLAY_VARIABLE_VSYNC        "vsync"
#define MAGE_DISPLAY_VARIABLE_WINDOWED     "windowed"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	[[nodiscard]] INT_PTR CALLBACK DisplayConfigurator
		::DisplayDialogProcDelegate(HWND dialog, 
			                        UINT message, 
			                        WPARAM wParam, 
			                        LPARAM lParam) {

		const auto configurator 
			= GetDialogCaller< DisplayConfigurator >(dialog, message, wParam, lParam);

		return configurator->DisplayDialogProc(dialog, message, wParam, lParam);
	}

	DisplayConfigurator::DisplayConfigurator(DXGI_FORMAT pixel_format)
		: m_pixel_format(pixel_format), 
		m_display_configuration(),
		m_display_configuration_script(),
		m_adapter(), m_output(), 
		m_display_modes() {

		// Load the settings script.
		const auto file_exists 
			= FileExists(MAGE_DEFAULT_DISPLAY_SETTINGS_FILE);
		m_display_configuration_script 
			= MakeUnique< VariableScript >(MAGE_DEFAULT_DISPLAY_SETTINGS_FILE, 
				                           file_exists);

		// Initialize the adapter and output.
		InitializeAdapterAndOutput();
		// Initialize the display modes.
		InitializeDisplayModes();

	}

	DisplayConfigurator::DisplayConfigurator(ComPtr< DXGIAdapter > adapter, 
		                                     ComPtr< DXGIOutput > output,
		                                     DXGI_FORMAT pixel_format)
		: m_pixel_format(pixel_format),
		m_display_configuration(), 
		m_display_configuration_script(),
		m_adapter(std::move(adapter)), 
		m_output(std::move(output)), 
		m_display_modes() {

		// Load the settings script.
		const auto file_exists 
			= FileExists(MAGE_DEFAULT_DISPLAY_SETTINGS_FILE);
		m_display_configuration_script 
			= MakeUnique< VariableScript >(MAGE_DEFAULT_DISPLAY_SETTINGS_FILE, 
				                           file_exists);

		// Initialize the display modes.
		InitializeDisplayModes();
	}

	DisplayConfigurator::DisplayConfigurator(
		DisplayConfigurator &&configurator) noexcept = default;

	DisplayConfigurator::~DisplayConfigurator() = default;

	/**
	 Checks whether the given display mode needs to be rejected.

	 @param[in]		display_mode_desc
					A reference to a display mode descriptor.
	 @return		@c true if the given display mode needs to be rejected.
					@c false otherwise.
	 */
	[[nodiscard]] static inline bool 
		RejectDisplayMode(const DXGI_MODE_DESC1 &display_mode_desc) noexcept {
		
		return (display_mode_desc.Width  < 512u) 
			|| (display_mode_desc.Height < 512u);
	}
	
	void DisplayConfigurator::InitializeAdapterAndOutput() {
		ComPtr< IDXGIFactory1 > factory;
		{
			const HRESULT result = CreateDXGIFactory1(
				__uuidof(IDXGIFactory1), (void **)factory.GetAddressOf());
			ThrowIfFailed(result, "IDXGIFactory1 creation failed: %08X.", result);
		}

		ComPtr< IDXGIAdapter1 > selected_adapter;
		ComPtr< IDXGIOutput >   selected_output;
		ComPtr< IDXGIAdapter1 > iterated_adapter;
		SIZE_T max_vram = 0;
		for (U32 i = 0u; 
			 factory->EnumAdapters1(i, iterated_adapter.GetAddressOf()) 
			 != DXGI_ERROR_NOT_FOUND; ++i) {
			
			// Get the primary IDXGIOutput.
			ComPtr< IDXGIOutput > iterated_output;
			{
				const HRESULT result = iterated_adapter
					->EnumOutputs(0u, iterated_output.GetAddressOf());
				if (FAILED(result)) {
					break;
				}
			}

			// Get the DXGI_ADAPTER_DESC .
			DXGI_ADAPTER_DESC desc;
			{
				const HRESULT result = iterated_adapter->GetDesc(&desc);
				ThrowIfFailed(result,
					"DXGI_ADAPTER_DESC retrieval failed: %08X.", result);
			}

			const auto vram = desc.DedicatedVideoMemory;
			if (vram <= max_vram) {
				continue;
			}

			selected_adapter = iterated_adapter;
			selected_output  = iterated_output;
			max_vram         = vram;
		}

		// Get the DXGIAdapter.
		{
			const HRESULT result = selected_adapter.As(&m_adapter);
			ThrowIfFailed(result, "DXGIAdapter creation failed: %08X.", result);
		}

		// Get the DXGIOutput.
		{
			const HRESULT result = selected_output.As(&m_output);
			ThrowIfFailed(result, "DXGIOutput creation failed: %08X.", result);
		}
	}
	
	void DisplayConfigurator::InitializeDisplayModes() {
		const U32 flags = DXGI_ENUM_MODES_INTERLACED;
		
		// Get the number of display modes that match the requested format 
		// and other input options.
		U32 nb_display_modes;
		{
			const HRESULT result = m_output->GetDisplayModeList1(m_pixel_format, 
					                                             flags, 
					                                             &nb_display_modes, 
					                                             nullptr);
			ThrowIfFailed(result,
				"Failed to get the number of display modes: %08X.", result);
		}
		
		// Get the display modes that match the requested format and other 
		// input options.
		auto dxgi_mode_descs = MakeUnique< DXGI_MODE_DESC1[] >(nb_display_modes);
		{
			const HRESULT result = m_output->GetDisplayModeList1(m_pixel_format, 
				                                                 flags, 
				                                                 &nb_display_modes, 
				                                                 dxgi_mode_descs.get());
			ThrowIfFailed(result, "Failed to get the display modes: %08X.", result);
		}

		// Enumerate the display modes.
		m_display_modes = std::vector< DXGI_MODE_DESC1 >();
		for (U32 mode = 0u; mode < nb_display_modes; ++mode) {
			
			// Reject small display modes.
			if (RejectDisplayMode(dxgi_mode_descs.get()[mode])) {
				continue;
			}

			// Add the display mode to the list.
			m_display_modes.push_back(dxgi_mode_descs.get()[mode]);
		}
	}

	[[nodiscard]] HRESULT DisplayConfigurator::Configure() const {
		// Creates a modal dialog box from a dialog box template resource.
		// 1. A handle to the module which contains the dialog box template. 
		//    If this parameter is nullptr, then the current executable is 
		//    used.
		// 2. The dialog box template.
		// 3. A handle to the window that owns the dialog box.
		// 4. A pointer to the dialog box procedure.
		// 5. The value to pass to the dialog box in the lParam parameter 
		//    of the WM_INITDIALOG message.
		const INT_PTR result_dialog = DialogBoxParam(nullptr, 
			                                         MAKEINTRESOURCE(IDD_DISPLAY_SETTINGS),
				                                     nullptr, 
			                                         DisplayDialogProcDelegate, 
				                                     reinterpret_cast< LPARAM >(this));
		
		return (IDOK == result_dialog) ? S_OK : E_FAIL;
	}
	
	/**
	 Converts the resolution of the given display format descriptor to a 
	 @c size_t.

	 @param[in]		desc
					A reference to the display format descriptor.
	 @return		A @c size_t value corresponding to the resolution of 
					the given display format descriptor.
	 */
	[[nodiscard]] static inline size_t 
		ConvertResolution(const DXGI_MODE_DESC1 &desc) noexcept {

		return static_cast< size_t >(MAKELONG(desc.Width, desc.Height));
	}

	/**
	 Converts the refresh rate of the given display format descriptor to a 
	 @c size_t.

	 @param[in]		desc
					A reference to the display format descriptor.
	 @return		A @c size_t value corresponding to the refresh rate of 
					the given display format descriptor.
	 */
	[[nodiscard]] static inline size_t 
		ConvertRefreshRate(const DXGI_MODE_DESC1 &desc) noexcept {

		return static_cast< size_t >(round(desc.RefreshRate.Numerator 
			 / static_cast< F32 >(desc.RefreshRate.Denominator)));
	}

	[[nodiscard]] INT_PTR DisplayConfigurator
		::DisplayDialogProc(HWND dialog, 
			                UINT message,
		                    [[maybe_unused]] WPARAM wParam, 
			                [[maybe_unused]] LPARAM lParam) {

		wchar_t buffer[16];

		// color depth (format) affects resolution affects refresh rate.

		switch (message) {
		
		case WM_INITDIALOG: {
			// Sent to the dialog box procedure immediately before a dialog box is 
			// displayed. Dialog box procedures typically use this message to 
			// initialize controls and carry out any other initialization tasks 
			// that affect the appearance of the dialog box.

			// Display the adapter details.
			DXGI_ADAPTER_DESC2 desc;
			m_adapter->GetDesc2(&desc);
			Edit_SetText(GetDlgItem(dialog, IDC_DISPLAY_ADAPTER), desc.Description);

			if (m_display_configuration_script->empty()) {
				m_display_configuration_script->Add(
					MAGE_DISPLAY_VARIABLE_AA,           0);
				m_display_configuration_script->Add(
					MAGE_DISPLAY_VARIABLE_REFRESH_RATE, 0);
				m_display_configuration_script->Add(
					MAGE_DISPLAY_VARIABLE_RESOLUTION,   0);
				m_display_configuration_script->Add(
					MAGE_DISPLAY_VARIABLE_VSYNC,    false);
				m_display_configuration_script->Add(
					MAGE_DISPLAY_VARIABLE_WINDOWED,  true);
			}
			
			// Windowed state
			{
				// Load the windowed state.
				const auto windowed = *m_display_configuration_script
					->GetValue< bool >(MAGE_DISPLAY_VARIABLE_WINDOWED);
				
				// Change the check state of a button control.
				// 1. A handle to the dialog box that contains the button.
				// 2. The identifier of the button to modify.
				// 3. The check state of the button.
				CheckDlgButton(dialog, IDC_WINDOWED, windowed);
				CheckDlgButton(dialog, IDC_FULLSCREEN, !windowed);
			}

			// Vsync state
			{
				// Load the vsync state.
				const auto vsync = *m_display_configuration_script
					->GetValue< bool >(MAGE_DISPLAY_VARIABLE_VSYNC);
				
				// Change the check state of a button control.
				// 1. A handle to the dialog box that contains the button.
				// 2. The identifier of the button to modify.
				// 3. The check state of the button.
				CheckDlgButton(dialog, IDC_VSYNC, vsync);
			}
			
			// Anti-aliasing state
			{
				// Remove all items from the list box and edit control of a combo box.
				ComboBox_ResetContent(GetDlgItem(dialog, IDC_AA));
				
				// Fill in the anti-aliasing combo box.
				ComboBoxAddValue(dialog, IDC_AA, 
					static_cast< size_t >(AADescriptor::None),     L"None");
				ComboBoxAddValue(dialog, IDC_AA, 
					static_cast< size_t >(AADescriptor::FXAA),     L"FXAA");
				ComboBoxAddValue(dialog, IDC_AA, 
					static_cast< size_t >(AADescriptor::MSAA_2x),  L"MSAA 2x");
				ComboBoxAddValue(dialog, IDC_AA, 
					static_cast< size_t >(AADescriptor::MSAA_4x),  L"MSAA 4x");
				ComboBoxAddValue(dialog, IDC_AA, 
					static_cast< size_t >(AADescriptor::MSAA_8x),  L"MSAA 8x");
				ComboBoxAddValue(dialog, IDC_AA, 
					static_cast< size_t >(AADescriptor::SSAA_2x),  L"SSAA 2x");
				ComboBoxAddValue(dialog, IDC_AA, 
					static_cast< size_t >(AADescriptor::SSAA_3x),  L"SSAA 3x");
				ComboBoxAddValue(dialog, IDC_AA, 
					static_cast< size_t >(AADescriptor::SSAA_4x),  L"SSAA 4x");
				
				const auto index = *m_display_configuration_script
					->GetValue< int >(MAGE_DISPLAY_VARIABLE_AA);
				ComboBoxSelect(dialog, IDC_AA, index);
			}
			
			// Resolution state
			{
				// Remove all items from the list box and edit control of a combo box.
				ComboBox_ResetContent(GetDlgItem(dialog, IDC_RESOLUTION));

				// Fill in the resolutions combo box.
				for (const auto &mode : m_display_modes) {
					swprintf_s(buffer, 
						       std::size(buffer), 
						       L"%u x %u", 
						       mode.Width, 
						       mode.Height);

					if (!ComboBoxContains(dialog, IDC_RESOLUTION, buffer)) {
						const auto resolution = ConvertResolution(mode);
						ComboBoxAddValue(dialog, IDC_RESOLUTION, resolution, buffer);
					}
				}

				const auto index = *m_display_configuration_script
					->GetValue< int >(MAGE_DISPLAY_VARIABLE_RESOLUTION);
				ComboBoxSelect(dialog, IDC_RESOLUTION, index);
			}

			// Refresh rate state
			{
				const auto selected_resolution 
					= ComboBoxSelectedValue(dialog, IDC_RESOLUTION);

				// Remove all items from the list box and edit control of a combo box.
				ComboBox_ResetContent(GetDlgItem(dialog, IDC_REFRESH_RATE));

				// Fill in the refresh rates combo box associated with the current resolution.
				for (const auto &mode : m_display_modes) {
					const auto resolution = ConvertResolution(mode);
					if (selected_resolution == resolution) {

						const auto refresh_rate = ConvertRefreshRate(mode);
						swprintf_s(buffer, 
							       std::size(buffer), 
							       L"%u Hz",
							       static_cast< unsigned int >(refresh_rate));

						if (!ComboBoxContains(dialog, IDC_REFRESH_RATE, buffer)) {
							ComboBoxAddValue(dialog, IDC_REFRESH_RATE, refresh_rate, buffer);
						}
					}
				}

				const int refresh_rate_index = *m_display_configuration_script
					->GetValue< int >(MAGE_DISPLAY_VARIABLE_REFRESH_RATE);
				ComboBoxSelect(dialog, IDC_REFRESH_RATE, refresh_rate_index);
			}

			return TRUE;
		}
		
		case WM_COMMAND: {
			// Sent when the user selects a command item from a menu, when a 
			// control sends a notification message to its parent window.
			
			switch (LOWORD(wParam)) {
			
			case IDOK: {
				
				// Load all the settings.
				const auto selected_aa
					= RetrieveAADescriptor(ComboBoxSelectedValue(dialog, IDC_AA));
				const auto selected_refresh_rate
					= ComboBoxSelectedValue(dialog, IDC_REFRESH_RATE);
				const auto selected_resolution
					= ComboBoxSelectedValue(dialog, IDC_RESOLUTION);
				
				const DXGI_MODE_DESC1 *selected_diplay_mode 
					= nullptr;
				for (const auto &display_mode : m_display_modes) {
					
					const auto resolution = ConvertResolution(display_mode);
					if (selected_resolution != resolution) {
						continue;
					}

					const auto refresh_rate = ConvertRefreshRate(display_mode);
					if (selected_refresh_rate != refresh_rate) {
						continue;
					}

					selected_diplay_mode = &display_mode;
					break;
				}
				if (!selected_diplay_mode) {
					Error("Selected display mode retrieval failed.");

					// Close the dialog.
					EndDialog(dialog, IDCANCEL);

					return TRUE;
				}
				
				const auto windowed = IsDlgButtonChecked(dialog, IDC_WINDOWED)
									? true : false;
				const auto vsync	= IsDlgButtonChecked(dialog, IDC_VSYNC)
									? true : false;

				// Store all the settings to the display configuration.
				m_display_configuration 
					= MakeUnique< DisplayConfiguration >(m_adapter, 
						                                 m_output, 
						                                 *selected_diplay_mode);
				m_display_configuration->SetWindowed(windowed);
				m_display_configuration->SetVSync(vsync);
				m_display_configuration->SetAADescriptor(selected_aa);

				// Get the selected index from each combo box.
				const auto aa_index
					= ComboBox_GetCurSel(GetDlgItem(dialog, IDC_AA));
				const auto refresh_rate_index
					= ComboBox_GetCurSel(GetDlgItem(dialog, IDC_REFRESH_RATE));
				const auto resolution_index
					= ComboBox_GetCurSel(GetDlgItem(dialog, IDC_RESOLUTION));
				
				// Store all the settings to the display configuration script.
				m_display_configuration_script->SetValue(
					MAGE_DISPLAY_VARIABLE_AA, aa_index);
				m_display_configuration_script->SetValue(
					MAGE_DISPLAY_VARIABLE_REFRESH_RATE, refresh_rate_index);
				m_display_configuration_script->SetValue(
					MAGE_DISPLAY_VARIABLE_RESOLUTION, resolution_index);
				m_display_configuration_script->SetValue(
					MAGE_DISPLAY_VARIABLE_VSYNC, vsync);
				m_display_configuration_script->SetValue(
					MAGE_DISPLAY_VARIABLE_WINDOWED, windowed);

				// Save all the settings in the display configuration script.
				m_display_configuration_script->ExportScript();

				// Close the dialog.
				EndDialog(dialog, IDOK);

				return TRUE;
			}
			
			case IDCANCEL: {
				// Close the dialog.
				EndDialog(dialog, IDCANCEL);

				return TRUE;
			}
			
			case IDC_RESOLUTION: {
				
				if (CBN_SELCHANGE == HIWORD(wParam)) {
					
					const auto selected_resolution
						= ComboBoxSelectedValue(dialog, IDC_RESOLUTION);
					const auto selected_refresh_rate
						= ComboBoxSelectedValue(dialog, IDC_REFRESH_RATE);

					// Remove all items from the list box and edit control of a 
					// combo box.
					ComboBox_ResetContent(GetDlgItem(dialog, IDC_REFRESH_RATE));
					
					// Update the refresh rate combo box.
					for (const auto &mode : m_display_modes) {
						
						const auto resolution = ConvertResolution(mode);
						
						if (selected_resolution == resolution) {
							
							const auto refresh_rate = ConvertRefreshRate(mode);
							swprintf_s(buffer, 
								       std::size(buffer), 
								       L"%u Hz",
								       static_cast< unsigned int >(refresh_rate));
							
							if (!ComboBoxContains(dialog, IDC_REFRESH_RATE, buffer)) {
								ComboBoxAddValue(dialog, IDC_REFRESH_RATE, refresh_rate, buffer);
								
								if (selected_refresh_rate == refresh_rate) {
									ComboBoxSelectValue(dialog, IDC_REFRESH_RATE, selected_refresh_rate);
								}
							}
						}
					}

					if (ComboBoxSelected(dialog, IDC_REFRESH_RATE) == nullptr) {
						ComboBoxSelect(dialog, IDC_REFRESH_RATE, 0);
					}
				}

				return TRUE;
			}
			}
		}
		}
		
		return FALSE;
	}
}