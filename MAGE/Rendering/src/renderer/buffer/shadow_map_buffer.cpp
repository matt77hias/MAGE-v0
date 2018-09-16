//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\buffer\shadow_map_buffer.hpp"
#include "renderer\factory.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// ShadowMapBuffer
	//-------------------------------------------------------------------------
	#pragma region

	ShadowMapBuffer::ShadowMapBuffer(ID3D11Device& device,
									 std::size_t nb_shadow_maps,
		                             const U32x2& resolution, 
		                             DepthFormat format)
		: m_format(format), 
		m_viewport(resolution),
		m_rasterizer_state(), 
		m_dsvs(), 
		m_srv() {

		// Setup the rasterizer state.
		SetupRasterizerState(device);
		// Setup the resource, DSVs and SRV.
		SetupShadowMapBuffer(device, nb_shadow_maps);
	}

	ShadowMapBuffer::ShadowMapBuffer(
		ShadowMapBuffer&& buffer) noexcept = default;
	
	ShadowMapBuffer::~ShadowMapBuffer() = default;
	
	ShadowMapBuffer& ShadowMapBuffer
		::operator=(ShadowMapBuffer&& buffer) noexcept = default;

	void ShadowMapBuffer::SetupRasterizerState(ID3D11Device& device) {
		const HRESULT result = CreateCullCounterClockwiseRasterizerState(
			                       device, 
			                       NotNull< ID3D11RasterizerState** >(
									   m_rasterizer_state.ReleaseAndGetAddressOf()),
			                       MAGE_DEFAULT_DEPTH_BIAS, 
			                       MAGE_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
			                       MAGE_DEFAULT_DEPTH_BIAS_CLAMP);
		ThrowIfFailed(result, "Rasterizer state creation failed: %08X.", result);
	}

	void ShadowMapBuffer::SetupShadowMapBuffer(ID3D11Device& device,
											   std::size_t nb_shadow_maps) {

		switch (m_format) {
		
		case DepthFormat::D16: {
			SetupShadowMapArray(device, 
				                nb_shadow_maps, 
				                DXGI_FORMAT_R16_TYPELESS, 
				                DXGI_FORMAT_D16_UNORM, 
				                DXGI_FORMAT_R16_UNORM);
			break;
		}
		
		default: {
			SetupShadowMapArray(device, 
				                nb_shadow_maps, 
				                DXGI_FORMAT_R32_TYPELESS, 
				                DXGI_FORMAT_D32_FLOAT, 
				                DXGI_FORMAT_R32_FLOAT);
			break;
		}
		}
	}

	void ShadowMapBuffer::SetupShadowMapArray(ID3D11Device& device,
											  std::size_t nb_shadow_maps,
		                                      DXGI_FORMAT texture_format,
		                                      DXGI_FORMAT dsv_format, 
		                                      DXGI_FORMAT srv_format) {
		// Clear the DSV vector.
		m_dsvs.clear();

		const auto resolution = m_viewport.GetSize();

		// Create the texture descriptor.
		D3D11_TEXTURE2D_DESC texture_desc = {};
		texture_desc.BindFlags        = D3D11_BIND_DEPTH_STENCIL 
			                          | D3D11_BIND_SHADER_RESOURCE;
		texture_desc.Width            = resolution[0];
		texture_desc.Height           = resolution[1];
		texture_desc.MipLevels        = 1u;
		texture_desc.ArraySize        = static_cast< U32 >(nb_shadow_maps);
		texture_desc.Format           = texture_format;
		texture_desc.SampleDesc.Count = 1u;
		// GPU:    read +    write
		// CPU: no read + no write
		texture_desc.Usage            = D3D11_USAGE_DEFAULT;
		
		ComPtr< ID3D11Texture2D > texture;

		// Create the texture.
		{
			const HRESULT result = device.CreateTexture2D(
				&texture_desc, nullptr, texture.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "Texture 2D creation failed: %08X.", result);
		}

		// Create the DSVs.
		{
			// Resize the DSV vector.
			m_dsvs.resize(static_cast< std::size_t >(texture_desc.ArraySize));

			// Create the DSV descriptor.
			D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc = {};
			dsv_desc.Format        = dsv_format;
			dsv_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
			dsv_desc.Texture2DArray.ArraySize = 1u;

			// Create the DSVs for each texture element.
			for (U32 i = 0u; i < texture_desc.ArraySize; ++i) {
				dsv_desc.Texture2DArray.FirstArraySlice = i;

				const HRESULT result = device.CreateDepthStencilView(
					texture.Get(), &dsv_desc, m_dsvs[i].ReleaseAndGetAddressOf());
				ThrowIfFailed(result, "DSV creation failed: %08X.", result);
			}
		}

		// Create the SRV.
		{
			// Create the SRV descriptor.
			D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc = {};
			srv_desc.Format        = srv_format;
			srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
			srv_desc.Texture2DArray.MipLevels = 1u;
			srv_desc.Texture2DArray.ArraySize = texture_desc.ArraySize;

			// Create the SRV for all texture elements.
			const HRESULT result = device.CreateShaderResourceView(
				texture.Get(), &srv_desc, m_srv.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "SRV creation failed: %08X.", result);
		}
	}
	
	#pragma endregion

	//-------------------------------------------------------------------------
	// ShadowCubeMapBuffer
	//-------------------------------------------------------------------------
	#pragma region

	ShadowCubeMapBuffer::ShadowCubeMapBuffer(ID3D11Device& device,
											 std::size_t nb_shadow_cube_maps,
											 const U32x2& resolution, 
		                                     DepthFormat format)
		: m_format(format),
		m_viewport(resolution),
		m_rasterizer_state(), 
		m_dsvs(), 
		m_srv() {

		// Setup the rasterizer state.
		SetupRasterizerState(device);
		// Setup the resource, DSVs and SRV.
		SetupShadowCubeMapBuffer(device, nb_shadow_cube_maps);
	}

	ShadowCubeMapBuffer::ShadowCubeMapBuffer(
		ShadowCubeMapBuffer&& buffer) noexcept = default;

	ShadowCubeMapBuffer::~ShadowCubeMapBuffer() = default;

	ShadowCubeMapBuffer& ShadowCubeMapBuffer
		::operator=(ShadowCubeMapBuffer&& buffer) noexcept = default;

	void ShadowCubeMapBuffer::SetupRasterizerState(ID3D11Device& device) {
		const HRESULT result = CreateCullCounterClockwiseRasterizerState(
			                       device, 
			                       NotNull< ID3D11RasterizerState** >(
									   m_rasterizer_state.ReleaseAndGetAddressOf()),
			                       MAGE_DEFAULT_DEPTH_BIAS,
			                       MAGE_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
			                       MAGE_DEFAULT_DEPTH_BIAS_CLAMP);
		ThrowIfFailed(result, "Rasterizer state creation failed: %08X.", result);
	}

	void ShadowCubeMapBuffer::SetupShadowCubeMapBuffer(ID3D11Device& device,
													   std::size_t nb_shadow_cube_maps) {
		switch (m_format) {
		
		case DepthFormat::D16: {
			SetupShadowCubeMapArray(device, 
				                    nb_shadow_cube_maps,
				                    DXGI_FORMAT_R16_TYPELESS, 
				                    DXGI_FORMAT_D16_UNORM, 
				                    DXGI_FORMAT_R16_UNORM);
			break;
		}
		
		default: {
			SetupShadowCubeMapArray(device, 
				                    nb_shadow_cube_maps,
				                    DXGI_FORMAT_R32_TYPELESS, 
				                    DXGI_FORMAT_D32_FLOAT, 
				                    DXGI_FORMAT_R32_FLOAT);
			break;
		}
		}
	}

	void ShadowCubeMapBuffer::SetupShadowCubeMapArray(ID3D11Device& device,
													  std::size_t nb_shadow_cube_maps,
		                                              DXGI_FORMAT texture_format,
		                                              DXGI_FORMAT dsv_format, 
		                                              DXGI_FORMAT srv_format) {
		// Clear the DSV vector.
		m_dsvs.clear();

		const auto resolution = m_viewport.GetSize();

		// Create the texture descriptor.
		D3D11_TEXTURE2D_DESC texture_desc = {};
		texture_desc.BindFlags        = D3D11_BIND_DEPTH_STENCIL 
			                          | D3D11_BIND_SHADER_RESOURCE;
		texture_desc.MiscFlags        = D3D11_RESOURCE_MISC_TEXTURECUBE;
		texture_desc.Width            = resolution[0];
		texture_desc.Height           = resolution[1];
		texture_desc.MipLevels        = 1u;
		texture_desc.ArraySize        = 6u * static_cast< U32 >(nb_shadow_cube_maps);
		texture_desc.Format           = texture_format;
		texture_desc.SampleDesc.Count = 1u;
		// GPU:    read +    write
		// CPU: no read + no write
		texture_desc.Usage            = D3D11_USAGE_DEFAULT;

		ComPtr< ID3D11Texture2D > texture;
		
		// Create the texture.
		{
			const HRESULT result = device.CreateTexture2D(
				&texture_desc, nullptr, texture.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "Texture 2D creation failed: %08X.", result);
		}

		// Create the DSVs.
		{
			// Resize the DSV vector.
			m_dsvs.resize(static_cast< std::size_t >(texture_desc.ArraySize));

			// Create the DSV descriptor.
			D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc = {};
			dsv_desc.Format        = dsv_format;
			dsv_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
			dsv_desc.Texture2DArray.ArraySize = 1u;

			// Create the DSVs for each texture element.
			for (U32 i = 0u; i < texture_desc.ArraySize; ++i) {
				dsv_desc.Texture2DArray.FirstArraySlice = i;

				const HRESULT result = device.CreateDepthStencilView(
					texture.Get(), &dsv_desc, m_dsvs[i].ReleaseAndGetAddressOf());
				ThrowIfFailed(result, "DSV creation failed: %08X.", result);
			}
		}

		// Create the SRV.
		{
			// Create the SRV descriptor.
			D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc = {};
			srv_desc.Format        = srv_format;
			srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBEARRAY;
			srv_desc.TextureCubeArray.MipLevels = 1u;
			srv_desc.TextureCubeArray.NumCubes  = static_cast< U32 >(nb_shadow_cube_maps);

			// Create the SRV for all texture elements.
			const HRESULT result = device.CreateShaderResourceView(
				texture.Get(), &srv_desc, m_srv.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "SRV creation failed: %08X.", result);
		}
	}

	#pragma endregion
}
