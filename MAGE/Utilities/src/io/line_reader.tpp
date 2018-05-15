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
		T result;
		const auto token_result 
			= mage::Read(nullptr, &m_context, result, 
						 NotNull< const_zstring >(GetDelimiters().c_str()));

		switch (token_result) {

		case TokenResult::Valid: {
			return result;
		}

		case TokenResult::None: {
			throw Exception("%ls: line %u: no value found.",
				            GetPath().c_str(), GetCurrentLineNumber());
		}

		default: {
			throw Exception("%ls: line %u: invalid value found.",
				            GetPath().c_str(), GetCurrentLineNumber());
		}
		}
	}

	template< typename T, size_t N, size_t A >
	const Array< T, N, A > LineReader::Read() {
		Array< T, N, A > result;
		const auto token_result 
			= mage::Read< T, N, A >(nullptr, &m_context, result, 
									NotNull< const_zstring >(GetDelimiters().c_str()));

		switch (token_result) {

		case TokenResult::Valid: {
			return result;
		}

		case TokenResult::None: {
			throw Exception("%ls: line %u: no value found.",
				            GetPath().c_str(), GetCurrentLineNumber());
		}

		default: {
			throw Exception("%ls: line %u: invalid value found.",
				            GetPath().c_str(), GetCurrentLineNumber());
		}
		}
	}

	template< typename T >
	[[nodiscard]]
	inline bool LineReader::Contains() const {
		return TokenResult::Valid 
			== mage::Contains< T >(NotNull< zstring >(m_context),
								   NotNull< const_zstring >(GetDelimiters().c_str()));
	}
}