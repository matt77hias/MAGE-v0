#ifndef MAGE_HEADER_BRDF
#define MAGE_HEADER_BRDF

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

/**
 Calculates the dot product of two given unit vectors and clamps negative 
 values to 0.

 @pre			@a x is normalized.
 @pre			@a y is normalized.
 @param[in]		x
				The first unit vector.
 @param[in]		y
				The second unit vector.
 @return		The dot product of the given unit vectors clamped between 0 
				and 1 (i.e. clamped cosine).
 */
float sat_dot(float3 x, float3 y) {
	return saturate(dot(x, y));
}

/**
 Calculates the reflected direction of the given light direction about the 
 given normal.

 @pre			@a n is normalized.
 @pre			@a l is normalized.
 @param[in]		n
				The surface normal.
 @param[in]		l
				The light (hit-to-light) direction.
 @return		The normalized reflected vector of the given light direction 
				about the given normal direction.
*/
float3 ReflectedDirection(float3 n, float3 l) {
	return reflect(-l, n);
}

/**
 Calculates the half direction between the given light and view direction.

 @pre			@a l is normalized.
 @pre			@a v is normalized.
 @param[in]		l
				The light (hit-to-light) direction.
 @param[in]		v
				The view (hit-to-eye) direction.
 @return		The normalized half direction between the given light and view 
				direction.
*/
float3 HalfDirection(float3 l, float3 v) {
	// l+v / ||l+v||
	return normalize(l + v);
}

/**
 Calculates the Lambertian BRDFxCos intensity
(independent of the diffuse reflectivity).

 @pre			@a n is normalized.
 @pre			@a l is normalized.
 @param[in]		n
				The surface normal.
 @param[in]		l
				The light (hit-to-light) direction.
 @return		the Lambertian BRDFxCos intensity
				(independent of the diffuse reflectivity).
 */
float LambertianBRDFxCos(float3 n, float3 l) {
	return sat_dot(n, l);
}

/**
 Calculates the Phong BRDFxCos specular intensity
 (independent of the specular reflectivity).

 @pre			@a n is normalized.
 @pre			@a l is normalized.
 @pre			@a v is normalized.
 @param[in]		n
				The surface normal.
 @param[in]		l
				The light (hit-to-light) direction.
 @param[in]		v
				The view (hit-to-eye) direction.
 @param[in]		Ns
				The specular/shininess exponent of the material.
 @return		the Phong BRDFxCos specular intensity
				(independent of the specular reflectivity).
 */
float PhongBRDFxCos(float3 n, float3 l, float3 v, float Ns) {
	// dot(r, v)^Ns / dot(n, l) * dot(n, l)
	const float3 r = ReflectedDirection(n, l);
	const float r_dot_v = sat_dot(r, v);
	return pow(r_dot_v, Ns);
}

/**
 Calculates the Modified Phong BRDFxCos specular intensity
 (independent of the specular reflectivity).

 @pre			@a n is normalized.
 @pre			@a l is normalized.
 @pre			@a v is normalized.
 @param[in]		n
				The surface normal.
 @param[in]		l
				The light (hit-to-light) direction.
 @param[in]		v
				The view (hit-to-eye) direction.
 @param[in]		Ns
				The specular/shininess exponent of the material.
 @return		the Modified Phong BRDFxCos specular intensity
				(independent of the specular reflectivity).
 */
float ModifiedPhongBRDFxCos(float3 n, float3 l, float3 v, float Ns) {
	// dot(r, v)^Ns * (Ns+2)/2 * dot(n, l)
	const float n_dot_l = sat_dot(n, l);
	return PhongBRDFxCos(n, l, v, Ns) * (0.5f * Ns + 1.0f) * n_dot_l;
}

/**
 Calculates the Blinn-Phong BRDFxCos specular intensity
 (independent of the specular reflectivity).

 @pre			@a n is normalized.
 @pre			@a l is normalized.
 @pre			@a v is normalized.
 @param[in]		n
				The surface normal.
 @param[in]		l
				The light (hit-to-light) direction.
 @param[in]		v
				The view (hit-to-eye) direction.
 @param[in]		Ns
				The specular/shininess exponent of the material.
 @return		the Blinn-Phong BRDFxCos specular intensity
				(independent of the specular reflectivity).
 */
