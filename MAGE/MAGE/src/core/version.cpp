//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\version.hpp"

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

	void PrintConsoleHeader() noexcept {
		
		printf("Engine version %u.%u.%u of %s at %s\n", 
			GetVersionMajor(), GetVersionMinor(), GetVersionPatch(),
			__DATE__, __TIME__);
		printf("Copyright (c) 2016-2017 Matthias Moulin.\n");
		
		fflush(stdout);
	}
}
