#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource.hpp"
#include "scene\world.hpp"
#include "material\material.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class PixelShader : public Resource {

	public:

		PixelShader(ComPtr< ID3D11Device2 > device, const wstring &fname);
		virtual ~PixelShader() = default;
		
		virtual void Render(ComPtr< ID3D11DeviceContext2 > device_context, const Material &material, const World &world) {
			UNUSED(material);
			UNUSED(world);
			device_context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);
		}

	protected:

		ComPtr< ID3D11PixelShader > m_pixel_shader;

	private:

		PixelShader(const PixelShader &pixel_shader) = delete;
		PixelShader &operator=(const PixelShader &pixel_shader) = delete;
		
		HRESULT InitializeShader(ComPtr< ID3D11Device2 > device);
	};
}