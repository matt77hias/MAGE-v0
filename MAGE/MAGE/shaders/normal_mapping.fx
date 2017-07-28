//-----------------------------------------------------------------------------
// Requires global variable: g_normal_texture
// Requires global variable: g_sampler
// Requires global variable: g_object_to_view_inverse_transpose
//-----------------------------------------------------------------------------

float3 BiasX2(float3 x) {
	return 2.0f * x - 1.0f;
}

float3 InverseBiasX2(float3 x) {
	return 0.5f * x + 0.5f;
}

// Returns the perturbed normal.
float3 TangentSpaceNormalMapping_PerturbNormal(float3 p, float3 n, float2 tex) {
	// Calculates the edge differences.
	const float3 dp_dj   = ddx(p);
	const float3 dp_di   = ddy(p);
	const float2 dtex_dj = ddx(tex);
	const float2 dtex_di = ddy(tex);

	// Solve the linear system of equations to obtain
	// the cotangents t and b.
	const float3 dp_di_ortho = cross(dp_di, n);
	const float3 dp_dj_ortho = cross(n, dp_dj);
	// t: gradient of texture coordinate u as a function of p.
	const float3 t = dtex_dj.x * dp_di_ortho + dtex_di.x * dp_dj_ortho;
	// b: gradient of texture coordinate v as a function of p.
	const float3 b = dtex_dj.y * dp_di_ortho + dtex_di.y * dp_dj_ortho;

	// Construct a scale-invariant frame.
	const float inv_det = rsqrt(max(dot(t, t), dot(b, b)));
	const float3x3 TBN = { t * inv_det, b * inv_det, n };

	const float3 coefficients = BiasX2(g_normal_texture.Sample(g_sampler, tex).xyz);
	return normalize(mul(coefficients, TBN));
}

// Returns the perturbed normal.
float3 ObjectSpaceNormalMapping_PerturbNormal(float2 tex) {
	const float3 coefficients = BiasX2(g_normal_texture.Sample(g_sampler, tex).xyz);
	return normalize(mul(coefficients, (float3x3)g_object_to_view_inverse_transpose));
}