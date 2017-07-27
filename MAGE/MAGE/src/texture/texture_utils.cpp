//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "texture\texture_utils.hpp"
#include "rendering\rendering_utils.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const XMVECTOR GetTexture2DSize(ID3D11ShaderResourceView *texture_srv) {
		Assert(texture_srv);

		ComPtr< ID3D11Resource > resource;
		texture_srv->GetResource(&resource);

		ComPtr< ID3D11Texture2D > texture;
		const HRESULT result_texture = resource.As(&texture);
		if (FAILED(result_texture)) {
			throw FormattedException("Conversion of ID3D11Resource to Texture2D failed.");
		}

		return GetTexture2DSize(texture.Get());
	}

	const XMVECTOR GetTexture2DSize(ID3D11Texture2D *texture) noexcept {
		Assert(texture);
		
		// Query the texture size.
		D3D11_TEXTURE2D_DESC desc;
		texture->GetDesc(&desc);

		const XMVECTOR width  = XMLoadInt(&desc.Width);
		const XMVECTOR height = XMLoadInt(&desc.Height);
		const XMVECTOR size   = XMVectorMergeXY(width, height);
		return XMConvertVectorUIntToFloat(size, 0);
	}

	bool HasAlpha(ID3D11ShaderResourceView *texture_srv) noexcept {
		Assert(texture_srv);

		ComPtr< ID3D11Resource > resource;
		texture_srv->GetResource(&resource);

		D3D11_RESOURCE_DIMENSION dimension;
		resource->GetType(&dimension);
		switch (dimension) {
		
		case D3D11_RESOURCE_DIMENSION_TEXTURE1D: {
			ComPtr< ID3D11Texture1D > texture;
			const HRESULT result_texture = resource.As(&texture);
			Assert(SUCCEEDED(result_texture));
			return HasAlpha(texture.Get());
		}

		case D3D11_RESOURCE_DIMENSION_TEXTURE2D: {
			ComPtr< ID3D11Texture2D > texture;
			const HRESULT result_texture = resource.As(&texture);
			Assert(SUCCEEDED(result_texture));
			return HasAlpha(texture.Get());
		}

		case D3D11_RESOURCE_DIMENSION_TEXTURE3D: {
			ComPtr< ID3D11Texture3D > texture;
			const HRESULT result_texture = resource.As(&texture);
			Assert(SUCCEEDED(result_texture));
			return HasAlpha(texture.Get());
		}

		default:
			return false;
		}
	}

	bool HasAlpha(ID3D11Texture1D *texture) noexcept {
		Assert(texture);

		// Query the texture size.
		D3D11_TEXTURE1D_DESC desc;
		texture->GetDesc(&desc);

		return HasAlpha(desc.Format);
	}

	bool HasAlpha(ID3D11Texture2D *texture) noexcept {
		Assert(texture);

		// Query the texture size.
		D3D11_TEXTURE2D_DESC desc;
		texture->GetDesc(&desc);

		return HasAlpha(desc.Format);
	}

	bool HasAlpha(ID3D11Texture3D *texture) noexcept {
		Assert(texture);

		// Query the texture size.
		D3D11_TEXTURE3D_DESC desc;
		texture->GetDesc(&desc);

		return HasAlpha(desc.Format);
	}
}