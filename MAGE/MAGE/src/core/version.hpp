#pragma once

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_VERSION_MAJOR 0
#define MAGE_VERSION_MINOR 19
#define MAGE_VERSION_PATCH 0

#define MAGE_QUOTE(S) #S
#define MAGE_STR(S) MAGE_QUOTE(S)
#define MAGE_VERSION_STRING MAGE_STR(MAGE_VERSION_MAJOR) "." MAGE_STR(MAGE_VERSION_MINOR) "." MAGE_STR(MAGE_VERSION_PATCH)

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Prints the header of the engine to the console.
	 */
	void PrintConsoleHeader();
}
