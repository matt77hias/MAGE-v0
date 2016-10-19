#pragma once

//-------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------
#define alloca _alloca

#ifndef MAGE_L1_CACHE_LINE_SIZE
#define MAGE_L1_CACHE_LINE_SIZE 64
#endif

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "memory/allocation.hpp"
#include "memory/arena.hpp"
#include "memory/reference.hpp"