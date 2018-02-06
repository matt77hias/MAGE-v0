//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "forward\forward_input.hlsli"
#include "transform\transform.hlsli"

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
GSInputPositionNormalTexture VS(VSInputPositionNormalTexture input) {
	return Transform(input, g_object_to_view, (float3x3)g_normal_to_view, 
					 g_texture_transform);
}
