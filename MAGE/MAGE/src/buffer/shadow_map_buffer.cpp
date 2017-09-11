//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "buffer\shadow_map_buffer.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// ShadowMapBuffer
	//-------------------------------------------------------------------------

	ShadowMapBuffer::ShadowMapBuffer(
		size_t nb_shadow_maps, UINT width, UINT height,
		DepthFormat format) 
		: ShadowMapBuffer(GetDevice(), 
			nb_shadow_maps, width, height, format) {}

	ShadowMapBuffer::ShadowMapBuffer(ID3D11Device2 *device,
		size_t nb_shadow_maps, UINT width, UINT height,
		DepthFormat format)
		: m_width(width), m_height(height), m_format(format), 
		m_viewport(), m_dsvs(), m_srv() {

		m_viewport.SetWidthAndHeight(m_width, m_height);
		SetupShadowMapBuffer(device, nb_shadow_maps);
	}

	void ShadowMapBuffer::SetupShadowMapBuffer(ID3D11Device2 *device,
		size_t nb_shadow_maps) {

		switch (m_format) {
		case DepthFormat::D16: {
			Setup16BitShadowMapArray(device, nb_shadow_maps);
			break;
		}
		default: {
			Setup24BitShadowMapArray(device, nb_shadow_maps);
		}
		}
	}

	void ShadowMapBuffer::Setup16BitShadowMapArray(ID3D11Device2 *device,
		size_t nb_shadow_maps) {

		SetupShadowMapArray(device, nb_shadow_maps,
									DXGI_FORMAT_R16_TYPELESS, 
									DXGI_FORMAT_D16_UNORM, 
									DXGI_FORMAT_R16_UNORM);
	}
	
	void ShadowMapBuffer::Setup24BitShadowMapArray(ID3D11Device2 *device,
		size_t nb_shadow_maps) {

		SetupShadowMapArray(device, nb_shadow_maps,
									DXGI_FORMAT_R24G8_TYPELESS, 
									DXGI_FORMAT_D24_UNORM_S8_UINT, 
									DXGI_FORMAT_R24_UNORM_X8_TYPELESS);
	}

	void ShadowMapBuffer::SetupShadowMapArray(ID3D11Device2 *device,
		size_t nb_shadow_maps, DXGI_FORMAT texture_format,
		DXGI_FORMAT dsv_format, DXGI_FORMAT srv_format) {

		Assert(device);

		// Clear the DSV vector (i.e. reset the DSVs).
		m_dsvs.clear();
		// Reset the SRV.
		m_srv.Reset();

		// Resize the DSV vector.
		m_dsvs.resize(nb_shadow_maps);

		// Create the texture descriptor.
		D3D11_TEXTURE2D_DESC texture_desc = {};
		texture_desc.Width            = m_width;
		texture_desc.Height           = m_height;;
		texture_desc.MipLevels        = 1u;
		texture_desc.ArraySize        = static_cast< UINT >(nb_shadow_maps);
		texture_desc.Format           = texture_format;
		texture_desc.SampleDesc.Count = 1u;
		texture_desc.Usage            = D3D11_USAGE_DEFAULT;
		texture_desc.BindFlags        = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
		
		// Create the texture.
		ComPtr< ID3D11Texture2D > texture;
		const HRESULT result_texture = device->CreateTexture2D(
			&texture_desc, nullptr,
			texture.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_texture, "Texture 2D creation failed: %08X.", result_texture);

		// Create the DSV descriptor.
		D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc = {};
		dsv_desc.Format        = dsv_format;
		dsv_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
		dsv_desc.Texture2DArray.ArraySize = 1u;
		
		// Create the DSVs for each texture element.
		for (UINT i = 0u; i < texture_desc.ArraySize; ++i) {
			dsv_desc.Texture2DArray.FirstArraySlice = i;

			const HRESULT result_dsv = device->CreateDepthStencilView(
				texture.Get(), &dsv_desc,
				m_dsvs[i].ReleaseAndGetAddressOf());
			ThrowIfFailed(result_dsv, "DSV creation failed: %08X.", result_dsv);
		}

		// Create the SRV descriptor.
		D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc = {};
		srv_desc.Format        = srv_format;
		srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srv_desc.Texture2DArray.MipLevels = 1u;
		srv_desc.Texture2DArray.ArraySize = texture_desc.ArraySize;

		// Create the SRV for all texture elements.
		const HRESULT result_srv = device->CreateShaderResourceView(
			texture.Get(), &srv_desc,
			m_srv.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_srv, "SRV creation failed: %08X.", result_srv);
	}
	
	//-------------------------------------------------------------------------
	// ShadowCubeMapBuffer
	//-------------------------------------------------------------------------

	ShadowCubeMapBuffer::ShadowCubeMapBuffer(
		size_t nb_shadow_cube_maps, UINT width, UINT height,
		DepthFormat format)
		: ShadowCubeMapBuffer(GetDevice(),
			nb_shadow_cube_maps, width, height, format) {}

	ShadowCubeMapBuffer::ShadowCubeMapBuffer(ID3D11Device2 *device,
		size_t nb_shadow_cube_maps, UINT width, UINT height,
		DepthFormat format)
		: m_width(width), m_height(height), m_format(format),
		m_viewport(), m_dsvs(), m_srv() {

		m_viewport.SetWidthAndHeight(m_width, m_height);
		SetupShadowCubeMapBuffer(device, nb_shadow_cube_maps);
	}

	void ShadowCubeMapBuffer::SetupShadowCubeMapBuffer(ID3D11Device2 *device,
		size_t nb_shadow_cube_maps) {

		switch (m_format) {
		case DepthFormat::D16: {
			Setup16BitShadowCubeMapArray(device, nb_shadow_cube_maps);
			break;
		}
		default: {
			Setup24BitShadowCubeMapArray(device, nb_shadow_cube_maps);
		}
		}
	}

	void ShadowCubeMapBuffer::Setup16BitShadowCubeMapArray(ID3D11Device2 *device,
		size_t nb_shadow_cube_maps) {

		SetupShadowCubeMapArray(device, nb_shadow_cube_maps,
								DXGI_FORMAT_R16_TYPELESS, 
								DXGI_FORMAT_D16_UNORM, 
								DXGI_FORMAT_R16_UNORM);
	}
	
	void ShadowCubeMapBuffer::Setup24BitShadowCubeMapArray(ID3D11Device2 *device,
		size_t nb_shadow_cube_maps) {

		SetupShadowCubeMapArray(device, nb_shadow_cube_maps,
								DXGI_FORMAT_R24G8_TYPELESS, 
								DXGI_FORMAT_D24_UNORM_S8_UINT, 
								DXGI_FORMAT_R24_UNORM_X8_TYPELESS);
	}

	void ShadowCubeMapBuffer::SetupShadowCubeMapArray(ID3D11Device2 *device,
		size_t nb_shadow_cube_maps, DXGI_FORMAT texture_format,
		DXGI_FORMAT dsv_format, DXGI_FORMAT srv_format) {

		Assert(device);

		// Clear the DSV vector (i.e. reset the DSVs).
		m_dsvs.clear();
		// Reset the SRV.
		m_srv.Reset();

		// Resize the DSV vector.
		m_dsvs.resize(nb_shadow_cube_maps);

		// Create the texture descriptor.
		D3D11_TEXTURE2D_DESC texture_desc = {};
		texture_desc.Width            = m_width;
		texture_desc.Height           = m_height;;
		texture_desc.MipLevels        = 1u;
		texture_desc.ArraySize        = 6u * static_cast< UINT >(nb_shadow_cube_maps);
		texture_desc.Format           = texture_format;
		texture_desc.SampleDesc.Count = 1u;
		texture_desc.Usage            = D3D11_USAGE_DEFAULT;
		texture_desc.BindFlags        = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
		texture_desc.MiscFlags        = D3D11_RESOURCE_MISC_TEXTURECUBE;

		// Create the texture.
		ComPtr< ID3D11Texture2D > texture;
		const HRESULT result_texture = device->CreateTexture2D(
			&texture_desc, nullptr,
			texture.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_texture, "Texture 2D creation failed: %08X.", result_texture);

		// Create the DSV descriptor.
		D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc = {};
		dsv_desc.Format        = dsv_format;
		dsv_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
		dsv_desc.Texture2DArray.ArraySize = 6u;
		
		// Create the DSVs for each texture element.
		for (UINT i = 0u; i < texture_desc.ArraySize; i += 6u) {
			dsv_desc.Texture2DArray.FirstArraySlice = i;

			const HRESULT result_dsv = device->CreateDepthStencilView(
				texture.Get(), &dsv_desc,
				m_dsvs[i].ReleaseAndGetAddressOf());
			ThrowIfFailed(result_dsv, "DSV creation failed: %08X.", result_dsv);
		}

		// Create the SRV descriptor.
		D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc = {};
		srv_desc.Format        = srv_format;
		srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srv_desc.Texture2DArray.MipLevels = 1u;
		srv_desc.Texture2DArray.ArraySize = texture_desc.ArraySize;

		// Create the SRV for all texture elements.
		const HRESULT result_srv = device->CreateShaderResourceView(
			texture.Get(), &srv_desc,
			m_srv.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_srv, "SRV creation failed: %08X.", result_srv);
	}
}