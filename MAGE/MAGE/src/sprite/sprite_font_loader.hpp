#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "rendering\rendering.hpp"
#include "string\string.hpp"
#include "sprite\sprite_font_output.hpp"
#include "sprite\sprite_font_descriptor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT ImportSpriteFontFromFile(const wstring &fname, ComPtr< ID3D11Device2 > device, SpriteFontOutput &output, const SpriteFontDescriptor &desc = SpriteFontDescriptor());
}