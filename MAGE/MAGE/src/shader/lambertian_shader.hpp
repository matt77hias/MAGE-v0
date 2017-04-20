#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shader.hpp"
#include "rendering\constant_buffer.hpp"

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

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit LambertianVertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		LambertianVertexShader(const LambertianVertexShader &vertex_shader) = delete;
		LambertianVertexShader(LambertianVertexShader &&vertex_shader) = default;
		virtual ~LambertianVertexShader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		LambertianVertexShader &operator=(const LambertianVertexShader &vertex_shader) = delete;
		LambertianVertexShader &operator=(LambertianVertexShader &&vertex_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void PrepareShading(const Material &material, const World &world, const TransformBuffer &transform_buffer) const override final;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		ConstantBuffer< TransformBuffer > m_transform_buffer;
	};

	//-------------------------------------------------------------------------
	// LambertianPixelShader
	//-------------------------------------------------------------------------

	class LambertianPixelShader : public PixelShader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit LambertianPixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		LambertianPixelShader(const LambertianPixelShader &pixel_shader) = delete;
		LambertianPixelShader(LambertianPixelShader &&pixel_shader) = default;
		virtual ~LambertianPixelShader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		LambertianPixelShader &operator=(const LambertianPixelShader &pixel_shader) = delete;
		LambertianPixelShader &operator=(LambertianPixelShader &&pixel_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void PrepareShading(const Material &material, const World &world) const override final;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		ConstantBuffer< MaterialBuffer > m_material_buffer;
	};

	//-------------------------------------------------------------------------
	// Combined Lambertian Shader
	//-------------------------------------------------------------------------

	CombinedShader CreateLambertianShader();
}