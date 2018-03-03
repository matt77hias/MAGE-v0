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
namespace mage::loader {

	/**
	 Imports the FONT from the given file.

	 @param[in]		fname
					A reference to the FONT filename.
	 @param[in]		device
					A reference to the device.
	 @param[out]	output
					A reference to the sprite font output.
	 @param[in]		desc
					A reference to the sprite font descriptor.
	 @throws		Exception
					Failed to import the sprite font from file.
	 */
	void ImportFontFromFile(const wstring& fname, 
		                    ID3D11Device& device, 
		                    SpriteFontOutput& output, 
		                    const SpriteFontDescriptor& desc 
		                        = SpriteFontDescriptor());
}