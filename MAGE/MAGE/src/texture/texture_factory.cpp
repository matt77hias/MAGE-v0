//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.hpp"
#include "texture\texture_factory.hpp"
#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SharedPtr< Texture > CreateBlackTexture() {
		return CreateTexture(L"black_texture", L"assets/sprites/color/black.dds");
	}

	SharedPtr< Texture > CreateWhiteTexture() {
		return CreateTexture(L"white_texture", L"assets/sprites/color/white.dds");
	}

	SharedPtr< Texture > CreateRedTexture() {
		return CreateTexture(L"red_texture", L"assets/sprites/color/red.dds");
	}

	SharedPtr< Texture > CreateGreenTexture() {
		return CreateTexture(L"green_texture", L"assets/sprites/color/green.dds");
	}

	SharedPtr< Texture > CreateBlueTexture() {
		return CreateTexture(L"blue_texture", L"assets/sprites/color/blue.dds");
	}

	//@TODO
	void CreateSingleColorTexture(const Color &color, ID3D11ShaderResourceView **texture_srv) {
		D3D11_TEXTURE2D_DESC texture_desc = {};
		texture_desc.Width              = 1;
		texture_desc.Height             = 1;
		texture_desc.MipLevels          = 1;
		texture_desc.ArraySize          = 1;
		texture_desc.Format             = DXGI_FORMAT_B8G8R8X8_UNORM;
		texture_desc.SampleDesc.Count   = 1;
		texture_desc.SampleDesc.Quality = 1;
		texture_desc.Usage              = D3D11_USAGE_IMMUTABLE;
		texture_desc.BindFlags          = D3D11_BIND_SHADER_RESOURCE;
		texture_desc.CPUAccessFlags     = 0;
		texture_desc.MiscFlags          = 0;
		
		D3D11_SUBRESOURCE_DATA texture_data = {};
		texture_data.pSysMem            = &color;
		
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ComPtr< ID3D11Texture2D > texture;
		const HRESULT result_resource = device->CreateTexture2D(&texture_desc, &texture_data, texture.ReleaseAndGetAddressOf());

		const HRESULT result_srv = device->CreateShaderResourceView(texture.Get(), nullptr, texture_srv);
	}
}