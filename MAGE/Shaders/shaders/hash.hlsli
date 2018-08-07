#ifndef MAGE_HEADER_HASH
#define MAGE_HEADER_HASH

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

uint Hash_Wang(uint key) {
	key = (key ^ 61u) ^ (key >> 16u);
	key = key + (key << 3u);
	key = key ^ (key >> 4u);
	key = key * 0x27D4EB2Du;
	key = key ^ (key >> 15u);
	return key;
}

uint Hash_Elias(uint key) {
	key = (key << 13u) ^ key;
	key = key * (key * key * 15731u + 789221u) + 1376312589u;
	return key;
}

#endif // MAGE_HEADER_HASH
