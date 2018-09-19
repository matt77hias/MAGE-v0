//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\variable_script_loader.hpp"
#include "loaders\var\var_loader.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	void ImportVariableScriptFromFile(const std::filesystem::path& path,  
									  ValueMap& variable_buffer) {
		
		std::wstring extension(path.extension());
		TransformToLowerCase(extension);

		if (L".var" == extension) {
			ImportVARFromFile(path, variable_buffer);
		}
		else {
			throw Exception("Unknown variable script file extension: {}", path);
		}
	}

	void ExportVariableScriptToFile(const std::filesystem::path& path, 
									const ValueMap& variable_buffer) {
		
		std::wstring extension(path.extension());
		TransformToLowerCase(extension);

		if (L".var" == extension) {
			ExportVARToFile(path, variable_buffer);
		}
		else {
			throw Exception("Unknown variable script file extension: {}", path);
		}
	}
}