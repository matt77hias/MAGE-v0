#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of glyphs.
	 */
	struct Glyph final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a glyph.
		 */
		Glyph() = default;

		/**
		 Constructs a glyph from the given glyph.

		 @param[in]		glyph
						A reference to the glyph to copy.
		 */
		Glyph(const Glyph &glyph) = default;

		/**
		 Constructs a glyph by moving the given glyph.

		 @param[in]		glyph
						A reference to the glyph to move.
		 */
		Glyph(Glyph &&glyph) = default;

		/**
		 Destructs this glyph.
		 */
		~Glyph() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given glyph to this glyph.

		 @param[in]		glyph
						A reference to the glyph to copy.
		 @return		A reference to copy of the given glyph (i.e. this 
						glyph).
		 */
		Glyph &operator=(const Glyph &glyph) = default;

		/**
		 Moves the given glyph to this glyph.

		 @param[in]		glyph
						A reference to the glyph to move.
		 @return		A reference to the moved glyph (i.e. this glyph).
		 */
		Glyph &operator=(Glyph &&glyph) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether this glyph's character is smaller than the given 
		 glyph's character.

		 @param[in]		rhs
						A reference to the glyph to compare against.
		 @return		@c true if the this glyph's character is smaller than 
						the given glyph's character. @c false otherwise.
		 */
		bool operator<(const Glyph &rhs) const noexcept {
			return m_character < rhs.m_character;
		}

		/**
		 Checks whether this glyph's character is smaller than the given 
		 character.

		 @param[in]		rhs
						The character to compare against.
		 @return		@c true if the this glyph's character is smaller than 
						the given character. @c false otherwise.
		 */
		bool operator<(wchar_t rhs) const noexcept {
			return m_character < static_cast< U32 >(rhs);
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The character of this glyph.
		 */
		U32 m_character;

		/**
		 The subrectangle of this glyph.
		 */
		RECT m_sub_rectangle;
		
		union {
			struct {

				/**
				 The offset of this glyph from the left.
				 */
				F32 m_offset_x;

				/**
				 The offset of this glyph from the top.
				 */
				F32 m_offset_y;
			};

			/**
			 The offsets of this glyph.
			 */
			F32 m_offsets[2];
		};

		/**
		 The offset of this glyph to the right.
		 */
		F32 m_advance_x;
	};
}