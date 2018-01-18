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

#define MAGE_DEFAULT_DISPLAY_SETTINGS_FILE L"./DisplaySettings.var"

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
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a display configurator.

		 @param[in]		pixel_format
						The pixel format.
		 */
		explicit DisplayConfigurator(DXGI_FORMAT pixel_format 
			                         = DXGI_FORMAT_R10G10B10A2_UNORM);

		/**
		 Constructs a display configurator.

		 @param[in]		adapter
						A pointer to the adapter.
		 @param[in]		output
						A pointer to the output.
		 @param[in]		pixel_format
						The pixel format.
		 */
		explicit DisplayConfigurator(ComPtr< IDXGIAdapter4 > adapter, 
			                         ComPtr< IDXGIOutput6 > output,
			                         DXGI_FORMAT pixel_format 
			                         = DXGI_FORMAT_R10G10B10A2_UNORM);

		/**
		 Constructs a display configurator from the given display configurator.

		 @param[in]		configurator
						A reference to a display configurator to copy.
		 */
		DisplayConfigurator(const DisplayConfigurator &configurator) = delete;

		/**
		 Constructs a display configurator by moving the given display configurator.

		 @param[in]		configurator
						A reference to a display configurator to move.
		 */
		DisplayConfigurator(DisplayConfigurator &&configurator) noexcept;

		/**
		 Destructs this display configurator.
		 */
		~DisplayConfigurator();

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
		DisplayConfigurator &operator=(
			const DisplayConfigurator &configurator) = delete;

		/**
		 Moves the given display configurator to this display configurator.

		 @param[in]		configurator
						A reference to a display configurator to move.
		 @return		A reference to the moved display configurator (i.e. 
						this display configurator).
		 */
		DisplayConfigurator &operator=(
			DisplayConfigurator &&configurator) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Configurs the display by enumerating the available display modes and 
		 options associated with the adapter output of the physical adapter 
		 with the most dedicated video memory.

		 @return		A success/error value.
		 */
		[[nodiscard]] HRESULT Configure() const;

		/**
		 Returns the display configuration of this display configurator.

		 @return		A pointer to the display configuration
						of this display configurator.
		 */
		[[nodiscard]] const DisplayConfiguration *
			GetDisplayConfiguration() const noexcept {

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
		[[nodiscard]] static INT_PTR CALLBACK DisplayDialogProcDelegate(
			HWND dialog, UINT message, WPARAM wParam, LPARAM lParam);

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
		[[nodiscard]] INT_PTR DisplayDialogProc(HWND dialog, 
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
		 A pointer to the display configuration of this display configurator.
		 */
		UniquePtr< DisplayConfiguration > m_display_configuration;

		/**
		 A pointer to the script which stores the display configuration
		 of this display configurator.
		 */
		UniquePtr< VariableScript > m_display_configuration_script;

		/**
		 A pointer to the adapter (e.g. video card) of this display 
		 configurator.
		 */
		ComPtr< IDXGIAdapter4 > m_adapter;

		/**
		 A pointer to the output (e.g. screen monitor) of this display 
		 configurator.
		 */
		ComPtr< IDXGIOutput6 > m_output;

		/**
		 The enumerated display modes of this display 
		 configurator.
		 */
		std::vector< DXGI_MODE_DESC1 > m_display_modes;
	};
}