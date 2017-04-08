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

		explicit LambertianVertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		LambertianVertexShader(const LambertianVertexShader &vertex_shader) = delete;
		LambertianVertexShader(LambertianVertexShader &&vertex_shader) = default;
		virtual ~LambertianVertexShader() = default;

		LambertianVertexShader &operator=(const LambertianVertexShader &vertex_shader) = delete;
		LambertianVertexShader &operator=(LambertianVertexShader &&vertex_shader) = delete;

		virtual void Draw(const Material &material, const World &world, const TransformBuffer &transform_buffer) const override;

	private:

		ComPtr< ID3D11Buffer > m_cb_transform;
	};

	//-------------------------------------------------------------------------
	// LambertianPixelShader
	//-------------------------------------------------------------------------

	class LambertianPixelShader : public PixelShader {

	public:

		explicit LambertianPixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		LambertianPixelShader(const LambertianPixelShader &pixel_shader) = delete;
		LambertianPixelShader(LambertianPixelShader &&pixel_shader) = default;
		virtual ~LambertianPixelShader() = default;

		LambertianPixelShader &operator=(const LambertianPixelShader &pixel_shader) = delete;
		LambertianPixelShader &operator=(LambertianPixelShader &&pixel_shader) = delete;

		virtual void Draw(const Material &material, const World &world) const override;

	private:

		ComPtr< ID3D11Buffer > m_cb_material;
	};

	//-------------------------------------------------------------------------
	// Combined Lambertian Shader
	//-------------------------------------------------------------------------

	CombinedShader CreateLambertianShader();
}