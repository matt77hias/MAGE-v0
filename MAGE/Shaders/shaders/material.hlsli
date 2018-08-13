#ifndef MAGE_HEADER_MATERIAL
#define MAGE_HEADER_MATERIAL

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

/**
 A struct of materials.
 */
struct Material {

	//-------------------------------------------------------------------------
	// Member Variables
	//-------------------------------------------------------------------------
	
	/**
	 The (linear) base color of this material.
	 */
	float3 m_base_color;

	/**
	 The (linear) roughness of this material.
	 */
	float m_roughness;
	
	/**
	 The (linear) metalness of this material.
	 */
	float m_metalness;
};

#endif // MAGE_HEADER_MATERIAL