#pragma once

//-------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------
#define alloca _alloca

#ifndef L1_CACHE_LINE_SIZE
#define L1_CACHE_LINE_SIZE 64
#endif

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "allocation.hpp"
#include "arena.hpp"
#include "reference.hpp"