float BlinnPhongBRDFxCos(float3 n, float3 l, float3 v, float Ns) {
	// dot(n, h)^Ns / dot(n, l) * dot(n, l)
	const float3 h = HalfDirection(l, v);
	const float n_dot_h = sat_dot(n, h);
	return pow(n_dot_h, Ns);
}

/**
 Calculates the Modified Blinn-Phong BRDFxCos specular intensity
 (independent of the specular reflectivity).

 @pre			@a n is normalized.
 @pre			@a l is normalized.
 @pre			@a v is normalized.
 @param[in]		n
				The surface normal.
 @param[in]		l
				The light (hit-to-light) direction.
 @param[in]		v
				The view (hit-to-eye) direction.
 @param[in]		Ns
				The specular/shininess exponent of the material.
 @return		the Modified Blinn-Phong BRDFxCos specular intensity
				(independent of the specular reflectivity).
 */
float ModifiedBlinnPhongBRDFxCos(float3 n, float3 l, float3 v, float Ns) {
	// dot(n, h)^Ns * dot(n, l)
	const float n_dot_l = sat_dot(n, l);
	return BlinnPhongBRDFxCos(n, l, v, Ns) * n_dot_l;
}
	
/**
 Calculates the Ward BRDFxCos specular intensity
 (independent of the specular reflectivity).

 @pre			@a n is normalized.
 @pre			@a l is normalized.
 @pre			@a v is normalized.
 @param[in]		n
				The surface normal.
 @param[in]		l
				The light (hit-to-light) direction.
 @param[in]		v
				The view (hit-to-eye) direction.
 @param[in]		alpha
				The isotropic specular lobe width of the material.
 @return		the Ward BRDFxCos specular intensity
				(independent of the specular reflectivity).
 */
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

/**
 Calculates the Ward-Duer BRDFxCos specular intensity
 (independent of the specular reflectivity).

 @pre			@a n is normalized.
 @pre			@a l is normalized.
 @pre			@a v is normalized.
 @param[in]		n
				The surface normal.
 @param[in]		l
				The light (hit-to-light) direction.
 @param[in]		v
				The view (hit-to-eye) direction.
 @param[in]		alpha
				The isotropic specular lobe width of the material.
 @return		the Ward-Duer BRDFxCos specular intensity
				(independent of the specular reflectivity).
 */
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

/**
 Calculates the Schlick approximation of the Fresnel reflectance.

 @param[in]		R0
				The reflection coefficient of the material.
 @param[in]		v_dot_h
				The cosine of the angle between the view 
				and half direction.
 @return		The Fresnel reflectance.
 */
float F_Schlick(float R0, float v_dot_h) {
	// Schlick's approximation for Fresnel term.
	const float a = 1.0f - v_dot_h;
	return R0 + (1.0f - R0) * a * a * a * a * a;
}

/**
 Calculates the Beckmann microfacet distribution.

 @param[in]		m
				The roughness of the material.
 @param[in]		n_dot_h
				The cosine of the angle between the normal 
				and half direction.
 @return		The Beckmann microfacet distribution.
 */
float D_Beckmann(float m, float n_dot_h) {
	const float n_dot_h2 = n_dot_h * n_dot_h;
	const float t2 = 1.0 - 1.0 / n_dot_h2;
	const float m2 = m * m;
	return exp(t2 / m2) / (m2 * n_dot_h2 * n_dot_h2);
}

/**
 Calculates the Cook-Torrance BRDFxCos specular intensity
 (independent of the specular reflectivity).

 @pre			@a n is normalized.
 @pre			@a l is normalized.
 @pre			@a v is normalized.
 @param[in]		n
				The surface normal.
 @param[in]		l
				The light (hit-to-light) direction.
 @param[in]		v
				The view (hit-to-eye) direction.
 @param[in]		m
				The roughness of the material.
 @param[in]		R0
				The reflection coefficient of the material.
 @return		the Cook-Torrance BRDFxCos specular intensity
				(independent of the specular reflectivity).
 */
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

#endif // MAGE_HEADER_BRDF