#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\scalar_types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

// The version numbers (major/minor/patch) are macros to support the use of 
// these numbers in conditional macro statements (e.g. if).
#define MAGE_VERSION_MAJOR 0
#define MAGE_VERSION_MINOR 163
#define MAGE_VERSION_PATCH 0

#define MAGE_QUOTE(S) #S
#define MAGE_STR(S) MAGE_QUOTE(S)
#define MAGE_VERSION_STRING MAGE_STR(MAGE_VERSION_MAJOR) "." \
							MAGE_STR(MAGE_VERSION_MINOR) "." \
							MAGE_STR(MAGE_VERSION_PATCH)

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Returns the version major number.

	 @return		The version major number.
	 */
	[[nodiscard]]
	constexpr U32 GetVersionMajor() noexcept {
		return static_cast< U32 >(MAGE_VERSION_MAJOR);
	}

	/**
	 Returns the version minor number.

	 @return		The version minor number.
	 */
	[[nodiscard]]
	constexpr U32 GetVersionMinor() noexcept {
		return static_cast< U32 >(MAGE_VERSION_MINOR);
	}

	/**
	 Returns the version patch number.

	 @return		The version patch number.
	 */
	[[nodiscard]]
	constexpr U32 GetVersionPatch() noexcept {
		return static_cast< U32 >(MAGE_VERSION_PATCH);
	}

	/**
	 Prints the header of the engine to the console.
	 */
	void PrintConsoleHeader() noexcept;
}
