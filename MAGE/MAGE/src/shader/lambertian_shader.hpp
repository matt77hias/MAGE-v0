#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\empty_shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_FNAME_LAMBERTIAN_VS L"D:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/MAGE/bin/x64/Debug/lambertian_VS.cso"
#define MAGE_FNAME_LAMBERTIAN_PS L"D:/Users/Matthias/Documents/Visual Studio 2015/Projects/MAGE/MAGE/MAGE/bin/x64/Debug/lambertian_PS.cso"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class LambertianVertexShader : public VertexShader {

	public:

		LambertianVertexShader(const RenderingDevice &device);
		virtual ~LambertianVertexShader() = default;

		virtual void Render(ComPtr< ID3D11DeviceContext2 > device_context, const Material &material, const World &world, const TransformBuffer &transform_buffer) const override {
			UNUSED(world);
			UNUSED(material);
			device_context->IASetInputLayout(m_vertex_layout.Get());
			device_context->UpdateSubresource(m_cb_transform.Get(), 0, nullptr, &transform_buffer, 0, 0);
			device_context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
			device_context->VSSetConstantBuffers(0, 1, m_cb_transform.GetAddressOf());
		}

	private:

		LambertianVertexShader(const LambertianVertexShader &vertex_shader) = delete;
		LambertianVertexShader &operator=(const LambertianVertexShader &vertex_shader) = delete;

		ComPtr< ID3D11Buffer > m_cb_transform;
	};

	inline CombinedShader CreateLambertianShader(const RenderingDevice &device) {
		SharedPtr< VertexShader > vs(new LambertianVertexShader(device));
		SharedPtr< PixelShader > ps(new EmptyPixelShader(device, MAGE_FNAME_LAMBERTIAN_PS));
		return CombinedShader(vs, ps);
	}
}