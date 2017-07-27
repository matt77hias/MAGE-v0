//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "texture\texture_utils.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const XMVECTOR GetTexture2DSize(ID3D11ShaderResourceView *texture) {
		Assert(texture);

		ComPtr< ID3D11Resource > resource;
		texture->GetResource(&resource);

		ComPtr< ID3D11Texture2D > texture2D;
		const HRESULT result_texture_2d = resource.As(&texture2D);
		if (FAILED(result_texture_2d)) {
			throw FormattedException("Conversion of ID3D11Resource to Texture2D failed.");
		}

		return GetTexture2DSize(texture2D.Get());
	}

	const XMVECTOR GetTexture2DSize(ID3D11Texture2D *texture) noexcept {
		Assert(texture);
		
		// Query the texture size.
		D3D11_TEXTURE2D_DESC desc;
		texture->GetDesc(&desc);

		const XMVECTOR width = XMLoadInt(&desc.Width);
		const XMVECTOR height = XMLoadInt(&desc.Height);
		const XMVECTOR size = XMVectorMergeXY(width, height);
		return XMConvertVectorUIntToFloat(size, 0);
	}
}