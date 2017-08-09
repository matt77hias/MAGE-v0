#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering.hpp"
#include "scripting\variable_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of device enumerations.
	 */
	class DeviceEnumeration final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

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
		static INT_PTR CALLBACK SettingsDialogProcDelegate(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The allowed pixel formats.
		 */
		static const DXGI_FORMAT s_pixel_formats[3];

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a device enumeration.
		 */
		DeviceEnumeration();

		/**
		 Constructs a device enumeration from the given device enumeration.

		 @param[in]		device_enumeration
						A reference to a device enumeration to copy.
		 */
		DeviceEnumeration(const DeviceEnumeration &device_enumeration) = delete;

		/**
		 Constructs a device enumeration by moving the given device enumeration.

		 @param[in]		device_enumeration
						A reference to a device enumeration to move.
		 */
		DeviceEnumeration(DeviceEnumeration &&device_enumeration);

		/**
		 Destructs this device enumeration.
		 */
		~DeviceEnumeration();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given device enumeration to this device enumeration.

		 @param[in]		device_enumeration
						A reference to a device enumeration to copy.
		 @return		A reference to the copy of the given device enumeration
						(i.e. this device enumeration).
		 */
		DeviceEnumeration &operator=(const DeviceEnumeration &device_enumeration) = delete;

		/**
		 Moves the given device enumeration to this device enumeration.

		 @param[in]		device_enumeration
						A reference to a device enumeration to move.
		 @return		A reference to the moved device enumeration
						(i.e. this device enumeration).
		 */
		DeviceEnumeration &operator=(DeviceEnumeration &&device_enumeration) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Enumerates the available display modes on the adapter output of
		 the physical adapter with the most dedicated video memory.

		 @return		A success/error value.
		 */
		HRESULT Enumerate();

		/**
		 Returns the adapter of this device enumeration.

		 @return		A pointer to the adapter 
						of this device enumeration.
		 */
		ComPtr< IDXGIAdapter2 > GetAdapter() const noexcept {
			return m_adapter;
		}

		/**
		 Returns the output of this device enumeration.

		 @return		A pointer to the output
						of this device enumeration.
		 */
		ComPtr< IDXGIOutput2 > GetOutput() const noexcept {
			return m_output;
		}

		/**
		 Returns the selected display mode by the user 
		 of this device enumeration.

		 @return		A pointer to the selected display mode
						of this device enumeration.
		 */
		const DXGI_MODE_DESC1 *GetDisplayMode() const noexcept {
			return m_selected_diplay_mode;
		}
		
		/**
		 Checks whether the application should run in windowed mode.

		 @return		@c true if the application should run in windowed mode.
						@c false otherwise.
		 */
		bool IsWindowed() const noexcept {
			return m_windowed;
		}

		/**
		 Checks whether the application should run in full screen mode.

		 @return		@c true if the application should run in full screen mode.
						@c false otherwise.
		 */
		bool IsFullScreen() const noexcept {
			return !m_windowed;
		}

		/**
		 Checks whether V-sync should be enabled.

		 @return		@c true if v-sync should be enabled.
						@c false otherwise.
		 */
		bool IsVSynced() const noexcept {
			return m_vsync;
		}

	private:

		/**
		 Initializes the adapter and the output of this device enumeration.

		 @throws		FormattedException
						Failed to initialize the adapter and the output 
						of this device enumeration.
		 */
		void InitializeAdapterAndOutput();

		/**
		 Initializes the display modes of this device enumeration.

		 @throws		FormattedException
						Failed to initialize the display modes
						of this device enumeration.
		 */
		void InitializeDisplayModes();

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
		INT_PTR SettingsDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------
		
		/**
		 A pointer to the adapter (or video card).
		 */
		ComPtr< IDXGIAdapter2 > m_adapter;

		/**
		 A pointer to the output.
		 */
		ComPtr< IDXGIOutput2 > m_output;

		/**
		 A pointer to the script which stores the device configuration.
		 */
		UniquePtr< VariableScript > m_settings_script;
		
		/**
		 The linked list of enumerated display modes.
		 */
		list< DXGI_MODE_DESC1 > m_display_modes;

		/**
		 A pointer to the selected display mode by the user.
		 */										
		const DXGI_MODE_DESC1 *m_selected_diplay_mode;

		/**
		 Flag indicating whether the application should run in windowed mode.
		 */
		bool m_windowed;
		
		/**
		 Flag indicating whether V-sync should be enabled.
		 */
		bool m_vsync;
	};

	/**
	 Returns the device enumeration associated with the current engine.

	 @pre			The current engine is not equal to @c nullptr.
	 @return		A pointer to the device enumeration 
					associated with the current engine.
	 */
	const DeviceEnumeration *GetDeviceEnumeration() noexcept;
}