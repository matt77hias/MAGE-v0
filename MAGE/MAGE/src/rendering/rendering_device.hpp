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

		RenderingDevice() = default;
		RenderingDevice(ComPtr< ID3D11Device2 > device) :
			m_device(device) {}
		RenderingDevice(const RenderingDevice &device) = default;
		~RenderingDevice() = default;

		RenderingDevice &operator=(const RenderingDevice &device) = default;

		D3D_FEATURE_LEVEL GetFeatureLevel() const {
			return m_device->GetFeatureLevel();
		}
		HRESULT CheckFormatSupport(DXGI_FORMAT format, UINT *format_support) const {
			return m_device->CheckFormatSupport(format, format_support);
		}

		HRESULT CreateBuffer(const D3D11_BUFFER_DESC *desc, const D3D11_SUBRESOURCE_DATA *init_data, ID3D11Buffer **buffer) const {
			return m_device->CreateBuffer(desc, init_data, buffer);
		}
		template < typename VertexT >
		HRESULT CreateVertexBuffer(ID3D11Buffer **buffer, const VertexT *vertices, size_t nb_vertices) const;
		template < typename IndexT >
		HRESULT CreateIndexBuffer(ID3D11Buffer **buffer, const IndexT *indices, size_t nb_indices) const;
		template < typename BufferT >
		HRESULT CreateConstantBuffer(ID3D11Buffer **buffer) const;

		HRESULT CreateTexture1D(const D3D11_TEXTURE1D_DESC *desc, const D3D11_SUBRESOURCE_DATA *init_data, ID3D11Texture1D **texture) const {
			return m_device->CreateTexture1D(desc, init_data, texture);
		}
		HRESULT CreateTexture2D(const D3D11_TEXTURE2D_DESC *desc, const D3D11_SUBRESOURCE_DATA *init_data, ID3D11Texture2D **texture) const {
			return m_device->CreateTexture2D(desc, init_data, texture);
		}
		HRESULT CreateTexture3D(const D3D11_TEXTURE3D_DESC *desc, const D3D11_SUBRESOURCE_DATA *init_data, ID3D11Texture3D **texture) const {
			return m_device->CreateTexture3D(desc, init_data, texture);
		}
		HRESULT CreateShaderResourceView(ID3D11Resource *resource, const D3D11_SHADER_RESOURCE_VIEW_DESC *desc, ID3D11ShaderResourceView **shader_resource_view) const {
			return m_device->CreateShaderResourceView(resource, desc, shader_resource_view);
		}

		HRESULT CreateVertexShader(ID3D11VertexShader **shader, ComPtr< ID3DBlob > shader_blob) const {
			return CreateVertexShader(shader, shader_blob->GetBufferPointer(), shader_blob->GetBufferSize(), nullptr);
		}
		HRESULT CreateVertexShader(ID3D11VertexShader **shader, const void *bytecode, SIZE_T bytecode_size, ID3D11ClassLinkage *class_linkage) const {
			return m_device->CreateVertexShader(bytecode, bytecode_size, class_linkage, shader);
		}
		HRESULT CreatePixelShader(ID3D11PixelShader **shader, ComPtr< ID3DBlob > shader_blob) const {
			return CreatePixelShader(shader, shader_blob->GetBufferPointer(), shader_blob->GetBufferSize(), nullptr);
		}
		HRESULT CreatePixelShader(ID3D11PixelShader **shader, const void *bytecode, SIZE_T bytecode_size, ID3D11ClassLinkage *class_linkage) const {
			return m_device->CreatePixelShader(bytecode, bytecode_size, class_linkage, shader);
		}
		HRESULT CreateVertexInputLayout(ID3D11InputLayout **input_layout, ComPtr< ID3DBlob > shader_blob,
			const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements) const {
			return CreateVertexInputLayout(input_layout, shader_blob->GetBufferPointer(), shader_blob->GetBufferSize(), 
				input_element_desc, static_cast< UINT >(nb_input_elements));
		}
		HRESULT CreateVertexInputLayout(ID3D11InputLayout **input_layout, const void *bytecode, SIZE_T bytecode_size,
			const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements) const {
			return m_device->CreateInputLayout(input_element_desc, static_cast< UINT >(nb_input_elements), bytecode, bytecode_size, input_layout);
		}

		HRESULT CreateSamplerState(const D3D11_SAMPLER_DESC *desc, ID3D11SamplerState **sampler_state) const {
			return m_device->CreateSamplerState(desc, sampler_state);
		}
		HRESULT CreateLinearSamplerState(ID3D11SamplerState **sampler_state) const;

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