#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"
#include "font\sprite_font_output.hpp"
#include "font\sprite_font_descriptor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT ImportSpriteFontFromFile(const wstring &fname, ID3D11Device2 *device, SpriteFontOutput &output, const SpriteFontDescriptor &desc = SpriteFontDescriptor());
}