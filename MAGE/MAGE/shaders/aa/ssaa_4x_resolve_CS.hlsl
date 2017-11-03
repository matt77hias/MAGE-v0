//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
// [numthreads(16, 8, 8)] = 1024
#define SSAA 4
#define GROUP_SIZE GROUP_SIZE_SSAA_4X
#include "aa\ssaa_resolve.hlsli"