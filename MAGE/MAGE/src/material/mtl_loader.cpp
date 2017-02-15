//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\mtl_loader.hpp"
#include "material\mtl_parser.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT LoadMTLMaterialFromFile(const wstring &fname, vector< Material > &material_buffer) {
		MTLParser parser(material_buffer);
		return parser.ParseFromFile(fname);
	}
}