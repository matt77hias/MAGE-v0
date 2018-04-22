//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// DISABLE_TEXTURE_BASE_COLOR               | not defined
// DISABLE_TEXTURE_MATERIAL                 | not defined
// DISABLE_TSNM                             | not defined
// MSAA_AS_SSAA                             | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "forward\forward_input.hlsli"

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
#ifdef MSAA_AS_SSAA
OMInputDeferred PS(PSInputPositionNormalTexture input, 
				   uint index : SV_SampleIndex) {
#else  // MSAA_AS_SSAA
OMInputDeferred PS(PSInputPositionNormalTexture input) {
#endif // MSAA_AS_SSAA

	// Obtain the base color of the material.
	const float4 base_color = GetMaterialBaseColor(input.tex_material);

	clip(base_color.w - TRANSPARENCY_THRESHOLD);

	// Obtain the material parameters [roughness, metalness] of the material.
	const float2 material_params = GetMaterialParameters(input.tex_material);
	// Obtain the surface normal expressed in world space.
	const float3 n_world = GetNormal(input.p_world, input.n_world, 
		                             input.tex_geometry);

	OMInputDeferred output;
	// Store the base color of the material.
	output.base_color  = float4(base_color.xyz, 1.0f);
	#pragma warning( push )
	#pragma warning( disable : 3578 ) // Partial initialization.
	// Store the material parameters [roughness, metalness] of the material.
	output.material.xy = material_params;
	// Pack and store the normal.
	output.n.xy        = NORMAL_ENCODE_FUNCTION(n_world);
	#pragma warning( pop )
	
	return output;
}