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

	//-------------------------------------------------------------------------
	// Utilities
	//-------------------------------------------------------------------------
	#pragma region

	[[nodiscard]]
	const U32x2 GetTexture2DSize(ID3D11ShaderResourceView& srv) {
		ComPtr< ID3D11Resource > resource;
		srv.GetResource(&resource);

		ComPtr< ID3D11Texture2D > texture;
		const HRESULT result = resource.As(&texture);
		ThrowIfFailed(result, 
					  "Conversion of ID3D11Resource to Texture2D failed: %08X.", 
					  result);

		return GetTexture2DSize(*texture.Get());
	}

	[[nodiscard]]
	const U32x2 GetTexture2DSize(ID3D11Texture2D& texture) noexcept {
		// Query the texture size.
		D3D11_TEXTURE2D_DESC desc;
		texture.GetDesc(&desc);

		return U32x2(desc.Width, desc.Height);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Texture
	//-------------------------------------------------------------------------
	#pragma region

	Texture::Texture(ID3D11Device& device, wstring fname)
		: Resource< Texture >(std::move(fname)), 
		m_texture_srv() {

		loader::ImportTextureFromFile(GetPath(), 
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

	Texture& Texture::operator=(Texture&& texture) noexcept = default;

	#pragma endregion
}