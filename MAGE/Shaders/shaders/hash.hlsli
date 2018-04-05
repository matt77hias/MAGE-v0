#ifndef MAGE_HEADER_HASH
#define MAGE_HEADER_HASH

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

uint Hash_Wang(uint x) {
	x = (x ^ 61u) ^ (x >> 16u);
	x = x + (x << 3u);
	x = x ^ (x >> 4u);
	x = x * 0x27D4EB2D;
	x = x ^ (x >> 15u);
	return x;
}

uint Hash_Elias(uint x) {
	x = (x << 13u) ^ x;
	x = x * (x * x * 15731u + 789221u) + 1376312589u;
	return x;
}

#endif //MAGE_HEADER_HASH