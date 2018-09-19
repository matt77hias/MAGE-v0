#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename T >
	const T LineReader::Read() {
		if (!ContainsTokens()) {
			throw Exception("{}: line {}: no value found.",
							GetPath(), GetCurrentLineNumber());
		}

		const auto token = GetCurrentToken();

		if (const auto result = StringTo< T >(token);
		    bool(result)) {

			++m_iterator;
			return *result;
		}
		else {
			throw Exception("%{}: line {}: invalid value found: {}.",
							GetPath(), GetCurrentLineNumber(), token);
		}
	}

	template<>
	inline const std::string_view LineReader::Read() {
		if (!ContainsTokens()) {
			throw Exception("{}: line {}: no string value found.",
							GetPath(), GetCurrentLineNumber());
		}

		const auto result = GetCurrentToken();

		++m_iterator;
		return result;
	}

	template<>
	inline const std::string LineReader::Read() {
		return std::string(Read< std::string_view >());
	}

	template< typename T, std::size_t N, size_t A >
	inline const Array< T, N, A > LineReader::Read() {
		Array< T, N, A > result;
		for (auto& element : result) {
			element = Read< T >();
		}

		return result;
	}

	template< typename T >
	[[nodiscard]]
	inline bool LineReader::Contains() const noexcept {
		if (!ContainsTokens()) {
			return false;
		}

		const auto token = GetCurrentToken();
		return static_cast< bool >(StringTo< T >(token));
	}

	template<>
	[[nodiscard]]
	inline bool LineReader::Contains< std::string_view >() const noexcept {
		return ContainsTokens();
	}

	template<>
	[[nodiscard]]
	inline bool LineReader::Contains< std::string >() const noexcept {
		return Contains< std::string_view >();
	}
}