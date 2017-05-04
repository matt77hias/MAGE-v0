//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\basic_shader.hpp"

#include "resource\resource_factory.hpp"
#include "shader\cso\transform_VS.hpp"
#include "shader\cso\diffuse_PS.hpp"
#include "shader\cso\lambertian_PS.hpp"
#include "shader\cso\phong_PS.hpp"
#include "shader\cso\blinn_phong_PS.hpp"
#include "shader\cso\modified_blinn_phong_PS.hpp"
#include "mesh\vertex.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// BasicVertexShader
	//-------------------------------------------------------------------------

	BasicVertexShader::BasicVertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &guid)
			: VertexShader(device, device_context, guid, 
				VertexPositionNormalTexture::input_element_desc, 
				VertexPositionNormalTexture::nb_input_elements) {}
			
	BasicVertexShader::BasicVertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &guid, const void *bytecode, SIZE_T bytecode_size)
			: VertexShader(device, device_context, guid, bytecode, bytecode_size,
				VertexPositionNormalTexture::input_element_desc, 
				VertexPositionNormalTexture::nb_input_elements) {}
	
	BasicVertexShader::BasicVertexShader(BasicVertexShader &&vertex_shader) = default;

	BasicVertexShader::~BasicVertexShader() = default;

	void BasicVertexShader::PrepareShading(ID3D11Buffer *transform) const {
		m_device_context->IASetInputLayout(m_vertex_layout.Get());
		m_device_context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
		m_device_context->VSSetConstantBuffers(0, 1, &transform);
	}

	//-------------------------------------------------------------------------
	// BasicPixelShader
	//-------------------------------------------------------------------------

	BasicPixelShader::BasicPixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &guid)
			: PixelShader(device, device_context, guid),
			m_material_buffer(m_device, m_device_context) {}
			
	BasicPixelShader::BasicPixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &guid, const void *bytecode, SIZE_T bytecode_size)
			: PixelShader(device, device_context, guid, bytecode, bytecode_size),
			m_material_buffer(m_device, m_device_context) {}
	
	BasicPixelShader::BasicPixelShader(BasicPixelShader &&pixel_shader) = default;

	BasicPixelShader::~BasicPixelShader() = default;

	void BasicPixelShader::PrepareShading(const Material &material, const Lighting &lighting) const {

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
	// Factory Methods
	//-------------------------------------------------------------------------

	CombinedShader CreateDiffuseShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBasicVertexShader(
			device, device_context, MAGE_GUID_TRANSFORM_VS, g_transform_vs, sizeof(g_transform_vs));
		SharedPtr< PixelShader >  ps = factory->CreateBasicPixelShader(
			device, device_context, MAGE_GUID_DIFFUSE_PS, g_diffuse_ps, sizeof(g_diffuse_ps));
		return CombinedShader(vs, ps);
	}

	CombinedShader CreateLambertianShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBasicVertexShader(
			device, device_context, MAGE_GUID_TRANSFORM_VS, g_transform_vs, sizeof(g_transform_vs));
		SharedPtr< PixelShader >  ps = factory->CreateBasicPixelShader(
			device, device_context, MAGE_GUID_LAMBERTIAN_PS, g_lambertian_ps, sizeof(g_lambertian_ps));
		return CombinedShader(vs, ps);
	}

	CombinedShader CreatePhongShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBasicVertexShader(
			device, device_context, MAGE_GUID_TRANSFORM_VS, g_transform_vs, sizeof(g_transform_vs));
		SharedPtr< PixelShader >  ps = factory->CreateBasicPixelShader(
			device, device_context, MAGE_GUID_PHONG_PS, g_phong_ps, sizeof(g_phong_ps));
		return CombinedShader(vs, ps);
	}

	CombinedShader CreateBlinnPhongShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBasicVertexShader(
			device, device_context, MAGE_GUID_TRANSFORM_VS, g_transform_vs, sizeof(g_transform_vs));
		SharedPtr< PixelShader >  ps = factory->CreateBasicPixelShader(
			device, device_context, MAGE_GUID_BLINN_PHONG_PS, g_blinn_phong_ps, sizeof(g_blinn_phong_ps));
		return CombinedShader(vs, ps);
	}

	CombinedShader CreateModifiedBlinnPhongShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateBasicVertexShader(
			device, device_context, MAGE_GUID_TRANSFORM_VS, g_transform_vs, sizeof(g_transform_vs));
		SharedPtr< PixelShader >  ps = factory->CreateBasicPixelShader(
			device, device_context, MAGE_GUID_MODIFIED_BLINN_PHONG_PS, g_modified_blinn_phong_ps, sizeof(g_modified_blinn_phong_ps));
		return CombinedShader(vs, ps);
	}
}