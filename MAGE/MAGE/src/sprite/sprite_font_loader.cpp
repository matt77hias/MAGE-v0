//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite_font_loader.hpp"
#include "sprite\font\font_loader.hpp"
#include "file\file_utils.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT ImportSpriteFontFromFile(const wstring &fname, const RenderingDevice &device, SpriteFontOutput &output, const SpriteFontDescriptor &desc) {
		const wstring extension = GetFileExtension(fname);

		if (extension == L"font" || extension == L"FONT") {
			return ImportFontFromFile(fname, device, output, desc);
		}

		Warning("Unknown sprite font file extension: %ls", fname.c_str());
		return E_FAIL;
	}
}