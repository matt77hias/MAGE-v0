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
	StructuredBuffer< DataT >::StructuredBuffer(
		size_t nb_initial_data_elements)
		: StructuredBuffer(Pipeline::GetDevice(), nb_initial_data_elements) {}

	template< typename DataT >
	StructuredBuffer< DataT >::StructuredBuffer(ID3D11Device2 *device,
		size_t nb_initial_data_elements)
		: m_buffer(), m_buffer_srv(),
		m_nb_data_elements(0), m_nb_used_data_elements(0) {

		SetupStructuredBuffer(device, nb_initial_data_elements);
	}

	template< typename DataT >
	void StructuredBuffer< DataT >::SetupStructuredBuffer(
		ID3D11Device2 *device, size_t nb_data_elements) {
		
		Assert(device);

		const HRESULT result_buffer = CreateDynamicStructuredBuffer< DataT >(
			device, m_buffer.ReleaseAndGetAddressOf(), nullptr, nb_data_elements);
		ThrowIfFailed(result_buffer, 
			"Structured buffer creation failed: %08X.", result_buffer);

		m_nb_data_elements = nb_data_elements;

		D3D11_SHADER_RESOURCE_VIEW_DESC resource_view_desc = {};
		resource_view_desc.Format              = DXGI_FORMAT_UNKNOWN;
		resource_view_desc.ViewDimension       = D3D11_SRV_DIMENSION_BUFFER;
		resource_view_desc.Buffer.FirstElement = 0;
		resource_view_desc.Buffer.NumElements  = static_cast< U32 >(m_nb_data_elements);

		const HRESULT result_buffer_srv = device->CreateShaderResourceView(
			m_buffer.Get(), &resource_view_desc, 
			m_buffer_srv.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_buffer_srv, 
			"SRV creation failed: %08X.", result_buffer_srv);
	}

	template< typename DataT >
	inline void StructuredBuffer< DataT >::UpdateData(
		ID3D11DeviceContext2 *device_context, const vector< DataT > &data) {

		UpdateData(Pipeline::GetDevice(), device_context, data);
	}

	template< typename DataT >
	void StructuredBuffer< DataT >::UpdateData(ID3D11Device2 *device, 
		ID3D11DeviceContext2 *device_context, const vector< DataT > &data) {
		
		Assert(device_context);
		Assert(m_buffer);

		m_nb_used_data_elements = data.size();
		if (m_nb_used_data_elements == 0) {
			return;
		}
		if (m_nb_data_elements < m_nb_used_data_elements) {
			SetupStructuredBuffer(device, m_nb_used_data_elements);
		}

		D3D11_MAPPED_SUBRESOURCE mapped_buffer;
		const HRESULT result = Pipeline::Map(device_context,
			m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_buffer);
		Assert(SUCCEEDED(result));

		memcpy(mapped_buffer.pData, data.data(), 
			m_nb_used_data_elements * sizeof(DataT));

		device_context->Unmap(m_buffer.Get(), 0);
	}

	template< typename DataT >
	template< typename PipelineStageT >
	inline void StructuredBuffer< DataT >::Bind(
		ID3D11DeviceContext2 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSRV(device_context, slot, Get());
	}
}