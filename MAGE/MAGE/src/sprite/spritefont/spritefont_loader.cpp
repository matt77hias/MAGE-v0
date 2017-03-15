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

	HRESULT ImportFontFromFile(const wstring &fname, const RenderingDevice &device, SpriteFontOutput &output, const SpriteFontDescriptor &desc) {
		FontReader reader(device, output, desc);
		return reader.ReadFromFile(fname);
	}
}