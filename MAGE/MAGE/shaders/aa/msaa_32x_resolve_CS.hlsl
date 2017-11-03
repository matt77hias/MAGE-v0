//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
// [numthreads(32, 4, 4)] = 512
#define MSAA 32
#define GROUP_SIZE GROUP_SIZE_MSAA_32X
#include "aa\msaa_resolve.hlsli"