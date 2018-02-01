//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "forward\forward_input.hlsli"
#include "transform\transform.hlsli"

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
PSInputPositionNormalTexture VS(VSInputPositionNormalTexture input) {
	return Transform(input, g_object_to_view, g_view_to_voxel, 
		             (float3x3)g_normal_to_view, g_texture_transform);
}
