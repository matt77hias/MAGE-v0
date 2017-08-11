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

float SchlickFresnel(float f0, float v_dot_h) {
	// Schlick's approximation for Fresnel term.
	return f0 + (1.0f - f0) * v_dot_h * v_dot_h * v_dot_h * v_dot_h * v_dot_h;
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
	const float n_dot_l = dot(n, l);
	const float n_dot_v = dot(n, v);
	const float a1 = n_dot_l * n_dot_v;
	if (a1 <= 0.0f) {
		return 0.0f;
	}

	const float3 h = HalfDirection(l, v);
	const float cos_theta = dot(n, h);
	const float tan_theta = cos_to_tan(cos_theta);
	const float a2 = tan_theta / g_material_parameters.x;
	return rsqrt(n_dot_v) * exp(-a2 * a2) / (4.0f * g_material_parameters.x * g_material_parameters.x);
}

// Calculates the (specular) Ward-Duer BRDFxCos intensity.
float WardDuerBRDFxCos(float3 n, float3 l, float3 v) {
	const float n_dot_l = dot(n, l);
	const float n_dot_v = dot(n, v);
	const float a1 = n_dot_l * n_dot_v;
	if (a1 <= 0.0f) {
		return 0.0f;
	}

	const float3 h = HalfDirection(l, v);
	const float cos_theta = dot(n, h);
	const float tan_theta = cos_to_tan(cos_theta);
	const float a2 = tan_theta / g_material_parameters.x;
	return exp(-a2 * a2) / (n_dot_v * 4.0f * g_material_parameters.x * g_material_parameters.x);
}

// Calculates the (specular) Cook-Torrance BRDFxCos intensity.
float CookTorranceBRDFxCos(float3 n, float3 l, float3 v) {
	const float n_dot_l = dot(n, l);
	const float n_dot_v = dot(n, v);
	const float a1 = n_dot_l * n_dot_v;
	if (a1 <= 0.0f) {
		return 0.0f;
	}
	
	const float3 h = HalfDirection(l, v);
	const float n_dot_h = dot(n, h);
	const float v_dot_h = dot(v, h);
	if (v_dot_h <= 0.0f) {
		return 0.0f;
	}

	const float a2 = 2.0f * n_dot_h / v_dot_h;
	const float G = min(1.0f, min(a2 * n_dot_v, a2 * n_dot_l));

	const float tan_theta = cos_to_tan(n_dot_h);
	const float a3 = tan_theta / g_material_parameters.y;
	const float D = exp(-a3 * a3) / (g_material_parameters.y * g_material_parameters.y * n_dot_h * n_dot_h * n_dot_h * n_dot_h);

	return D * G * SchlickFresnel(g_material_parameters.z, v_dot_h) / n_dot_v;
}