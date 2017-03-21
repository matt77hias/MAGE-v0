//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.hpp"
#include "rendering\rendering_factory.hpp"
#include "shader\lambertian_shader.hpp"
#include "shader\cso\lambertian_PS.h"
#include "shader\cso\lambertian_VS.h"
#include "mesh\vertex.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct MaterialBuffer {
		XMVECTOR x;
	};

	//-------------------------------------------------------------------------
	// LambertianVertexShader
	//-------------------------------------------------------------------------

	LambertianVertexShader::LambertianVertexShader(ID3D11Device2 &device)
		: VertexShader(device, MAGE_GUID_LAMBERTIAN_VS, g_lambertian_vs, sizeof(g_lambertian_vs),
			VertexPositionNormalTexture::input_element_desc,
			VertexPositionNormalTexture::nb_input_elements) {

		const HRESULT result_cb_transform = CreateConstantBuffer< TransformBuffer >(device, m_cb_transform.ReleaseAndGetAddressOf());
		if (FAILED(result_cb_transform)) {
			Error("Transformation constant buffer creation failed: %08X.", result_cb_transform);
			return;
		}
	}

	void LambertianVertexShader::Render(ID3D11DeviceContext2 &device_context, const Material &material, const World &world, const TransformBuffer &transform_buffer) const {
		UNUSED(world);
		UNUSED(material);
		device_context.IASetInputLayout(m_vertex_layout.Get());
		device_context.UpdateSubresource(m_cb_transform.Get(), 0, nullptr, &transform_buffer, 0, 0);
		device_context.VSSetShader(m_vertex_shader.Get(), nullptr, 0);
		device_context.VSSetConstantBuffers(0, 1, m_cb_transform.GetAddressOf());
	}

	//-------------------------------------------------------------------------
	// LambertianPixelShader
	//-------------------------------------------------------------------------

	LambertianPixelShader::LambertianPixelShader(ID3D11Device2 &device)
		: PixelShader(device, MAGE_GUID_LAMBERTIAN_PS, g_lambertian_ps, sizeof(g_lambertian_ps)) {

		const HRESULT result_cb_material = CreateConstantBuffer< MaterialBuffer >(device, m_cb_material.ReleaseAndGetAddressOf());
		if (FAILED(result_cb_material)) {
			Error("Material constant buffer creation failed: %08X.", result_cb_material);
			return;
		}

		const HRESULT result_sampler_state = CreateLinearWrapSamplerState(device, m_sampler.ReleaseAndGetAddressOf());
		if (FAILED(result_sampler_state)) {
			Error("Sampler state creation failed: %08X.", result_sampler_state);
			return;
		}
	}

	void LambertianPixelShader::Render(ID3D11DeviceContext2 &device_context, const Material &material, const World &world) const {
		UNUSED(material);
		UNUSED(world);
		device_context.PSSetShader(m_pixel_shader.Get(), nullptr, 0);
		device_context.PSSetShaderResources(0, 1, material.m_diffuse_reflectivity_texture->GetTextureResourceView().GetAddressOf());
		device_context.PSSetSamplers(0, 1, m_sampler.GetAddressOf());
	}

	//-------------------------------------------------------------------------
	// Combined Lambertian Shader
	//-------------------------------------------------------------------------

	CombinedShader CreateLambertianShader() {
		ID3D11Device2 &device = GetRenderingDevice();
		ResourceFactory &factory = GetResourceFactory();
		SharedPtr< VertexShader > vs = factory.CreateLambertianVertexShader(device);
		SharedPtr< PixelShader > ps = factory.CreateLambertianPixelShader(device);
		return CombinedShader(vs, ps);
	}
}