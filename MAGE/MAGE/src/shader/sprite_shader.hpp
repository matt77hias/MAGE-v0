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

		explicit SpriteVertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		SpriteVertexShader(SpriteVertexShader &&vertex_shader) = default;
		virtual ~SpriteVertexShader() = default;

		virtual void Draw(const XMMATRIX &transform) const override;

	private:

		SpriteVertexShader(const SpriteVertexShader &vertex_shader) = delete;
		SpriteVertexShader &operator=(const SpriteVertexShader &vertex_shader) = delete;
		SpriteVertexShader &operator=(SpriteVertexShader &&vertex_shader) = delete;

		ComPtr< ID3D11Buffer > m_cb_transform;
	};

	//-------------------------------------------------------------------------
	// SpritePixelShader
	//-------------------------------------------------------------------------

	class SpritePixelShader : public PixelShader {

	public:

		explicit SpritePixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		SpritePixelShader(SpritePixelShader &&pixel_shader) = default;
		virtual ~SpritePixelShader() = default;

		virtual void Draw(ID3D11ShaderResourceView * const *texture) const override;

	private:

		SpritePixelShader(const SpritePixelShader &pixel_shader) = delete;
		SpritePixelShader &operator=(const SpritePixelShader &pixel_shader) = delete;
		SpritePixelShader &operator=(SpritePixelShader &&pixel_shader) = delete;
	};

	//-------------------------------------------------------------------------
	// Combined Sprite Shader
	//-------------------------------------------------------------------------

	CombinedShader CreateSpriteShader();
}