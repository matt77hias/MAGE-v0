//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\spritefont\spritefont_loader.hpp"
#include "sprite\spritefont\spritefont_reader.hpp"

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