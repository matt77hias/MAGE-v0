//-----------------------------------------------------------------------------
// Requires global variable: normal_texture_map
// Requires global variable: texture_sampler
// Requires global variable: object_to_view_inverse_transpose
//-----------------------------------------------------------------------------

// Perturbs the given normal.
float3 TangentSpaceNormalMapping_PerturbNormal(float3 p, float3 n, float2 tex) {
	// Calculates the edge differences.
	const float3 dp_dj = ddx(p);
	const float3 dp_di = ddy(p);
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

	float3 coefficients = normal_texture_map.Sample(texture_sampler, tex).xyz;
	coefficients = 2.0f * coefficients - 1.0f;
	return normalize(mul(coefficients, TBN));
}

// Perturbs the given normal.
float3 ObjectSpaceNormalMapping_PerturbNormal(float2 tex) {
	float3 coefficients = normal_texture_map.Sample(texture_sampler, tex).xyz;
	coefficients = 2.0f * coefficients - 1.0f;
	return normalize(mul(coefficients, (float3x3)object_to_view_inverse_transpose));
}