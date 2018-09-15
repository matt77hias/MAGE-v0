#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	template< typename... ArgsT >
	[[nodiscard]]
	const std::string Format(std::string_view format_str, const ArgsT&... args);

	template< typename... ArgsT >
	[[nodiscard]]
	const std::wstring Format(std::wstring_view format_str, const ArgsT&... args);

	template< typename OutputIt, typename... ArgsT >
	OutputIt FormatTo(OutputIt it, 
					  std::string_view format_str, const ArgsT&... args);

	template< typename OutputIt, typename... ArgsT >
	OutputIt FormatTo(OutputIt it, 
					  std::wstring_view format_str, const ArgsT&... args);

	template< typename OutputIt, typename... ArgsT >
	OutputIt FormatTo(OutputIt it, size_t length, 
					  std::string_view format_str, const ArgsT&... args);

	template< typename OutputIt, typename... ArgsT >
	OutputIt FormatTo(OutputIt it, size_t length, 
					  std::wstring_view format_str, const ArgsT&... args);

	template< typename... ArgsT >
	void Print(std::string_view format_str, const ArgsT&... args);

	template< typename... ArgsT >
	void Print(std::wstring_view format_str, const ArgsT&... args);

	template< typename... ArgsT >
	void PrintTo(NotNull< std::FILE* > stream, 
				 std::string_view format_str, const ArgsT&... args);

	template< typename... ArgsT >
	void PrintTo(NotNull< std::FILE* > stream, 
				 std::wstring_view format_str, const ArgsT&... args);

	template< typename... ArgsT >
	void PrintTo(NotNull< zstring > buffer, size_t length, 
				 std::string_view format_str, const ArgsT&... args);

	template< typename... ArgsT >
	void PrintTo(NotNull< wzstring > buffer, size_t length, 
				 std::wstring_view format_str, const ArgsT&... args);

	template< size_t N, typename... ArgsT >
	void PrintTo(char (&buffer)[N], 
				 std::string_view format_str, const ArgsT&... args);

	template< size_t N, typename... ArgsT >
	void PrintTo(wchar_t (&buffer)[N], 
				 std::wstring_view format_str, const ArgsT&... args);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\format.tpp"

#pragma endregion