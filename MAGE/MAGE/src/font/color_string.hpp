#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"
#include "math\math.hpp"
#include "material\color.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of color strings representing a string and its color.
	 */
	struct ColorString final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a color string fromt the given string and color.

		 @param[in]		str
						A reference to the string.
		 @param[in]		color
						A reference to the color.
		 */
		explicit ColorString(const wstring &str, const Color &color)
			: m_str(str), m_color(color) {}
		
		/**
		 Constructs a color string fromt the given string and color.

		 @param[in]		str
						A reference to the string.
		 @param[in]		color
						The color.
		 */
		explicit ColorString(const wstring &str, FXMVECTOR color = Colors::White)
			: m_str(str), m_color() {
			SetColor(color);
		}

		/**
		 Constructs a color string fromt the given string and color.

		 @param[in]		str
						A reference to the string.
		 @param[in]		color
						A reference to the color.
		 */
		explicit ColorString(wstring &&str, const Color &color)
			: m_str(std::move(str)), m_color(color) {}

		/**
		 Constructs a color string fromt the given string and color.

		 @param[in]		str
						A reference to the string.
		 @param[in]		color
						The color.
		 */
		explicit ColorString(wstring &&str, FXMVECTOR color = Colors::White)
			: m_str(std::move(str)), m_color() {
			SetColor(color);
		}

		/**
		 Constructs a color string fromt the given string and color.

		 @pre			@a str is not equal to @c nullptr.
		 @param[in]		str
						A pointer to the string.
		 @param[in]		color
						A reference to the color.
		 */
		explicit ColorString(const wchar_t *str, const Color &color)
			: m_str(str), m_color(color) {}

		/**
		 Constructs a color string fromt the given str and color.

		 @pre			@a str is not equal to @c nullptr.
		 @param[in]		str
						A pointer to the str.
		 @param[in]		color
						The color.
		 */
		explicit ColorString(const wchar_t *str, FXMVECTOR color = Colors::White)
			: m_str(str), m_color() {
			SetColor(color);
		}

		/**
		 Constructs a color string from the given color string.

		 @param[in]		color_string
						A reference to the color string to copy.
		 */
		ColorString(const ColorString &color_string) = default;

		/**
		 Constructs a color string by moving the given color string.

		 @param[in]		color_string
						A reference to the color string to move.
		 */
		ColorString(ColorString &&color_string) = default;

		/**
		 Destructs this color string.
		 */
		~ColorString() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given color string to this color string.

		 @param[in]		color_string
						A reference to the color string to copy.
		 @return		A reference to the copy of the given color string
						(i.e. this color string).
		 */
		ColorString &operator=(const ColorString &color_string) = default;

		/**
		 Moves the given color string to this color string.

		 @param[in]		color_string
						A reference to the color string to move.
		 @return		A reference to the moved color string
						(i.e. this color string).
		 */
		ColorString &operator=(ColorString &&color_string) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the string of this color string.

		 @return		A pointer to the string of this color string.
		 */
		const wchar_t *c_str() const noexcept {
			return m_str.c_str();
		}

		/**
		 Returns the string of this color string.

		 @return		A reference to the string of this color string.
		 */
		const wstring &GetString() const noexcept {
			return m_str;
		}
		
		/**
		 Sets the string of this color string to the given string.

		 @param[in]		str
						A reference to the string.
		 */
		void SetString(const wstring &str) {
			m_str = str;
		}

		/**
		 Sets the string of this color string to the given string.

		 @param[in]		str
						A reference to the string.
		 */
		void SetString(wstring &&str) noexcept {
			m_str = std::move(str);
		}

		/**
		 Sets the string of this color string to the given string.

		 @pre			@a str is not equal to @c nullptr. 
		 @param[in]		str
						A pointer to the string.
		 */
		void SetString(const wchar_t *str) {
			Assert(str);
			m_str = str;
		}

		/**
		 Returns the color of this color string.

		 @return		The color of this color string.
		 */
		const Color GetColor() const noexcept {
			return m_color;
		}

		/**
		 Returns the color of this color string as @c XMVECTOR.

		 @return		The color of this color string as @c XMVECTOR.
		 */
		const XMVECTOR GetColorVector() const noexcept {
			return XMLoadFloat4(&m_color);
		}

		/**
		 Sets the color of this color string to the given color.

		 @param[in]		color
						A reference to the color.
		 */
		void SetColor(const Color &color) noexcept {
			m_color = color;
		}

		/**
		 Sets the color of this color string to the given color.

		 @param[in]		color
						A reference to the color.
		 */
		void SetColor(Color &&color) noexcept {
			m_color = std::move(color);
		}

		/**
		 Sets the color of this color string to the given color.

		 @param[in]		color
						The color.
		 */
		void SetColor(FXMVECTOR color) noexcept {
			XMStoreFloat4(&m_color, color);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The string of this color string.
		 */
		wstring m_str;

		/**
		 The color of this color string. 
		 */
		Color m_color;
	};
}