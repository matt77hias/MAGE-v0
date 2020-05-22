#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Returns the number of physical cores (i.e. physical processors).

	 @return		The number of physical cores (i.e. physical processors).
	 */
	[[nodiscard]]
	FU16 NumberOfPhysicalCores();

	/**
	 Returns the number of system cores (i.e. logical processors).

	 @return		The number of system cores (i.e. logical processors).
	 */
	[[nodiscard]]
	FU16 NumberOfSystemCores() noexcept;
}