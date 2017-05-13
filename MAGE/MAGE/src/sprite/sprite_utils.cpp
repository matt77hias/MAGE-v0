//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "sprite\sprite_utils.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const XMMATRIX GetViewportTransform(ID3D11DeviceContext *device_context, DXGI_MODE_ROTATION rotation_mode) {
		Assert(device_context);
		
		UINT nb_of_viewports = 1;
		D3D11_VIEWPORT viewport;
		device_context->RSGetViewports(&nb_of_viewports, &viewport);
		if (nb_of_viewports != 1) {
			throw FormattedException("No viewport is set.");
		}
		
		return GetViewportTransform(viewport, rotation_mode);
	}

	const XMMATRIX GetViewportTransform(ID3D11DeviceContext *device_context, DXGI_MODE_ROTATION rotation_mode, D3D11_VIEWPORT *viewport) {
		Assert(device_context);
		Assert(viewport);
		
		UINT nb_of_viewports = 1;
		device_context->RSGetViewports(&nb_of_viewports, viewport);
		if (nb_of_viewports != 1) {
			throw FormattedException("No viewport is set.");
		}

		return GetViewportTransform(*viewport, rotation_mode);
	}
	
	const XMMATRIX GetViewportTransform(const D3D11_VIEWPORT &viewport, DXGI_MODE_ROTATION rotation_mode) noexcept {
		const float scale_x = (viewport.Width  > 0.0f) ? 2.0f / viewport.Width  : 0.0f;
		const float scale_y = (viewport.Height > 0.0f) ? 2.0f / viewport.Height : 0.0f;
		
		switch (rotation_mode) {
		
		case DXGI_MODE_ROTATION_ROTATE90:
			return XMMATRIX
			{
				 0.0f,    -scale_y, 0.0f, 0.0f,
				-scale_x,  0.0f,    0.0f, 0.0f,
				 0.0f,     0.0f,    1.0f, 0.0f,
				 1.0f,     1.0f,    0.0f, 1.0f
			};
		
		case DXGI_MODE_ROTATION_ROTATE180:
			return XMMATRIX
			{
				-scale_x,  0.0f,    0.0f, 0.0f,
				 0.0f,     scale_y, 0.0f, 0.0f,
				 0.0f,     0.0f,    1.0f, 0.0f,
				 1.0f,    -1.0f,    0.0f, 1.0f
			};
		
		case DXGI_MODE_ROTATION_ROTATE270:
			return XMMATRIX
			{
				 0.0f,     scale_y, 0.0f, 0.0f,
				 scale_x,  0.0f,    0.0f, 0.0f,
				 0.0f,     0.0f,    1.0f, 0.0f,
				-1.0f,    -1.0f,    0.0f, 1.0f
			};
		
		default:
			return XMMATRIX
			{
				 scale_x,  0.0f,    0.0f, 0.0f,
				 0.0f,    -scale_y, 0.0f, 0.0f,
				 0.0f,     0.0f,    1.0f, 0.0f,
				-1.0f,     1.0f,    0.0f, 1.0f
			};
		}
	}

	const XMVECTOR GetTexture2DSize(ID3D11ShaderResourceView *texture) {
		Assert(texture);
		
		ComPtr< ID3D11Resource > resource;
		texture->GetResource(&resource);

		ComPtr< ID3D11Texture2D > texture2D;
		const HRESULT result_texture_2d = resource.As(&texture2D);
		if (FAILED(result_texture_2d)) {
			throw FormattedException("Conversion of ID3D11Resource to Texture2D failed.");
		}

		// Query the texture size.
		D3D11_TEXTURE2D_DESC desc;
		texture2D->GetDesc(&desc);

		const XMVECTOR width  = XMLoadInt(&desc.Width);
		const XMVECTOR height = XMLoadInt(&desc.Height);
		const XMVECTOR size   = XMVectorMergeXY(width, height);
		return XMConvertVectorUIntToFloat(size, 0);
	}
}