//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

// Calculates the dot product of two unit vectors and clamps negative values to 0. 
float sat_dot(float3 x, float3 y) {
	return saturate(dot(x, y));
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

// Calculates the Lambertian BRDFxCos (independent of Kd).
float LambertianBRDFxCos(float3 n, float3 l) {
	return sat_dot(n, l);
}

// Calculates the (specular) Phong BRDFxCos intensity.
float PhongBRDFxCos(float3 n, float3 l, float3 v, float Ns) {
	// dot(r, v)^Ns / dot(n, l) * dot(n, l)
	const float3 r = ReflectedDirection(n, l);
	const float r_dot_v = sat_dot(r, v);
	return pow(r_dot_v, Ns);
}

// Calculates the (specular) Modified Phong BRDFxCos intensity.
float ModifiedPhongBRDFxCos(float3 n, float3 l, float3 v, float Ns) {
	// dot(r, v)^Ns * (Ns+2)/2 * dot(n, l)
	const float n_dot_l = sat_dot(n, l);
	return PhongBRDFxCos(n, l, v, Ns) * (0.5f * Ns + 1.0f) * n_dot_l;
}

// Calculates the (specular) Blinn-Phong BRDFxCos intensity.
float BlinnPhongBRDFxCos(float3 n, float3 l, float3 v, float Ns) {
	// dot(n, h)^Ns / dot(n, l) * dot(n, l)
	const float3 h = HalfDirection(l, v);
	const float n_dot_h = sat_dot(n, h);
	return pow(n_dot_h, Ns);
}

// Calculates the (specular) Modified Blinn-Phong BRDFxCos intensity.
float ModifiedBlinnPhongBRDFxCos(float3 n, float3 l, float3 v, float Ns) {
	// dot(n, h)^Ns * dot(n, l)
	const float n_dot_l = sat_dot(n, l);
	return BlinnPhongBRDFxCos(n, l, v, Ns) * n_dot_l;
}
	
// Calculates the (specular) Ward BRDFxCos intensity.
float WardBRDFxCos(float3 n, float3 l, float3 v, float alpha) {
	const float n_dot_l = sat_dot(n, l);
	const float n_dot_v = sat_dot(n, v);
	if (n_dot_l * n_dot_v == 0) {
		return 0.0f;
	}

	const float3 h = HalfDirection(l, v);
	const float n_dot_h = dot(n, h);
	const float n_dot_h2 = n_dot_h * n_dot_h;
	const float t2 = 1.0 - 1.0 / n_dot_h2;
	const float a2 = alpha * alpha;

	return sqrt(n_dot_l / n_dot_v) * exp(t2 / a2) / (4.0f * a2);
}

// Calculates the (specular) Ward-Duer BRDFxCos intensity.
float WardDuerBRDFxCos(float3 n, float3 l, float3 v, float alpha) {
	const float n_dot_l = sat_dot(n, l);
	const float n_dot_v = sat_dot(n, v);
	if (n_dot_l * n_dot_v == 0) {
		return 0.0f;
	}

	const float3 h = HalfDirection(l, v);
	const float n_dot_h = dot(n, h);
	const float n_dot_h2 = n_dot_h * n_dot_h;
	const float t2 = 1.0 - 1.0 / n_dot_h2;
	const float a2 = alpha * alpha;

	return exp(t2 / a2) / (n_dot_v * 4.0f * a2);
}

float F_Schlick(float R0, float v_dot_h) {
	// Schlick's approximation for Fresnel term.
	const float a = 1.0f - v_dot_h;
	return R0 + (1.0f - R0) * a * a * a * a * a;
}

float D_Beckmann(float m, float n_dot_h) {
	const float n_dot_h2 = n_dot_h * n_dot_h;
	const float t2 = 1.0 - 1.0 / n_dot_h2;
	const float m2 = m * m;
	return exp(t2 / m2) / (m2 * n_dot_h2 * n_dot_h2);
}

// Calculates the (specular) Cook-Torrance BRDFxCos intensity.
float CookTorranceBRDFxCos(float3 n, float3 l, float3 v, float m, float R0) {
	const float n_dot_l = sat_dot(n, l);
	const float n_dot_v = sat_dot(n, v);
	if (n_dot_l * n_dot_v == 0) {
		return 0.0f;
	}
	
	const float3 h = HalfDirection(l, v);
	const float n_dot_h = dot(n, h);
	const float v_dot_h = dot(v, h);
	
	const float a = n_dot_h / v_dot_h;
	const float G = min(1.0f, 2.0f * min(a * n_dot_v, a * n_dot_l));
	const float D = D_Beckmann(m, n_dot_h);
	const float F = F_Schlick(R0, v_dot_h);

	return G * D * F / n_dot_v;
}