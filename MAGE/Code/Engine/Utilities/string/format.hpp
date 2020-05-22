#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\formats.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	template< typename StringT, typename... ArgsT >
	[[nodiscard]]
	const auto Format(const StringT& format_str, const ArgsT&... args);

	template< typename... ArgsT >
	void Print(std::string_view format_str, const ArgsT&... args);

	template< typename... ArgsT >
	void Print(std::wstring_view format_str, const ArgsT&... args);

	template< typename OutputIt, typename... ArgsT >
	OutputIt AppendWrite(OutputIt it,
						 std::string_view format_str, const ArgsT&... args);

	template< typename OutputIt, typename... ArgsT >
	OutputIt AppendWrite(OutputIt it,
						 std::wstring_view format_str, const ArgsT&... args);

	template< typename OutputIt, typename... ArgsT >
	OutputIt AppendWrite(OutputIt it, std::size_t length,
						 std::string_view format_str, const ArgsT&... args);

	template< typename OutputIt, typename... ArgsT >
	OutputIt AppendWrite(OutputIt it, std::size_t length,
						 std::wstring_view format_str, const ArgsT&... args);

	template< typename... ArgsT >
	void WriteTo(NotNull< std::FILE* > stream,
				 std::string_view format_str, const ArgsT&... args);

	template< typename... ArgsT >
	void WriteTo(NotNull< std::FILE* > stream,
				 std::wstring_view format_str, const ArgsT&... args);

	template< typename... ArgsT >
	void WriteTo(NotNull< zstring > buffer, std::size_t length,
				 std::string_view format_str, const ArgsT&... args);

	template< typename... ArgsT >
	void WriteTo(NotNull< wzstring > buffer, std::size_t length,
				 std::wstring_view format_str, const ArgsT&... args);

	template< std::size_t N, typename... ArgsT >
	void WriteTo(char (&buffer)[N],
				 std::string_view format_str, const ArgsT&... args);

	template< std::size_t N, typename... ArgsT >
	void WriteTo(wchar_t (&buffer)[N],
				 std::wstring_view format_str, const ArgsT&... args);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\format.tpp"

#pragma endregion