#ifndef MAGE_HEADER_VOXEL
#define MAGE_HEADER_VOXEL

struct Voxel {
	uint encoded_L;
	uint encoded_n;
};

static const float g_max_length = 10.0f;

uint EncodeRadiance(float3 L) {
	const float L_length     = length(L);
	const float L_inv_length = 1.0f / L_length;

	// [0, inf) -> [0,1] -> [0,255]
	const uint length = uint(255.0f * saturate(L_length / g_max_length));
	// [0, L_inv_length)^3 -> [0,1]^3 -> [0,255]^3
	const uint3 color = uint3(255.0f * L * L_inv_length);
	
	// |........|........|........|........|
	// | lenght |  red   |  green |  blue  |
	const uint encoded_L = (length  << 24u)
		                 | (color.x << 16u) 
		                 | (color.y <<  8u) 
		                 |  color.z;
	return encoded_L;
}

float3 DecodeRadiance(uint encoded_L) {
	static const float u_to_f = 1.0f / 255.0f;
	
	// [0,2^32-1] -> [0,255]^4
	const uint4 uL = 0xFF & uint4(encoded_L >> 24u,
		                          encoded_L >> 16u,
		                          encoded_L >>  8u,
		                          encoded_L);
	// [0,255]^4 -> [0,1]^4
	const float4 fL = uL * u_to_f;
	
	// [0,1] -> [0, g_max_length]
	const float L_length = fL.x * g_max_length;
	// [0,1]^3 -> [0, L_length]^3
	const float3 L = fL.yzw * L_length;
	
	return L;
}

uint EncodeNormal(float3 n) {
	static const float3 f_to_i = float3(1023.0f, 511.0f, 1023.0f);

	// [-1,1]^3 -> [-1023,1023]x[-511,511]x[-1023,1023]
	const int3  normal      = int3(n * f_to_i);
	const uint3 normal_sign = min(sign(normal), 0u);
	const uint3 normal_size = abs(normal);

	// |.:.......|...:.:....|.....:.:..|........|
	// |s|     x     |s|     y    |s|     z     |
	const uint encoded_n = (normal_sign.x << 31u)
		                 | (normal_size.x << 21u)
		                 | (normal_sign.y << 20u)
		                 | (normal_size.y << 11u)
		                 | (normal_sign.z << 10u)
		                 |  normal_size.z;
	return encoded_n;
}

float3 DecodeNormal(uint encoded_n) {
	static const float3 i_to_f = float3(1.0f / 1023.0f, 
										1.0f /  511.0f, 
										1.0f / 1023.0f);

	const uint3 normal_sign = 0x1 & uint3(encoded_n >> 31u,
		                                  encoded_n >> 20u,
		                                  encoded_n >> 10u);
	const uint3 normal_size = uint3(0x3FF, 0x1FF, 0x3FF)
		                    & uint3(encoded_n >> 21u,
		                            encoded_n >> 11u,
		                            encoded_n);
	
	// [-1023,1023]x[-511,511]x[-1023,1023]
	const int3 normal = (2*int3(normal_sign)-1) * normal_size;
	// [-1023,1023]x[-511,511]x[-1023,1023] -> [-1,1]^3
	const float3 n = normal * i_to_f;

	return normalize(n);
}

#endif // MAGE_HEADER_VOXEL