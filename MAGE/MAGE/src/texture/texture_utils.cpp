//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "texture\texture_utils.hpp"
#include "logging\error.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	[[nodiscard]] const XMVECTOR XM_CALLCONV 
		GetTexture2DSize(ID3D11ShaderResourceView *texture_srv) {
		
		Assert(texture_srv);

		ComPtr< ID3D11Resource > resource;
		texture_srv->GetResource(&resource);

		ComPtr< ID3D11Texture2D > texture;
		const HRESULT result = resource.As(&texture);
		ThrowIfFailed(result,
			"Conversion of ID3D11Resource to Texture2D failed: %08X.", 
			result);

		return GetTexture2DSize(texture.Get());
	}

	[[nodiscard]] const XMVECTOR XM_CALLCONV 
		GetTexture2DSize(ID3D11Texture2D *texture) noexcept {
		
		Assert(texture);
		
		// Query the texture size.
		D3D11_TEXTURE2D_DESC desc;
		texture->GetDesc(&desc);

		const auto width  = XMLoadInt(&desc.Width);
		const auto height = XMLoadInt(&desc.Height);
		const auto size   = XMVectorMergeXY(width, height);
		return XMConvertVectorUIntToFloat(size, 0u);
	}
}