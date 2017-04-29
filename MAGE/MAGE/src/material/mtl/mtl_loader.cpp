//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\mtl\mtl_loader.hpp"
#include "material\mtl\mtl_reader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void ImportMTLMaterialFromFile(const wstring &fname, vector< Material > &materials) {
		MTLReader reader(materials);
		reader.ReadFromFile(fname);
	}
}