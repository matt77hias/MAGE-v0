//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "texture\texture.hpp"
#include "loaders\texture_loader.hpp"
#include "utils\logging\error.hpp"
#include "utils\exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Texture::Texture(wstring fname)
		: Texture(std::move(fname), Pipeline::GetDevice()) {}

	Texture::Texture(wstring fname, ID3D11Device5 *device)
		: Resource< Texture >(std::move(fname)), 
		m_texture_srv() {

		Assert(device);

		ImportTextureFromFile(
			GetFilename(), device, m_texture_srv.ReleaseAndGetAddressOf());
	}

	Texture::Texture(wstring guid,
		const D3D11_TEXTURE2D_DESC *desc,
		const D3D11_SUBRESOURCE_DATA *initial_data)
		: Texture(std::move(guid), Pipeline::GetDevice(), desc, initial_data) {}

	Texture::Texture(wstring guid, ID3D11Device5 *device,
		const D3D11_TEXTURE2D_DESC *desc, 
		const D3D11_SUBRESOURCE_DATA *initial_data)
		: Resource< Texture >(std::move(guid)), 
		m_texture_srv() {

		Assert(device);

		ComPtr< ID3D11Texture2D > texture;
		{
			const HRESULT result = device->CreateTexture2D(
				desc, initial_data, texture.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "Texture 2D creation failed: %08X.", result);
		}
		{
			const HRESULT result = device->CreateShaderResourceView(
				texture.Get(), nullptr, m_texture_srv.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "Texture SRV creation failed: %08X.", result);
		}
	}
}