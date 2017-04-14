#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "font\sprite_font.hpp"
#include "text\sprite_text_item.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class SpriteText {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		virtual ~SpriteText() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		SpriteText &operator=(const SpriteText &sprite_text);
		SpriteText &operator=(SpriteText &&sprite_text) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual SpriteText *Clone() const = 0;

		virtual void Draw(SpriteBatch &sprite_batch) const = 0;

		const string &GetName() const {
			return m_name;
		}
		void SetName(const string &name) {
			m_name = name;
		}
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

		SpriteEffect GetSpriteEffects() const {
			return m_effects;
		}
		void SetSpriteEffects(SpriteEffect effects) {
			m_effects = effects;
		}
		SpriteTransform *GetTransform() {
			return m_transform.get();
		}
		const SpriteTransform *GetTransform() const {
			return m_transform.get();
		}

		const XMVECTOR MeasureString() const;

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		explicit SpriteText(const string &name, SharedPtr< SpriteFont > font,
			SpriteEffect effects = SpriteEffect_None) 
			: m_name(name), m_effects(effects),
			m_font(font), m_transform(new SpriteTransform()) {}
		SpriteText(const SpriteText &sprite_text);
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

		string m_name;
		vector< SpriteTextItem > m_items;
		SpriteEffect m_effects;
		SharedPtr< SpriteFont > m_font;
		UniquePtr< SpriteTransform > m_transform;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "text\sprite_text.tpp"

#pragma endregion