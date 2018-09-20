#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename T >
	[[nodiscard]]
	inline const std::optional< T > StringTo(std::string_view str) noexcept {
		using std::from_chars;

		const char* const first = str.data();
		const char* const last  = str.data() + str.size();
		T result = {};
		const auto [ptr, error_code] = from_chars(first, last, result);

		if (last != ptr
			|| std::errc::invalid_argument    == error_code
			|| std::errc::result_out_of_range == error_code) {

			return {};
		}
		else {
			return result;
		}
	}

	template<>
	[[nodiscard]]
	inline const std::optional< bool > StringTo(std::string_view str) noexcept {
		if ("true" == str) {
			return true;
		}
		if ("false" == str) {
			return false;
		}

		return {};
	}

	template< typename T >
	[[nodiscard]]
	inline const std::optional< T > StringPrefixTo(std::string_view str) noexcept {
		using std::from_chars;

		const char* const first = str.data();
		const char* const last  = str.data() + str.size();
		T result = {};
		const auto [ptr, error_code] = from_chars(first, last, result);

		if (first == ptr
			|| std::errc::invalid_argument    == error_code
			|| std::errc::result_out_of_range == error_code) {

			return {};
		}
		else {
			return result;
		}
	}
}