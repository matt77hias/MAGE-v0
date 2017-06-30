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
	 A class of tangent-space-normal-map vertex shaders.
	 */
	class TSNMVertexShader : public VertexShader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a tangent-space-normal-map vertex shader.

		 @pre			The current engine must be loaded.
		 @param[in]		fname
						A reference to the filename
						(the globally unique identifier).
		 @throws		FormattedException
						Failed to initialize this vertex shader.
		 */
		explicit TSNMVertexShader(const wstring &fname);

		/**
		 Constructs a tangent-space-normal-map vertex shader.

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
		explicit TSNMVertexShader(const wstring &fname,
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		
		/**
		 Constructs a tangent-space-normal-map vertex shader.

		 @pre			The current engine must be loaded.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		compiled_vertex_shader
						A reference to the compiled vertex shader.
		 @throws		FormattedException
						Failed to initialize this vertex shader.
		 */
		explicit TSNMVertexShader(const wstring &guid,
			const CompiledVertexShader &compiled_vertex_shader);

		/**
		 Constructs a tangent-space-normal-map vertex shader.

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
		explicit TSNMVertexShader(const wstring &guid,
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const CompiledVertexShader &compiled_vertex_shader);
		
		/**
		 Constructs a tangent-space-normal-map vertex shader 
		 from the given tangent-space-normal-map vertex shader.

		 @param[in]		vertex_shader
						A reference to the tangent-space-normal-map vertex shader to copy.
		 */
		TSNMVertexShader(const TSNMVertexShader &vertex_shader) = delete;
		
		/**
		 Constructs a tangent-space-normal-map vertex shader by moving 
		 the given tangent-space-normal-map vertex shader.

		 @param[in]		vertex_shader
						A reference to the tangent-space-normal-map vertex shader to move.
		 */
		TSNMVertexShader(TSNMVertexShader &&vertex_shader);

		/**
		 Destructs this tangent-space-normal-map vertex shader.
		 */
		virtual ~TSNMVertexShader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given tangent-space-normal-map vertex shader 
		 to this tangent-space-normal-map vertex shader.

		 @param[in]		vertex_shader
						A reference to the tangent-space-normal-map vertex shader to copy.
		 @return		A reference to the copy of the given tangent-space-normal-map vertex shader
						(i.e. this tangent-space-normal-map vertex shader).
		 */
		TSNMVertexShader &operator=(const TSNMVertexShader &vertex_shader) = delete;
		
		/**
		 Copies the given tangent-space-normal-map vertex shader 
		 to this tangent-space-normal-map vertex shader.

		 @param[in]		vertex_shader
						A reference to the tangent-space-normal-map vertex shader to copy.
		 @return		A reference to the moved tangent-space-normal-map vertex shader
						(i.e. this tangent-space-normal-map vertex shader).
		 */
		TSNMVertexShader &operator=(TSNMVertexShader &&vertex_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Prepares this tangent-space-normal-map vertex shader for shading.

		 @pre			@a transform is not equal to @c nullptr.
		 @param[in]		transform
						A pointer to the transform buffer.
		 */
		virtual void PrepareShading(ID3D11Buffer *transform) const override final;
	};

	//-------------------------------------------------------------------------
	// TSNMPixelShader
	//-------------------------------------------------------------------------

	/**
	 A class of tangent-space-normal-map pixel shaders.
	 */
	class TSNMPixelShader : public PixelShader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a tangent-space-normal-map pixel shader.

		 @pre			The current engine must be loaded.
		 @param[in]		fname
						A reference to the filename
						(the globally unique identifier).
		 @throws		FormattedException
						Failed to initialize this pixel shader.
		 */
		explicit TSNMPixelShader(const wstring &fname);

		/**
		 Constructs a tangent-space-normal-map pixel shader.

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
		explicit TSNMPixelShader(const wstring &fname,
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);

		/**
		 Constructs a tangent-space-normal-map pixel shader.

		 @pre			The current engine must be loaded.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		compiled_pixel_shader
						A reference to the compiled pixel shader.
		 @throws		FormattedException
						Failed to initialize this pixel shader.
		 */
		explicit TSNMPixelShader(const wstring &guid,
			const CompiledPixelShader &compiled_pixel_shader);

		/**
		 Constructs a tangent-space-normal-map pixel shader.

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
		explicit TSNMPixelShader(const wstring &guid,
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const CompiledPixelShader &compiled_pixel_shader);
		
		/**
		 Constructs a tangent-space-normal-map pixel shader 
		 from the given tangent-space-normal-map pixel shader.

		 @param[in]		pixel_shader
						A reference to the tangent-space-normal-map pixel shader to copy.
		 */
		TSNMPixelShader(const TSNMPixelShader &pixel_shader) = delete;

		/**
		 Constructs a tangent-space-normal-map pixel shader by moving 
		 the given tangent-space-normal-map pixel shader.

		 @param[in]		pixel_shader
						A reference to the tangent-space-normal-map pixel shader to move.
		 */
		TSNMPixelShader(TSNMPixelShader &&pixel_shader);

		/**
		 Destructs this tangent-space-normal-map pixel shader.
		 */
		virtual ~TSNMPixelShader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given tangent-space-normal-map pixel shader 
		 to this tangent-space-normal-map pixel shader.

		 @param[in]		pixel_shader
						A reference to the tangent-space-normal-map pixel shader to copy.
		 @return		A reference to the copy of the given tangent-space-normal-map pixel shader
						(i.e. this tangent-space-normal-map pixel shader).
		 */
		TSNMPixelShader &operator=(const TSNMPixelShader &pixel_shader) = delete;

		/**
		 Moves the given tangent-space-normal-map pixel shader 
		 to this tangent-space-normal-map pixel shader.

		 @param[in]		pixel_shader
						A reference to the tangent-space-normal-map pixel shader to move.
		 @return		A reference to the moved tangent-space-normal-map pixel shader
						(i.e. this tangent-space-normal-map pixel shader).
		 */
		TSNMPixelShader &operator=(TSNMPixelShader &&pixel_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Prepares this tangent-space-normal-map pixel shader for shading.

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
		 A pointer to the material buffer of this tangent-space-normal-map pixel shader.
		 */
		ConstantBuffer< MaterialBuffer > m_material_buffer;
	};
}