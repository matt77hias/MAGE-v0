#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\factory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	template< typename T >
	ConstantBuffer< T >::ConstantBuffer(ID3D11Device& device)
		: m_buffer() {

		SetupConstantBuffer(device);
	}

	template< typename T >
	void ConstantBuffer< T >::SetupConstantBuffer(ID3D11Device& device) {
		const HRESULT result = CreateDynamicConstantBuffer< T >(
			device, NotNull< ID3D11Buffer** >(m_buffer.ReleaseAndGetAddressOf()));
		ThrowIfFailed(result, "Constant buffer creation failed: {:08X}.", result);
	}

	template< typename T >
	void ConstantBuffer< T >
		::UpdateData(ID3D11DeviceContext& device_context, const T& data) {

		// Map the buffer.
		D3D11_MAPPED_SUBRESOURCE mapped_buffer;
		BufferLock lock(device_context, *m_buffer.Get(),
						D3D11_MAP_WRITE_DISCARD, mapped_buffer);

		memcpy(mapped_buffer.pData, &data, sizeof(T));
	}

	template< typename T >
	template< typename PipelineStageT >
	inline void ConstantBuffer< T >
		::Bind(ID3D11DeviceContext& device_context, U32 slot) const noexcept {

		PipelineStageT::BindConstantBuffer(device_context, slot, m_buffer.Get());
	}
}