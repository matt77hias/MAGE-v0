#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite_object.hpp"
#include "font\sprite_font.hpp"
#include "text\sprite_text_item.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class SpriteText : public SpriteObject {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		virtual ~SpriteText() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		SpriteText &operator=(const SpriteText &sprite_text) = default;
		SpriteText &operator=(SpriteText &&sprite_text) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual SpriteText *Clone() const = 0;

		virtual void Draw(SpriteBatch &sprite_batch) const = 0;

		SharedPtr< SpriteFont > GetFont() const {
			return m_font;
		}
		void SetFont(SharedPtr< SpriteFont > font) {
			m_font = font;
		}
		void SetText(const wstring &text) {
			m_items.clear();
			m_items.push_back(SpriteTextItem(text));
		}
		void SetText(const wchar_t *text) {
			m_items.clear();
			m_items.push_back(SpriteTextItem(text));
		}
		void SetText(const SpriteTextItem &text) {
			m_items.clear();
			m_items.push_back(SpriteTextItem(text));
		}
		void AppendText(const wstring &text) {
			m_items.push_back(SpriteTextItem(text));
		}
		void AppendText(const wchar_t *text) {
			m_items.push_back(SpriteTextItem(text));
		}
		void AppendText(const SpriteTextItem &text) {
			m_items.push_back(SpriteTextItem(text));
		}
		void SetColor(const Color &color);
		void SetColor(const XMVECTOR &color);
		const XMVECTOR MeasureString() const;

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		explicit SpriteText(const string &name, SharedPtr< SpriteFont > font,
			SpriteEffect effects = SpriteEffect_None) 
			: SpriteObject(name, effects), m_items(), m_font(font) {}
		SpriteText(const SpriteText &sprite_text) = default;
		SpriteText(SpriteText &&sprite_text) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		const SpriteFont *GetRawFont() const {
			return m_font.get();
		}

		template< typename ActionT >
		inline void ForEachSpriteTextItem(ActionT action);
		template< typename ActionT >
		inline void ForEachSpriteTextItem(ActionT action) const;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A vector with the sprite text items of this sprite text.
		 */
		vector< SpriteTextItem > m_items;

		/**
		 A pointer to the sprite font of this sprite text.
		 */
		SharedPtr< SpriteFont > m_font;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "text\sprite_text.tpp"

#pragma endregion