//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "texture\texture_factory.hpp"
#include "resource\resource_manager.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	inline D3D11_TEXTURE2D_DESC CreateSingleColorTexture2DDesc() noexcept {
		D3D11_TEXTURE2D_DESC texture_desc = {};
		texture_desc.Width              = 1;
		texture_desc.Height             = 1;
		texture_desc.MipLevels          = 1;
		texture_desc.ArraySize          = 1;
		texture_desc.Format             = DXGI_FORMAT_B8G8R8X8_UNORM;
		texture_desc.SampleDesc.Count   = 1;
		texture_desc.Usage              = D3D11_USAGE_IMMUTABLE;
		texture_desc.BindFlags          = D3D11_BIND_SHADER_RESOURCE;
		return texture_desc;
	}

	SharedPtr< const Texture > CreateMAGETexture() {
		return ResourceManager::Get()->GetOrCreateTexture(L"assets/sprites/mage.dds");
	}

	SharedPtr< const Texture > CreateReferenceTexture() {
		return ResourceManager::Get()->GetOrCreateTexture(L"assets/sprites/reference.dds");
	}

	SharedPtr< const Texture > CreateBlackTexture() {
		const D3D11_TEXTURE2D_DESC texture_desc = CreateSingleColorTexture2DDesc();

		static const uint32_t color = 0x000000FF;

		D3D11_SUBRESOURCE_DATA texture_data = {};
		texture_data.pSysMem     = &color;
		texture_data.SysMemPitch = sizeof(uint32_t);
		
		return ResourceManager::Get()->GetOrCreateTexture(MAGE_GUID_TEXTURE_BLACK, &texture_desc, &texture_data);
	}

	SharedPtr< const Texture > CreateWhiteTexture() {
		const D3D11_TEXTURE2D_DESC texture_desc = CreateSingleColorTexture2DDesc();

		static const uint32_t color = 0xFFFFFFFF;

		D3D11_SUBRESOURCE_DATA texture_data = {};
		texture_data.pSysMem     = &color;
		texture_data.SysMemPitch = sizeof(uint32_t);

		return ResourceManager::Get()->GetOrCreateTexture(MAGE_GUID_TEXTURE_WHITE, &texture_desc, &texture_data);
	}

	SharedPtr< const Texture > CreateRedTexture() {
		const D3D11_TEXTURE2D_DESC texture_desc = CreateSingleColorTexture2DDesc();

		static const uint32_t color = 0x0000FFFF;

		D3D11_SUBRESOURCE_DATA texture_data = {};
		texture_data.pSysMem     = &color;
		texture_data.SysMemPitch = sizeof(uint32_t);

		return ResourceManager::Get()->GetOrCreateTexture(MAGE_GUID_TEXTURE_RED, &texture_desc, &texture_data);
	}

	SharedPtr< const Texture > CreateGreenTexture() {
		const D3D11_TEXTURE2D_DESC texture_desc = CreateSingleColorTexture2DDesc();

		static const uint32_t color = 0x00FF00FF;

		D3D11_SUBRESOURCE_DATA texture_data = {};
		texture_data.pSysMem     = &color;
		texture_data.SysMemPitch = sizeof(uint32_t);

		return ResourceManager::Get()->GetOrCreateTexture(MAGE_GUID_TEXTURE_GREEN, &texture_desc, &texture_data);
	}

	SharedPtr< const Texture > CreateBlueTexture() {
		const D3D11_TEXTURE2D_DESC texture_desc = CreateSingleColorTexture2DDesc();

		static const uint32_t color = 0xFF0000FF;

		D3D11_SUBRESOURCE_DATA texture_data = {};
		texture_data.pSysMem     = &color;
		texture_data.SysMemPitch = sizeof(uint32_t);

		return ResourceManager::Get()->GetOrCreateTexture(MAGE_GUID_TEXTURE_BLUE, &texture_desc, &texture_data);
	}
}