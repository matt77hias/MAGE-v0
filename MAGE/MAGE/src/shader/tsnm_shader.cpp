//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\tsnm_shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

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

	void TSNMPixelShader::PrepareShading(const Material &material, const SceneInfo &scene) const {

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
		m_device_context->PSSetConstantBuffers(2, 1, &scene.m_scene_buffer);
		m_device_context->PSSetShaderResources(1, 1, &scene.m_omni_lights);
		m_device_context->PSSetShaderResources(2, 1, &scene.m_spot_lights);

		ID3D11ShaderResourceView *diffuse_texture = material.GetDiffuseReflectivitySRV();
		Assert(diffuse_texture);
		m_device_context->PSSetShaderResources(0, 1, &diffuse_texture);
		ID3D11ShaderResourceView *normal_texture = material.GetNormalSRV();
		Assert(normal_texture);
		m_device_context->PSSetShaderResources(4, 1, &normal_texture);
	}
}