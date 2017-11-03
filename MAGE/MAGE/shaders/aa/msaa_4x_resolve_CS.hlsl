//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
// [numthreads(4, 16, 16)] = 1024
#define MSAA 4
#define GROUP_SIZE GROUP_SIZE_MSAA_4X
#include "aa\msaa_resolve.hlsli"