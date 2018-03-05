//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\sprite_font_loader.hpp"
#include "loaders\font\font_loader.hpp"
#include "file\file_utils.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <algorithm>
#include <cwctype>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	void ImportSpriteFontFromFile(const wstring& fname, 
		                          ID3D11Device& device, 
		                          SpriteFontOutput& output, 
		                          const SpriteFontDescriptor& desc) {
		
		auto extension = GetFileExtension(fname);
		std::transform(extension.begin(), extension.end(), extension.begin(),
					   std::towlower);

		if (L"font" == extension) {
			ImportFontFromFile(fname, device, output, desc);
		}
		else {
			throw Exception("Unknown sprite font file extension: %ls", 
				            fname.c_str());
		}
	}
}