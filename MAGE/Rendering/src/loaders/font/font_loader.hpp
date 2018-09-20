#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\font\sprite_font_output.hpp"
#include "resource\font\sprite_font_descriptor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <filesystem>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	/**
	 Imports the font from the FONT file associated with the given path.

	 @param[in]		path
					A reference to the path.
	 @param[in]		device
					A reference to the device.
	 @param[out]	output
					A reference to the sprite font output.
	 @param[in]		desc
					A reference to the sprite font descriptor.
	 @throws		Exception
					Failed to import the sprite font from file.
	 */
	void ImportFontFromFile(const std::filesystem::path& path,
		                    ID3D11Device& device,
		                    SpriteFontOutput& output,
		                    const SpriteFontDescriptor& desc
		                        = SpriteFontDescriptor());
}