#pragma once

#include "resource\resource.hpp"
#include "collection\collection.hpp"
#include "rendering\rendering_device.hpp"

#include "sprite\glyph.hpp"
#include "sprite\sprite_transform.hpp"
#include "sprite\sprite_batch.hpp"
#include "sprite\sprite_effects.hpp"
#include "material\color.hpp"



namespace mage {

	class SpriteFont {

	public:

		SpriteFont(const RenderingDevice &device, const wstring &fname, bool force_srgb);
		virtual ~SpriteFont() = default;

		void DrawString(SpriteBatch &sprite_batch, const wchar_t *text, const SpriteTransform &transform,
			XMVECTOR color = Colors::White, SpriteEffects effects = SpriteEffects_None, float layer_depth = 0.0f) const;

		XMVECTOR MeasureString(const wchar_t *text);
		RECT MeasureDrawBounds(const wchar_t *text, const XMFLOAT2 &position);
		
		float GetLineSpacing() const;
		void SetLineSpacing(float spacing);
		wchar_t GetDefaultCharacter() const;
		void SetDefaultCharacter(wchar_t character);
		bool ContainsCharacter(wchar_t character) const;

		const Glyph *GetGlyph(wchar_t character) const;
		void GetSpriteSheet(ID3D11ShaderResourceView **texture);

	private:

		SpriteFont(const SpriteFont &font) = delete;
		SpriteFont &operator=(const SpriteFont &font) = delete;

		ComPtr< ID3D11ShaderResourceView > m_texture;
		vector < Glyph > m_glyphs;
		const Glyph *m_default_glyph;
		float m_line_spacing;
	};
}