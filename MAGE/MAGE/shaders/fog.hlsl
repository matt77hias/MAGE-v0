//TODO

float ComputeFogFactor(float4 p) {
	return saturate(dot(p, fog_vector));
}

void ApplyFog(inout float4 color, float fog_factor) {
	color.rgb = lerp(color.rgb, fog_color * color.a, fog_factor);
}