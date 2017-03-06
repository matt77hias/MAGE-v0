//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "version.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdio.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void PrintConsoleHeader() {
		printf("Engine version %s of %s at %s\n", MAGE_VERSION_STRING, __DATE__, __TIME__);
		printf("Copyright (c) 2016 Matthias Moulin.\n");
		fflush(stdout);
	}
}