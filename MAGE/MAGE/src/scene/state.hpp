#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\scalar_types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 An enumeration of the different states.

	 This contains:
	 @c Active,
	 @c Passive and
	 @c Terminated.
	 */
	enum class State : U8 {
		Active,
		Passive,
		Terminated
	};
}