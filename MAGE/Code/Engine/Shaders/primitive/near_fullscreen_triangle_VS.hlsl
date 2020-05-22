//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "primitive\fullscreen_triangle.hlsli"

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------

// Number of vertices: 3
// Topology: D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST

float4 VS(uint vertex_id : SV_VertexID) : SV_POSITION {
	return NearFullScreenTriangleNDC(vertex_id);
}