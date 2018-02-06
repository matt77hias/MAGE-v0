//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\conversion.hpp"
#include "rendering\display_configuration.hpp"
#include "logging\error.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Normalized <> Absolute Pixel
	//-------------------------------------------------------------------------
	#pragma region

	[[nodiscard]] F32 NormalizedToAbsolutePixelX(F32 x) noexcept {
		const auto config = DisplayConfiguration::Get();
		const auto width  = static_cast< F32 >(config->GetDisplayWidth());

		return NormalizedToAbsolute(x, width);
	}

	[[nodiscard]] F32 NormalizedToAbsolutePixelY(F32 y) noexcept {
		const auto config = DisplayConfiguration::Get();
		const auto height = static_cast< F32 >(config->GetDisplayHeight());

		return NormalizedToAbsolute(y, height);
	}

	[[nodiscard]] const F32x2 
		NormalizedToAbsolutePixel(const F32x2 &p) noexcept {

		const auto config = DisplayConfiguration::Get();
		const auto width  = static_cast< F32 >(config->GetDisplayWidth());
		const auto height = static_cast< F32 >(config->GetDisplayHeight());

		return NormalizedToAbsolute(p, F32x2(width, height));
	}

	[[nodiscard]] const XMVECTOR XM_CALLCONV
		NormalizedToAbsolutePixel(FXMVECTOR p) noexcept {

		const auto config = DisplayConfiguration::Get();
		const auto width  = static_cast< F32 >(config->GetDisplayWidth());
		const auto height = static_cast< F32 >(config->GetDisplayHeight());

		return NormalizedToAbsolute(p, XMVectorSet(width, height, width, height));
	}

	[[nodiscard]] F32 AbsoluteToNormalizedPixelX(F32 x) noexcept {
		const auto config = DisplayConfiguration::Get();
		const auto width  = static_cast< F32 >(config->GetDisplayWidth());

		return AbsoluteToNormalized(x, width);
	}

	[[nodiscard]] F32 AbsoluteToNormalizedPixelY(F32 y) noexcept {
		const auto config = DisplayConfiguration::Get();
		const auto height = static_cast< F32 >(config->GetDisplayHeight());

		return AbsoluteToNormalized(y, height);
	}

	[[nodiscard]] const F32x2 
		AbsoluteToNormalizedPixel(const F32x2 &p) noexcept {

		const auto config = DisplayConfiguration::Get();
		const auto width  = static_cast< F32 >(config->GetDisplayWidth());
		const auto height = static_cast< F32 >(config->GetDisplayHeight());

		return AbsoluteToNormalized(p, F32x2(width, height));
	}

	[[nodiscard]] const XMVECTOR XM_CALLCONV
		AbsoluteToNormalizedPixel(FXMVECTOR p) noexcept {

		const auto config = DisplayConfiguration::Get();
		const auto width  = static_cast< F32 >(config->GetDisplayWidth());
		const auto height = static_cast< F32 >(config->GetDisplayHeight());

		return AbsoluteToNormalized(p, XMVectorSet(width, height, width, height));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Normalized <> Absolute Texel
	//-------------------------------------------------------------------------
	#pragma region

	[[nodiscard]] const XMVECTOR XM_CALLCONV 
		GetTexture2DSize(ID3D11ShaderResourceView *srv) {
		
		Assert(srv);

		ComPtr< ID3D11Resource > resource;
		srv->GetResource(&resource);

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

		const auto width  = XMLoad(desc.Width);
		const auto height = XMLoad(desc.Height);
		const auto size   = XMVectorMergeXY(width, height);
		return XMConvertVectorUIntToFloat(size, 0u);
	}

	static void GetTexture2DSize(ID3D11Texture2D *texture,
		                         float &width,
		                         float &height) noexcept {

		Assert(texture);

		// Query the texture size.
		D3D11_TEXTURE2D_DESC desc;
		texture->GetDesc(&desc);

		width  = static_cast< float >(desc.Width);
		height = static_cast< float >(desc.Height);
	}

	static void GetTexture2DSize(ID3D11ShaderResourceView *srv, 
		                         float &width, 
		                         float &height) {

		Assert(srv);

		ComPtr< ID3D11Resource > resource;
		srv->GetResource(&resource);

		ComPtr< ID3D11Texture2D > texture;
		const HRESULT result = resource.As(&texture);
		ThrowIfFailed(result, 
			          "Conversion of ID3D11Resource to Texture2D failed: %08X.",
			          result);

		GetTexture2DSize(texture.Get(), width, height);
	}

	[[nodiscard]] F32 
		NormalizedToAbsoluteTexelX(F32 x, ID3D11ShaderResourceView *texture) {

		float width, height;
		GetTexture2DSize(texture, width, height);

		return NormalizedToAbsolute(x, width);
	}

	[[nodiscard]] F32 
		NormalizedToAbsoluteTexelY(F32 y, ID3D11ShaderResourceView *texture) {

		float width, height;
		GetTexture2DSize(texture, width, height);

		return NormalizedToAbsolute(y, height);
	}

	[[nodiscard]] const F32x2 
		NormalizedToAbsoluteTexel(const F32x2 &p, ID3D11ShaderResourceView *texture) {

		float width, height;
		GetTexture2DSize(texture, width, height);

		return NormalizedToAbsolute(p, F32x2(width, height));
	}

	[[nodiscard]] const XMVECTOR XM_CALLCONV 
		NormalizedToAbsoluteTexel(FXMVECTOR p, ID3D11ShaderResourceView *texture) {

		float width, height;
		GetTexture2DSize(texture, width, height);

		return NormalizedToAbsolute(p, XMVectorSet(width, height, width, height));
	}

	[[nodiscard]] F32 
		AbsoluteToNormalizedTexelX(F32 x, ID3D11ShaderResourceView *texture) {

		float width, height;
		GetTexture2DSize(texture, width, height);

		return AbsoluteToNormalized(x, width);
	}

	[[nodiscard]] F32 
		AbsoluteToNormalizedTexelY(F32 y, ID3D11ShaderResourceView *texture) {

		float width, height;
		GetTexture2DSize(texture, width, height);

		return AbsoluteToNormalized(y, height);
	}

	[[nodiscard]] const F32x2 
		AbsoluteToNormalizedTexel(const F32x2 &p, ID3D11ShaderResourceView *texture) {

		float width, height;
		GetTexture2DSize(texture, width, height);

		return AbsoluteToNormalized(p, F32x2(width, height));
	}

	[[nodiscard]] const XMVECTOR XM_CALLCONV 
		AbsoluteToNormalizedTexel(FXMVECTOR p, ID3D11ShaderResourceView *texture) {

		float width, height;
		GetTexture2DSize(texture, width, height);

		return AbsoluteToNormalized(p, XMVectorSet(width, height, width, height));
	}

	#pragma endregion
}