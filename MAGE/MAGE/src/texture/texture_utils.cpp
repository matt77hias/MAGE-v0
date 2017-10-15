//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "texture\texture_utils.hpp"
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
		ThrowIfFailed(result_texture, 
			"Conversion of ID3D11Resource to Texture2D failed: %08X.", 
			result_texture);

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
}