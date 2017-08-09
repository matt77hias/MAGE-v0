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
		 @pre			@a compiled_shader is not equal to @c nullptr.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		compiled_shader
						A pointer to the compiled pixel shader.
		 @throws		FormattedException
						Failed to initialize this pixel shader.
		 */
		explicit TSNMPixelShader(const wstring &guid,
			const CompiledShader *compiled_shader);

		/**
		 Constructs a tangent-space-normal-map pixel shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a compiled_shader is not equal to @c nullptr.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		compiled_shader
						A pointer to the compiled pixel shader.
		 @throws		FormattedException
						Failed to initialize this pixel shader.
		 */
		explicit TSNMPixelShader(const wstring &guid,
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const CompiledShader *compiled_shader);
		
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
		 @param[in]		scene
						A reference to the scene info.
		 */
		virtual void PrepareShading(const Material &material, const SceneInfo &scene) const override final;

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