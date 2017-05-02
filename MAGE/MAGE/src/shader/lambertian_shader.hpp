#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shader.hpp"
#include "rendering\constant_buffer.hpp"
#include "buffer\material_buffer.hpp"

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

	/**
	 A class of lambertian vertex shaders.
	 */
	class LambertianVertexShader : public VertexShader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a lambertian vertex shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to initialize this lambertian vertex shader.
		 */
		explicit LambertianVertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		
		/**
		 Constructs a lambertian vertex shader from the given lambertian vertex shader.

		 @param[in]		vertex_shader
						A reference to the lambertian vertex shader to copy.
		 */
		LambertianVertexShader(const LambertianVertexShader &vertex_shader) = delete;
		
		/**
		 Constructs a lambertian vertex shader by moving the given lambertian vertex shader.

		 @param[in]		vertex_shader
						A reference to the lambertian vertex shader to move.
		 */
		LambertianVertexShader(LambertianVertexShader &&vertex_shader);

		/**
		 Destructs this lambertian vertex shader.
		 */
		virtual ~LambertianVertexShader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given lambertian vertex shader to this lambertian vertex shader.

		 @param[in]		vertex_shader
						A reference to the lambertian vertex shader to copy.
		 @return		A reference to the copy of the given lambertian vertex shader
						(i.e. this lambertian vertex shader).
		 */
		LambertianVertexShader &operator=(const LambertianVertexShader &vertex_shader) = delete;
		
		/**
		 Copies the given lambertian vertex shader to this lambertian vertex shader.

		 @param[in]		vertex_shader
						A reference to the lambertian vertex shader to copy.
		 @return		A reference to the moved lambertian vertex shader
						(i.e. this lambertian vertex shader).
		 */
		LambertianVertexShader &operator=(LambertianVertexShader &&vertex_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Prepares this lambertian vertex shader for shading.

		 @pre			@a transform is not equal to @c nullptr.
		 @param[in]		transform
						A pointer to the transform buffer.
		 */
		virtual void PrepareShading(ID3D11Buffer *transform) const override final;
	};

	//-------------------------------------------------------------------------
	// LambertianPixelShader
	//-------------------------------------------------------------------------

	/**
	 A class of lambertian pixel shaders.
	 */
	class LambertianPixelShader : public PixelShader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a lambertian pixel shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to initialize this lambertian pixel shader.
		 */
		explicit LambertianPixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		
		/**
		 Constructs a lambertian pixel shader from the given lambertian pixel shader.

		 @param[in]		pixel_shader
						A reference to the lambertian pixel shader to copy.
		 */
		LambertianPixelShader(const LambertianPixelShader &pixel_shader) = delete;

		/**
		 Constructs a lambertian pixel shader by moving the given lambertian pixel shader.

		 @param[in]		pixel_shader
						A reference to the lambertian pixel shader to move.
		 */
		LambertianPixelShader(LambertianPixelShader &&pixel_shader);

		/**
		 Destructs this lambertian pixel shader.
		 */
		virtual ~LambertianPixelShader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given lambertian pixel shader to this lambertian pixel shader.

		 @param[in]		pixel_shader
						A reference to the lambertian pixel shader to copy.
		 @return		A reference to the copy of the given lambertian pixel shader
						(i.e. this lambertian pixel shader).
		 */
		LambertianPixelShader &operator=(const LambertianPixelShader &pixel_shader) = delete;

		/**
		 Moves the given lambertian pixel shader to this lambertian pixel shader.

		 @param[in]		pixel_shader
						A reference to the lambertian pixel shader to move.
		 @return		A reference to the moved lambertian pixel shader
						(i.e. this lambertian pixel shader).
		 */
		LambertianPixelShader &operator=(LambertianPixelShader &&pixel_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Prepares this lambertian pixel shader for shading.

		 @param[in]		material
						A reference to the material.
		 @param[in]		lighting
						A reference to the lighting buffer.
		 */
		virtual void PrepareShading(const Material &material, const Lighting &lighting) const override final;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the material buffer of this lambertian pixel shader.
		 */
		ConstantBuffer< MaterialBuffer > m_material_buffer;
	};

	//-------------------------------------------------------------------------
	// Combined Lambertian Shader
	//-------------------------------------------------------------------------

	/**
	 Creates a lambertian shader.

	 @pre			The current engine must be loaded.
	 @throws		FormattedException
					Failed to create the lambertian shader.
	 */
	CombinedShader CreateLambertianShader();
}