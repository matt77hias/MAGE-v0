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
	
	void ImportVARFromFile(const std::filesystem::path& path,
						   ValueMap& variable_buffer) {

		VARReader reader(variable_buffer);
		reader.ReadFromFile(path);
	}

	void ExportVARToFile(const std::filesystem::path& path,
		                 const ValueMap& variable_buffer) {

		VARWriter writer(variable_buffer);
		writer.WriteToFile(path);
	}
}