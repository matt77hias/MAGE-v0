#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"
#include "math\math.hpp"
#include "material\color.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct SpriteTextItem final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit SpriteTextItem(const wstring &text, const Color &color)
			: m_text(text), m_color(color) {}
		explicit SpriteTextItem(const wstring &text, const XMVECTOR &color = Colors::White)
			: m_text(text), m_color() {
			SetColor(color);
		}
		SpriteTextItem(const SpriteTextItem &sprite_text_item) = default;
		SpriteTextItem(SpriteTextItem &&sprite_text_item) = default;
		~SpriteTextItem() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		SpriteTextItem &operator=(const SpriteTextItem &sprite_text_item) = default;
		SpriteTextItem &operator=(SpriteTextItem &&sprite_text_item) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		const wstring &GetText() const {
			return m_text;
		}
		void SetText(const wstring &text) {
			m_text = text;
		}
		void SetText(const wchar_t *text) {
			m_text = text;
		}
		const Color GetColor() const {
			return m_color;
		}
		const XMVECTOR GetColorVector() const {
			return XMLoadFloat4(&m_color);
		}
		void SetColor(const Color &color) {
			m_color = color;
		}
		void SetColor(const XMVECTOR &color) {
			XMStoreFloat4(&m_color, color);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		wstring m_text;
		Color m_color;
	};
}