//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\var\var_loader.hpp"
#include "loaders\var\var_reader.hpp"
#include "loaders\var\var_writer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {
	
	void ImportVARFromFile(const wstring &fname, 
		std::map< string, Value > &variable_buffer) {

		VARReader reader(variable_buffer);
		reader.ReadFromFile(fname);
	}

	void ExportVARToFile(const wstring &fname, 
		const std::map< string, Value > &variable_buffer) {

		VARWriter writer(variable_buffer);
		writer.WriteToFile(fname);
	}
}