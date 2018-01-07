//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
// [numthreads(8, 8, 8)] = 512
#define MSAA 8
#define GROUP_SIZE GROUP_SIZE_MSAA_8X
#include "aa\msaa_resolve.hlsli"