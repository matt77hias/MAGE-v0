//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\spritefont\spritefont_loader.hpp"
#include "loaders\spritefont\spritefont_reader.hpp"
#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void ImportFontFromFile(const wstring &fname, ID3D11Device5 *device, 
		SpriteFontOutput &output, const SpriteFontDescriptor &desc) {
		
		Assert(device);

		SpriteFontReader reader(device, output, desc);
		reader.ReadFromFile(fname);
	}
}