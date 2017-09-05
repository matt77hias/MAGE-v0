#ifndef MAGE_HEADER_PRIMITIVES
#define MAGE_HEADER_PRIMITIVES

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

float4 FullScreenTriangleNDC(uint vertex_id) {
	// v0 = (-1,-1, 0)
	// v1 = (-1, 3, 0)
	// v2 = ( 3,-1, 0)
	const float x = (vertex_id / 2) * 4.0f - 1.0f;
	const float y = (vertex_id % 2) * 4.0f - 1.0f;
	return float4(x, y, 0.0f, 1.0f);
}

float2 FullScreenTriangleUV(uint vertex_id) {
	const float u =        (vertex_id / 2) * 2.0f;
	const float v = 1.0f - (vertex_id % 2) * 2.0f;
	return float2(u, v);
}

#endif // MAGE_HEADER_PRIMITIVES