//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\vs\vs_loader.hpp"
#include "loaders\vs\vs_reader.hpp"
#include "loaders\vs\vs_writer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	void ImportVSFromFile(const wstring &fname, 
		vector< Variable > &variable_buffer) {

		VSReader reader(variable_buffer);
		reader.ReadFromFile(fname);
	}

	void ExportVSToFile(const wstring &fname, 
		const vector< Variable > &variable_buffer) {

		VSWriter writer(variable_buffer);
		writer.WriteToFile(fname);
	}
}