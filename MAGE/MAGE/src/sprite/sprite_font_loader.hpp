#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"
#include "rendering\rendering_device.hpp"
#include "sprite\sprite_font_output.hpp"
#include "sprite\sprite_font_descriptor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT ImportSpriteFontFromFile(const wstring &fname, const RenderingDevice &device, SpriteFontOutput &output, const SpriteFontDescriptor &desc = SpriteFontDescriptor());
}