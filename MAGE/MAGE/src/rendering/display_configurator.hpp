#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\display_configuration.hpp"
#include "scripting\variable_script.hpp"

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

	/**
	 A class of display configurators.
	 */
	class DisplayConfigurator final {

	public:

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
		 Constructs a display configurator.
		 */
		DisplayConfigurator();

		/**
		 Constructs a display configurator from the given display configurator.

		 @param[in]		display_configurator
						A reference to a display configurator to copy.
		 */
		DisplayConfigurator(const DisplayConfigurator &display_configurator) = delete;

		/**
		 Constructs a display configurator by moving the given display configurator.

		 @param[in]		display_configurator
						A reference to a display configurator to move.
		 */
		DisplayConfigurator(DisplayConfigurator &&display_configurator);

		/**
		 Destructs this display configurator.
		 */
		~DisplayConfigurator();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given display configurator to this display configurator.

		 @param[in]		display_configurator
						A reference to a display configurator to copy.
		 @return		A reference to the copy of the given display configurator
						(i.e. this display configurator).
		 */
		DisplayConfigurator &operator=(const DisplayConfigurator &display_configurator) = delete;

		/**
		 Moves the given display configurator to this display configurator.

		 @param[in]		display_configurator
						A reference to a display configurator to move.
		 @return		A reference to the moved display configurator
						(i.e. this display configurator).
		 */
		DisplayConfigurator &operator=(DisplayConfigurator &&display_configurator) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Configurs the display by enumerating the available display modes 
		 and options associated with the adapter output of the physical adapter 
		 with the most dedicated video memory.

		 @return		A success/error value.
		 */
		HRESULT Configure();

		/**
		 Returns the display configuration of this display configurator.

		 @return		A reference to the display configuration
						of this display configurator.
		 */
		const DisplayConfiguration &GetDisplayConfiguration() const noexcept {
			return m_display_configuration;
		}

	private:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Engine-defined callback function used with the CreateDialog
		 for display configuration.

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
		static INT_PTR CALLBACK DisplayDialogProcDelegate(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Initializes the adapter and the output this display configurator.

		 @throws		FormattedException
						Failed to initialize the adapter and the output 
						of this display configurator.
		 */
		void InitializeAdapterAndOutput();

		/**
		 Initializes the display modes of this display configurator.

		 @throws		FormattedException
						Failed to initialize the display modes
						of this display configurator.
		 */
		void InitializeDisplayModes();

		/**
		 Engine-defined callback function used with the CreateDialog
		 for display configuration.

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
		INT_PTR DisplayDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------
		
		/**
		 The display configuration of this display configurator.
		 */
		DisplayConfiguration m_display_configuration;

		/**
		 A pointer to the script which stores the display configuration
		 of this display configurator.
		 */
		UniquePtr< VariableScript > m_display_configuration_script;

		/**
		 The linked list of enumerated display modes of this display configurator.
		 */
		list< DXGI_MODE_DESC1 > m_display_modes;
	};
}