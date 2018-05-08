//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\font\font_loader.hpp"
#include "loaders\font\font_reader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	void ImportFontFromFile(const std::filesystem::path& path, 
		                    ID3D11Device& device, 
		                    SpriteFontOutput& output, 
		                    const SpriteFontDescriptor& desc) {
		
		SpriteFontReader reader(device, output, desc);
		reader.ReadFromFile(path);
	}
}