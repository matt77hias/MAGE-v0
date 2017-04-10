//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "font\spritefont\spritefont_loader.hpp"
#include "font\spritefont\spritefont_reader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT ImportFontFromFile(const wstring &fname, ID3D11Device2 *device, SpriteFontOutput &output, const SpriteFontDescriptor &desc) {
		SpriteFontReader reader(device, output, desc);
		return reader.ReadFromFile(fname);
	}
}