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

#define MAGE_GUID_TRANSFORM_VS L"transform_vs"
#define MAGE_GUID_DIFFUSE_PS L"diffuse_ps"
#define MAGE_GUID_LAMBERTIAN_PS L"lambertian_ps"
#define MAGE_GUID_PHONG_PS L"phong_ps"
#define MAGE_GUID_BLINN_PHONG_PS L"blinn_phong_ps"
#define MAGE_GUID_MODIFIED_BLINN_PHONG_PS L"modified_blinn_phong_ps"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// LambertianVertexShader
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

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		guid
						A reference to the globally unique identifier
						of this vertex shader (i.e. filename of the 
						compiled shader output).
		 @throws		FormattedException
						Failed to initialize this vertex shader.
		 */
		explicit BasicVertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &guid);
		
		/**
		 Constructs a basic vertex shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a bytecode is not equal to @c nullptr.
		 @pre			The size of the data pointed to by @a bytecode
						is equal to @a bytecode_size (bytes).
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		guid
						A reference to the globally unique identifier
						of this vertex shader.
		 @param[in]		bytecode
						A pointer to the shader bytecode.
		 @param[in]		bytecode_size
						The size of the given shader bytecode.
		 @throws		FormattedException
						Failed to initialize this vertex shader.
		*/
		explicit BasicVertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &guid, const void *bytecode, SIZE_T bytecode_size);
		
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

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		guid
						A reference to the globally unique identifier
						of this pixel shader (i.e. filename of the
						compiled shader output).
		 @throws		FormattedException
						Failed to initialize this pixel shader.
		 */
		explicit BasicPixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &guid);

		/**
		 Constructs a basic pixel shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a bytecode is not equal to @c nullptr.
		 @pre			The size of the data pointed to by @a bytecode
						is equal to @a bytecode_size (bytes).
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		guid
						A reference to the globally unique identifier
						of this pixel shader.
		 @param[in]		bytecode
						A pointer to the shader bytecode.
		 @param[in]		bytecode_size
						The size of the given shader bytecode.
		 @throws		FormattedException
						Failed to initialize this pixel shader.
		 */
		explicit BasicPixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &guid, const void *bytecode, SIZE_T bytecode_size);
		
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
		 @param[in]		lighting
						A reference to the lighting buffer.
		 */
		virtual void PrepareShading(const Material &material, const Lighting &lighting) const override final;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the material buffer of this basic pixel shader.
		 */
		ConstantBuffer< MaterialBuffer > m_material_buffer;
	};

	//-------------------------------------------------------------------------
	// Factory Methods
	//-------------------------------------------------------------------------

	/**
	 Creates a diffuse shader.

	 @pre			The current engine must be loaded.
	 @throws		FormattedException
					Failed to create the lambertian shader.
	 */
	CombinedShader CreateDiffuseShader();

	/**
	 Creates a Lambertian shader.

	 @pre			The current engine must be loaded.
	 @throws		FormattedException
					Failed to create the lambertian shader.
	 */
	CombinedShader CreateLambertianShader();

	/**
	 Creates a Phong shader.

	 @pre			The current engine must be loaded.
	 @throws		FormattedException
					Failed to create the lambertian shader.
	 */
	CombinedShader CreatePhongShader();

	/**
	 Creates a Blinn-Phong shader.

	 @pre			The current engine must be loaded.
	 @throws		FormattedException
					Failed to create the lambertian shader.
	 */
	CombinedShader CreateBlinnPhongShader();

	/**
	 Creates a Modified Blinn-Phong shader.

	 @pre			The current engine must be loaded.
	 @throws		FormattedException
					Failed to create the lambertian shader.
	 */
	CombinedShader CreateModifiedBlinnPhongShader();
}