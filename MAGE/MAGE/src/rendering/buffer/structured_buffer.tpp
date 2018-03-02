#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_factory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename DataT >
	StructuredBuffer< DataT >
		::StructuredBuffer(ID3D11Device& device, size_t capacity)
		: m_buffer(), 
		m_buffer_srv(),
		m_capacity(0), 
		m_size(0) {

		SetupStructuredBuffer(device, capacity);
	}

	template< typename DataT >
	void StructuredBuffer< DataT >
		::SetupStructuredBuffer(ID3D11Device& device, size_t capacity) {

		// Create the buffer resource.
		{
			const HRESULT result = CreateDynamicStructuredBuffer< DataT >(
				device, m_buffer.ReleaseAndGetAddressOf(), nullptr, capacity);
			ThrowIfFailed(result, "Structured buffer creation failed: %08X.", result);
		}

		m_capacity = capacity;

		// Create the SRV.
		{
			// Create the SRV descriptor.
			D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc = {};
			srv_desc.Format              = DXGI_FORMAT_UNKNOWN;
			srv_desc.ViewDimension       = D3D11_SRV_DIMENSION_BUFFER;
			srv_desc.Buffer.FirstElement = 0u;
			srv_desc.Buffer.NumElements  = static_cast< U32 >(m_capacity);
			
			const HRESULT result = device.CreateShaderResourceView(
				m_buffer.Get(), &srv_desc, m_buffer_srv.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "SRV creation failed: %08X.", result);
		}
	}

	template< typename DataT >
	void StructuredBuffer< DataT >
		::UpdateData(ID3D11DeviceContext& device_context, 
			         const AlignedVector< DataT >& data) {

		m_size = data.size();

		if (0u == m_size) {
			return;
		}
		if (m_capacity < m_size) {
			ComPtr< ID3D11Device > device;
			device_context->GetDevice(device.ReleaseAndGetAddressOf());
			SetupStructuredBuffer(*device.Get(), m_size);
		}

		Assert(m_buffer);

		// Map the buffer.
		D3D11_MAPPED_SUBRESOURCE mapped_buffer;
		BufferLock lock(device_context, *m_buffer.Get(), 
						D3D11_MAP_WRITE_DISCARD, mapped_buffer);
			
		memcpy(mapped_buffer.pData, data.data(), m_size * sizeof(DataT));
	}

	template< typename DataT >
	template< typename PipelineStageT >
	inline void StructuredBuffer< DataT >
		::Bind(ID3D11DeviceContext& device_context, U32 slot) const noexcept {

		PipelineStageT::BindSRV(device_context, slot, Get());
	}
}