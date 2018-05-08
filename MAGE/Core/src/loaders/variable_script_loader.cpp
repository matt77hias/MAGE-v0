//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\variable_script_loader.hpp"
#include "loaders\var\var_loader.hpp"
#include "string\string_utils.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	void ImportVariableScriptFromFile(const std::filesystem::path& path,  
									  std::map< string, Value >& 
									  variable_buffer) {
		
		wstring extension(path.extension());
		TransformToLowerCase(extension);

		if (L"var" == extension) {
			ImportVARFromFile(path, variable_buffer);
		}
		else {
			throw Exception("Unknown variable script file extension: %ls", 
							path.c_str());
		}
	}

	void ExportVariableScriptToFile(const std::filesystem::path& path, 
									const std::map< string, Value >& 
									variable_buffer) {
		
		wstring extension(path.extension());
		TransformToLowerCase(extension);

		if (L"var" == extension) {
			ExportVARToFile(path, variable_buffer);
		}
		else {
			throw Exception("Unknown variable script file extension: %ls", 
							path.c_str());
		}
	}
}