#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\font\sprite_font_output.hpp"
#include "sprite\font\sprite_font_descriptor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Imports the SPRITEFONT from the given file.

	 @pre			@a device is not equal to @c nullptr.
	 @param[in]		fname
					A reference to the SPRITEFONT filename.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	output
					A reference to the sprite font output.
	 @param[in]		desc
					A reference to the sprite font descriptor.
	 @throws		FormattedException
					Failed to import the sprite font from file.
	 */
	void ImportFontFromFile(const wstring &fname, ID3D11Device5 *device, 
		SpriteFontOutput &output, 
		const SpriteFontDescriptor &desc = SpriteFontDescriptor());
}