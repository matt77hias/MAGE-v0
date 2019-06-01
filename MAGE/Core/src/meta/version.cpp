//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "meta\version.hpp"
#include "string\format.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void PrintConsoleHeader() noexcept {
		Print("Engine version {}.{}.{} of {} at {}\n",
			  GetVersionMajor(), GetVersionMinor(), GetVersionPatch(),
			  __DATE__, __TIME__);
		Print("Copyright (c) 2016-2019 Matthias Moulin.\n");

		std::fflush(stdout);
	}
}
