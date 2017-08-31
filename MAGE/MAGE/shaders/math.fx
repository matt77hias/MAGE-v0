//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

float3 BiasX2(float3 x) {
	return 2.0f * x - 1.0f;
}

float3 InverseBiasX2(float3 x) {
	return 0.5f * x + 0.5f;
}

float NDCZToViewZ(float p_ndc_z, float2 projection_values) {
	return projection_values.x / (p_ndc_z + projection_values.y);
}

float3 NDCToView(float3 p_ndc, float4 projection_values) {
	const float depth = NDCZToViewZ(p_ndc.z, projection_values.zw);
	return float3(p_ndc.xy * projection_values.xy, 1.0f) * depth;
}