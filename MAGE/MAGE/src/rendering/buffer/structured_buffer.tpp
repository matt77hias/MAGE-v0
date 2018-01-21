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
		::StructuredBuffer(size_t nb_initial_data_elements)
		: StructuredBuffer(Pipeline::GetDevice(), nb_initial_data_elements) {}

	template< typename DataT >
	StructuredBuffer< DataT >
		::StructuredBuffer(ID3D11Device5 *device, 
			               size_t nb_initial_data_elements)
		: m_buffer(), 
		m_buffer_srv(),
		m_nb_data_elements(0), 
		m_nb_used_data_elements(0) {

		SetupStructuredBuffer(device, nb_initial_data_elements);
	}

	template< typename DataT >
	void StructuredBuffer< DataT >
		::SetupStructuredBuffer(ID3D11Device5 *device, 
			                    size_t nb_data_elements) {
		
		Assert(device);

		// Create the buffer resource.
		{
			const HRESULT result = CreateDynamicStructuredBuffer< DataT >(
				device, m_buffer.ReleaseAndGetAddressOf(), nullptr, nb_data_elements);
			ThrowIfFailed(result,
				"Structured buffer creation failed: %08X.", result);
		}

		m_nb_data_elements = nb_data_elements;

		D3D11_SHADER_RESOURCE_VIEW_DESC resource_view_desc = {};
		resource_view_desc.Format              = DXGI_FORMAT_UNKNOWN;
		resource_view_desc.ViewDimension       = D3D11_SRV_DIMENSION_BUFFER;
		resource_view_desc.Buffer.FirstElement = 0;
		resource_view_desc.Buffer.NumElements  = static_cast< U32 >(m_nb_data_elements);

		// Create the SRV.
		{
			const HRESULT result = device->CreateShaderResourceView(
				m_buffer.Get(), &resource_view_desc,
				m_buffer_srv.ReleaseAndGetAddressOf());
			ThrowIfFailed(result,
				"SRV creation failed: %08X.", result);
		}
	}

	template< typename DataT >
	inline void StructuredBuffer< DataT >
		::UpdateData(ID3D11DeviceContext4 *device_context, 
			         const AlignedVector< DataT > &data) {

		UpdateData(Pipeline::GetDevice(), device_context, data);
	}

	template< typename DataT >
	void StructuredBuffer< DataT >
		::UpdateData(ID3D11Device5 *device, 
		             ID3D11DeviceContext4 *device_context, 
			         const AlignedVector< DataT > &data) {
		
		Assert(device_context);
		Assert(m_buffer);

		m_nb_used_data_elements = data.size();
		if (0 == m_nb_used_data_elements) {
			return;
		}
		if (m_nb_data_elements < m_nb_used_data_elements) {
			SetupStructuredBuffer(device, m_nb_used_data_elements);
		}

		// Map the buffer.
		{ 
			D3D11_MAPPED_SUBRESOURCE mapped_buffer;
			BufferLock(device_context, m_buffer.Get(), 
			           D3D11_MAP_WRITE_DISCARD, &mapped_buffer);
			
			memcpy(mapped_buffer.pData, 
				   data.data(),
				   m_nb_used_data_elements * sizeof(DataT));
		}
	}

	template< typename DataT >
	template< typename PipelineStageT >
	inline void StructuredBuffer< DataT >
		::Bind(ID3D11DeviceContext4 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSRV(device_context, slot, Get());
	}
}