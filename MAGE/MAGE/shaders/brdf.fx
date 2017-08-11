//-----------------------------------------------------------------------------
// Requires global variable: g_Ns
// Requires global variable: g_material_parameters
//-----------------------------------------------------------------------------

// Converts given cos_theta to tan_theta.
float cos_to_tan(float c) {
	return sqrt(1.0 / (c*c) - 1.0);
}

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

float F_Schlick(float f0, float v_dot_h) {
	// Schlick's approximation for Fresnel term.
	const float a = 1.0f - v_dot_h;
	return f0 + (1.0f - f0) * a * a * a * a * a;
}

float D_Beckmann(float m, float n_dot_h) {
	const float n_dot_h2 = n_dot_h * n_dot_h;
	const float t2 = 1.0 - 1.0 / n_dot_h2;
	const float m2 = m * m;
	return exp(t2 / m2) / (m2 * n_dot_h2 * n_dot_h2);
}

// Calculates the Lambertian BRDFxCos (independent of Kd).
float LambertianBRDFxCos(float3 n, float3 l) {
	return max_dot(n, l);
}

// Calculates the (specular) Phong BRDFxCos intensity.
float PhongBRDFxCos(float3 n, float3 l, float3 v) {
	// dot(r, v)^Ns / dot(n, l) * dot(n, l)
	const float3 r = ReflectedDirection(n, l);
	return pow(max_dot(r, v), g_Ns);
}

// Calculates the (specular) Modified Phong BRDFxCos intensity.
float ModifiedPhongBRDFxCos(float3 n, float3 l, float3 v) {
	// dot(r, v)^Ns * (Ns+2)/2 * dot(n, l)
	return PhongBRDFxCos(n, l, v) * (g_Ns + 2.0f) * 0.5f * max_dot(n, l);
}

// Calculates the (specular) Blinn-Phong BRDFxCos intensity.
float BlinnPhongBRDFxCos(float3 n, float3 l, float3 v) {
	// dot(n, h)^Ns / dot(n, l) * dot(n, l)
	const float3 h = HalfDirection(l, v);
	return pow(max_dot(n, h), g_Ns);
}

// Calculates the (specular) Modified Blinn-Phong BRDFxCos intensity.
float ModifiedBlinnPhongBRDFxCos(float3 n, float3 l, float3 v) {
	// dot(n, h)^Ns * dot(n, l)
	return BlinnPhongBRDFxCos(n, l, v) * max_dot(n, l);
}
	
// Calculates the (specular) Ward BRDFxCos intensity.
float WardBRDFxCos(float3 n, float3 l, float3 v) {
	const float n_dot_l = max_dot(n, l);
	const float n_dot_v = max_dot(n, v);
	if (n_dot_l * n_dot_v == 0) {
		return 0.0f;
	}

	const float3 h = HalfDirection(l, v);
	const float n_dot_h = dot(n, h);
	const float n_dot_h2 = n_dot_h * n_dot_h;
	const float t2 = 1.0 - 1.0 / n_dot_h2;
	const float a2 = g_material_parameters.x * g_material_parameters.x;

	return sqrt(n_dot_l / n_dot_v) * exp(t2 / a2) / (4.0f * a2);
}

// Calculates the (specular) Ward-Duer BRDFxCos intensity.
float WardDuerBRDFxCos(float3 n, float3 l, float3 v) {
	const float n_dot_l = max_dot(n, l);
	const float n_dot_v = max_dot(n, v);
	if (n_dot_l * n_dot_v == 0) {
		return 0.0f;
	}

	const float3 h = HalfDirection(l, v);
	const float n_dot_h = dot(n, h);
	const float n_dot_h2 = n_dot_h * n_dot_h;
	const float t2 = 1.0 - 1.0 / n_dot_h2;
	const float a2 = g_material_parameters.x * g_material_parameters.x;

	return exp(t2 / a2) / (n_dot_v * 4.0f * a2);
}

// Calculates the (specular) Cook-Torrance BRDFxCos intensity.
float CookTorranceBRDFxCos(float3 n, float3 l, float3 v) {
	const float n_dot_l = max_dot(n, l);
	const float n_dot_v = max_dot(n, v);
	if (n_dot_l * n_dot_v == 0) {
		return 0.0f;
	}
	
	const float3 h = HalfDirection(l, v);
	const float n_dot_h = dot(n, h);
	const float v_dot_h = dot(v, h);
	
	const float a = n_dot_h / v_dot_h;
	const float G = min(1.0f, 2.0f * min(a * n_dot_v, a * n_dot_l));
	const float D = D_Beckmann(g_material_parameters.y, n_dot_h);
	const float F = F_Schlick(g_material_parameters.z, v_dot_h);

	return G * D * F / n_dot_v;
}