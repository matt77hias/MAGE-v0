//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	VertexShader::VertexShader(ID3D11Device& device,
							   std::wstring guid,
		                       const CompiledShader& compiled_shader,
							   gsl::span< const D3D11_INPUT_ELEMENT_DESC >
							   input_element_descs)
		: Resource< VertexShader >(std::move(guid)),
		m_vertex_shader(),
		m_vertex_layout() {

		SetupShader(device, compiled_shader, std::move(input_element_descs));
	}

	VertexShader::VertexShader(VertexShader&& vertex_shader) noexcept = default;

	VertexShader::~VertexShader() = default;

	VertexShader& VertexShader
		::operator=(VertexShader&& vertex_shader) noexcept = default;

	void VertexShader::SetupShader(ID3D11Device& device,
		                           const CompiledShader& compiled_shader,
								   gsl::span< const D3D11_INPUT_ELEMENT_DESC >
								   input_element_descs) {

		// Create the vertex shader.
		{
			const HRESULT result = device.CreateVertexShader(
				                           compiled_shader.GetBytecode(),
				                           compiled_shader.GetBytecodeSize(),
				                           nullptr,
				                           m_vertex_shader.ReleaseAndGetAddressOf());
			ThrowIfFailed(result,
						  "Vertex shader creation failed: {:08X}.", result);
		}

		if (nullptr == input_element_descs.data()) {
			// If the vertex shader has no input signature (i.e. the mesh is
			// generated on the fly on the GPU), no vertex input layout needs
			// to be generated.
			return;
		}

		// Create the vertex input layout.
		{
			const HRESULT result = device.CreateInputLayout(
				                           input_element_descs.data(),
				                           static_cast< U32 >(input_element_descs.size()),
				                           compiled_shader.GetBytecode(),
				                           compiled_shader.GetBytecodeSize(),
				                           m_vertex_layout.ReleaseAndGetAddressOf());
			ThrowIfFailed(result,
						  "Vertex input layout creation failed: {:08X}.", result);
		}
	}
}