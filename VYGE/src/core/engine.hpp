#pragma once

#include "targetver.h"

#ifndef POINTER_SIZE
#if defined(__amd64__) || defined(_M_X64)
#define POINTER_SIZE 8
#elif defined(__i386__) || defined(_M_IX86)
#define POINTER_SIZE 4
#endif
#endif

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#include <stdint.h>
#include <stdio.h>
#include <tchar.h>

#include <string>
using std::string;

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "../math/math.hpp"
#include "../collection/collection.hpp"
#include "../memory/memory.hpp"
#include "../parallel/parallel.hpp"
#include "../resource/resource.hpp"