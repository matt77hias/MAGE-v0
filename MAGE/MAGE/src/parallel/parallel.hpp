#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Returns the number of physical cores (i.e. physical processors).

	 @return		The number of physical cores (i.e. physical processors).
	 */
	size_t NumberOfPhysicalCores() noexcept;

	/**
	 Returns the number of system cores (i.e. logical processors).

	 @return		The number of system cores (i.e. logical processors).
	 */
	size_t NumberOfSystemCores() noexcept;
}