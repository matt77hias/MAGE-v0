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
	ConstantBuffer< DataT >::ConstantBuffer()
		: ConstantBuffer(GetRenderingDevice(), GetRenderingDeviceContext()) {}

	template< typename DataT >
	ConstantBuffer< DataT >::ConstantBuffer(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context)
		: m_device(device), m_device_context(device_context), m_buffer() {

		Assert(m_device);
		Assert(m_device_context);

		SetupConstantBuffer();
	}

	template< typename DataT >
	void ConstantBuffer< DataT >::SetupConstantBuffer() {
		const HRESULT result_buffer = CreateConstantBuffer< DataT >(m_device, m_buffer.ReleaseAndGetAddressOf());
		if (FAILED(result_buffer)) {
			throw FormattedException("Constant buffer creation failed: %08X.", result_buffer);
		}
	}

	template< typename DataT >
	void ConstantBuffer< DataT >::UpdateData(const DataT &data) const {
		Assert(m_buffer);

		D3D11_MAPPED_SUBRESOURCE mapped_buffer;
		const HRESULT result = m_device_context->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_buffer);
		Assert(SUCCEEDED(result));

		memcpy(mapped_buffer.pData, &data, sizeof(DataT));

		m_device_context->Unmap(m_buffer.Get(), 0);
	}
}