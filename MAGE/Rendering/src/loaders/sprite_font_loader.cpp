//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\sprite_font_loader.hpp"
#include "loaders\font\font_loader.hpp"
#include "string\string_utils.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	void ImportSpriteFontFromFile(const std::filesystem::path& path,
		                          ID3D11Device& device, 
		                          SpriteFontOutput& output, 
		                          const SpriteFontDescriptor& desc) {
		
		std::wstring extension(path.extension());
		TransformToLowerCase(extension);

		if (L".font" == extension) {
			ImportFontFromFile(path, device, output, desc);
		}
		else {
			throw Exception("Unknown sprite font file extension: {}", path);
		}
	}
}