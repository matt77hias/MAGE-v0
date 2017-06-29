//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "texture\texture.hpp"
#include "texture\texture_loader.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Texture::Texture(const wstring &fname)
		: Texture(GetRenderingDevice(), fname) {}

	Texture::Texture(ID3D11Device2 *device, const wstring &fname)
		: Resource< Texture >(fname, fname), m_device(device), m_texture_srv() {

		Assert(m_device);

		ImportTextureFromFile(GetFilename(), m_device, m_texture_srv.ReleaseAndGetAddressOf());
	}

	Texture::Texture(const wstring &guid,
		const D3D11_TEXTURE2D_DESC *desc,
		const D3D11_SUBRESOURCE_DATA *initial_data)
		: Texture(GetRenderingDevice(), guid, desc, initial_data) {}

	Texture::Texture(ID3D11Device2 *device, const wstring &guid,
		const D3D11_TEXTURE2D_DESC *desc, const D3D11_SUBRESOURCE_DATA *initial_data)
		: Resource< Texture >(guid), m_device(device), m_texture_srv() {

		Assert(m_device);

		ComPtr< ID3D11Texture2D > texture;
		const HRESULT result_resource = device->CreateTexture2D(desc, initial_data, texture.ReleaseAndGetAddressOf());
		if (FAILED(result_resource)) {
			throw FormattedException("Texture creation failed: %08X.", result_resource);
		}

		const HRESULT result_srv = device->CreateShaderResourceView(texture.Get(), nullptr, m_texture_srv.ReleaseAndGetAddressOf());
		if (FAILED(result_srv)) {
			throw FormattedException("Texture shader resource view creation failed: %08X.", result_srv);
		}
	}
}