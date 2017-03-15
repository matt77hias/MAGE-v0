#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct Glyph final {

	public:

		Glyph() = default;
		Glyph(const Glyph &glyph) = default;
		~Glyph() = default;

		Glyph &operator=(const Glyph &glyph) = default;

		bool operator<(const Glyph &glyph) const {
			return m_character < glyph.m_character;
		}
		bool operator<(wchar_t character) const {
			return m_character < static_cast< uint32_t >(character);
		}

		uint32_t m_character;
		RECT m_sub_rectangle;
		
		union {
			struct {
				float m_offset_x;
				float m_offset_y;
			};
			float m_offsets[2];
		};

		float m_advance_x;
	};
}