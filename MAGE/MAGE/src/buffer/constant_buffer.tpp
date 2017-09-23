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
		: ConstantBuffer(Pipeline::GetDevice()) {}

	template< typename DataT >
	ConstantBuffer< DataT >::ConstantBuffer(ID3D11Device2 *device)
		: m_buffer() {

		SetupConstantBuffer(device);
	}

	template< typename DataT >
	void ConstantBuffer< DataT >::SetupConstantBuffer(ID3D11Device2 *device) {
		Assert(device);

		const HRESULT result_buffer = CreateDynamicConstantBuffer< DataT >(
			device, m_buffer.ReleaseAndGetAddressOf(), nullptr);
		ThrowIfFailed(result_buffer, "Constant buffer creation failed: %08X.", result_buffer);
	}

	template< typename DataT >
	void ConstantBuffer< DataT >::UpdateData(
		ID3D11DeviceContext2 *device_context, const DataT &data) {

		Assert(device_context);
		Assert(m_buffer);

		D3D11_MAPPED_SUBRESOURCE mapped_buffer;
		const HRESULT result = Pipeline::Map(device_context,
			m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_buffer);
		Assert(SUCCEEDED(result));

		memcpy(mapped_buffer.pData, &data, sizeof(DataT));

		device_context->Unmap(m_buffer.Get(), 0);
	}

	template< typename DataT >
	template< typename PipelineStageT >
	inline void ConstantBuffer< DataT >::Bind(
		ID3D11DeviceContext2 *device_context, UINT slot) const noexcept {

		PipelineStageT::BindConstantBuffer(device_context, slot, Get());
	}
}