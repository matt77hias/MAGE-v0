#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "display\display_configuration.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::rendering {

	/**
	 A class of display configurators.
	 */
	class DisplayConfigurator {

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
			                         = DXGI_FORMAT_R8G8B8A8_UNORM);

		/**
		 Constructs a display configurator.

		 @param[in]		adapter
						A pointer to the adapter.
		 @param[in]		output
						A pointer to the output.
		 @param[in]		pixel_format
						The pixel format.
		 */
		explicit DisplayConfigurator(ComPtr< DXGIAdapter > adapter,
			                         ComPtr< DXGIOutput > output,
			                         DXGI_FORMAT pixel_format 
			                         = DXGI_FORMAT_R8G8B8A8_UNORM);

		/**
		 Constructs a display configurator from the given display configurator.

		 @param[in]		configurator
						A reference to a display configurator to copy.
		 */
		DisplayConfigurator(const DisplayConfigurator& configurator) = delete;

		/**
		 Constructs a display configurator by moving the given display configurator.

		 @param[in]		configurator
						A reference to a display configurator to move.
		 */
		DisplayConfigurator(DisplayConfigurator&& configurator) noexcept;

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
		DisplayConfigurator& operator=(
			const DisplayConfigurator& configurator) = delete;

		/**
		 Moves the given display configurator to this display configurator.

		 @param[in]		configurator
						A reference to a display configurator to move.
		 @return		A reference to the moved display configurator (i.e. 
						this display configurator).
		 */
		DisplayConfigurator& operator=(
			DisplayConfigurator&& configurator) = delete;

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
		const DisplayConfiguration* GetDisplayConfiguration() const noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		class Impl;

		/**
		 A pointer to the implementation of this display configurator.
		 */
		UniquePtr< Impl > m_impl;
	};
}