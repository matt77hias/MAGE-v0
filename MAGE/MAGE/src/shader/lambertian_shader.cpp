//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.hpp"
#include "rendering\rendering_factory.hpp"
#include "shader\lambertian_shader.hpp"
#include "shader\cso\lambertian_PS.hpp"
#include "shader\cso\lambertian_VS.hpp"
#include "mesh\vertex.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// LambertianVertexShader
	//-------------------------------------------------------------------------

	LambertianVertexShader::LambertianVertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context)
		: VertexShader(device, device_context, MAGE_GUID_LAMBERTIAN_VS, g_lambertian_vs, sizeof(g_lambertian_vs),
			VertexPositionNormalTexture::input_element_desc, VertexPositionNormalTexture::nb_input_elements) {}

	void LambertianVertexShader::PrepareShading(ID3D11Buffer *transform) const {
		m_device_context->IASetInputLayout(m_vertex_layout.Get());
		m_device_context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
		m_device_context->VSSetConstantBuffers(0, 1, &transform);
	}

	//-------------------------------------------------------------------------
	// LambertianPixelShader
	//-------------------------------------------------------------------------

	LambertianPixelShader::LambertianPixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context)
		: PixelShader(device, device_context, MAGE_GUID_LAMBERTIAN_PS, g_lambertian_ps, sizeof(g_lambertian_ps)),
		m_material_buffer(m_device, m_device_context) {}

	void LambertianPixelShader::PrepareShading(const Material &material, const Lighting &lighting) const {

		MaterialBuffer buffer;
		buffer.m_Kd       = material.m_diffuse_reflectivity;
		buffer.m_dissolve = material.m_dissolve;
		buffer.m_Ks       = material.m_specular_reflectivity;
		buffer.m_Ns       = material.m_specular_exponent;
		m_material_buffer.UpdateData(buffer);
		
		m_device_context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);
		
		m_device_context->PSSetConstantBuffers(1, 1, m_material_buffer.GetAddressOf());
		m_device_context->PSSetConstantBuffers(2, 1, &lighting.m_light_data);
		m_device_context->PSSetShaderResources(1, 1, &lighting.m_omni_lights);
		m_device_context->PSSetShaderResources(2, 1, &lighting.m_spot_lights);

		// TODO
		if (material.m_diffuse_reflectivity_texture) {
			m_device_context->PSSetShaderResources(0, 1, material.m_diffuse_reflectivity_texture->GetTextureResourceViewAddress());
		}
	}

	//-------------------------------------------------------------------------
	// Combined Lambertian Shader
	//-------------------------------------------------------------------------

	CombinedShader CreateLambertianShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);
		
		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);
		
		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateLambertianVertexShader(device, device_context);
		SharedPtr< PixelShader >  ps = factory->CreateLambertianPixelShader(device, device_context);
		return CombinedShader(vs, ps);
	}
}