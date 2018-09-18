//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "display\display_configurator.hpp"
#include "display\display_settings.hpp"
#include "platform\windows_utils.hpp"
#include "resource\script\variable_script.hpp"
#include "ui\combo_box.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <vector>
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
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

/**
 AMD "Optimus" enablement
 */
extern "C" {
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// Utilities
	//-------------------------------------------------------------------------
	namespace {

		/**
		 Checks whether the given display mode needs to be rejected.

		 @param[in]		desc
						A reference to a display mode descriptor.
		 @return		@c true if the given display mode needs to be rejected.
						@c false otherwise.
		 */
		[[nodiscard]]
		inline bool RejectDisplayMode(const DXGI_MODE_DESC& desc) noexcept {
			return (desc.Width < 512u) || (desc.Height < 512u);
		}

		/**
		 Converts the resolution of the given display format descriptor to a 
		 @c std::size_t.

		 @param[in]		desc
						A reference to the display format descriptor.
		 @return		A @c std::size_t value corresponding to the resolution of 
						the given display format descriptor.
		 */
		[[nodiscard]]
		inline std::size_t ConvertResolution(const DXGI_MODE_DESC& desc) noexcept {
			return static_cast< std::size_t >(MAKELONG(desc.Width, desc.Height));
		}

		/**
		 Converts the refresh rate of the given display format descriptor to a 
		 @c std::size_t.

		 @param[in]		desc
						A reference to the display format descriptor.
		 @return		A @c std::size_t value corresponding to the refresh rate of 
						the given display format descriptor.
		 */
		[[nodiscard]]
		inline std::size_t ConvertRefreshRate(const DXGI_MODE_DESC& desc) noexcept {
			return static_cast< std::size_t >(round(desc.RefreshRate.Numerator
				 / static_cast< F32 >(desc.RefreshRate.Denominator)));
		}
	}

	//-------------------------------------------------------------------------
	// DisplayConfigurator::Impl
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of display configurators.
	 */
	class DisplayConfigurator::Impl {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a display configurator.

		 @param[in]		pixel_format
						The pixel format.
		 */
		explicit Impl(DXGI_FORMAT pixel_format = DXGI_FORMAT_R8G8B8A8_UNORM);

		/**
		 Constructs a display configurator.

		 @param[in]		adapter
						A pointer to the adapter.
		 @param[in]		output
						A pointer to the output.
		 @param[in]		pixel_format
						The pixel format.
		 */
		explicit Impl(ComPtr< DXGIAdapter > adapter, 
					  ComPtr< DXGIOutput > output, 
					  DXGI_FORMAT pixel_format = DXGI_FORMAT_R8G8B8A8_UNORM);

		/**
		 Constructs a display configurator from the given display configurator.

		 @param[in]		configurator
						A reference to a display configurator to copy.
		 */
		Impl(const Impl& configurator) = delete;

		/**
		 Constructs a display configurator by moving the given display configurator.

		 @param[in]		configurator
						A reference to a display configurator to move.
		 */
		Impl(Impl&& configurator) noexcept;

		/**
		 Destructs this display configurator.
		 */
		~Impl();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given display configurator to this display configurator.

		 @param[in]		configurator
						A reference to a display configurator to copy.
		 @return		A reference to the copy of the given display 
						configurator (i.e. this display configurator).
		 */
		Impl& operator=(const Impl& configurator) = delete;

		/**
		 Moves the given display configurator to this display configurator.

		 @param[in]		configurator
						A reference to a display configurator to move.
		 @return		A reference to the moved display configurator (i.e. 
						this display configurator).
		 */
		Impl& operator=(Impl&& configurator) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Configurs the display by enumerating the available display modes and 
		 options associated with the adapter output of the physical adapter 
		 with the most dedicated video memory.

		 @return		A success/error value.
		 */
		[[nodiscard]]
		HRESULT Configure() const;

		/**
		 Returns the display configuration of this display configurator.

		 @return		A pointer to the display configuration
						of this display configurator.
		 */
		[[nodiscard]]
		const DisplayConfiguration* GetDisplayConfiguration() const noexcept {
			return m_display_configuration.get();
		}

	private:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Engine-defined callback function used with the CreateDialog for 
		 display configuration.

		 @param[in]		dialog
						A handle to the dialog box.
		 @param[in]		message
						The message.
		 @param[in]		wParam
						Additional message-specific information.
		 @param[in]		lParam
						Additional message-specific information.
		 @return		@c true if @a message is processed. @c false otherwise.
		 */
		[[nodiscard]]
		static INT_PTR CALLBACK DisplayDialogProcDelegate(HWND dialog, 
														  UINT message, 
														  WPARAM wParam, 
														  LPARAM lParam);

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		static constexpr const_wzstring s_display_settings_fname 
			                            = L"./DisplaySettings.var";

		static constexpr const_zstring s_display_variable_aa = "anti-aliasing";
		
		static constexpr const_zstring s_display_variable_refresh_rate = "refresh";
		
		static constexpr const_zstring s_display_variable_resolution = "resolution";
		
		static constexpr const_zstring s_display_variable_vsync = "vsync";
		
		static constexpr const_zstring s_display_variable_windowed = "windowed";

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Initializes the adapter and the output this display configurator.

		 @throws		Exception
						Failed to initialize the adapter and the output of this 
						display configurator.
		 */
		void InitializeAdapterAndOutput();

		/**
		 Initializes the display modes of this display configurator.

		 @throws		Exception
						Failed to initialize the display modes of this display 
						configurator.
		 */
		void InitializeDisplayModes();

		/**
		 Engine-defined callback function used with the CreateDialog for 
		 display configuration.

		 @param[in]		dialog
						A handle to the dialog box.
		 @param[in]		message
						The message.
		 @param[in]		wParam
						Additional message-specific information.
		 @param[in]		lParam
						Additional message-specific information.
		 @return		@c true if @a message is processed. @c false otherwise.
		 */
		[[nodiscard]]
		INT_PTR DisplayDialogProc(HWND dialog, 
								  UINT message, 
								  [[maybe_unused]] WPARAM wParam, 
								  [[maybe_unused]] LPARAM lParam);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------
		
		/**
		 The supported pixel format of this display configurator.
		 */
		DXGI_FORMAT m_pixel_format;

		/**
		 A pointer to the adapter (e.g. video card) of this display 
		 configurator.
		 */
		ComPtr< DXGIAdapter > m_adapter;

		/**
		 A pointer to the output (e.g. screen monitor) of this display 
		 configurator.
		 */
		ComPtr< DXGIOutput > m_output;

		/**
		 A pointer to the display configuration of this display configurator.
		 */
		UniquePtr< DisplayConfiguration > m_display_configuration;

		/**
		 A pointer to the script which stores the display configuration
		 of this display configurator.
		 */
		UniquePtr< VariableScript > m_script;

		/**
		 The enumerated display modes of this display 
		 configurator.
		 */
		std::vector< DXGI_MODE_DESC > m_display_modes;
	};

	[[nodiscard]]
	INT_PTR CALLBACK DisplayConfigurator::Impl
		::DisplayDialogProcDelegate(HWND dialog, 
									UINT message, 
			                        WPARAM wParam, 
									LPARAM lParam) {

		const auto not_null_dialog = NotNull< HWND >(dialog);
		const auto configurator = GetDialogCaller< DisplayConfigurator::Impl >
			                      (not_null_dialog, message, wParam, lParam);

		if (configurator) {
			return configurator->DisplayDialogProc(not_null_dialog, message, 
												   wParam, lParam);
		}
		else {
			return TRUE;
		}
	}

	DisplayConfigurator::Impl::Impl(DXGI_FORMAT pixel_format)
		: m_pixel_format(pixel_format), 
		m_adapter(), 
		m_output(),
		m_display_configuration(),
		m_script(),
		m_display_modes() {

		// Load the settings script.
		const auto file_exists = std::filesystem::is_regular_file(s_display_settings_fname);
		m_script = MakeUnique< VariableScript >(s_display_settings_fname, file_exists);

		// Initialize the adapter and output.
		InitializeAdapterAndOutput();
		// Initialize the display modes.
		InitializeDisplayModes();
	}

	DisplayConfigurator::Impl::Impl(ComPtr< DXGIAdapter > adapter,
		                            ComPtr< DXGIOutput > output,
		                            DXGI_FORMAT pixel_format)
		: m_pixel_format(pixel_format),
		m_adapter(std::move(adapter)),
		m_output(std::move(output)),
		m_display_configuration(), 
		m_script(),
		m_display_modes() {

		// Load the settings script.
		const auto file_exists = std::filesystem::is_regular_file(s_display_settings_fname);
		m_script = MakeUnique< VariableScript >(s_display_settings_fname, file_exists);

		// Initialize the display modes.
		InitializeDisplayModes();
	}

	DisplayConfigurator::Impl::Impl(Impl&& configurator) noexcept = default;

	DisplayConfigurator::Impl::~Impl() = default;

	void DisplayConfigurator::Impl::InitializeAdapterAndOutput() {
		ComPtr< IDXGIFactory > factory;
		{
			const HRESULT result = CreateDXGIFactory(
				__uuidof(IDXGIFactory), (void**)factory.GetAddressOf());
			ThrowIfFailed(result, "IDXGIFactory creation failed: {:08X}.", result);
		}

		ComPtr< IDXGIAdapter > selected_adapter;
		ComPtr< IDXGIOutput  > selected_output;
		ComPtr< IDXGIAdapter > iterated_adapter;
		std::size_t max_vram = 0u;
		for (U32 i = 0u; 
			 factory->EnumAdapters(i, iterated_adapter.ReleaseAndGetAddressOf()) 
			 != DXGI_ERROR_NOT_FOUND; ++i) {
			
			// Get the primary IDXGIOutput.
			ComPtr< IDXGIOutput > iterated_output;
			{
				const HRESULT result = 
					iterated_adapter->EnumOutputs(0u, iterated_output.ReleaseAndGetAddressOf());
				if (FAILED(result)) {
					// EnumAdapters order:
					// 1. The adapter with the primary desktop output.
					// 2. The other adapters with outputs.
					// 3. The adapters without outputs.
					break;
				}
			}

			// Get the DXGI_ADAPTER_DESC .
			DXGI_ADAPTER_DESC desc;
			{
				const HRESULT result = iterated_adapter->GetDesc(&desc);
				ThrowIfFailed(result, 
							  "DXGI_ADAPTER_DESC retrieval failed: {:08X}.", 
							  result);
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
			ThrowIfFailed(result, "DXGIAdapter creation failed: {:08X}.", result);
		}

		// Get the DXGIOutput.
		{
			const HRESULT result = selected_output.As(&m_output);
			ThrowIfFailed(result, "DXGIOutput creation failed: {:08X}.", result);
		}
	}
	
	void DisplayConfigurator::Impl::InitializeDisplayModes() {
		const U32 flags = DXGI_ENUM_MODES_INTERLACED;
		
		// Get the number of display modes that match the requested format 
		// and other input options.
		U32 nb_display_modes;
		{
			const HRESULT result = m_output->GetDisplayModeList(m_pixel_format, 
					                                            flags, 
					                                            &nb_display_modes, 
					                                            nullptr);
			ThrowIfFailed(result, 
						  "Failed to get the number of display modes: {:08X}.", 
						  result);
		}
		
		// Get the display modes that match the requested format and other 
		// input options.
		auto dxgi_mode_descs = MakeUnique< DXGI_MODE_DESC[] >(nb_display_modes);
		{
			const HRESULT result = m_output->GetDisplayModeList(m_pixel_format, 
				                                                flags, 
				                                                &nb_display_modes, 
				                                                dxgi_mode_descs.get());
			ThrowIfFailed(result, 
						  "Failed to get the display modes: {:08X}.", 
						  result);
		}

		// Enumerate the display modes.
		m_display_modes = std::vector< DXGI_MODE_DESC >();
		for (U32 mode = 0u; mode < nb_display_modes; ++mode) {
			
			// Reject small display modes.
			if (RejectDisplayMode(dxgi_mode_descs[mode])) {
				continue;
			}

			// Add the display mode to the list.
			m_display_modes.push_back(dxgi_mode_descs[mode]);
		}
	}

	[[nodiscard]]
	HRESULT DisplayConfigurator::Impl::Configure() const {
		// Creates a modal dialog box from a dialog box template resource.
		// 1. A handle to the module which contains the dialog box template. 
		//    If this parameter is nullptr, then the current executable is 
		//    used.
		// 2. The dialog box template.
		// 3. A handle to the window that owns the dialog box.
		// 4. A pointer to the dialog box procedure.
		// 5. The value to pass to the dialog box in the lParam parameter 
		//    of the WM_INITDIALOG message.
		const INT_PTR result_dialog 
			= DialogBoxParam(nullptr, 
							 MAKEINTRESOURCE(IDD_DISPLAY_SETTINGS), 
							 nullptr, 
							 DisplayDialogProcDelegate, 
							 reinterpret_cast< LPARAM >(this));
		
		return (IDOK == result_dialog) ? S_OK : E_FAIL;
	}
	
	[[nodiscard]]
	INT_PTR DisplayConfigurator::Impl
		::DisplayDialogProc(HWND dialog, 
							UINT message, 
							[[maybe_unused]] WPARAM wParam, 
							[[maybe_unused]] LPARAM lParam) {

		wchar_t buffer[16];

		const auto not_null_buffer = NotNull< const_wzstring >(buffer);
		const auto not_null_dialog = NotNull< HWND >(dialog);

		// color depth (format) affects resolution affects refresh rate.

		switch (message) {
		
		case WM_INITDIALOG: {
			// Sent to the dialog box procedure immediately before a dialog box is 
			// displayed. Dialog box procedures typically use this message to 
			// initialize controls and carry out any other initialization tasks 
			// that affect the appearance of the dialog box.

			// Display the adapter details.
			DXGI_ADAPTER_DESC desc;
			m_adapter->GetDesc(&desc);
			Edit_SetText(GetDlgItem(dialog, IDC_DISPLAY_ADAPTER), desc.Description);

			using std::empty;
			if (empty(*m_script)) {
				m_script->Add(s_display_variable_aa, 0);
				m_script->Add(s_display_variable_refresh_rate, 0);
				m_script->Add(s_display_variable_resolution, 0);
				m_script->Add(s_display_variable_vsync, false);
				m_script->Add(s_display_variable_windowed, true);
			}
			
			// Windowed state
			{
				// Load the windowed state.
				const auto windowed 
					= *m_script->GetValue< bool >(s_display_variable_windowed);
				
				// Change the check state of a button control.
				// 1. A handle to the dialog box that contains the button.
				// 2. The identifier of the button to modify.
				// 3. The check state of the button.
				CheckDlgButton(dialog, IDC_WINDOWED,    windowed);
				CheckDlgButton(dialog, IDC_FULLSCREEN, !windowed);
			}

			// Vsync state
			{
				// Load the vsync state.
				const auto vsync 
					= *m_script->GetValue< bool >(s_display_variable_vsync);
				
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
				ComboBoxAddValue(not_null_dialog, IDC_AA, 
								 static_cast< std::size_t >(AntiAliasing::None),
								 NotNull< const_wzstring >(L"None"));
				ComboBoxAddValue(not_null_dialog, IDC_AA, 
								 static_cast< std::size_t >(AntiAliasing::FXAA),
								 NotNull< const_wzstring >(L"FXAA"));
				ComboBoxAddValue(not_null_dialog, IDC_AA, 
								 static_cast< std::size_t >(AntiAliasing::MSAA_2x),
								 NotNull< const_wzstring >(L"MSAA 2x"));
				ComboBoxAddValue(not_null_dialog, IDC_AA, 
								 static_cast< std::size_t >(AntiAliasing::MSAA_4x),
								 NotNull< const_wzstring >(L"MSAA 4x"));
				ComboBoxAddValue(not_null_dialog, IDC_AA, 
								 static_cast< std::size_t >(AntiAliasing::MSAA_8x),
								 NotNull< const_wzstring >(L"MSAA 8x"));
				ComboBoxAddValue(not_null_dialog, IDC_AA, 
								 static_cast< std::size_t >(AntiAliasing::SSAA_2x),
								 NotNull< const_wzstring >(L"SSAA 2x"));
				ComboBoxAddValue(not_null_dialog, IDC_AA, 
								 static_cast< std::size_t >(AntiAliasing::SSAA_3x),
								 NotNull< const_wzstring >(L"SSAA 3x"));
				ComboBoxAddValue(not_null_dialog, IDC_AA, 
								 static_cast< std::size_t >(AntiAliasing::SSAA_4x),
								 NotNull< const_wzstring >(L"SSAA 4x"));
				
				const auto index 
					= *m_script->GetValue< S32 >(s_display_variable_aa);
				ComboBoxSelect(not_null_dialog, IDC_AA, index);
			}
			
			// Resolution state
			{
				// Remove all items from the list box and edit control of a combo box.
				ComboBox_ResetContent(GetDlgItem(dialog, IDC_RESOLUTION));

				// Fill in the resolutions combo box.
				for (const auto& mode : m_display_modes) {
					WriteTo(buffer, L"{} x {}", mode.Width, mode.Height);

					if (!ComboBoxContains(not_null_dialog, IDC_RESOLUTION, not_null_buffer)) {
						const auto resolution = ConvertResolution(mode);
						ComboBoxAddValue(not_null_dialog, IDC_RESOLUTION, resolution, not_null_buffer);
					}
				}

				const auto index 
					= *m_script->GetValue< S32 >(s_display_variable_resolution);
				ComboBoxSelect(not_null_dialog, IDC_RESOLUTION, index);
			}

			// Refresh rate state
			{
				const auto selected_resolution 
					= ComboBoxSelectedValue(not_null_dialog, IDC_RESOLUTION);

				// Remove all items from the list box and edit control of a combo box.
				ComboBox_ResetContent(GetDlgItem(dialog, IDC_REFRESH_RATE));

				// Fill in the refresh rates combo box associated with the current resolution.
				for (const auto& mode : m_display_modes) {
					const auto resolution = ConvertResolution(mode);
					if (selected_resolution == resolution) {

						const auto refresh_rate = ConvertRefreshRate(mode);
						WriteTo(buffer, L"{} Hz", refresh_rate);

						if (!ComboBoxContains(not_null_dialog, IDC_REFRESH_RATE, not_null_buffer)) {
							ComboBoxAddValue(not_null_dialog, IDC_REFRESH_RATE, refresh_rate, not_null_buffer);
						}
					}
				}

				const auto refresh_rate_index 
					= *m_script->GetValue< S32 >(s_display_variable_refresh_rate);
				ComboBoxSelect(not_null_dialog, IDC_REFRESH_RATE, refresh_rate_index);
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
					= RetrieveAntiAliasing(ComboBoxSelectedValue(not_null_dialog, IDC_AA));
				const auto selected_refresh_rate
					= ComboBoxSelectedValue(not_null_dialog, IDC_REFRESH_RATE);
				const auto selected_resolution
					= ComboBoxSelectedValue(not_null_dialog, IDC_RESOLUTION);
				
				const DXGI_MODE_DESC* selected_diplay_mode = nullptr;
				for (const auto& display_mode : m_display_modes) {
					
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
				m_display_configuration->SetAA(selected_aa);

				// Get the selected index from each combo box.
				const auto aa_index
					= ComboBox_GetCurSel(GetDlgItem(dialog, IDC_AA));
				const auto refresh_rate_index
					= ComboBox_GetCurSel(GetDlgItem(dialog, IDC_REFRESH_RATE));
				const auto resolution_index
					= ComboBox_GetCurSel(GetDlgItem(dialog, IDC_RESOLUTION));
				
				// Store all the settings to the display configuration script.
				m_script->SetValue(s_display_variable_aa, aa_index);
				m_script->SetValue(s_display_variable_refresh_rate, refresh_rate_index);
				m_script->SetValue(s_display_variable_resolution, resolution_index);
				m_script->SetValue(s_display_variable_vsync, vsync);
				m_script->SetValue(s_display_variable_windowed, windowed);

				// Save all the settings in the display configuration script.
				m_script->ExportScript();

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
						= ComboBoxSelectedValue(not_null_dialog, IDC_RESOLUTION);
					const auto selected_refresh_rate
						= ComboBoxSelectedValue(not_null_dialog, IDC_REFRESH_RATE);

					// Remove all items from the list box and edit control of a 
					// combo box.
					ComboBox_ResetContent(GetDlgItem(dialog, IDC_REFRESH_RATE));
					
					// Update the refresh rate combo box.
					for (const auto& mode : m_display_modes) {
						
						const auto resolution = ConvertResolution(mode);
						
						if (selected_resolution == resolution) {
							
							const auto refresh_rate = ConvertRefreshRate(mode);
							WriteTo(buffer, L"{} Hz", refresh_rate);
							
							if (!ComboBoxContains(not_null_dialog, IDC_REFRESH_RATE, not_null_buffer)) {
								ComboBoxAddValue(not_null_dialog, IDC_REFRESH_RATE, refresh_rate, not_null_buffer);
								
								if (selected_refresh_rate == refresh_rate) {
									ComboBoxSelectValue(not_null_dialog, IDC_REFRESH_RATE, selected_refresh_rate);
								}
							}
						}
					}

					if (ComboBoxSelected(not_null_dialog, IDC_REFRESH_RATE) == nullptr) {
						ComboBoxSelect(not_null_dialog, IDC_REFRESH_RATE, 0);
					}
				}

				return TRUE;
			}
			}
		}
		}
		
		return FALSE;
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// DisplayConfigurator
	//-------------------------------------------------------------------------
	#pragma region
	
	DisplayConfigurator::DisplayConfigurator(DXGI_FORMAT pixel_format) 
		: m_impl(MakeUnique< Impl >(pixel_format)) {}

	DisplayConfigurator::DisplayConfigurator(ComPtr< DXGIAdapter > adapter,
											 ComPtr< DXGIOutput > output, 
											 DXGI_FORMAT pixel_format)
		: m_impl(MakeUnique< Impl >(std::move(adapter), 
									std::move(output), 
									pixel_format)) {}

	DisplayConfigurator::DisplayConfigurator(
		DisplayConfigurator&& configurator) noexcept = default;

	DisplayConfigurator::~DisplayConfigurator() = default;

	[[nodiscard]]
	HRESULT DisplayConfigurator::Configure() const {
		return m_impl->Configure();
	}

	[[nodiscard]]
	const DisplayConfiguration* DisplayConfigurator
		::GetDisplayConfiguration() const noexcept {

		return m_impl->GetDisplayConfiguration();
	}

	#pragma endregion
}