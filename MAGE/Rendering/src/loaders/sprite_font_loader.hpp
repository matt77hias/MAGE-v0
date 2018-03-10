#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\font\sprite_font_output.hpp"
#include "resource\font\sprite_font_descriptor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	/**
	 Imports the sprite font from the given file.

	 @param[in]		fname
					A reference to the filename.
	 @param[in]		device
					A reference to the device.
	 @param[out]	output
					A reference to the sprite font output.
	 @param[in]		desc
					A reference to the sprite font descriptor.
	 @throws		Exception
					Failed to import the sprite font from file.
	 */
	void ImportSpriteFontFromFile(const wstring& fname, 
		                          ID3D11Device& device, 
		                          SpriteFontOutput& output, 
		                          const SpriteFontDescriptor& desc 
		                              = SpriteFontDescriptor());
}