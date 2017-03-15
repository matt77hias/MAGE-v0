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

	HRESULT ImportMTLMaterialFromFile(const wstring &fname, vector< Material > &material_buffer) {
		MTLReader reader(material_buffer);
		return reader.ReadFromFile(fname);
	}
}