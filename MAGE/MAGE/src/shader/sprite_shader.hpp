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

#define MAGE_GUID_SPRITE_VS L"sprite_vs"
#define MAGE_GUID_SPRITE_PS L"sprite_ps"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// SpriteVertexShader
	//-------------------------------------------------------------------------

	/**
	 A class of sprite vertex shaders.
	 */
	class SpriteVertexShader : public VertexShader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite vertex shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to initialize this sprite vertex shader.
		 */
		explicit SpriteVertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		
		/**
		 Constructs a sprite vertex shader from the given sprite vertex shader.

		 @param[in]		vertex_shader
						A reference to the sprite vertex shader to copy.
		 */
		SpriteVertexShader(const SpriteVertexShader &vertex_shader) = delete;
		
		/**
		 Constructs a sprite vertex shader by moving the given sprite vertex shader.

		 @param[in]		vertex_shader
						A reference to the sprite vertex shader to move.
		 */
		SpriteVertexShader(SpriteVertexShader &&vertex_shader) = default;
		
		/**
		 Destructs this sprite vertex shader.
		 */
		virtual ~SpriteVertexShader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sprite vertex shader to this sprite vertex shader.

		 @param[in]		vertex_shader
						A reference to the sprite vertex shader to copy.
		 @return		A reference to the copy of the given sprite vertex shader
						(i.e. this sprite vertex shader).
		 */
		SpriteVertexShader &operator=(const SpriteVertexShader &vertex_shader) = delete;

		/**
		 Copies the given sprite vertex shader to this sprite vertex shader.

		 @param[in]		vertex_shader
						A reference to the sprite vertex shader to copy.
		 @return		A reference to the moved sprite vertex shader
						(i.e. this sprite vertex shader).
		 */
		SpriteVertexShader &operator=(SpriteVertexShader &&vertex_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Prepares this sprite vertex shader for shading.

		 @pre			@a transform is not equal to @c nullptr.
		 @param[in]		transform
						A pointer to the transform buffer.
		 */
		virtual void PrepareShading(ID3D11Buffer *transform) const override final;
	};

	//-------------------------------------------------------------------------
	// SpritePixelShader
	//-------------------------------------------------------------------------

	/**
	 A class of sprite pixel shaders.
	 */
	class SpritePixelShader : public PixelShader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite pixel shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to initialize this sprite pixel shader.
		 */
		explicit SpritePixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		
		/**
		 Constructs a sprite pixel shader from the given sprite pixel shader.

		 @param[in]		pixel_shader
						A reference to the sprite pixel shader to copy.
		 */
		SpritePixelShader(const SpritePixelShader &pixel_shader) = delete;

		/**
		 Constructs a sprite pixel shader by moving the given sprite pixel shader.

		 @param[in]		pixel_shader
						A reference to the sprite pixel shader to move.
		 */
		SpritePixelShader(SpritePixelShader &&pixel_shader) = default;

		/**
		 Destructs this sprite pixel shader.
		 */
		virtual ~SpritePixelShader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sprite pixel shader to this sprite pixel shader.

		 @param[in]		pixel_shader
						A reference to the sprite pixel shader to copy.
		 @return		A reference to the copy of the given sprite pixel shader
						(i.e. this sprite pixel shader).
		 */
		SpritePixelShader &operator=(const SpritePixelShader &pixel_shader) = delete;

		/**
		 Moves the given sprite pixel shader to this sprite pixel shader.

		 @param[in]		pixel_shader
						A reference to the sprite pixel shader to move.
		 @return		A reference to the moved sprite pixel shader
						(i.e. this sprite pixel shader).
		 */
		SpritePixelShader &operator=(SpritePixelShader &&pixel_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Prepares this sprite pixel shader for shading.

		 @param[in]		texture
						A pointer to the texture shader resource view.
		 */
		virtual void PrepareShading(ID3D11ShaderResourceView *texture) const override final;
	};

	//-------------------------------------------------------------------------
	// Combined Sprite Shader
	//-------------------------------------------------------------------------

	/**
	 Creates a sprite shader.

	 @pre			The current engine must be loaded.
	 @throws		FormattedException
					Failed to create the sprite shader.
	 */
	CombinedShader CreateSpriteShader();
}