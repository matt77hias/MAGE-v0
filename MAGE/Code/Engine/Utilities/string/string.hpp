#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <gsl\pointers>
#include <gsl\string_span>
#include <string>
#include <string_view>

#pragma endregion

//-----------------------------------------------------------------------------
// Type Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	using zstring        = gsl::zstring<>;
	using wzstring       = gsl::wzstring<>;
	using const_zstring  = gsl::czstring<>;
	using const_wzstring = gsl::cwzstring<>;

	/**
	 A type for representing not-null values.
	 */
	template< typename T >
	using NotNull = gsl::not_null< T >;
}