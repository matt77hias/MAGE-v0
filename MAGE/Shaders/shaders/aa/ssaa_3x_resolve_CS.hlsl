//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
// [numthreads(9, 8, 8)] = 576
#define SSAA 3
#define GROUP_SIZE GROUP_SIZE_SSAA_3X
#include "aa\ssaa_resolve.hlsli"