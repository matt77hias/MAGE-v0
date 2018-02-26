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
	ConstantBuffer< DataT >::ConstantBuffer(ID3D11Device *device)
		: m_buffer() {

		SetupConstantBuffer(device);
	}

	template< typename DataT >
	void ConstantBuffer< DataT >::SetupConstantBuffer(ID3D11Device *device) {
		Assert(device);

		const HRESULT result = CreateDynamicConstantBuffer< DataT >(
			device, m_buffer.ReleaseAndGetAddressOf(), nullptr);
		ThrowIfFailed(result, "Constant buffer creation failed: %08X.", result);
	}

	template< typename DataT >
	void ConstantBuffer< DataT >
		::UpdateData(ID3D11DeviceContext *device_context, const DataT &data) {

		Assert(device_context);
		Assert(m_buffer);

		// Map the buffer.
		D3D11_MAPPED_SUBRESOURCE mapped_buffer;
		BufferLock lock(device_context, m_buffer.Get(), 
						D3D11_MAP_WRITE_DISCARD, &mapped_buffer);

		memcpy(mapped_buffer.pData, &data, sizeof(DataT));
	}

	template< typename DataT >
	template< typename PipelineStageT >
	inline void ConstantBuffer< DataT >
		::Bind(ID3D11DeviceContext *device_context, U32 slot) const noexcept {

		PipelineStageT::BindConstantBuffer(device_context, slot, Get());
	}
}