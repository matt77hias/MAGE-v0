//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\texture\texture_factory.hpp"
#include "resource\rendering_resource_manager.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_GUID_TEXTURE_BLACK	L"mage_black_texture"
#define MAGE_GUID_TEXTURE_WHITE	L"mage_white_texture"
#define MAGE_GUID_TEXTURE_RED	L"mage_red_texture"
#define MAGE_GUID_TEXTURE_GREEN	L"mage_green_texture"
#define MAGE_GUID_TEXTURE_BLUE	L"mage_blue_texture"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// General Factory Methods
	//-------------------------------------------------------------------------
	namespace {

		/**
		 Creates a flat (single-texel) 2D texture.

		 @param[in]		resource_manager
						A reference to the resource manager.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		color
						The color.
		 @return		A pointer to the texture.
		 @throws		Exception
						Failed to create the texture.
		 */
		[[nodiscard]]
		inline TexturePtr CreateFlatTexture2D(ResourceManager& resource_manager, 
											  const wstring& guid, 
											  U32 color) {

			D3D11_TEXTURE2D_DESC texture_desc = {};
			texture_desc.Width              = 1u;
			texture_desc.Height             = 1u;
			texture_desc.MipLevels          = 1u;
			texture_desc.ArraySize          = 1u;
			texture_desc.Format             = DXGI_FORMAT_B8G8R8X8_UNORM;
			texture_desc.SampleDesc.Count   = 1u;
			texture_desc.Usage              = D3D11_USAGE_IMMUTABLE;
			texture_desc.BindFlags          = D3D11_BIND_SHADER_RESOURCE;

			D3D11_SUBRESOURCE_DATA texture_data = {};
			texture_data.pSysMem     = &color;
			texture_data.SysMemPitch = sizeof(color);

			return resource_manager.GetOrCreate< Texture >(guid, 
														   texture_desc, 
														   texture_data);
		}
	}

	//-------------------------------------------------------------------------
	// Factory Methods: Flat
	//-------------------------------------------------------------------------
	#pragma region

	TexturePtr CreateBlackTexture(ResourceManager& resource_manager) {
		return CreateFlatTexture2D(resource_manager, 
								   MAGE_GUID_TEXTURE_BLACK, 
								   0xFF000000);
	}

	TexturePtr CreateWhiteTexture(ResourceManager& resource_manager) {
		return CreateFlatTexture2D(resource_manager,
								   MAGE_GUID_TEXTURE_WHITE,
								   0xFFFFFFFF);
	}

	TexturePtr CreateRedTexture(ResourceManager& resource_manager) {
		return CreateFlatTexture2D(resource_manager,
								   MAGE_GUID_TEXTURE_RED,
								   0xFF000000);
	}

	TexturePtr CreateGreenTexture(ResourceManager& resource_manager) {
		return CreateFlatTexture2D(resource_manager,
								   MAGE_GUID_TEXTURE_GREEN,
								   0xFF00FF00);
	}

	TexturePtr CreateBlueTexture(ResourceManager& resource_manager) {
		return CreateFlatTexture2D(resource_manager,
								   MAGE_GUID_TEXTURE_BLUE,
								   0xFF0000FF);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Miscellaneous
	//-------------------------------------------------------------------------
	#pragma region

	TexturePtr CreateMAGETexture(ResourceManager& resource_manager) {
		return resource_manager.GetOrCreate< Texture >(
			                    L"assets/textures/mage.dds");
	}

	TexturePtr CreateReferenceTexture(ResourceManager& resource_manager) {
		return resource_manager.GetOrCreate< Texture >(
			                    L"assets/textures/reference.dds");
	}

	#pragma endregion
}