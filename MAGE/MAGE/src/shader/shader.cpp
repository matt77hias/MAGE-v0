//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shader.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

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

	//-------------------------------------------------------------------------
	// HullShader
	//-------------------------------------------------------------------------

	HullShader::HullShader(const wstring &guid,
		const CompiledShader *compiled_shader)
		: HullShader(guid, GetRenderingDevice(), GetRenderingDeviceContext(),
			compiled_shader) {}

	HullShader::HullShader(const wstring &guid,
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const CompiledShader *compiled_shader)
		: Resource< HullShader >(guid), 
		m_device(device), m_device_context(device_context), 
		m_hull_shader() {

		Assert(device);
		Assert(device_context);
		Assert(compiled_shader);

		SetupShader(compiled_shader);
	}

	HullShader::HullShader(HullShader &&hull_shader) = default;

	HullShader::~HullShader() = default;

	void HullShader::SetupShader(const CompiledShader *compiled_shader) {

		// Create the hull shader.
		const HRESULT result_hull_shader = m_device->CreateHullShader(compiled_shader->GetBytecode(),
																		compiled_shader->GetBytecodeSize(),
																		nullptr,
																		m_hull_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_hull_shader)) {
			throw FormattedException("Hull shader creation failed: %08X.", result_hull_shader);
		}
	}
	
	//-------------------------------------------------------------------------
	// DomainShader
	//-------------------------------------------------------------------------

	DomainShader::DomainShader(const wstring &guid,
		const CompiledShader *compiled_shader)
		: DomainShader(guid, GetRenderingDevice(), GetRenderingDeviceContext(),
			compiled_shader) {}

	DomainShader::DomainShader(const wstring &guid,
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const CompiledShader *compiled_shader)
		: Resource< DomainShader >(guid), 
		m_device(device), m_device_context(device_context), 
		m_domain_shader() {

		Assert(device);
		Assert(device_context);
		Assert(compiled_shader);

		SetupShader(compiled_shader);
	}

	DomainShader::DomainShader(DomainShader &&domain_shader) = default;

	DomainShader::~DomainShader() = default;

	void DomainShader::SetupShader(const CompiledShader *compiled_shader) {

		// Create the domain shader.
		const HRESULT result_domain_shader = m_device->CreateDomainShader(compiled_shader->GetBytecode(),
																			compiled_shader->GetBytecodeSize(),
																			nullptr,
																			m_domain_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_domain_shader)) {
			throw FormattedException("Domain shader creation failed: %08X.", result_domain_shader);
		}
	}
	
	//-------------------------------------------------------------------------
	// GeometryShader
	//-------------------------------------------------------------------------

	GeometryShader::GeometryShader(const wstring &guid,
		const CompiledShader *compiled_shader)
		: GeometryShader(guid, GetRenderingDevice(), GetRenderingDeviceContext(),
			compiled_shader) {}

	GeometryShader::GeometryShader(const wstring &guid,
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const CompiledShader *compiled_shader)
		: Resource< GeometryShader >(guid), 
		m_device(device), m_device_context(device_context), 
		m_geometry_shader() {

		Assert(device);
		Assert(device_context);
		Assert(compiled_shader);

		SetupShader(compiled_shader);
	}

	GeometryShader::GeometryShader(GeometryShader &&geometry_shader) = default;

	GeometryShader::~GeometryShader() = default;

	void GeometryShader::SetupShader(const CompiledShader *compiled_shader) {

		// Create the geometry shader.
		const HRESULT result_geometry_shader = m_device->CreateGeometryShader(compiled_shader->GetBytecode(),
																				compiled_shader->GetBytecodeSize(),
																				nullptr,
																				m_geometry_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_geometry_shader)) {
			throw FormattedException("Geometry shader creation failed: %08X.", result_geometry_shader);
		}
	}
	
	//-------------------------------------------------------------------------
	// PixelShader
	//-------------------------------------------------------------------------

	PixelShader::PixelShader(const wstring &guid,
		const CompiledShader *compiled_shader)
		: PixelShader(guid, GetRenderingDevice(), GetRenderingDeviceContext(),
			compiled_shader) {}

	PixelShader::PixelShader(const wstring &guid,
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const CompiledShader *compiled_shader)
		: Resource< PixelShader >(guid), 
		m_device(device), m_device_context(device_context), 
		m_pixel_shader() {

		Assert(device);
		Assert(device_context);
		Assert(compiled_shader);

		SetupShader(compiled_shader);
	}

	PixelShader::PixelShader(PixelShader &&pixel_shader) = default;

	PixelShader::~PixelShader() = default;

	void PixelShader::SetupShader(const CompiledShader *compiled_shader) {

		// Create the pixel shader.
		const HRESULT result_pixel_shader = m_device->CreatePixelShader(compiled_shader->GetBytecode(),
																		compiled_shader->GetBytecodeSize(),
																		nullptr,
																		m_pixel_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_pixel_shader)) {
			throw FormattedException("Pixel shader creation failed: %08X.", result_pixel_shader);
		}
	}
	
	//-------------------------------------------------------------------------
	// ComputeShader
	//-------------------------------------------------------------------------

	ComputeShader::ComputeShader(const wstring &guid,
		const CompiledShader *compiled_shader)
		: ComputeShader(guid, GetRenderingDevice(), GetRenderingDeviceContext(),
			compiled_shader) {}

	ComputeShader::ComputeShader(const wstring &guid,
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const CompiledShader *compiled_shader)
		: Resource< ComputeShader >(guid), 
		m_device(device), m_device_context(device_context), 
		m_compute_shader() {

		Assert(device);
		Assert(device_context);
		Assert(compiled_shader);

		SetupShader(compiled_shader);
	}

	ComputeShader::ComputeShader(ComputeShader &&compute_shader) = default;

	ComputeShader::~ComputeShader() = default;

	void ComputeShader::SetupShader(const CompiledShader *compiled_shader) {

		// Create the compute shader.
		const HRESULT result_compute_shader = m_device->CreateComputeShader(compiled_shader->GetBytecode(),
																			compiled_shader->GetBytecodeSize(),
																			nullptr,
																			m_compute_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_compute_shader)) {
			throw FormattedException("Compute shader creation failed: %08X.", result_compute_shader);
		}
	}
}