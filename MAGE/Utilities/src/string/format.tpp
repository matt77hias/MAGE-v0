#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <cstdio>
#include <fmt\format.h>
#include <iterator>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename... ArgsT >
	[[nodiscard]]
	inline const std::string Format(std::string_view format_str, 
									const ArgsT&... args) {

		return fmt::format(format_str, args...);
	}

	template< typename... ArgsT >
	[[nodiscard]]
	inline const std::wstring Format(std::wstring_view format_str, 
									 const ArgsT&... args) {

		return fmt::format(format_str, args...);
	}

	template< typename... ArgsT >
	inline void Print(std::string_view format_str, const ArgsT&... args) {
		return fmt::print(format_str, args...);
	}

	template< typename... ArgsT >
	inline void Print(std::wstring_view format_str, const ArgsT&... args) {
		return fmt::print(format_str, args...);
	}

	template< typename OutputIt, typename... ArgsT >
	inline OutputIt AppendWrite(OutputIt it, 
								std::string_view format_str, const ArgsT&... args) {

		return fmt::format_to(it, format_str, args...);
	}

	template< typename OutputIt, typename... ArgsT >
	inline OutputIt AppendWrite(OutputIt it, 
								std::wstring_view format_str, const ArgsT&... args) {

		return fmt::format_to(it, format_str, args...);
	}

	template< typename OutputIt, typename... ArgsT >
	inline OutputIt AppendWrite(OutputIt it, size_t length, 
								std::string_view format_str, const ArgsT&... args) {

		return fmt::format_to_n(it, length, format_str, args...);
	}

	template< typename OutputIt, typename... ArgsT >
	inline OutputIt AppendWrite(OutputIt it, size_t length, 
								std::wstring_view format_str, const ArgsT&... args) {

		return fmt::format_to_n(it, length, format_str, args...);
	}

	template< typename... ArgsT >
	inline void WriteTo(NotNull< std::FILE* > stream,
						std::string_view format_str, const ArgsT&... args) {
		
		fmt::print(stream, format_str, args...);
	}

	template< typename... ArgsT >
	inline void WriteTo(NotNull< std::FILE* > stream,
						std::wstring_view format_str, const ArgsT&... args) {

		fmt::print(stream, format_str, args...);
	}

	template< typename... ArgsT >
	inline void WriteTo(NotNull< zstring > buffer, size_t length,
						std::string_view format_str, const ArgsT&... args) {

		auto it = FormatTo(buffer, length - 1u, format_str, args...);
		*it = '\n';
	}

	template< typename... ArgsT >
	inline void WriteTo(NotNull< wzstring > buffer, size_t length,
						std::wstring_view format_str, const ArgsT&... args) {

		auto it = FormatTo(buffer, length - 1u, format_str, args...);
		*it = L'\n';
	}

	template< size_t N, typename... ArgsT >
	inline void WriteTo(char (&buffer)[N],
						std::string_view format_str, const ArgsT&... args) {

		Print(NotNull< zstring >(buffer), N, format_str, args...);
	}

	template< size_t N, typename... ArgsT >
	inline void WriteTo(wchar_t (&buffer)[N],
						std::wstring_view format_str, const ArgsT&... args) {
		
		Print(NotNull< wzstring >(buffer), N, format_str, args...);
	}
}