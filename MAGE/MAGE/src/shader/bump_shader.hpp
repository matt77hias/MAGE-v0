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
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// LambertianVertexShader
	//-------------------------------------------------------------------------

	/**
	 A class of bump vertex shaders.
	 */
	class BumpVertexShader : public VertexShader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a bump vertex shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		fname
						A reference to the filename.
		 @throws		FormattedException
						Failed to initialize this vertex shader.
		 */
		explicit BumpVertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &fname);
		
		/**
		 Constructs a bump vertex shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		compiled_vertex_shader
						A reference to the compiled vertex shader.
		 @throws		FormattedException
						Failed to initialize this vertex shader.
		*/
		explicit BumpVertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const CompiledVertexShader &compiled_vertex_shader);
		
		/**
		 Constructs a bump vertex shader from the given bump vertex shader.

		 @param[in]		vertex_shader
						A reference to the bump vertex shader to copy.
		 */
		BumpVertexShader(const BumpVertexShader &vertex_shader) = delete;
		
		/**
		 Constructs a bump vertex shader by moving the given bump vertex shader.

		 @param[in]		vertex_shader
						A reference to the bump vertex shader to move.
		 */
		BumpVertexShader(BumpVertexShader &&vertex_shader);

		/**
		 Destructs this bump vertex shader.
		 */
		virtual ~BumpVertexShader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given bump vertex shader to this bump vertex shader.

		 @param[in]		vertex_shader
						A reference to the bump vertex shader to copy.
		 @return		A reference to the copy of the given bump vertex shader
						(i.e. this bump vertex shader).
		 */
		BumpVertexShader &operator=(const BumpVertexShader &vertex_shader) = delete;
		
		/**
		 Copies the given bump vertex shader to this bump vertex shader.

		 @param[in]		vertex_shader
						A reference to the bump vertex shader to copy.
		 @return		A reference to the moved bump vertex shader
						(i.e. this bump vertex shader).
		 */
		BumpVertexShader &operator=(BumpVertexShader &&vertex_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Prepares this bump vertex shader for shading.

		 @pre			@a transform is not equal to @c nullptr.
		 @param[in]		transform
						A pointer to the transform buffer.
		 */
		virtual void PrepareShading(ID3D11Buffer *transform) const override final;
	};

	//-------------------------------------------------------------------------
	// BumpPixelShader
	//-------------------------------------------------------------------------

	/**
	 A class of bump pixel shaders.
	 */
	class BumpPixelShader : public PixelShader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a bump pixel shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		fname
						A reference to the filename.
		 @throws		FormattedException
						Failed to initialize this pixel shader.
		 */
		explicit BumpPixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &fname);

		/**
		 Constructs a bump pixel shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		compiled_pixel_shader
						A reference to the compiled pixel shader.
		 @throws		FormattedException
						Failed to initialize this pixel shader.
		 */
		explicit BumpPixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const CompiledPixelShader &compiled_pixel_shader);
		
		/**
		 Constructs a bump pixel shader from the given bump pixel shader.

		 @param[in]		pixel_shader
						A reference to the bump pixel shader to copy.
		 */
		BumpPixelShader(const BumpPixelShader &pixel_shader) = delete;

		/**
		 Constructs a bump pixel shader by moving the given bump pixel shader.

		 @param[in]		pixel_shader
						A reference to the bump pixel shader to move.
		 */
		BumpPixelShader(BumpPixelShader &&pixel_shader);

		/**
		 Destructs this bump pixel shader.
		 */
		virtual ~BumpPixelShader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given bump pixel shader to this bump pixel shader.

		 @param[in]		pixel_shader
						A reference to the bump pixel shader to copy.
		 @return		A reference to the copy of the given bump pixel shader
						(i.e. this bump pixel shader).
		 */
		BumpPixelShader &operator=(const BumpPixelShader &pixel_shader) = delete;

		/**
		 Moves the given bump pixel shader to this bump pixel shader.

		 @param[in]		pixel_shader
						A reference to the bump pixel shader to move.
		 @return		A reference to the moved bump pixel shader
						(i.e. this bump pixel shader).
		 */
		BumpPixelShader &operator=(BumpPixelShader &&pixel_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Prepares this bump pixel shader for shading.

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
		 A pointer to the material buffer of this bump pixel shader.
		 */
		ConstantBuffer< MaterialBuffer > m_material_buffer;
	};
}