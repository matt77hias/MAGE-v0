//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\font\sprite_font_factory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// Factory Methods: Miscellaneous
	//-------------------------------------------------------------------------
	#pragma region

	SpriteFontPtr CreateConsolasFont(ResourceManager& resource_manager) {
		return resource_manager.GetOrCreate< SpriteFont >(
			                    L"assets/fonts/consolas.font");
	}

	#pragma endregion
}