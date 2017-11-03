//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
// [numthreads(16, 8, 8)] = 1024
#define MSAA 16
#define GROUP_SIZE GROUP_SIZE_MSAA_16X
#include "aa\msaa_resolve.hlsli"