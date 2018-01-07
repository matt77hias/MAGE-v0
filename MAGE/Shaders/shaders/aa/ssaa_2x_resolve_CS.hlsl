//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
// [numthreads(4, 16, 16)] = 1024
#define SSAA 2
#define GROUP_SIZE GROUP_SIZE_SSAA_2X
#include "aa\ssaa_resolve.hlsli"