#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "rendering\rendering.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class RenderingDevice final {

	public:

		RenderingDevice(ComPtr< ID3D11Device2 > device) :
			m_device(device) {}
		RenderingDevice(const RenderingDevice &device) = default;
		~RenderingDevice() = default;

		RenderingDevice &operator=(const RenderingDevice &device) = default;

		template < typename VertexT >
		HRESULT CreateVertexBuffer(ID3D11Buffer **buffer, const VertexT *vertices, size_t nb_vertices) const;
		template < typename IndexT >
		HRESULT CreateIndexBuffer(ID3D11Buffer **buffer, const IndexT *indices, size_t nb_indices) const;
		template < typename BufferT >
		HRESULT CreateConstantBuffer(ID3D11Buffer **buffer) const;

		HRESULT RenderingDevice::CreateVertexShader(ID3D11VertexShader **shader, ComPtr< ID3DBlob > shader_blob) const;
		HRESULT RenderingDevice::CreatePixelShader(ID3D11PixelShader **shader, ComPtr< ID3DBlob > shader_blob) const;
		HRESULT RenderingDevice::CreateVertexInputLayout(ID3D11InputLayout **input_layout, ComPtr< ID3DBlob > shader_blob,
			const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements) const;

	private:

		ComPtr< ID3D11Device2 > m_device;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_device.tpp"

#pragma endregion