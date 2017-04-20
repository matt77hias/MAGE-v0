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

	class SpriteVertexShader : public VertexShader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit SpriteVertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		SpriteVertexShader(const SpriteVertexShader &vertex_shader) = delete;
		SpriteVertexShader(SpriteVertexShader &&vertex_shader) = default;
		virtual ~SpriteVertexShader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		SpriteVertexShader &operator=(const SpriteVertexShader &vertex_shader) = delete;
		SpriteVertexShader &operator=(SpriteVertexShader &&vertex_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void PrepareShading(const XMMATRIX &transform) const override final;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		ComPtr< ID3D11Buffer > m_cb_transform;
	};

	//-------------------------------------------------------------------------
	// SpritePixelShader
	//-------------------------------------------------------------------------

	class SpritePixelShader : public PixelShader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit SpritePixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		SpritePixelShader(const SpritePixelShader &pixel_shader) = delete;
		SpritePixelShader(SpritePixelShader &&pixel_shader) = default;
		virtual ~SpritePixelShader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		SpritePixelShader &operator=(const SpritePixelShader &pixel_shader) = delete;
		SpritePixelShader &operator=(SpritePixelShader &&pixel_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void PrepareShading(ID3D11ShaderResourceView * const *texture) const override final;
	};

	//-------------------------------------------------------------------------
	// Combined Sprite Shader
	//-------------------------------------------------------------------------

	CombinedShader CreateSpriteShader();
}