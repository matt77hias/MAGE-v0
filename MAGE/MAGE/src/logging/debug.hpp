#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <assert.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#ifdef NDEBUG
#define Assert(expr) (__noop)
#else
#define Assert(expr) ((expr) ? __noop : Fatal("Assertion \"%s\" failed in %s, line %d", \
               #expr, __FILE__, __LINE__))
#endif

#pragma endregion