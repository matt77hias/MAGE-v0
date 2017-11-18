//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\sprite_font_loader.hpp"
#include "loaders\font\font_loader.hpp"
#include "utils\file\file_utils.hpp"
#include "utils\logging\error.hpp"
#include "utils\exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void ImportSpriteFontFromFile(const wstring &fname, ID3D11Device5 *device, 
		SpriteFontOutput &output, const SpriteFontDescriptor &desc) {
		
		Assert(device);

		const wstring extension = GetFileExtension(fname);

		if (extension == L"font" || extension == L"FONT") {
			ImportFontFromFile(fname, device, output, desc);
		}
		else {
			throw FormattedException(
				"Unknown sprite font file extension: %ls", fname.c_str());
		}
	}
}