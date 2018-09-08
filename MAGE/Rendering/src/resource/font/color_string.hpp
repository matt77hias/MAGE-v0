#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "spectrum\color.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	/**
	 A class of color strings representing a string and its color.
	 */
	class ColorString {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a color string fromt the given string and color.

		 @param[in]		str
						The string.
		 @param[in]		color
						A reference to the (linear) color.
		 */
		ColorString(std::wstring str, RGBA color = color::White) noexcept
			: m_str(std::move(str)), 
			m_color(std::move(color)) {}
		
		/**
		 Constructs a color string from the given color string.

		 @param[in]		color_string
						A reference to the color string to copy.
		 */
		ColorString(const ColorString& color_string) = default;

		/**
		 Constructs a color string by moving the given color string.

		 @param[in]		color_string
						A reference to the color string to move.
		 */
		ColorString(ColorString&& color_string) noexcept = default;

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
		ColorString& operator=(const ColorString& color_string) = default;

		/**
		 Moves the given color string to this color string.

		 @param[in]		color_string
						A reference to the color string to move.
		 @return		A reference to the moved color string (i.e. this color 
						string).
		 */
		ColorString& operator=(ColorString&& color_string) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the string of this color string.

		 @return		A pointer to the string of this color string.
		 */
		[[nodiscard]]
		NotNull< const_wzstring > c_str() const noexcept {
			return NotNull< const_wzstring >(m_str.c_str());
		}

		/**
		 Returns the string of this color string.

		 @return		A reference to the string of this color string.
		 */
		[[nodiscard]]
		const std::wstring& GetString() const noexcept {
			return m_str;
		}
		
		/**
		 Sets the string of this color string to the given string.

		 @param[in]		str
						The string.
		 */
		void SetString(std::wstring str) noexcept {
			m_str = std::move(str);
		}

		/**
		 Returns the (linear) color of this color string.

		 @return		A reference to (linear) color of this color string.
		 */
		[[nodiscard]]
		RGBA& GetColor() noexcept {
			return m_color;
		}

		/**
		 Returns the (linear) color of this color string.

		 @return		A reference to (linear) color of this color string.
		 */
		[[nodiscard]]
		const RGBA& GetColor() const noexcept {
			return m_color;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The string of this color string.
		 */
		std::wstring m_str;

		/**
		 The (linear) color of this color string. 
		 */
		RGBA m_color;
	};
}