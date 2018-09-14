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
#include <fmt\core.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void PrintConsoleHeader() noexcept {
		fmt::print("Engine version {}.{}.{} of {} at {}\n",
					GetVersionMajor(), GetVersionMinor(), GetVersionPatch(), 
				   __DATE__, __TIME__);
		fmt::print("Copyright (c) 2016-2018 Matthias Moulin.\n");
		
		std::fflush(stdout);
	}
}
