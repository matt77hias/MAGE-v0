#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_GUID_LAMBERTIAN_VS L"lambertian_vs"
#define MAGE_GUID_LAMBERTIAN_PS L"lambertian_ps"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// LambertianVertexShader
	//-------------------------------------------------------------------------

	class LambertianVertexShader : public VertexShader {

	public:

		LambertianVertexShader(ID3D11Device2 &device);
		virtual ~LambertianVertexShader() = default;

		virtual void Render(ID3D11DeviceContext2 &device_context, const Material &material, const World &world, const TransformBuffer &transform_buffer) const override;

	private:

		LambertianVertexShader(const LambertianVertexShader &vertex_shader) = delete;
		LambertianVertexShader(LambertianVertexShader &&vertex_shader) = delete;
		LambertianVertexShader &operator=(const LambertianVertexShader &vertex_shader) = delete;
		LambertianVertexShader &operator=(LambertianVertexShader &&vertex_shader) = delete;

		ComPtr< ID3D11Buffer > m_cb_transform;
	};

	//-------------------------------------------------------------------------
	// LambertianPixelShader
	//-------------------------------------------------------------------------

	class LambertianPixelShader : public PixelShader {

	public:

		LambertianPixelShader(ID3D11Device2 &device);
		virtual ~LambertianPixelShader() = default;

		virtual void Render(ID3D11DeviceContext2 &device_context, const Material &material, const World &world) const override;

	private:

		LambertianPixelShader(const LambertianPixelShader &pixel_shader) = delete;
		LambertianPixelShader(LambertianPixelShader &&pixel_shader) = delete;
		LambertianPixelShader &operator=(const LambertianPixelShader &pixel_shader) = delete;
		LambertianPixelShader &operator=(LambertianPixelShader &&pixel_shader) = delete;

		ComPtr< ID3D11Buffer > m_cb_material;
		ComPtr< ID3D11SamplerState >m_sampler;
	};

	//-------------------------------------------------------------------------
	// Combined Lambertian Shader
	//-------------------------------------------------------------------------

	CombinedShader CreateLambertianShader();
}