#ifndef MAGE_HEADER_RNG
#define MAGE_HEADER_RNG

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

float UniformUintToFloat(uint u) {
	// IEEE-754: 2^-32 = 0x2F800000
	return float(u) * asfloat(0x2F800000u);
}

uint UniformUint_LCG(uint state) {
	static const uint multiplier = 1664525u;
	static const uint increment  = 1013904223u;
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
