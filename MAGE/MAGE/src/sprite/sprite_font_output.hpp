#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "rendering\rendering.hpp"
#include "collection\collection.hpp"
#include "sprite\glyph.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct SpriteFontOutput final {

	public:

		SpriteFontOutput() = default;
		~SpriteFontOutput() = default;
	
		ComPtr< ID3D11ShaderResourceView > m_texture;
		vector < Glyph > m_glyphs;
		wchar_t m_default_character;
		float m_line_spacing;

	private:

		SpriteFontOutput(const SpriteFontOutput &output) = delete;
		SpriteFontOutput(SpriteFontOutput &&output) = delete;
		SpriteFontOutput &operator=(const SpriteFontOutput &output) = delete;
		SpriteFontOutput &operator=(SpriteFontOutput &&output) = delete;
	};
}
