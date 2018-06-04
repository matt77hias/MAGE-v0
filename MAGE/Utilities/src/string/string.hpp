#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <string>

#include <gsl/pointers>
#include <gsl/string_span>
namespace mage {
	using zstring        = gsl::zstring<>;
	using wzstring       = gsl::wzstring<>;
	using const_zstring  = gsl::czstring<>;
	using const_wzstring = gsl::cwzstring<>;

	/**
	 A class of not-null values.
	 */
	template< typename T >
	using NotNull = gsl::not_null< T >;
}

#pragma endregion