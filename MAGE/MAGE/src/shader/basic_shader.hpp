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
	// BasicVertexShader
	//-------------------------------------------------------------------------

	/**
	 A class of basic vertex shaders.
	 */
	class BasicVertexShader : public VertexShader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a basic vertex shader.

		 @pre			The current engine must be loaded.
		 @param[in]		fname
						A reference to the filename
						(the globally unique identifier).
		 @throws		FormattedException
						Failed to initialize this vertex shader.
		 */
		explicit BasicVertexShader(const wstring &fname);

		/**
		 Constructs a basic vertex shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		fname
						A reference to the filename
						(the globally unique identifier).
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to initialize this vertex shader.
		 */
		explicit BasicVertexShader(const wstring &fname,
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		
		/**
		 Constructs a basic vertex shader.

		 @pre			The current engine must be loaded.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		compiled_vertex_shader
						A reference to the compiled vertex shader.
		 @throws		FormattedException
						Failed to initialize this vertex shader.
		 */
		explicit BasicVertexShader(const wstring &guid,
			const CompiledVertexShader &compiled_vertex_shader);

		/**
		 Constructs a basic vertex shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		compiled_vertex_shader
						A reference to the compiled vertex shader.
		 @throws		FormattedException
						Failed to initialize this vertex shader.
		*/
		explicit BasicVertexShader(const wstring &guid,
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const CompiledVertexShader &compiled_vertex_shader);
		
		/**
		 Constructs a basic vertex shader from the given basic vertex shader.

		 @param[in]		vertex_shader
						A reference to the basic vertex shader to copy.
		 */
		BasicVertexShader(const BasicVertexShader &vertex_shader) = delete;
		
		/**
		 Constructs a basic vertex shader by moving the given basic vertex shader.

		 @param[in]		vertex_shader
						A reference to the basic vertex shader to move.
		 */
		BasicVertexShader(BasicVertexShader &&vertex_shader);

		/**
		 Destructs this basic vertex shader.
		 */
		virtual ~BasicVertexShader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given basic vertex shader to this basic vertex shader.

		 @param[in]		vertex_shader
						A reference to the basic vertex shader to copy.
		 @return		A reference to the copy of the given basic vertex shader
						(i.e. this basic vertex shader).
		 */
		BasicVertexShader &operator=(const BasicVertexShader &vertex_shader) = delete;
		
		/**
		 Copies the given basic vertex shader to this basic vertex shader.

		 @param[in]		vertex_shader
						A reference to the basic vertex shader to copy.
		 @return		A reference to the moved basic vertex shader
						(i.e. this basic vertex shader).
		 */
		BasicVertexShader &operator=(BasicVertexShader &&vertex_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Prepares this basic vertex shader for shading.

		 @pre			@a transform is not equal to @c nullptr.
		 @param[in]		transform
						A pointer to the transform buffer.
		 */
		virtual void PrepareShading(ID3D11Buffer *transform) const override final;
	};

	//-------------------------------------------------------------------------
	// BasicPixelShader
	//-------------------------------------------------------------------------

	/**
	 A class of basic pixel shaders.
	 */
	class BasicPixelShader : public PixelShader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a basic pixel shader.

		 @pre			The current engine must be loaded.
		 @param[in]		fname
						A reference to the filename
						(the globally unique identifier).
		 @throws		FormattedException
						Failed to initialize this pixel shader.
		 */
		explicit BasicPixelShader(const wstring &fname);

		/**
		 Constructs a basic pixel shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		fname
						A reference to the filename
						(the globally unique identifier).
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to initialize this pixel shader.
		 */
		explicit BasicPixelShader(const wstring &fname,
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);

		/**
		 Constructs a basic pixel shader.

		 @pre			The current engine must be loaded.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		compiled_pixel_shader
						A reference to the compiled pixel shader.
		 @throws		FormattedException
						Failed to initialize this pixel shader.
		 */
		explicit BasicPixelShader(const wstring &guid,
			const CompiledPixelShader &compiled_pixel_shader);

		/**
		 Constructs a basic pixel shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		compiled_pixel_shader
						A reference to the compiled pixel shader.
		 @throws		FormattedException
						Failed to initialize this pixel shader.
		 */
		explicit BasicPixelShader(const wstring &guid,
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const CompiledPixelShader &compiled_pixel_shader);
		
		/**
		 Constructs a basic pixel shader from the given basic pixel shader.

		 @param[in]		pixel_shader
						A reference to the basic pixel shader to copy.
		 */
		BasicPixelShader(const BasicPixelShader &pixel_shader) = delete;

		/**
		 Constructs a basic pixel shader by moving the given basic pixel shader.

		 @param[in]		pixel_shader
						A reference to the basic pixel shader to move.
		 */
		BasicPixelShader(BasicPixelShader &&pixel_shader);

		/**
		 Destructs this basic pixel shader.
		 */
		virtual ~BasicPixelShader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given basic pixel shader to this basic pixel shader.

		 @param[in]		pixel_shader
						A reference to the basic pixel shader to copy.
		 @return		A reference to the copy of the given basic pixel shader
						(i.e. this basic pixel shader).
		 */
		BasicPixelShader &operator=(const BasicPixelShader &pixel_shader) = delete;

		/**
		 Moves the given basic pixel shader to this basic pixel shader.

		 @param[in]		pixel_shader
						A reference to the basic pixel shader to move.
		 @return		A reference to the moved basic pixel shader
						(i.e. this basic pixel shader).
		 */
		BasicPixelShader &operator=(BasicPixelShader &&pixel_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Prepares this basic pixel shader for shading.

		 @param[in]		material
						A reference to the material.
		 @param[in]		scene
						A reference to the scene info.
		 */
		virtual void PrepareShading(const Material &material, const SceneInfo &scene) const override final;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the material buffer of this basic pixel shader.
		 */
		ConstantBuffer< MaterialBuffer > m_material_buffer;
	};
}