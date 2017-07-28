//-----------------------------------------------------------------------------
// Requires global variable: Ns
// Requires global variable: material_param1
// Requires global variable: material_param2
// Requires global variable: material_param3
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

float SchlickFresnel(float f0, float v_dot_h) {
	// Schlick's approximation for Fresnel term.
	return f0 + (1.0f - f0) * v_dot_h * v_dot_h * v_dot_h * v_dot_h * v_dot_h;
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

// Calculates the (specular) Ward BRDF (independent of ks).
float WardBRDF(float3 n, float3 l, float3 v) {
	const float a1 = dot(n, l) * dot(n, v);
	if (a1 <= 0.0f) {
		return 0.0f;
	}

	const float3 h = HalfDirection(l, v);
	const float cos_theta = dot(n, h);
	const float tan_theta = tan(acos(cos_theta));
	const float a2 = tan_theta / material_param1;
	return rsqrt(a1) * exp(-a2 * a2) / (4.0f * material_param1 * material_param1);
}

// Calculates the (specular) Ward-Duer BRDF (independent of ks).
float WardDuerBRDF(float3 n, float3 l, float3 v) {
	const float a1 = dot(n, l) * dot(n, v);
	if (a1 <= 0.0f) {
		return 0.0f;
	}

	const float3 h = HalfDirection(l, v);
	const float cos_theta = dot(n, h);
	const float tan_theta = tan(acos(cos_theta));
	const float a2 = tan_theta / material_param1;
	return exp(-a2 * a2) / (a1 * 4.0f * material_param1 * material_param1);
}

// Calculates the (specular) Cook-Torrance BRDF (independent of ks).
float CookTorranceBRDF(float3 n, float3 l, float3 v) {
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

	const float tan_theta = tan(acos(n_dot_h));
	const float a3 = tan_theta / material_param2;
	const float D = exp(-a3 * a3) / (material_param2 * material_param2 * n_dot_h * n_dot_h * n_dot_h * n_dot_h);

	return D * G * SchlickFresnel(material_param3, v_dot_h) / a1;
}