#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"

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
		bool operator<(uint32_t character) const {
			return m_character < character;
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

	inline bool operator<(const Glyph &left, const Glyph &right) {
		return left.m_character < right.m_character;
	}

	inline bool operator<(const Glyph &left, uint32_t right) {
		return left.m_character < right;
	}

	inline bool operator<(uint32_t left, const Glyph &right) {
		return left < right.m_character;
	}
}