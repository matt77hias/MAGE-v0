//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_manager.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

// Include HLSL bindings.
#include "..\..\shaders\hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const RenderingOutputManager *RenderingOutputManager::Get() noexcept {
		Assert(RenderingManager::Get());

		return RenderingManager::Get()->GetRenderingOutputManager();
	}

	RenderingOutputManager::RenderingOutputManager(
		ID3D11Device2 *device, U32 width, U32 height)
		: m_srvs{}, m_rtvs{}, m_uavs{}, m_dsv() {

		SetupBuffers(device, width, height);
	}

	RenderingOutputManager::RenderingOutputManager(
		RenderingOutputManager &&rendering_output_manager) = default;

	RenderingOutputManager::~RenderingOutputManager() = default;

	void RenderingOutputManager::SetupBuffers(
		ID3D11Device2 *device, U32 width, U32 height) {
		
		Assert(device);

		// Setup the GBuffer buffers.
		SetupBuffer(device, width, height, 
			DXGI_FORMAT_R8G8B8A8_UNORM,
			ReleaseAndGetAddressOfSRV(SRVIndex::GBuffer_BaseColor),
			ReleaseAndGetAddressOfRTV(RTVIndex::GBuffer_BaseColor),
			nullptr);
		SetupBuffer(device, width, height, 
			DXGI_FORMAT_R8G8B8A8_UNORM,
			ReleaseAndGetAddressOfSRV(SRVIndex::GBuffer_Material),
			ReleaseAndGetAddressOfRTV(RTVIndex::GBuffer_Material),
			nullptr);
		SetupBuffer(device, width, height, 
			DXGI_FORMAT_R11G11B10_FLOAT,
			ReleaseAndGetAddressOfSRV(SRVIndex::GBuffer_Normal),
			ReleaseAndGetAddressOfRTV(RTVIndex::GBuffer_Normal),
			nullptr);

		// Setup the HDR buffers.
		SetupBuffer(device, width, height, 
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			ReleaseAndGetAddressOfSRV(SRVIndex::HDR0),
			ReleaseAndGetAddressOfRTV(RTVIndex::HDR0),
			ReleaseAndGetAddressOfUAV(UAVIndex::HDR0));
		SetupBuffer(device, width, height, 
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			ReleaseAndGetAddressOfSRV(SRVIndex::HDR1),
			ReleaseAndGetAddressOfRTV(RTVIndex::HDR1),
			ReleaseAndGetAddressOfUAV(UAVIndex::HDR1));

		// Setup the depth buffer.
		SetupDepthBuffer(device, width, height);
	}

	void RenderingOutputManager::SetupBuffer(
		ID3D11Device2 *device, U32 width, U32 height,
		DXGI_FORMAT format, ID3D11ShaderResourceView **srv,
		ID3D11RenderTargetView **rtv, ID3D11UnorderedAccessView **uav) {

		// Create the texture descriptor.
		D3D11_TEXTURE2D_DESC texture_desc = {};
		texture_desc.Width            = width;
		texture_desc.Height           = height;
		texture_desc.MipLevels        = 1u;
		texture_desc.ArraySize        = 1u;
		texture_desc.Format           = format;
		texture_desc.SampleDesc.Count = 1u;
		texture_desc.Usage            = D3D11_USAGE_DEFAULT;
		texture_desc.BindFlags        = D3D11_BIND_SHADER_RESOURCE;
		if (rtv) {
			texture_desc.BindFlags   |= D3D11_BIND_RENDER_TARGET;
		}
		if (uav) {
			texture_desc.BindFlags   |= D3D11_BIND_UNORDERED_ACCESS;
		}
		
		// Create the texture.
		ComPtr< ID3D11Texture2D > texture;
		const HRESULT result_texture = device->CreateTexture2D(
			&texture_desc, nullptr, texture.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_texture, 
			"Texture 2D creation failed: %08X.", result_texture);

		// Create the SRV.
		const HRESULT result_srv = device->CreateShaderResourceView(
			texture.Get(), nullptr, srv);
		ThrowIfFailed(result_srv,
			"SRV creation failed: %08X.", result_srv);

		if (rtv) {
			// Create the RTV.
			const HRESULT result_rtv = device->CreateRenderTargetView(
				texture.Get(), nullptr, rtv);
			ThrowIfFailed(result_rtv,
				"RTV creation failed: %08X.", result_rtv);
		}

		if (uav) {
			// Create the UAV.
			const HRESULT result_uav = device->CreateUnorderedAccessView(
				texture.Get(), nullptr, uav);
			ThrowIfFailed(result_uav,
				"UAV creation failed: %08X.", result_uav);
		}
	}

	void RenderingOutputManager::SetupDepthBuffer(
		ID3D11Device2 *device, U32 width, U32 height) {

		// Create the texture descriptor.
		D3D11_TEXTURE2D_DESC texture_desc = {};
		texture_desc.Width            = width;
		texture_desc.Height           = height;
		texture_desc.MipLevels        = 1u;
		texture_desc.ArraySize        = 1u;
		texture_desc.Format           = DXGI_FORMAT_R24G8_TYPELESS;
		texture_desc.SampleDesc.Count = 1u;
		texture_desc.Usage            = D3D11_USAGE_DEFAULT;
		texture_desc.BindFlags        = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_DEPTH_STENCIL;

		// Create the texture.
		ComPtr< ID3D11Texture2D > texture;
		const HRESULT result_texture = device->CreateTexture2D(
			&texture_desc, nullptr, 
			texture.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_texture, 
			"Texture 2D creation failed: %08X.", result_texture);

		// Create the SRV descriptor.
		D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc = {};
		srv_desc.Format               = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		srv_desc.ViewDimension        = D3D11_SRV_DIMENSION_TEXTURE2D;
		srv_desc.Texture2D.MipLevels  = 1u;
		
		// Create the SRV.
		const HRESULT result_srv = device->CreateShaderResourceView(
			texture.Get(), &srv_desc,
			m_srvs[static_cast< size_t >(SRVIndex::GBuffer_Depth)].ReleaseAndGetAddressOf());
		ThrowIfFailed(result_srv, 
			"SRV creation failed: %08X.", result_srv);

		// Create the DSV descriptor.
		D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc = {};
		dsv_desc.Format               = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsv_desc.ViewDimension        = D3D11_DSV_DIMENSION_TEXTURE2D;

		// Create the DSV.
		const HRESULT result_dsv = device->CreateDepthStencilView(
			texture.Get(), &dsv_desc,
			m_dsv.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_dsv, 
			"DSV creation failed: %08X.", result_dsv);
	}

	void RenderingOutputManager::BindBegin(
		ID3D11DeviceContext2 *device_context) const noexcept {

		// Collect the GBuffer SRVs.
		ID3D11ShaderResourceView * const srvs[SLOT_SRV_GBUFFER_COUNT - 1u] = {};
		// Bind no GBuffer SRVs.
		Pipeline::CS::BindSRVs(device_context,
			SLOT_SRV_GBUFFER_START, _countof(srvs), srvs);

		// Clear the GBuffer RTVs.
		Pipeline::OM::ClearRTV(device_context, 
			GetRTV(RTVIndex::GBuffer_BaseColor));
		Pipeline::OM::ClearRTV(device_context, 
			GetRTV(RTVIndex::GBuffer_Material));
		Pipeline::OM::ClearRTV(device_context, 
			GetRTV(RTVIndex::GBuffer_Normal));

		// Clear the DSV.
		Pipeline::OM::ClearDSV(device_context, m_dsv.Get());

		// Bind no HDR SRV.
		Pipeline::PS::BindSRV(device_context, 
			SLOT_SRV_IMAGE, nullptr);

		// Clear the HDR RTV.
		Pipeline::OM::ClearRTV(device_context,
			GetRTV(RTVIndex::HDR0));
	}

	void RenderingOutputManager::BindGBuffer(
		ID3D11DeviceContext2 *device_context) const noexcept {

		// Collect the GBuffer RTVs.
		ID3D11RenderTargetView * const rtvs[SLOT_SRV_GBUFFER_COUNT - 1u] = {
			GetRTV(RTVIndex::GBuffer_BaseColor),
			GetRTV(RTVIndex::GBuffer_Material),
			GetRTV(RTVIndex::GBuffer_Normal)
		};
		// Bind the GBuffer RTVs and DSV.
		Pipeline::OM::BindRTVsAndDSV(device_context, 
			_countof(rtvs), rtvs, m_dsv.Get());
	}
	
	void RenderingOutputManager::BindDeferred(
		ID3D11DeviceContext2 *device_context) const noexcept {
		
		// Bind no RTV and no DSV.
		Pipeline::OM::BindRTVAndDSV(device_context,
			nullptr, nullptr);

		// Collect the GBuffer SRVs. 
		ID3D11ShaderResourceView * const srvs[SLOT_SRV_GBUFFER_COUNT] = {
			GetSRV(SRVIndex::GBuffer_BaseColor),
			GetSRV(SRVIndex::GBuffer_Material),
			GetSRV(SRVIndex::GBuffer_Normal),
			GetSRV(SRVIndex::GBuffer_Depth)
		};
		// Bind the GBuffer SRVs.
		Pipeline::CS::BindSRVs(device_context,
			SLOT_SRV_GBUFFER_START, _countof(srvs), srvs);

		// Bind the HDR UAV.
		Pipeline::CS::BindUAV(device_context,
			SLOT_UAV_IMAGE, GetUAV(UAVIndex::HDR0));
	}

	void RenderingOutputManager::BindForward(
		ID3D11DeviceContext2 *device_context) const noexcept {

		// Bind no Depth SRV.
		Pipeline::CS::BindSRV(device_context,
			SLOT_SRV_DEPTH, nullptr);

		// Bind no HDR UAV.
		Pipeline::CS::BindUAV(device_context,
			SLOT_UAV_IMAGE, nullptr);
		
		// Bind the HDR RTV and DSV.
		Pipeline::OM::BindRTVAndDSV(device_context,
			GetRTV(RTVIndex::HDR0), m_dsv.Get());
	}
	
	void RenderingOutputManager::BindEnd(
		ID3D11DeviceContext2 *device_context) const noexcept {

		// Bind the HDR RTV and DSV.
		Pipeline::OM::BindRTVAndDSV(device_context,
			RenderingManager::Get()->GetBackBufferRTV(), nullptr);

		// Bind HDR SRV.
		Pipeline::PS::BindSRV(device_context,
			SLOT_SRV_IMAGE, GetSRV(SRVIndex::HDR0));
	}
}