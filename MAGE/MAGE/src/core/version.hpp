#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

// The version numbers (major/minor/patch) must be macros, allowing the use of 
// these numbers in preprocessor directives (e.g. if).
#define MAGE_VERSION_MAJOR 0
#define MAGE_VERSION_MINOR 84
#define MAGE_VERSION_PATCH 0

#define MAGE_QUOTE(S) #S
#define MAGE_STR(S) MAGE_QUOTE(S)
#define MAGE_VERSION_STRING MAGE_STR(MAGE_VERSION_MAJOR) "." \
							MAGE_STR(MAGE_VERSION_MINOR) "." \
							MAGE_STR(MAGE_VERSION_PATCH)

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Returns the version major number.

	 @return		The version major number.
	 */
	constexpr U32 GetVersionMajor() noexcept {
		return MAGE_VERSION_MAJOR;
	}

	/**
	 Returns the version minor number.

	 @return		The version minor number.
	 */
	constexpr U32 GetVersionMinor() noexcept {
		return MAGE_VERSION_MINOR;
	}

	/**
	 Returns the version patch number.

	 @return		The version patch number.
	 */
	constexpr U32 GetVersionPatch() noexcept {
		return MAGE_VERSION_PATCH;
	}

	/**
	 Prints the header of the engine to the console.
	 */
	void PrintConsoleHeader() noexcept;
}
