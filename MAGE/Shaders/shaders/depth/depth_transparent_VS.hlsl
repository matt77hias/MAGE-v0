//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "depth\depth_input.hlsli"

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
PSInputTexture VS(VSInputPositionNormalTexture input) {
	PSInputTexture output;
	output.p   = Transform(input.p,
						   g_object_to_world,
						   g_world_to_camera2,
						   g_camera2_to_projection2);
	output.tex = Transform(input.tex, g_texture_transform);
	return output;
}