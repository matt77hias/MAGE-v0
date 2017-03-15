//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\vs\vs_loader.hpp"
#include "scripting\vs\vs_reader.hpp"
#include "scripting\vs\vs_writer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	HRESULT ImportVSFromFile(const wstring &fname, vector< Variable * > &variable_buffer) {
		VSReader reader(variable_buffer);
		return reader.ReadFromFile(fname);
	}

	HRESULT ExportVSToFile(const wstring &fname, const vector< Variable * > &variable_buffer) {
		VSWriter writer(variable_buffer);
		return writer.WriteToFile(fname);
	}
}