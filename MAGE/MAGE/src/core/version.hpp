#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "support.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_VERSION_MAJOR 0
#define MAGE_VERSION_MINOR 1
#define MAGE_VERSION_PATCH 0

#define MAGE_QUOTE(S) #S
#define MAGE_STR(S) MAGE_QUOTE(S)
#define MAGE_VERSION_STRING MAGE_STR(MAGE_VERSION_MAJOR) "." MAGE_STR(MAGE_VERSION_MINOR) "." MAGE_STR(MAGE_VERSION_PATCH)

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Prints the header of the engine to the console.
	 */
	inline void PrintConsoleHeader() {
		printf("Engine version %s of %s at %s\n", MAGE_VERSION_STRING, __DATE__, __TIME__);
		printf("Copyright (c) 2016 Matthias Moulin.\n");
		fflush(stdout);
	}
}