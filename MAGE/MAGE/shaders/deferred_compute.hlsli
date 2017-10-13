//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "deferred_input.hlsli"
#include "lighting.hlsli"

//-----------------------------------------------------------------------------
// UAVs
//-----------------------------------------------------------------------------
RW_TEXTURE_2D(g_output, float4, SLOT_UAV_IMAGE);

//-----------------------------------------------------------------------------
// Compute Shader
//-----------------------------------------------------------------------------

#ifndef GROUP_SIZE
#define GROUP_SIZE GROUP_SIZE_DEFAULT
#endif

[numthreads(GROUP_SIZE, GROUP_SIZE, 1)]
void CS(uint3 thread_id : SV_DispatchThreadID) {

	const float2 location = thread_id.xy;

	// Obtain the base color of the material.
	const float3 base_color = GetGBufferMaterialBaseColor(location);
	// Obtain the parameters of the material.
	const float2 material   = GetGBufferMaterialParameters(location);
	// Obtain the view-space normal.
	const float3 n_view     = GetGBufferNormal(location);
	// Obtain the view-space hit position.
	const float2 p_ndc_xy   = DispatchThreadIDtoNDC(location);
	const float3 p_view     = GetGBufferPosition(location, p_ndc_xy);

	// Calculate the pixel radiance.
	const float3 L = BRDFShading(p_view, n_view, 
		                         base_color, material.x, material.y);

	// Store the pixel color.
	g_output[location] = float4(L, 1.0f);
}