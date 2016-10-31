#pragma once

//-------------------------------------------------------------------------
// Engine Defines
//-------------------------------------------------------------------------
#pragma region

#define alloca _alloca

#ifndef MAGE_L1_CACHE_LINE_SIZE
#define MAGE_L1_CACHE_LINE_SIZE 64
#endif

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\allocation.hpp"
#include "memory\arena.hpp"

#pragma endregion