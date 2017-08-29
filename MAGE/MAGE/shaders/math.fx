//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

float3 BiasX2(float3 x) {
	return 2.0f * x - 1.0f;
}

float3 InverseBiasX2(float3 x) {
	return 0.5f * x + 0.5f;
}