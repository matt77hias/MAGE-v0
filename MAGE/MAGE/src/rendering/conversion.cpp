//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\conversion.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Texture Size
	//-------------------------------------------------------------------------
	#pragma region

	[[nodiscard]]
	const U32x2 GetTexture2DSize(ID3D11ShaderResourceView &srv) {
		ComPtr< ID3D11Resource > resource;
		srv.GetResource(&resource);

		ComPtr< ID3D11Texture2D > texture;
		{
			const HRESULT result = resource.As(&texture);
			ThrowIfFailed(result,
						  "Conversion of ID3D11Resource to Texture2D failed: %08X.",
						  result);
		}

		return GetTexture2DSize(*texture.Get());
	}

	[[nodiscard]]
	const U32x2 GetTexture2DSize(ID3D11Texture2D &texture) noexcept {
		// Query the texture size.
		D3D11_TEXTURE2D_DESC desc;
		texture.GetDesc(&desc);

		return U32x2(desc.Width, desc.Height);
	}

	#pragma endregion
}