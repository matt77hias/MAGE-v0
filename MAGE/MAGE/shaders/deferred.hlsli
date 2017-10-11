//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "deferred_input.hlsli"
#include "lighting.hlsli"

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(PSInputNDCPosition input) : SV_Target {

	// Load the depth from the GBuffer depth texture.
	const float  depth      = g_depth_texture[input.p.xy];
	// Obtain the NDC space coodinates.
	const float3 p_ndc      = float3(input.p_ndc, depth);
	// Obtain the view space coodinates.
	const float3 p_view     = NDCtoView(p_ndc, g_projection_values);

	// Load the normal from the GBuffer normal texture.
	const float3 normal     = g_normal_texture[input.p.xy];
	// Unpack the view-space normal: [0,1] -> [-1,1]
	const float3 n_view     = UnpackNormal(normal);

	// Load the base color from the GBuffer base color texture.
	const float3 base_color = g_base_color_texture[input.p.xy].xyz;

	// Load the material data the GBuffer material texture.
	const float2 material   = g_material_texture[input.p.xy].xy;
	// Unpack the roughness of the material.
	const float  roughness  = material.x;
	// Unpack the metalness of the material.
	const float  metalness  = material.y;
	
	// Calculate the pixel radiance.
	const float3 L = BRDFShading(p_view, n_view, 
		                         base_color, roughness, metalness);

	return float4(L, 1.0f);
}