//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
// [numthreads(2, 16, 16)] = 512
#define MSAA 2
#define GROUP_SIZE GROUP_SIZE_MSAA_4X
#include "aa\msaa_resolve.hlsli"