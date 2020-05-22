//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "primitive\cube.hlsli"
#include "transform\transform.hlsli"

//-----------------------------------------------------------------------------
// Geometry Shader
//-----------------------------------------------------------------------------
[maxvertexcount(14)]
void GS(point GSInputPositionColor input[1],
		inout TriangleStream< PSInputColor > output_stream) {

	const float4 color = input[0].color;

	[branch]
	if (0.0f != color.a) {
		for (uint i = 0u; i < 14u; ++i) {
			const float3 offset  = OffsettedUnitCube(i) * g_voxel_size;
			const float3 p_world = input[0].p_world + offset;

			PSInputColor output;
			output.p = Transform(p_world,
								 g_world_to_camera,
								 g_camera_to_projection);
			output.color = color;

			// Output a vertex.
			output_stream.Append(output);
		}

		// End the current triangle strip.
		output_stream.RestartStrip();
	}
}
