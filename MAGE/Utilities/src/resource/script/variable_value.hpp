#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <map>
#include <variant>

#pragma endregion

//-----------------------------------------------------------------------------
// Type Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A value type for representing the types of variables.
	 */
	using Value = std::variant< bool,
			                    F32, F32x2, F32x3, F32x4,
								S32, S32x2, S32x3, S32x4,
								U32, U32x2, U32x3, U32x4,
		                        std::string >;
	/**
	 A value map type for representing the mapping type between the name and
	 value of variables.
	 */
	using ValueMap = std::map< std::string, Value, std::less<> >;
}