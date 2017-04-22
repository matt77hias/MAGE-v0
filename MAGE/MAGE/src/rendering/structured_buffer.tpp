#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_factory.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename DataT >
	StructuredBuffer< DataT >::StructuredBuffer(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		size_t nb_initial_data_elements)
		: m_device(device), m_device_context(device_context), 
		m_buffer(), m_nb_data_elements(0), m_shader_resource_view() {

		const HRESULT result_buffer = SetupStructuredBuffer(nb_initial_data_elements);
		if (FAILED(result_buffer)) {
			Error("Structured buffer setup failed: %08X.", result_buffer);
		}
	}

	template< typename DataT >
	HRESULT StructuredBuffer< DataT >::SetupStructuredBuffer(size_t nb_data_elements) const {
		const HRESULT result_buffer = CreateStructuredBuffer< DataT >(m_device, m_buffer.ReleaseAndGetAddressOf(), nb_data_elements);
		if (FAILED(result_buffer)) {
			Error("Structured buffer creation failed: %08X.", result_buffer);
			return result_buffer;
		}

		m_nb_data_elements = nb_data_elements;

		D3D11_SHADER_RESOURCE_VIEW_DESC resource_view_desc;
		ZeroMemory(&resource_view_desc, sizeof(resource_view_desc));
		resource_view_desc.Format              = DXGI_FORMAT_UNKNOWN;
		resource_view_desc.ViewDimension       = D3D11_SRV_DIMENSION_BUFFER;
		resource_view_desc.Buffer.FirstElement = 0;
		resource_view_desc.Buffer.NumElements  = static_cast< UINT >(m_nb_data_elements);

		const HRESULT result_shader_resource_view = m_device->CreateShaderResourceView(m_buffer.Get(), &resource_view_desc, m_shader_resource_view.ReleaseAndGetAddressOf());
		if (FAILED(result_shader_resource_view)) {
			Error("Shader resource view creation failed: %08X.", result_shader_resource_view);
			return result_shader_resource_view;
		}

		return S_OK;
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
		m_device_context->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_buffer);

		memcpy(mapped_buffer.pData, data.data(), nb_requested_data_elements * sizeof(DataT));

		m_device_context->Unmap(m_buffer.Get(), 0);
	}
}