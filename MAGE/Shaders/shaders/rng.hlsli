#ifndef MAGE_HEADER_RNG
#define MAGE_HEADER_RNG

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "hash.hlsli"

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

uint UniformUint(uint seed) {
	return Hash_Wang(seed);
}

float UniformFloat(uint seed) {
	static const uint mantissa_mask = 0x7FFFFF;
	const uint u = UniformUint(seed);

	return frac(float(u & mantissa_mask) / float(mantissa_mask));
}

#endif // MAGE_HEADER_RNG