#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory_buffer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <algorithm>
#include <cctype>
#include <charconv>
#include <cwctype>
#include <optional>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// String Conversions
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Converts the given string to a @c T value.

	 @tparam		T
					The data type.
	 @param[in]		str
					The string to convert.
	 @return		A @c T value if the the conversion of the given string
					succeeded.
	 */
	template< typename T >
	[[nodiscard]]
	const std::optional< T > StringTo(std::string_view str) noexcept;

	/**
	 Converts the prefix of the given string to a @c T value.

	 @tparam		T
					The data type.
	 @param[in]		str
					The string to convert.
	 @return		A @c T value if the the conversion of the prefix of the
					given string succeeded.
	 */
	template< typename T >
	[[nodiscard]]
	const std::optional< T > StringPrefixTo(std::string_view str) noexcept;

	#pragma endregion

	//-------------------------------------------------------------------------
	// Inter-string Conversions
	//-------------------------------------------------------------------------
	#pragma region

	class UTF8toUTF16 {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit UTF8toUTF16(std::string_view s)
			: m_buffer() {

			Convert(s);
		}
		UTF8toUTF16(const UTF8toUTF16& converter) = delete;
		UTF8toUTF16(UTF8toUTF16&& converter) noexcept = default;
		~UTF8toUTF16() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		UTF8toUTF16& operator=(const UTF8toUTF16& converter) = delete;
		UTF8toUTF16& operator=(UTF8toUTF16&& converter) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		[[nodiscard]]
		std::size_t size() const noexcept {
			return m_buffer.size() - 1u;
		}

		[[nodiscard]]
		const wchar_t* c_str() const noexcept {
			return m_buffer.data();
		}

		[[nodiscard]]
		const std::wstring str() const {
			return { c_str(), size() };
		}

		[[nodiscard]]
		operator std::wstring_view() const noexcept {
			return { c_str(), size() };
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		DWORD Convert(std::string_view s);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		MemoryBuffer< wchar_t, 512u > m_buffer;
	};

	class UTF16toUTF8 {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit UTF16toUTF8(std::wstring_view s)
			: m_buffer() {

			Convert(s);
		}
		UTF16toUTF8(const UTF16toUTF8& converter) = delete;
		UTF16toUTF8(UTF16toUTF8&& converter) noexcept = default;
		~UTF16toUTF8() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		UTF16toUTF8& operator=(const UTF16toUTF8& converter) = delete;
		UTF16toUTF8& operator=(UTF16toUTF8&& converter) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		[[nodiscard]]
		std::size_t size() const noexcept {
			return m_buffer.size() - 1u;
		}

		[[nodiscard]]
		const char* c_str() const noexcept {
			return m_buffer.data();
		}

		[[nodiscard]]
		const std::string str() const {
			return { c_str(), size() };
		}

		[[nodiscard]]
		operator std::string_view() const noexcept {
			return { c_str(), size() };
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		DWORD Convert(std::wstring_view s);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		MemoryBuffer< char, 512u > m_buffer;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// Transformations
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Transforms the given string to lower case.

	 @param[in,out] str
					A reference to the string to transform.
	 */
	inline void TransformToLowerCase(std::string& str) {
		using std::begin;
		using std::cbegin;
		using std::cend;

		constexpr auto f = [](char c) noexcept {
			return static_cast< char >(std::tolower(c));
		};
		std::transform(cbegin(str), cend(str), begin(str), f);
	}

	/**
	 Transforms the given string to lower case.

	 @param[in,out] str
					A reference to the string to transform.
	 */
	inline void TransformToLowerCase(std::wstring& str) {
		using std::begin;
		using std::cbegin;
		using std::cend;

		constexpr auto f = [](wchar_t c) noexcept {
			return static_cast< wchar_t >(std::towlower(c));
		};
		std::transform(cbegin(str), cend(str), begin(str), f);
	}

	/**
	 Transforms the given string to upper case.

	 @param[in,out] str
					A reference to the string to transform.
	 */
	inline void TransformToUpperCase(std::string& str) {
		using std::begin;
		using std::cbegin;
		using std::cend;

		constexpr auto f = [](char c) noexcept {
			return static_cast< char >(std::toupper(c));
		};
		std::transform(cbegin(str), cend(str), begin(str), f);
	}

	/**
	 Transforms the given string to upper case.

	 @param[in,out] str
					A reference to the string to transform.
	 */
	inline void TransformToUpperCase(std::wstring& str) {
		using std::begin;
		using std::cbegin;
		using std::cend;

		constexpr auto f = [](wchar_t c) noexcept {
			return static_cast< wchar_t >(std::towupper(c));
		};
		std::transform(cbegin(str), cend(str), begin(str), f);
	}

	#pragma endregion
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string_utils.tpp"

#pragma endregion