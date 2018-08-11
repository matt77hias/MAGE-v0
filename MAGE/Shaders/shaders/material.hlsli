#ifndef MAGE_HEADER_MATERIAL
#define MAGE_HEADER_MATERIAL

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

struct Material {
	// The (linear) base color of this material.
	float3 base_color;
	// The (linear) roughness of this material.
	float  roughness;
	// The (linear) metalness of this material.
	float  metalness;
};

#endif // MAGE_HEADER_MATERIAL