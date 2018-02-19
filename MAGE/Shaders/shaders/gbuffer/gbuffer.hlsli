//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// DISABLE_BASE_COLOR_TEXTURE               | not defined
// DISABLE_MATERIAL_TEXTURE                 | not defined
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
	const float2 material = GetMaterialParameters(input.tex_material);
	// Obtain the surface normal expressed in world space.
	const float3 n_world  = GetNormal(input.p_world, input.n_world,
									  input.tex_geometry);

	OMInputDeferred output;
	#pragma warning( push )
	#pragma warning( disable : 3578 ) // Partial initialization.
	// Store the base color of the material.
	output.base_color.xyz = base_color.xyz;
	// Store the material parameters [roughness, metalness] of the material.
	output.material.xy    = material;
	// Pack and store the normal.
	output.n.xyz          = PackNormal(n_world);
	#pragma warning( pop )
	
	return output;
}