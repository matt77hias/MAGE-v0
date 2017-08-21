//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// VertexShader
	//-------------------------------------------------------------------------

	VertexShader::VertexShader(const wstring &guid,
		const CompiledShader *compiled_shader,
		const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements)
		: VertexShader(guid, GetRenderingDevice(), GetRenderingDeviceContext(),
			compiled_shader, input_element_desc, nb_input_elements) {}

	VertexShader::VertexShader(const wstring &guid, 
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const CompiledShader *compiled_shader, 
		const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements)
		: Resource< VertexShader >(guid),
		m_device(device), m_device_context(device_context), 
		m_vertex_shader(), m_vertex_layout() {

		Assert(device);
		Assert(device_context);
		Assert(compiled_shader);
		Assert(input_element_desc);

		SetupShader(compiled_shader, input_element_desc, nb_input_elements);
	}

	VertexShader::VertexShader(VertexShader &&vertex_shader) = default;

	VertexShader::~VertexShader() = default;

	void VertexShader::SetupShader(const CompiledShader *compiled_shader,
		const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements) {

		// Create the vertex shader.
		const HRESULT result_vertex_shader = m_device->CreateVertexShader(
																			compiled_shader->GetBytecode(),
																			compiled_shader->GetBytecodeSize(),
																			nullptr,
																			m_vertex_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_vertex_shader)) {
			throw FormattedException("Vertex shader creation failed: %08X.", result_vertex_shader);
		}

		// Create the vertex input layout.
		const HRESULT result_vertex_input_layout = m_device->CreateInputLayout(
																			input_element_desc,
																			static_cast< UINT >(nb_input_elements),
																			compiled_shader->GetBytecode(),
																			compiled_shader->GetBytecodeSize(),
																			m_vertex_layout.ReleaseAndGetAddressOf());
		if (FAILED(result_vertex_input_layout)) {
			throw FormattedException("Vertex input layout creation failed: %08X.", result_vertex_input_layout);
		}
	}
}