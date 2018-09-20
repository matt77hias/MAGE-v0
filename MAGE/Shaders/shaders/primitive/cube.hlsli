#ifndef MAGE_HEADER_CUBE
#define MAGE_HEADER_CUBE

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

// Number of vertices: 14
// Topology: D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP

/**
 Returns the position in object space of the vertex corresponding to the given
 id of a cube triangle strip centered at [0.5,0.5,0.5] with a size of [1,1,1].

 @pre			0 <= @a vertex_id < 14
 @param[in]		vertex_id
				The vertex id.
 @return		The position in object space of the vertex corresponding to
				the given id of a cube triangle strip centered at [0.5,0.5,0.5]
				with a size of [1,1,1].
 */
float3 OffsettedUnitCube(uint vertex_id) {
	// 0x287A = 10100001111010
	// 0x02AF = 00001010101111
	// 0x31E3 = 11000111100011
	const uint mask = 1u << vertex_id;
	return float3((0x287A & mask) != 0u,
		          (0x02AF & mask) != 0u,
				  (0x31E3 & mask) != 0u);
}

// Number of vertices: 14
// Topology: D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP

/**
 Returns the position in object space of the vertex corresponding to the given
 id of a cube triangle strip centered at [0,0,0] with a size of [1,1,1].

 @pre			0 <= @a vertex_id < 14
 @param[in]		vertex_id
				The vertex id.
 @return		The position in object space of the vertex corresponding to
				the given id of a cube triangle strip centered at [0,0,0]
				with a size of [1,1,1].
 */
float3 UnitCube(uint vertex_id) {
	return OffsettedUnitCube(vertex_id) - 0.5f;
}

#endif // MAGE_HEADER_CUBE