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
		const D3D11_INPUT_ELEMENT_DESC *input_element_desc, 
		size_t nb_input_elements)
		: VertexShader(guid, Pipeline::GetDevice(), compiled_shader, 
			input_element_desc, nb_input_elements) {}

	VertexShader::VertexShader(const wstring &guid, ID3D11Device2 *device,
		const CompiledShader *compiled_shader, 
		const D3D11_INPUT_ELEMENT_DESC *input_element_desc, 
		size_t nb_input_elements)
		: Resource< VertexShader >(guid), m_vertex_shader(), m_vertex_layout() {

		SetupShader(device, compiled_shader, input_element_desc, nb_input_elements);
	}

	VertexShader::VertexShader(VertexShader &&vertex_shader) = default;

	VertexShader::~VertexShader() = default;
	
	void VertexShader::SetupShader(
		ID3D11Device2 *device, const CompiledShader *compiled_shader,
		const D3D11_INPUT_ELEMENT_DESC *input_element_desc, 
		size_t nb_input_elements) {

		Assert(device);
		Assert(compiled_shader);

		// Create the vertex shader.
		const HRESULT result_vertex_shader = device->CreateVertexShader(
			compiled_shader->GetBytecode(), compiled_shader->GetBytecodeSize(),
			nullptr, m_vertex_shader.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_vertex_shader, 
			"Vertex shader creation failed: %08X.", result_vertex_shader);

		if (!input_element_desc) {
			// If the vertex shader has no input signature (i.e. the mesh is 
			// generated on the fly on the GPU), no vertex input layout needs 
			// to be generated.
			return;
		}

		// Create the vertex input layout.
		const HRESULT result_vertex_input_layout = device->CreateInputLayout(
			input_element_desc, static_cast< U32 >(nb_input_elements),
			compiled_shader->GetBytecode(), compiled_shader->GetBytecodeSize(),
			m_vertex_layout.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_vertex_input_layout, 
			"Vertex input layout creation failed: %08X.", result_vertex_input_layout);
	}
}