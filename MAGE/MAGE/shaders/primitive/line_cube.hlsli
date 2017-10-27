#ifndef MAGE_HEADER_LINE_CUBE
#define MAGE_HEADER_LINE_CUBE

// Number of vertices: 24
// Topology: D3D11_PRIMITIVE_TOPOLOGY_LINELIST
//
// v0: [-0.5, -0.5, -0.5]
// v1: [-0.5, -0.5,  0.5]
// v2: [-0.5,  0.5, -0.5]
// v3: [-0.5,  0.5,  0.5]
// v4: [ 0.5, -0.5, -0.5]
// v5: [ 0.5, -0.5,  0.5]
// v6: [ 0.5,  0.5, -0.5]
// v7: [ 0.5,  0.5,  0.5]
//
// e0:  [v0, v1]
// e1:  [v0, v2]
// e2:  [v0, v4]
// e3:  [v1, v3]
// e4:  [v1, v5]
// e5:  [v2, v3]
// e6:  [v2, v6]
// e7:  [v3, v7]
// e8:  [v4, v5]
// e9:  [v4, v6]
// e10: [v5, v7]
// e11: [v6, v7]

/**
 The vertices of a line cube.
 */
static const float3 g_line_cube[24] = {
	float3(-0.5, -0.5, -0.5),
	float3(-0.5, -0.5,  0.5),
	float3(-0.5, -0.5, -0.5),
	float3(-0.5,  0.5, -0.5),
	float3(-0.5, -0.5, -0.5),
	float3( 0.5, -0.5, -0.5),
	float3(-0.5, -0.5,  0.5),
	float3(-0.5,  0.5,  0.5),
	float3(-0.5, -0.5,  0.5),
	float3( 0.5, -0.5,  0.5),
	float3(-0.5,  0.5, -0.5),
	float3(-0.5,  0.5,  0.5),
	float3(-0.5,  0.5, -0.5),
	float3( 0.5,  0.5, -0.5),
	float3(-0.5,  0.5,  0.5),
	float3( 0.5,  0.5,  0.5),
	float3( 0.5, -0.5, -0.5),
	float3( 0.5, -0.5,  0.5),
	float3( 0.5, -0.5, -0.5),
	float3( 0.5,  0.5, -0.5),
	float3( 0.5, -0.5,  0.5),
	float3( 0.5,  0.5,  0.5),
	float3( 0.5,  0.5, -0.5),
	float3( 0.5,  0.5,  0.5)
};

#endif // MAGE_HEADER_LINE_CUBE