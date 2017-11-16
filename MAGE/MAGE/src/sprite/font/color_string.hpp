#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\math.hpp"
#include "material\color.hpp"
#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of color strings representing a string and its color.
	 */
	class ColorString final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a color string fromt the given string and color.

		 @param[in]		str
						The string.
		 @param[in]		color
						A reference to the sRGB color.
		 */
		explicit ColorString(wstring str, const SRGBA &color = color::White)
			: m_str(std::move(str)), m_color(color) {}
		
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
		 @return		A reference to the copy of the given color string (i.e. 
						this color string).
		 */
		ColorString &operator=(const ColorString &color_string) = default;

		/**
		 Moves the given color string to this color string.

		 @param[in]		color_string
						A reference to the color string to move.
		 @return		A reference to the moved color string (i.e. this color 
						string).
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
						The string.
		 */
		void SetString(wstring str) noexcept {
			m_str = std::move(str);
		}

		/**
		 Returns the sRGB color of this color string.

		 @return		A reference to sRGB color of this color string.
		 */
		SRGBA &GetColor() noexcept {
			return m_color;
		}

		/**
		 Returns the sRGB color of this color string.

		 @return		A reference to sRGB color of this color string.
		 */
		const SRGBA &GetColor() const noexcept {
			return m_color;
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
		 The sRGB color of this color string. 
		 */
		SRGBA m_color;
	};
}