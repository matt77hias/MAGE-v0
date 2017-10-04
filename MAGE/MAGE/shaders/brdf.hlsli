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
float F_Schlick_depracted(float R0, float v_dot_h) {
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
float D_Beckmann_depracted(float m, float n_dot_h) {
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
 @return		The Cook-Torrance BRDFxCos specular intensity
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
	const float D = D_Beckmann_depracted(m, n_dot_h);
	const float F = F_Schlick_depracted(R0, v_dot_h);

	return G * D * F / n_dot_v;
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Normal Distribution Function
//-----------------------------------------------------------------------------

/**
 Calculates the Beckmann Normal Distribution Function component.

 @param[in]		n_dot_h
				The clamped cosine of the half angle. The half angle is the 
				angle between the surface normal and the half direction between 
				the view (hit-to-eye) and light (hit-to-light) direction.
 @param[in]		alpha
				The alpha value which is equal to the square of the surface
				roughness.
 @return		The Beckmann Normal Distribution Function component.
 */
float D_Beckmann(float n_dot_h, float alpha) {
	//               1            [  n_dot_h^2 - 1  ]             1             [tan(theta_h)]^2
	// D:= -------------------- e^[-----------------] = -------------------- e^-[------------]
	//     pi alpha^2 n_dot_h^4   [n_dot_h^2 alpha^2]   pi alpha^2 n_dot_h^4    [   alpha    ]

	const float inv_alpha2   = 1.0f / sqr(alpha);
	const float n_dot_h2     = sqr(n_dot_h);
	const float inv_n_dot_h4 = 1.0f / sqr(n_dot_h2);
	const float t2           = SqrCosToSqrTan(n_dot_h2);

	return g_inv_pi * inv_alpha2 * inv_n_dot_h4 * exp(-t2 * inv_alpha2);
}

/**
 Calculates the Ward-Duer Normal Distribution Function component.

 @param[in]		n_dot_h
				The clamped cosine of the half angle. The half angle is the 
				angle between the surface normal and the half direction between 
				the view (hit-to-eye) and light (hit-to-light) direction.
 @param[in]		alpha
				The alpha value which is equal to the square of the surface
				roughness.
 @return		The Ward-Duer Normal Distribution Function component.
 */
float D_WardDuer(float n_dot_h, float alpha) {
	//         1        [  n_dot_h^2 - 1  ]        1        [tan(theta_h)]^2
	// D:= ---------- e^[-----------------] = ---------- e^-[------------]
	//     pi alpha^2   [n_dot_h^2 alpha^2]   pi alpha^2    [   alpha    ]
	
	const float inv_alpha2   = 1.0f / sqr(alpha);
	const float n_dot_h2     = sqr(n_dot_h);
	const float t2           = SqrCosToSqrTan(n_dot_h2);

	return g_inv_pi * inv_alpha2 * exp(-t2 * inv_alpha2);
}

/**
 Calculates the Blinn-Phong Normal Distribution Function component.

 @param[in]		n_dot_h
				The clamped cosine of the half angle. The half angle is the 
				angle between the surface normal and the half direction between 
				the view (hit-to-eye) and light (hit-to-light) direction.
 @param[in]		alpha
				The alpha value which is equal to the square of the surface
				roughness.
 @return		The Blinn-Phong Normal Distribution Function component.
 */
float D_BlinnPhong(float n_dot_h, float alpha) {
	//         1              [   2       ]   Ns + 2
	// D:= ---------- n_dot_h^[------- - 2] = ------ n_dot_h^Ns
	//     pi alpha^2         [alpha^2    ]    pi 2

	const float inv_alpha2 = 1.0f / sqr(alpha);
	const float Ns         = 2.0f * inv_alpha2 - 2.0f;

	return g_inv_pi * inv_alpha2 * pow(n_dot_h, Ns);
}

/**
 Calculates the Trowbridge-Reitz Normal Distribution Function component.

 @param[in]		n_dot_h
				The clamped cosine of the half angle. The half angle is the 
				angle between the surface normal and the half direction between 
				the view (hit-to-eye) and light (hit-to-light) direction.
 @param[in]		alpha
				The alpha value which is equal to the square of the surface
				roughness.
 @return		The Trowbridge-Reitz Normal Distribution Function component.
 */
float D_TrowbridgeReitz(float n_dot_h, float alpha) {
	//                  alpha^2                                      c
	// D:= ---------------------------------- = ---------------------------------------------
	//     pi (n_dot_h^2 (alpha^2 - 1) + 1)^2   (alpha^2 * cos(theta_h)^2 + sin(theta_h)^2)^2

	const float alpha2   = sqr(alpha);
	const float n_dot_h2 = sqr(n_dot_h);
	const float temp1    = n_dot_h2 * (alpha2 - 1.0f) + 1.0f;

	return g_inv_pi * alpha2 / (temp1 * temp1);
}

/**
 Calculates the GGX Normal Distribution Function component.

 @param[in]		n_dot_h
				The clamped cosine of the half angle. The half angle is the 
				angle between the surface normal and the half direction between 
				the view (hit-to-eye) and light (hit-to-light) direction.
 @param[in]		alpha
				The alpha value which is equal to the square of the surface
				roughness.
 @return		The GGX Normal Distribution Function component.
 */
float D_GGX(float n_dot_h, float alpha) {
	return D_TrowbridgeReitz(n_dot_h, alpha);
}

/**
 Calculates the GTR2 Normal Distribution Function component.

 @param[in]		n_dot_h
				The clamped cosine of the half angle. The half angle is the 
				angle between the surface normal and the half direction between 
				the view (hit-to-eye) and light (hit-to-light) direction.
 @param[in]		alpha
				The alpha value which is equal to the square of the surface
				roughness.
 @return		The GTR2 Normal Distribution Function component.
 */
float D_GTR2(float n_dot_h, float alpha) {
	return D_TrowbridgeReitz(n_dot_h, alpha);
}

/**
 Calculates the Berry Normal Distribution Function component.

 @param[in]		n_dot_h
				The clamped cosine of the half angle. The half angle is the 
				angle between the surface normal and the half direction between 
				the view (hit-to-eye) and light (hit-to-light) direction.
 @param[in]		alpha
				The alpha value which is equal to the square of the surface
				roughness.
 @return		The Berry Normal Distribution Function component.
 */
float D_Berry(float n_dot_h, float alpha) {
	//                      alpha^2 - 1                                          c
	// D:= --------------------------------------------- = -------------------------------------------
	//     log(alpha^2) pi (n_dot_h^2 (alpha^2 - 1) + 1)   (alpha^2 * cos(theta_h)^2 + sin(theta_h)^2)

	const float alpha2   = sqr(alpha);
	const float n_dot_h2 = sqr(n_dot_h);
	const float temp1    = n_dot_h2 * (alpha2 - 1.0f) + 1.0f;

	return (alpha >= 1.0f) 
		? g_inv_pi : g_inv_pi * (alpha2 - 1.0f) / (log(alpha2) * temp1);
}

/**
 Calculates the GTR1 Normal Distribution Function component.

 @param[in]		n_dot_h
				The clamped cosine of the half angle. The half angle is the 
				angle between the surface normal and the half direction between 
				the view (hit-to-eye) and light (hit-to-light) direction.
 @param[in]		alpha
				The alpha value which is equal to the square of the surface
				roughness.
 @return		The GTR1 Normal Distribution Function component.
 */
float D_GTR1(float n_dot_h, float alpha) {
	return D_Berry(n_dot_h, alpha);
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Partial Geometric Schadowing
//-----------------------------------------------------------------------------

/**
 Calculates the GGX partial Geometric Schadowing component.

 @param[in]		n_dot_vl
				The clamped cosine of the view angle. The view angle is the 
				angle between the surface normal and the view (hit-to-eye) 
				direction. Or the clamped cosine of the light angle. The light 
				angle is the angle between the surface normal and the light 
				(hit-to-light) direction.
 @param[in]		alpha
				The alpha value which is equal to the square of the surface
				roughness.
 @return		The GGX partial Geometric Schadowing component.
 */
float G1_GGX(float n_dot_vl, float alpha) {
	//                          2 n_dot_vl                                              2
	// G1 := --------------------------------------------------- = --------------------------------------------
	//       n_dot_vl + sqrt(alpha^2 + (1 - alpha^2) n_dot_vl^2)   1 + sqrt((alpha/n_dot_vl)^2 + (1 - alpha^2))

	const float alpha2    = sqr(alpha);
	const float n_dot_vl2 = sqr(n_dot_vl);

	return 2.0f * n_dot_vl / (n_dot_vl * sqrt(alpha2 + (1.0f - alpha2) * n_dot_vl2));
}

/**
 Calculates the Schlick partial Geometric Schadowing component.

 @param[in]		n_dot_vl
				The clamped cosine of the view angle. The view angle is the 
				angle between the surface normal and the view (hit-to-eye) 
				direction. Or the clamped cosine of the light angle. The light 
				angle is the angle between the surface normal and the light 
				(hit-to-light) direction.
 @param[in]		alpha
				The alpha value which is equal to the square of the surface
				roughness.
 @return		The Schlick-GGX partial Geometric Schadowing component.
 */
float G1_SchlickGGX(float n_dot_vl, float alpha) {
	//             n_dot_vl                      n_dot_vl
	// G1 := --------------------- = --------------------------------
	//       n_dot_vl (1 - k) + k    n_dot_vl (1 - alpha/2) + alpha/2

	const float k = 0.5f * alpha;

	return n_dot_vl / (n_dot_vl * (1.0f - k) + k);
}

/**
 Calculates the Beckmann partial Geometric Schadowing component.

 @param[in]		n_dot_vl
				The clamped cosine of the view angle. The view angle is the 
				angle between the surface normal and the view (hit-to-eye) 
				direction. Or the clamped cosine of the light angle. The light 
				angle is the angle between the surface normal and the light 
				(hit-to-light) direction.
 @param[in]		alpha
				The alpha value which is equal to the square of the surface
				roughness.
 @return		The Beckmann partial Geometric Schadowing component.
 */
float G1_Beckmann(float n_dot_vl, float alpha) {
	//                n_dot_vl
	// c  := --------------------------
	//       alpha sqrt(1 - n_dot_vl^2)
	//
	//         3.535 c + 2.181 c^2
	// G1 := ----------------------- (if c < 1.6) | 1 (otherwise)
	//       1 + 2.276 c + 2.577 c^2

	const float n_dot_vl2 = sqr(n_dot_vl);
	const float c         = n_dot_vl2 / (alpha * sqrt(1.0f - n_dot_vl2));
	const float c2        = sqr(c);

	return (c < 1.6) ? (3.535f * c + 2.8181f * c2) / (1.0f + 2.276 * c + 2.577 * c2) : 1.0f;
}

/**
 Calculates the Schlick-Beckmann partial Geometric Schadowing component.

 @param[in]		n_dot_vl
				The clamped cosine of the view angle. The view angle is the 
				angle between the surface normal and the view (hit-to-eye) 
				direction. Or the clamped cosine of the light angle. The light 
				angle is the angle between the surface normal and the light 
				(hit-to-light) direction.
 @param[in]		alpha
				The alpha value which is equal to the square of the surface
				roughness.
 @return		The Schlick-Beckmann partial Geometric Schadowing component.
 */
float G1_SchlickBeckmann(float n_dot_vl, float alpha) {
	//             n_dot_vl                               n_dot_vl
	// G1 := --------------------- = --------------------------------------------------
	//       n_dot_vl (1 - k) + k    n_dot_vl (1 - alpha sqrt(2/pi)) + alpha sqrt(2/pi)
	
	const float k = alpha * g_sqrt_2_inv_pi;

	return n_dot_vl / (n_dot_vl * (1.0f - k) + k);
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Geometric Schadowing
//-----------------------------------------------------------------------------

/**
 Calculates the Implicit Geometric Schadowing component.

 @param[in]		n_dot_v
				The clamped cosine of the view angle. The view angle is the 
				angle between the surface normal and the view (hit-to-eye) 
				direction.
 @param[in]		n_dot_l
				The clamped cosine of the light angle. The light angle is the 
				angle between the surface normal and the light (hit-to-light) 
				direction.
 @param[in]		n_dot_h
				The clamped cosine of the half angle. The half angle is the 
				angle between the surface normal and the half direction between 
				the view (hit-to-eye) and light (hit-to-light) direction.
 @param[in]		v_dot_h
				The clamped cosine of the difference angle. The difference 
				angle is the angle between the view (hit-to-eye) direction and 
				half direction and is the angle between the light 
				(hit-to-light) direction and half direction.
 @param[in]		alpha
				The alpha value which is equal to the square of the surface
				roughness.
 @return		The Implicit Geometric Schadowing component.
 */
float G_Implicit(float n_dot_v, float n_dot_l,
	float n_dot_h, float v_dot_h, float alpha) {
	// G := n_dot_v n_dot_l
	
	return n_dot_v * n_dot_l;
}

/**
 Calculates the Neumann Geometric Schadowing component.

 @param[in]		n_dot_v
				The clamped cosine of the view angle. The view angle is the 
				angle between the surface normal and the view (hit-to-eye) 
				direction.
 @param[in]		n_dot_l
				The clamped cosine of the light angle. The light angle is the 
				angle between the surface normal and the light (hit-to-light) 
				direction.
 @param[in]		n_dot_h
				The clamped cosine of the half angle. The half angle is the 
				angle between the surface normal and the half direction between 
				the view (hit-to-eye) and light (hit-to-light) direction.
 @param[in]		v_dot_h
				The clamped cosine of the difference angle. The difference 
				angle is the angle between the view (hit-to-eye) direction and 
				half direction and is the angle between the light 
				(hit-to-light) direction and half direction.
 @param[in]		alpha
				The alpha value which is equal to the square of the surface
				roughness.
 @return		The Neumann Geometric Schadowing component.
 */
float G_Neumann(float n_dot_v, float n_dot_l,
	float n_dot_h, float v_dot_h, float alpha) {
	//         n_dot_v n_dot_l
	// G := ---------------------
	//      max(n_dot_v, n_dot_l)

	return (n_dot_v * n_dot_l) / max(n_dot_v, n_dot_l);
}

/**
 Calculates the Kelemann Geometric Schadowing component.

 @param[in]		n_dot_v
				The clamped cosine of the view angle. The view angle is the 
				angle between the surface normal and the view (hit-to-eye) 
				direction.
 @param[in]		n_dot_l
				The clamped cosine of the light angle. The light angle is the 
				angle between the surface normal and the light (hit-to-light) 
				direction.
 @param[in]		n_dot_h
				The clamped cosine of the half angle. The half angle is the 
				angle between the surface normal and the half direction between 
				the view (hit-to-eye) and light (hit-to-light) direction.
 @param[in]		v_dot_h
				The clamped cosine of the difference angle. The difference 
				angle is the angle between the view (hit-to-eye) direction and 
				half direction and is the angle between the light 
				(hit-to-light) direction and half direction.
 @param[in]		alpha
				The alpha value which is equal to the square of the surface
				roughness.
 @return		The Kelemann Geometric Schadowing component.
 */
float G_Kelemann(float n_dot_v, float n_dot_l,
	float n_dot_h, float v_dot_h, float alpha) {
	//      n_dot_v n_dot_l
	// G := ---------------
	//          v_dot_h

	return (n_dot_v * n_dot_l) / v_dot_h;
}

/**
 Calculates the Cook-Torrance Geometric Schadowing component.

 @param[in]		n_dot_v
				The clamped cosine of the view angle. The view angle is the 
				angle between the surface normal and the view (hit-to-eye) 
				direction.
 @param[in]		n_dot_l
				The clamped cosine of the light angle. The light angle is the 
				angle between the surface normal and the light (hit-to-light) 
				direction.
 @param[in]		n_dot_h
				The clamped cosine of the half angle. The half angle is the 
				angle between the surface normal and the half direction between 
				the view (hit-to-eye) and light (hit-to-light) direction.
 @param[in]		v_dot_h
				The clamped cosine of the difference angle. The difference 
				angle is the angle between the view (hit-to-eye) direction and 
				half direction and is the angle between the light 
				(hit-to-light) direction and half direction.
 @param[in]		alpha
				The alpha value which is equal to the square of the surface
				roughness.
 @return		The Cook-Torrance Geometric Schadowing component.
 */
float G_CookTorrance(float n_dot_v, float n_dot_l,
	float n_dot_h, float v_dot_h, float alpha) {
	//         [   2 n_dot_h n_dot_v  2 n_dot_h n_dot_l]
	// G := min[1, -----------------, -----------------]
	//         [        v_dot_h           v_dot_h      ]

	const float temp1 = n_dot_h / v_dot_h;
	
	return min(1.0f, 2.0f * min(temp1 * n_dot_v, temp1 * n_dot_l));
}

/**
 Calculates the Smith GGX Geometric Schadowing component.

 @param[in]		n_dot_v
				The clamped cosine of the view angle. The view angle is the 
				angle between the surface normal and the view (hit-to-eye) 
				direction.
 @param[in]		n_dot_l
				The clamped cosine of the light angle. The light angle is the 
				angle between the surface normal and the light (hit-to-light) 
				direction.
 @param[in]		n_dot_h
				The clamped cosine of the half angle. The half angle is the 
				angle between the surface normal and the half direction between 
				the view (hit-to-eye) and light (hit-to-light) direction.
 @param[in]		v_dot_h
				The clamped cosine of the difference angle. The difference 
				angle is the angle between the view (hit-to-eye) direction and 
				half direction and is the angle between the light 
				(hit-to-light) direction and half direction.
 @param[in]		alpha
				The alpha value which is equal to the square of the surface
				roughness.
 @return		The Smith GGX Geometric Schadowing component.
 */
float G_Smith_GGX(float n_dot_v, float n_dot_l,
	float n_dot_h, float v_dot_h, float alpha) {

	return G1_GGX(n_dot_v, alpha) * G1_GGX(n_dot_l, alpha);
}

/**
 Calculates the Smith Schlick-GGX Geometric Schadowing component.

 @param[in]		n_dot_v
				The clamped cosine of the view angle. The view angle is the 
				angle between the surface normal and the view (hit-to-eye) 
				direction.
 @param[in]		n_dot_l
				The clamped cosine of the light angle. The light angle is the 
				angle between the surface normal and the light (hit-to-light) 
				direction.
 @param[in]		n_dot_h
				The clamped cosine of the half angle. The half angle is the 
				angle between the surface normal and the half direction between 
				the view (hit-to-eye) and light (hit-to-light) direction.
 @param[in]		v_dot_h
				The clamped cosine of the difference angle. The difference 
				angle is the angle between the view (hit-to-eye) direction and 
				half direction and is the angle between the light 
				(hit-to-light) direction and half direction.
 @param[in]		alpha
				The alpha value which is equal to the square of the surface
				roughness.
 @return		The Smith Schlick-GGX Geometric Schadowing component.
 */
float G_Smith_SchlickGGX(float n_dot_v, float n_dot_l,
	float n_dot_h, float v_dot_h, float alpha) {

	return G1_SchlickGGX(n_dot_v, alpha) * G1_SchlickGGX(n_dot_l, alpha);
}

/**
 Calculates the Smith Beckmann Geometric Schadowing component.

 @param[in]		n_dot_v
				The clamped cosine of the view angle. The view angle is the 
				angle between the surface normal and the view (hit-to-eye) 
				direction.
 @param[in]		n_dot_l
				The clamped cosine of the light angle. The light angle is the 
				angle between the surface normal and the light (hit-to-light) 
				direction.
 @param[in]		n_dot_h
				The clamped cosine of the half angle. The half angle is the 
				angle between the surface normal and the half direction between 
				the view (hit-to-eye) and light (hit-to-light) direction.
 @param[in]		v_dot_h
				The clamped cosine of the difference angle. The difference 
				angle is the angle between the view (hit-to-eye) direction and 
				half direction and is the angle between the light 
				(hit-to-light) direction and half direction.
 @param[in]		alpha
				The alpha value which is equal to the square of the surface
				roughness.
 @return		The Smith Beckmann Geometric Schadowing component.
 */
float G_Smith_Beckmann(float n_dot_v, float n_dot_l,
	float n_dot_h, float v_dot_h, float alpha) {

	return G1_Beckmann(n_dot_v, alpha) * G1_Beckmann(n_dot_l, alpha);
}

/**
 Calculates the Smith Schlick-Beckmann Geometric Schadowing component.

 @param[in]		n_dot_v
				The clamped cosine of the view angle. The view angle is the 
				angle between the surface normal and the view (hit-to-eye) 
				direction.
 @param[in]		n_dot_l
				The clamped cosine of the light angle. The light angle is the 
				angle between the surface normal and the light (hit-to-light) 
				direction.
 @param[in]		n_dot_h
				The clamped cosine of the half angle. The half angle is the 
				angle between the surface normal and the half direction between 
				the view (hit-to-eye) and light (hit-to-light) direction.
 @param[in]		v_dot_h
				The clamped cosine of the difference angle. The difference 
				angle is the angle between the view (hit-to-eye) direction and 
				half direction and is the angle between the light 
				(hit-to-light) direction and half direction.
 @param[in]		alpha
				The alpha value which is equal to the square of the surface
				roughness.
 @return		The Smith Schlick-Beckmann Geometric Schadowing component.
 */
float G_Smith_SchlickBeckmann(float n_dot_v, float n_dot_l,
	float n_dot_h, float v_dot_h, float alpha) {

	return G1_SchlickBeckmann(n_dot_v, alpha) * G1_SchlickBeckmann(n_dot_l, alpha);
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Fresnel
//-----------------------------------------------------------------------------

/**
 Calculates the None Fresnel component.

 @param[in]		v_dot_h
				The clamped cosine of the difference angle. The difference 
				angle is the angle between the view (hit-to-eye) direction and 
				half direction and is the angle between the light 
				(hit-to-light) direction and half direction.
 @param[in]		F0
				The reflectance at normal incidence.
 @return		The None Fresnel component.
 */
float F_None(float v_dot_h, float F0) {
	// F := F0

	return F0;
}

/**
 Calculates the Schlick Fresnel component.

 @param[in]		v_dot_h
				The clamped cosine of the difference angle. The difference 
				angle is the angle between the view (hit-to-eye) direction and 
				half direction and is the angle between the light 
				(hit-to-light) direction and half direction.
 @param[in]		F0
				The reflectance at normal incidence.
 @return		The Schlick Fresnel component.
 */
float F_Schlick(float v_dot_h, float F0) {
	// F := F0 + (1 - F0) (1 - v_dot_h)^5

	const float m = (1.0f - v_dot_h);
	const float m2 = sqr(m);
	const float m5 = sqr(m2) * m;
	
	return lerp(F0, 1.0f, m5);
}

/**
 Calculates the Cook-Torrance Fresnel component.

 @param[in]		v_dot_h
				The clamped cosine of the difference angle. The difference 
				angle is the angle between the view (hit-to-eye) direction and 
				half direction and is the angle between the light 
				(hit-to-light) direction and half direction.
 @param[in]		F0
				The reflectance at normal incidence.
 @return		The Cook-Torrance Fresnel component.
 */
float F_CookTorrance(float v_dot_h, float F0) {
	// c   := v_dot_h
	//
	//        1 + sqrt(F0)
	// eta := ------------
	//        1 - sqrt(F0)
	//
	// g   := sqrt(eta^2 + c^2 - 1)
    //
	//        1 [g - c]^2 [    [(g + c) (c - 1)]^2]
	// F   := - [-----]   [1 + [---------------]  ]
	//        2 [g + c]   [    [(g - c) (c + 1)]  ]

	const float sqrt_F0  = sqrt(F0);
	const float eta      = (1.0f + sqrt_F0) / (1.0f - sqrt_F0);
	const float eta2     = sqr(eta);
	const float v_dot_h2 = sqr(v_dot_h);
	const float g        = sqrt(eta2 + v_dot_h2 - 1.0f);
	const float g1       = g + v_dot_h;
	const float g2       = g - v_dot_h;

	return 0.5f * sqr(g2 / g1) * (1.0f + sqr((g1 * (v_dot_h - 1.0f)) / (g2 * (v_dot_h + 1.0f))));
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Cook-Torrance BRDFs
//-----------------------------------------------------------------------------

#ifndef BRDF_F_COMPONENT
#define BRDF_F_COMPONENT F_Schlick
#endif

#ifndef BRDF_D_COMPONENT
#define BRDF_D_COMPONENT D_TrowbridgeReitz
#endif

#ifndef BRDF_G_COMPONENT
#define BRDF_G_COMPONENT G_Smith_SchlickGGX
#endif

/**
 Calculates the Cook-Torrance BRDFxCos.

 @pre			@a n is normalized.
 @pre			@a l is normalized.
 @pre			@a v is normalized.
 @param[in]		n
				The surface normal.
 @param[in]		l
				The light (hit-to-light) direction.
 @param[in]		v
				The view (hit-to-eye) direction.
 @param[in]		roughness
				The roughness of the material.
 @param[in]		metallic
				The metallic coefficient of the material.
 @return		The Cook-Torrance BRDFxCos specular intensity.
 */
float3 CookTorranceBRDFxCos_new(float3 n, float3 l, float3 v, 
	float3 base_color, float roughness, float metallic) {
	
	const float  alpha   = sqr(roughness);
	const float  n_dot_l = sat_dot(n, l);
	const float  n_dot_v = sat_dot(n, v);
	const float3 h       = HalfDirection(l, v);
	const float  n_dot_h = sat_dot(n, h);
	const float  v_dot_h = sat_dot(v, h);
	
	const float F = BRDF_F_COMPONENT(v_dot_h, 0.3f);
	const float D = BRDF_D_COMPONENT(n_dot_h, alpha);
	const float G = BRDF_G_COMPONENT(n_dot_v, n_dot_l, n_dot_h, v_dot_h, alpha);
	
	const float3 Fd = g_inv_pi * base_color * sat_dot(n, l);
	const float3 Fs = 0.25f * G * D * F / n_dot_v;

	return Fd + Fs;
}

#endif // MAGE_HEADER_BRDF