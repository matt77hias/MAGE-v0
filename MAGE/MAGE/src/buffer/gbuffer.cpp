//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "buffer\gbuffer.hpp"
#include "rendering\renderer.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	GBuffer::GBuffer()
		: GBuffer(GetDevice()) {}

	GBuffer::GBuffer(ID3D11Device2 *device)
		: m_rtvs{}, m_srvs{} {

		SetupBuffers(device);
	}

	void GBuffer::BindPacking(ID3D11DeviceContext2 *device_context) noexcept {
		static const FLOAT color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

		// Collect and clear the RTVs.
		ID3D11RenderTargetView *rtvs[GetNumberOfRTVs()];
		for (UINT i = 0; i < GetNumberOfRTVs(); ++i) {
			rtvs[i] = m_rtvs[i].Get();
			OM::ClearRTV(device_context, rtvs[i], color);
		}
		
		// Collect the (cleared) DSV of the renderer.
		const Renderer * const renderer = Renderer::Get();
		ID3D11DepthStencilView * const dsv = renderer->GetDepthBufferDSV();

		// Bind the RTVs and DSV.
		OM::BindRTVsAndDSV(device_context, GetNumberOfRTVs(), rtvs, dsv);
	}

	void GBuffer::BindUnpacking(ID3D11DeviceContext2 *device_context, UINT slot) noexcept {
		
		// Reuse the (cleared) RTV of the renderer.
		const Renderer * const renderer = Renderer::Get();
		ID3D11RenderTargetView *rtv = renderer->GetBackBufferRTV();

		// Bind the RTV and no DSV.
		OM::BindRTVAndDSV(device_context, rtv, nullptr);

		// Collect the SRVs (incl. depth SRV of the renderer).
		ID3D11ShaderResourceView *srvs[GetNumberOfSRVs() + 1];
		for (UINT i = 0; i < GetNumberOfSRVs(); ++i) {
			srvs[i] = m_srvs[i].Get();
		}
		srvs[GetNumberOfSRVs()] = renderer->GetDepthBufferSRV();
	
		// Bind the SRVs.
		PS::BindSRVs(device_context, slot, GetNumberOfSRVs(), srvs);
	}

	void GBuffer::BindRestore(ID3D11DeviceContext2 *device_context, UINT slot) noexcept {
		// Collect the SRVs (incl. depth SRV of the renderer).
		ID3D11ShaderResourceView *srvs[GetNumberOfSRVs() + 1];
		for (UINT i = 0; i < GetNumberOfSRVs() + 1; ++i) {
			srvs[i] = nullptr;
		}

		// Bind the SRVs.
		PS::BindSRVs(device_context, slot, GetNumberOfSRVs(), srvs);

		// Restore the RTV and DSV of the renderer.
		const Renderer * const renderer = Renderer::Get();
		renderer->BindRTVAndDSV();
	}

	void GBuffer::SetupBuffers(ID3D11Device2 *device) {
		Assert(device);
		
		const Renderer * const renderer = Renderer::Get();
		Assert(renderer);
		const UINT width  = static_cast< UINT >(renderer->GetWidth());
		const UINT height = static_cast< UINT >(renderer->GetHeight());

		// Setup the normal buffer.
		SetupBuffer(device, static_cast< size_t >(GBufferIndex::Normal), 
			width, height, DXGI_FORMAT_R11G11B10_FLOAT);
		
		// Setup the diffuse buffer;
		SetupBuffer(device, static_cast< size_t >(GBufferIndex::Diffuse),
			width, height, DXGI_FORMAT_R8G8B8A8_UNORM);

		// Setup the specular buffer.
		SetupBuffer(device, static_cast< size_t >(GBufferIndex::Specular),
			width, height, DXGI_FORMAT_R8G8B8A8_UNORM);
	}

	void GBuffer::SetupBuffer(ID3D11Device2 *device, UINT index,
		UINT width, UINT height, DXGI_FORMAT format) {

		// Create the texture descriptor.
		D3D11_TEXTURE2D_DESC texture_desc = {};
		texture_desc.Width            = width;
		texture_desc.Height           = height;
		texture_desc.MipLevels        = 1u;
		texture_desc.ArraySize        = 1u;
		texture_desc.Format           = format;
		texture_desc.SampleDesc.Count = 1u;
		texture_desc.Usage            = D3D11_USAGE_DEFAULT;
		texture_desc.BindFlags        = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

		// Create the texture.
		ComPtr< ID3D11Texture2D > texture;
		const HRESULT result_texture = device->CreateTexture2D(
			&texture_desc, nullptr, 
			texture.ReleaseAndGetAddressOf());
		if (FAILED(result_texture)) {
			throw FormattedException("Texture 2D creation failed: %08X.", result_texture);
		}

		// Create the RTV descriptor.
		D3D11_RENDER_TARGET_VIEW_DESC rtv_desc = {};
		rtv_desc.Format               = format;
		rtv_desc.ViewDimension        = D3D11_RTV_DIMENSION_TEXTURE2D;

		// Create the RTV.
		const HRESULT result_rtv = device->CreateRenderTargetView(
			texture.Get(), &rtv_desc,
			m_rtvs[index].ReleaseAndGetAddressOf());
		if (FAILED(result_rtv)) {
			throw FormattedException("RTV creation failed: %08X.", result_rtv);
		}

		// Create the SRV descriptor.
		D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc = {};
		srv_desc.Format               = format;
		srv_desc.ViewDimension        = D3D11_SRV_DIMENSION_TEXTURE2D;
		srv_desc.Texture2D.MipLevels  = 1u;
		
		// Create the SRV.
		const HRESULT result_srv = device->CreateShaderResourceView(
			texture.Get(), &srv_desc,
			m_srvs[index].ReleaseAndGetAddressOf());
		if (FAILED(result_srv)) {
			throw FormattedException("SRV creation failed: %08X.", result_srv);
		}
	}
}