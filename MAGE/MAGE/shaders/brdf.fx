//-----------------------------------------------------------------------------
// Requires global variable: Ns
//-----------------------------------------------------------------------------

// Calculates the dot product of two vectors and clamp negative values to 0. 
float max_dot(float3 x, float3 y) {
	return max(0.0f, dot(x, y));
}

// Calculates the reflected direction of the given l about the given n.
float3 ReflectedDirection(float3 n, float3 l) {
	return reflect(-l, n);
}

// Calculates the half direction between the given l and given v.
float3 HalfDirection(float3 l, float3 v) {
	// l+v / ||l+v||
	return normalize(l + v);
}

// Calculates the Lambertian BRDF (independent of kd).
float LambertianBRDF(float3 n, float3 l) {
	return max_dot(n, l);
}

// Calculates the (specular) Phong BRDF (independent of ks).
float PhongBRDF(float3 n, float3 l, float3 v) {
	// dot(r, v)^Ns / dot(n, l)
	const float n_dot_l = dot(n, l);
	if (n_dot_l <= 0.0f) {
		return 0.0f;
	}
	const float3 r = ReflectedDirection(n, l);
	return pow(max_dot(r, v), Ns) / n_dot_l;
}

// Calculates the (specular) Modified Blinn-Phong BRDF (independent of ks).
float ModifiedBlinnPhongBRDF(float3 n, float3 l, float3 v) {
	// dot(n, h)^Ns
	const float3 h = HalfDirection(l, v);
	return pow(max_dot(n, h), Ns);
}

// Calculates the (specular) Modified Phong BRDF (independent of ks).
float ModifiedPhongBRDF(float3 n, float3 l, float3 v) {
	// dot(n, h)^Ns * (Ns+2)/2
	return ModifiedBlinnPhongBRDF(n, l, v) * (Ns + 2.0f) / 2.0f;
}

// Calculates the (specular) Blinn-Phong BRDF (independent of ks).
float BlinnPhongBRDF(float3 n, float3 l, float3 v) {
	// dot(n, h)^Ns / dot(n, l)
	const float n_dot_l = dot(n, l);
	if (n_dot_l <= 0.01f) { // Prevents flickering.
		return 0.0f;
	}
	return ModifiedBlinnPhongBRDF(n, l, v) / n_dot_l;
}