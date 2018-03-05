//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\texture\texture.hpp"
#include "loaders\texture_loader.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	Texture::Texture(ID3D11Device& device, wstring fname)
		: Resource< Texture >(std::move(fname)), 
		m_texture_srv() {

		loader::ImportTextureFromFile(GetFilename(), 
									  device, 
									  m_texture_srv.ReleaseAndGetAddressOf());
	}

	Texture::Texture(ID3D11Device& device, wstring guid, 
					 const D3D11_TEXTURE2D_DESC& desc, 
					 const D3D11_SUBRESOURCE_DATA& initial_data)
		: Resource< Texture >(std::move(guid)), 
		m_texture_srv() {

		ComPtr< ID3D11Texture2D > texture;
		
		// Create the texture.
		{
			const HRESULT result = device.CreateTexture2D(
				&desc, &initial_data, texture.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "Texture 2D creation failed: %08X.", result);
		}
		
		// Create the SRV.
		{
			const HRESULT result = device.CreateShaderResourceView(
				texture.Get(), nullptr, m_texture_srv.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "Texture SRV creation failed: %08X.", result);
		}
	}

	Texture::Texture(Texture&& texture) noexcept = default;

	Texture::~Texture() = default;

	Texture &Texture::operator=(Texture&& texture) noexcept = default;
}