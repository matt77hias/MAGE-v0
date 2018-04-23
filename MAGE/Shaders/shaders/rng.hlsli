#ifndef MAGE_HEADER_RNG
#define MAGE_HEADER_RNG

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

float UniformUintToFloat(uint u) {
	return float(u & 0xFFFFFF) * asfloat(0x33800000);
}

uint UniformUint_LCG(uint state) {
	static const float multiplier = 1664525u;
	static const float increment  = 1013904223u;
	return multiplier * state + increment;
}

float UniformFloat_LCG(inout uint state) {
	state = UniformUint_LCG(state);
	return UniformUintToFloat(state);
}

uint UniformUint_Xorshift(uint state) {
	state ^= (state << 13u);
	state ^= (state >> 17u);
	state ^= (state << 5u);
	return state;
}

float UniformFloat_Xorshift(inout uint state) {
	state = UniformUint_Xorshift(state);
	return UniformUintToFloat(state);
}

#endif // MAGE_HEADER_RNG
