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

	template< typename DataT >
	const DataT LineReader::Read() {
		DataT result;
		const auto token_result = mage::Read< DataT >(nullptr, 
			                                          &m_context, 
			                                          result, 
				                                      GetDelimiters().c_str());

		switch (token_result) {

		case TokenResult::Valid: {
			return result;
		}

		case TokenResult::None: {
			throw Exception("%ls: line %u: no value found.",
				            GetFilename().c_str(), 
				            GetCurrentLineNumber());
		}

		default: {
			throw Exception("%ls: line %u: invalid value found.",
				            GetFilename().c_str(), 
				            GetCurrentLineNumber());
		}
		}
	}

	template< typename DataT >
	[[nodiscard]]
	inline bool LineReader::Contains() const {
		return mage::Contains< DataT >(m_context, GetDelimiters().c_str()) 
			   == TokenResult::Valid;
	}
}