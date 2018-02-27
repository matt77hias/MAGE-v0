//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "texture\texture_factory.hpp"
#include "texture\texture.hpp"
#include "rendering\resource_manager.hpp"
#include "logging\error.hpp"

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
namespace mage {

	/**
	 Create a 2D texture descriptor for a single color (i.e. one texel) texture.

	 @return		A 2D texture descriptor for a single color (i.e. one texel) 
					texture.
	 */
	[[nodiscard]] static inline const D3D11_TEXTURE2D_DESC 
		CreateSingleColorTexture2DDesc() noexcept {

		D3D11_TEXTURE2D_DESC texture_desc = {};
		texture_desc.Width              = 1u;
		texture_desc.Height             = 1u;
		texture_desc.MipLevels          = 1u;
		texture_desc.ArraySize          = 1u;
		texture_desc.Format             = DXGI_FORMAT_B8G8R8X8_UNORM;
		texture_desc.SampleDesc.Count   = 1u;
		texture_desc.Usage              = D3D11_USAGE_IMMUTABLE;
		texture_desc.BindFlags          = D3D11_BIND_SHADER_RESOURCE;
		return texture_desc;
	}

	SharedPtr< const Texture > CreateMAGETexture(ResourceManager *resource_manager) {
		Assert(resource_manager);

		return resource_manager->GetOrCreate< Texture >(L"assets/textures/mage.dds");
	}

	SharedPtr< const Texture > CreateReferenceTexture(ResourceManager *resource_manager) {
		Assert(resource_manager);

		return resource_manager->GetOrCreate< Texture >(L"assets/textures/reference.dds");
	}

	SharedPtr< const Texture > CreateBlackTexture(ResourceManager *resource_manager) {
		Assert(resource_manager);
		
		const auto texture_desc = CreateSingleColorTexture2DDesc();

		static constexpr U32 color = 0xFF000000;

		D3D11_SUBRESOURCE_DATA texture_data = {};
		texture_data.pSysMem     = &color;
		texture_data.SysMemPitch = sizeof(color);
		
		return resource_manager->GetOrCreate< Texture >(
			MAGE_GUID_TEXTURE_BLACK, &texture_desc, &texture_data);
	}

	SharedPtr< const Texture > CreateWhiteTexture(ResourceManager *resource_manager) {
		Assert(resource_manager);
		
		const auto texture_desc = CreateSingleColorTexture2DDesc();

		static constexpr U32 color = 0xFFFFFFFF;

		D3D11_SUBRESOURCE_DATA texture_data = {};
		texture_data.pSysMem     = &color;
		texture_data.SysMemPitch = sizeof(color);

		return resource_manager->GetOrCreate< Texture >(
			MAGE_GUID_TEXTURE_WHITE, &texture_desc, &texture_data);
	}

	SharedPtr< const Texture > CreateRedTexture(ResourceManager *resource_manager) {
		Assert(resource_manager);
		
		const auto texture_desc = CreateSingleColorTexture2DDesc();

		static constexpr U32 color = 0xFF000000;

		D3D11_SUBRESOURCE_DATA texture_data = {};
		texture_data.pSysMem     = &color;
		texture_data.SysMemPitch = sizeof(color);

		return resource_manager->GetOrCreate< Texture >(
			MAGE_GUID_TEXTURE_RED, &texture_desc, &texture_data);
	}

	SharedPtr< const Texture > CreateGreenTexture(ResourceManager *resource_manager) {
		Assert(resource_manager);
		
		const auto texture_desc = CreateSingleColorTexture2DDesc();

		static constexpr U32 color = 0xFF00FF00;

		D3D11_SUBRESOURCE_DATA texture_data = {};
		texture_data.pSysMem     = &color;
		texture_data.SysMemPitch = sizeof(color);

		return resource_manager->GetOrCreate< Texture >(
			MAGE_GUID_TEXTURE_GREEN, &texture_desc, &texture_data);
	}

	SharedPtr< const Texture > CreateBlueTexture(ResourceManager *resource_manager) {
		Assert(resource_manager);
		
		const auto texture_desc = CreateSingleColorTexture2DDesc();

		static constexpr U32 color = 0xFF0000FF;

		D3D11_SUBRESOURCE_DATA texture_data = {};
		texture_data.pSysMem     = &color;
		texture_data.SysMemPitch = sizeof(color);

		return resource_manager->GetOrCreate< Texture >(
			MAGE_GUID_TEXTURE_BLUE, &texture_desc, &texture_data);
	}
}