//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\tsnm_shader.hpp"
#include "mesh\vertex.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// TSNMVertexShader
	//-------------------------------------------------------------------------

	TSNMVertexShader::TSNMVertexShader(const wstring &fname)
		: TSNMVertexShader(fname, GetRenderingDevice(), GetRenderingDeviceContext()) {}

	TSNMVertexShader::TSNMVertexShader(const wstring &fname, 
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context) 
		: VertexShader(fname, device, device_context, 
			VertexPositionNormalTexture::s_input_element_desc, 
			VertexPositionNormalTexture::s_nb_input_elements) {}
			
	TSNMVertexShader::TSNMVertexShader(const wstring &guid, 
		const CompiledVertexShader &compiled_vertex_shader)
		: TSNMVertexShader(guid, GetRenderingDevice(), GetRenderingDeviceContext(),
			compiled_vertex_shader) {}

	TSNMVertexShader::TSNMVertexShader(const wstring &guid, 
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const CompiledVertexShader &compiled_vertex_shader)
		: VertexShader(guid, device, device_context, 
			compiled_vertex_shader,
			VertexPositionNormalTexture::s_input_element_desc, 
			VertexPositionNormalTexture::s_nb_input_elements) {}
	
	TSNMVertexShader::TSNMVertexShader(TSNMVertexShader &&vertex_shader) = default;

	TSNMVertexShader::~TSNMVertexShader() = default;

	void TSNMVertexShader::PrepareShading(ID3D11Buffer *transform) const {
		m_device_context->IASetInputLayout(m_vertex_layout.Get());
		m_device_context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
		m_device_context->VSSetConstantBuffers(0, 1, &transform);
	}

	//-------------------------------------------------------------------------
	// TSNMPixelShader
	//-------------------------------------------------------------------------

	TSNMPixelShader::TSNMPixelShader(const wstring &fname)
		: TSNMPixelShader(fname, GetRenderingDevice(), GetRenderingDeviceContext()) {}

	TSNMPixelShader::TSNMPixelShader(const wstring &fname,
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context)
			: PixelShader(fname, device, device_context),
			m_material_buffer(m_device, m_device_context) {}
		
	TSNMPixelShader::TSNMPixelShader(const wstring &guid, 
		const CompiledPixelShader &compiled_pixel_shader)
		: TSNMPixelShader(guid, GetRenderingDevice(), GetRenderingDeviceContext(),
			compiled_pixel_shader) {}

	TSNMPixelShader::TSNMPixelShader(const wstring &guid, 
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const CompiledPixelShader &compiled_pixel_shader)
			: PixelShader(guid, device, device_context, compiled_pixel_shader),
			m_material_buffer(m_device, m_device_context) {}
	
	TSNMPixelShader::TSNMPixelShader(TSNMPixelShader &&pixel_shader) = default;

	TSNMPixelShader::~TSNMPixelShader() = default;

	void TSNMPixelShader::PrepareShading(const Material &material, const Lighting &lighting) const {

		MaterialBuffer buffer;
		buffer.m_Kd                 = material.GetDiffuseReflectivity();
		buffer.m_dissolve           = material.GetDissolve();
		buffer.m_Ks                 = material.GetSpecularReflectivity();
		buffer.m_Ns                 = material.GetSpecularExponent();
		buffer.m_extra_parameters.x = material.GetExtraParameter(0);
		buffer.m_extra_parameters.y = material.GetExtraParameter(1);
		buffer.m_extra_parameters.z = material.GetExtraParameter(2);
		buffer.m_extra_parameters.w = material.GetExtraParameter(3);
		m_material_buffer.UpdateData(buffer);
		
		m_device_context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);
		
		m_device_context->PSSetConstantBuffers(1, 1, m_material_buffer.GetAddressOf());
		m_device_context->PSSetConstantBuffers(2, 1, &lighting.m_light_data);
		m_device_context->PSSetShaderResources(1, 1, &lighting.m_omni_lights);
		m_device_context->PSSetShaderResources(2, 1, &lighting.m_spot_lights);

		Assert(material.GetDiffuseReflectivitySRV());
		m_device_context->PSSetShaderResources(0, 1, material.GetDiffuseReflectivitySRVAddress());
		Assert(material.GetNormalSRV());
		m_device_context->PSSetShaderResources(4, 1, material.GetNormalSRVAddress());
	}
}