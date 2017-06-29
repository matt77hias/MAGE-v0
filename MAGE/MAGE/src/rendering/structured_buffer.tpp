#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_factory.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename DataT >
	StructuredBuffer< DataT >::StructuredBuffer()
		: StructuredBuffer(GetRenderingDevice(), GetRenderingDeviceContext()) {}

	template< typename DataT >
	StructuredBuffer< DataT >::StructuredBuffer(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		size_t nb_initial_data_elements)
		: m_device(device), m_device_context(device_context), 
		m_buffer(), m_nb_data_elements(0), m_buffer_srv() {

		Assert(m_device);
		Assert(m_device_context);

		SetupStructuredBuffer(nb_initial_data_elements);
	}

	template< typename DataT >
	void StructuredBuffer< DataT >::SetupStructuredBuffer(size_t nb_data_elements) const {
		
		const HRESULT result_buffer = CreateStructuredBuffer< DataT >(m_device, m_buffer.ReleaseAndGetAddressOf(), nb_data_elements);
		if (FAILED(result_buffer)) {
			throw FormattedException("Structured buffer creation failed: %08X.", result_buffer);
		}

		m_nb_data_elements = nb_data_elements;

		D3D11_SHADER_RESOURCE_VIEW_DESC resource_view_desc = {};
		resource_view_desc.Format              = DXGI_FORMAT_UNKNOWN;
		resource_view_desc.ViewDimension       = D3D11_SRV_DIMENSION_BUFFER;
		resource_view_desc.Buffer.FirstElement = 0;
		resource_view_desc.Buffer.NumElements  = static_cast< UINT >(m_nb_data_elements);

		const HRESULT result_buffer_srv = m_device->CreateShaderResourceView(m_buffer.Get(), &resource_view_desc, m_buffer_srv.ReleaseAndGetAddressOf());
		if (FAILED(result_buffer_srv)) {
			throw FormattedException("Shader resource view creation failed: %08X.", result_buffer_srv);
		}
	}

	template< typename DataT >
	void StructuredBuffer< DataT >::UpdateData(const vector< DataT > &data) const {
		Assert(m_buffer);

		const size_t nb_requested_data_elements = data.size();
		if (nb_requested_data_elements == 0) {
			return;
		}
		if (m_nb_data_elements < nb_requested_data_elements) {
			SetupStructuredBuffer(nb_requested_data_elements);
		}

		D3D11_MAPPED_SUBRESOURCE mapped_buffer;
		const HRESULT result = m_device_context->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_buffer);
		Assert(SUCCEEDED(result));

		memcpy(mapped_buffer.pData, data.data(), nb_requested_data_elements * sizeof(DataT));

		m_device_context->Unmap(m_buffer.Get(), 0);
	}
}