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
		: m_device(device), m_device_context(device_context), m_buffer(), m_nb_data_elements(0) {

		const HRESULT result_buffer = SetupStructuredBuffer(nb_initial_data_elements);
		if (FAILED(result_buffer)) {
			Error("Structured buffer setup failed: %08X.", result_buffer);
		}
	}

	template< typename DataT >
	HRESULT StructuredBuffer< DataT >::SetupStructuredBuffer(size_t nb_data_elements) const {
		const HRESULT result_buffer = CreateConstantBuffer< DataT >(m_device, m_buffer.ReleaseAndGetAddressOf(), nb_data_elements);
		if (FAILED(result_buffer)) {
			Error("Structured buffer creation failed: %08X.", result_buffer);
			return result_buffer;
		}

		m_nb_data_elements = nb_data_elements;
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

		memcpy(mapped_buffer.pData, &data[0], nb_requested_data_elements * sizeof(DataT));

		m_device_context->Unmap(m_buffer.Get(), 0);
	}
}