#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename T >
	const T LineReader::Read() {
		if (!ContainsTokens()) {
			throw Exception("%ls: line %u: no value found.",
							GetPath().c_str(), GetCurrentLineNumber());
		}

		if (const auto result
			= StringTo< T >(NotNull< const char* >(&(*m_token_iterator->first)),
							NotNull< const char* >(&(*m_token_iterator->second))); 
		    bool(result)) {

			++m_token_iterator;
			return result.value();
		}
		else {
			const auto token = m_token_iterator->str();
			throw Exception("%ls: line %u: invalid value found: %s.",
							GetPath().c_str(), GetCurrentLineNumber(), 
							token.c_str());
		}
	}

	template<>
	inline const string LineReader::Read() {
		if (!ContainsTokens()) {
			throw Exception("%ls: line %u: no string value found.",
							GetPath().c_str(), GetCurrentLineNumber());
		}

		auto result = m_token_iterator->str();

		result.erase(std::remove(result.begin(), result.end(), '"'), 
					 result.end());

		++m_token_iterator;
		return result;
	}

	template< typename T, size_t N, size_t A >
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

		return static_cast< bool >(
			StringTo< T >(NotNull< const char* >(&(*m_token_iterator->first)), 
						  NotNull< const char* >(&(*m_token_iterator->second))));
	}

	template<>
	[[nodiscard]]
	inline bool LineReader::Contains< string >() const noexcept {
		return ContainsTokens();
	}
}