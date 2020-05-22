//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "depth\depth_input.hlsli"

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
float4 VS(VSInputPositionNormalTexture input) : SV_Position {
    return Transform(input.p,
	                 g_object_to_world,
					 g_world_to_camera2,
					 g_camera2_to_projection2);
}
