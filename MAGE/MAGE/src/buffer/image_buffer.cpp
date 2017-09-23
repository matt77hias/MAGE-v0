//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "buffer\image_buffer.hpp"
#include "rendering\renderer.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

// Include HLSL bindings.
#include "..\..\shaders\hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	ImageBuffer::ImageBuffer()
		: ImageBuffer(GetDevice()) {}
	
	ImageBuffer::ImageBuffer(ID3D11Device2 *device)
		: m_uav(), m_srv() {

		const Renderer * const renderer = Renderer::Get();
		Assert(renderer);
		const UINT width  = static_cast< UINT >(renderer->GetWidth());
		const UINT height = static_cast< UINT >(renderer->GetHeight());

		SetupBuffer(device, width, height);
	}

	void ImageBuffer::BindPacking(ID3D11DeviceContext2 *device_context) noexcept {
		// Bind no SRV.
		Pipeline::PS::BindSRV(device_context,
			SLOT_SRV_IMAGE, nullptr);
		
		// Bind the UAV.
		Pipeline::CS::BindUAV(device_context,
			SLOT_UAV_IMAGE, m_uav.Get());
	}

	void ImageBuffer::BindUnpacking(ID3D11DeviceContext2 *device_context) noexcept {
		// Bind no UAV.
		Pipeline::CS::BindUAV(device_context,
			SLOT_UAV_IMAGE, nullptr);
		
		// Bind the SRV.
		Pipeline::PS::BindSRV(device_context,
			SLOT_SRV_IMAGE, m_srv.Get());
	}

	void ImageBuffer::SetupBuffer(ID3D11Device2 *device, 
		UINT width, UINT height) {

		Assert(device);

		// Create the texture descriptor.
		D3D11_TEXTURE2D_DESC texture_desc = {};
		texture_desc.Width            = width;
		texture_desc.Height           = height;
		texture_desc.MipLevels        = 1u;
		texture_desc.ArraySize        = 1u;
		texture_desc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
		texture_desc.SampleDesc.Count = 1u;
		texture_desc.Usage            = D3D11_USAGE_DEFAULT;
		texture_desc.BindFlags        = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;

		// Create the texture.
		ComPtr< ID3D11Texture2D > texture;
		const HRESULT result_texture = device->CreateTexture2D(
			&texture_desc, nullptr, 
			texture.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_texture, "Texture 2D creation failed: %08X.", result_texture);

		// Create the UAV.
		const HRESULT result_uav = device->CreateUnorderedAccessView(
			texture.Get(), nullptr,
			m_uav.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_uav, "UAV creation failed: %08X.", result_uav);

		// Create the SRV.
		const HRESULT result_srv = device->CreateShaderResourceView(
			texture.Get(), nullptr,
			m_srv.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_srv, "SRV creation failed: %08X.", result_srv);
	}
}