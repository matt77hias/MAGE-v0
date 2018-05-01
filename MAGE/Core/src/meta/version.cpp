//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "meta\version.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <cstdio>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void PrintConsoleHeader() noexcept {
		std::printf("Engine version %u.%u.%u of %s at %s\n", 
					GetVersionMajor(), GetVersionMinor(), GetVersionPatch(), 
			   __DATE__, __TIME__);
		std::printf("Copyright (c) 2016-2018 Matthias Moulin.\n");
		
		std::fflush(stdout);
	}
}
