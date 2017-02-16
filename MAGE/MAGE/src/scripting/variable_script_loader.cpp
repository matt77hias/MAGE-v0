//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\variable_script_loader.hpp"
#include "scripting\variable_script_reader.hpp"
#include "scripting\variable_script_writer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	HRESULT ImportVariableScriptFromFile(const wstring &fname, vector< Variable * > &variable_buffer) {
		VSReader reader(variable_buffer);
		return reader.ReadFromFile(fname);
	}

	HRESULT ExportVariableScriptToFile(const wstring &fname, const vector< Variable * > &variable_buffer) {
		VSWriter writer(variable_buffer);
		return writer.WriteToFile(fname);
	}
}