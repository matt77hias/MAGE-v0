//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\variable_script.hpp"
#include "string\string_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	VariableScript::VariableScript(const wstring &name, const wstring &path)
		: Resource(name, path), m_variables(list< Variable * >()) {
		ImportScript();
	}

	VariableScript::~VariableScript() {
		RemoveAllVariables();
	}

	HRESULT VariableScript::ImportScript(const wstring &fname) {
		// Open the script file.
		FILE *file = nullptr;
		const wstring &filename = (fname != L"") ? fname : GetFilename();
		const errno_t result_fopen_s = _wfopen_s(&file, filename.c_str(), L"r");
		if (result_fopen_s) {
			Error("Could not import script: %ls", filename.c_str());
			return E_FAIL;
		}

		// format: s
		// Any number of non-whitespace characters, stopping at the first whitespace character found.
		// A terminating null character is automatically added at the end of the stored sequence.

		bool read = false;
		char buffer[MAX_PATH];
		// Read the first word.
		fscanf_s(file, "%s", buffer, (unsigned int)_countof(buffer));
		// Continue reading from the file until the eof is reached.
		while (feof(file) == 0) {
			// Check if the file position indicator is between a #begin and #end
			// statement. If so then read the data into the variable linked list.
			if (read) {
				// Stop reading data if an #end statement has been reached.
				if (str_equals(buffer, MAGE_SCRIPT_END_TOKEN)) {
					read = false;
				}
				else {
					ImportVariable(buffer, file);
				}
			}
			else if (str_equals(buffer, MAGE_SCRIPT_BEGIN_TOKEN)) {
				read = true;
			}

			// Read the next word.
			fscanf_s(file, "%s", buffer, (unsigned int)_countof(buffer));
		}

		// Close the script file.
		fclose(file);

		return S_OK;
	}

	HRESULT VariableScript::ExportScript(const wstring &fname) {
		// Open the script file.
		FILE *file = nullptr;
		const wstring &filename = (fname != L"") ? fname : GetFilename();
		const errno_t result_fopen_s = _wfopen_s(&file, filename.c_str(), L"w");
		if (result_fopen_s) {
			Error("Could not export script: %ls", filename.c_str());
			return E_FAIL;
		}

		// Write the #begin statement to the file.
		fputs(MAGE_SCRIPT_BEGIN_TOKEN, file);
		fputs("\n", file);

		// Iterate the states looking for the specified variable.
		for (list< Variable * >::const_iterator it = m_variables.cbegin(); it != m_variables.cend(); ++it) {
			ExportVariable(*it, file);
		}

		// Write the #end statement to the file.
		fputs(MAGE_SCRIPT_END_TOKEN, file);

		// Close the script file.
		fclose(file);

		return S_OK;
	}

	HRESULT VariableScript::ImportVariable(const string &name, FILE *file) {
		// Ensure the file pointer is valid.
		if (file == nullptr) {
			Error("Could not import variable: %s", name);
			return E_FAIL;
		}

		// Read the variable's type.
		char buffer[MAX_PATH];
		// Read the first word containing the type.
		fscanf_s(file, "%s", buffer, (unsigned int)_countof(buffer));

		if (str_equals(buffer, "bool")) {
			// The variable is a bool.
			bool *value = new bool();
			fscanf_s(file, "%s", buffer, (unsigned int)_countof(buffer));
			*value = (str_equals(buffer, "true")) ? true : false;
			AddVariable(name, BoolType, value);
		}
		else if (str_equals(buffer, "int")) {
			// The variable is an int.
			int *value = new int();
			fscanf_s(file, "%s", buffer, (unsigned int)_countof(buffer));
			*value = atoi(buffer);
			AddVariable(name, IntType, value);
		}
		else if (str_equals(buffer, "float")) {
			// The variable is a float.
			float *value = new float();
			fscanf_s(file, "%s", buffer, (unsigned int)_countof(buffer));
			*value = strtof(buffer, nullptr);
			AddVariable(name, FloatType, value);
		}
		else if (str_equals(buffer, "float3")) {
			// The variable is a float3.
			float3 *value = new float3();
			fscanf_s(file, "%s", buffer, (unsigned int)_countof(buffer));
			value->x = strtof(buffer, nullptr);
			fscanf_s(file, "%s", buffer, (unsigned int)_countof(buffer));
			value->y = strtof(buffer, nullptr);
			fscanf_s(file, "%s", buffer, (unsigned int)_countof(buffer));
			value->z = strtof(buffer, nullptr);
			AddVariable(name, Float3Type, value);
		}
		else if (str_equals(buffer, "float4")) {
			// The variable is a float4.
			float4 *value = new float4();
			fscanf_s(file, "%s", buffer, (unsigned int)_countof(buffer));
			value->x = strtof(buffer, nullptr);
			fscanf_s(file, "%s", buffer, (unsigned int)_countof(buffer));
			value->y = strtof(buffer, nullptr);
			fscanf_s(file, "%s", buffer, (unsigned int)_countof(buffer));
			value->z = strtof(buffer, nullptr);
			fscanf_s(file, "%s", buffer, (unsigned int)_countof(buffer));
			value->w = strtof(buffer, nullptr);
			AddVariable(name, Float4Type, value);
		}
		else if (str_equals(buffer, "colour")) {
			// The variable is a colour.
			colour *value = new colour();
			fscanf_s(file, "%s", buffer, (unsigned int)_countof(buffer));
			value->x = strtof(buffer, nullptr);
			fscanf_s(file, "%s", buffer, (unsigned int)_countof(buffer));
			value->y = strtof(buffer, nullptr);
			fscanf_s(file, "%s", buffer, (unsigned int)_countof(buffer));
			value->z = strtof(buffer, nullptr);
			fscanf_s(file, "%s", buffer, (unsigned int)_countof(buffer));
			value->w = strtof(buffer, nullptr);
			AddVariable(name, ColourType, value);
		}
		else if (str_equals(buffer, "string")) {
			// The variable is a string.
			
			// format: c
			// 	The next character.

			// Find the opening inverted commas.
			ZeroMemory(buffer, _countof(buffer));
			bool commas_found = false;
			fscanf_s(file, "%c", buffer, (unsigned int)_countof(buffer));
			while (true) {
				if (str_equals(buffer, "\"")) {
					commas_found = true;
					break;
				}

				if (!str_equals(buffer, " ")) {
					// Used to specify a position within a file.
					fpos_t pos;
					// Retrieves the current position in the stream.
					fgetpos(file, &pos);
					// Restores the current position in the stream to --pos.
					fsetpos(file, &--pos);
					break;
				}

				fscanf_s(file, "%c", buffer, (unsigned int)_countof(buffer));
			}

			// Read the string.
			char complete_string[MAX_PATH];
			ZeroMemory(complete_string, _countof(complete_string));
			bool add_spacing = false;
			do {
				fscanf_s(file, "%s", buffer, (unsigned int)_countof(buffer));

				if (str_equals(&buffer[strlen(buffer) - 1], "\"")) {
					buffer[strlen(buffer) - 1] = 0;
					commas_found = false;
				}

				if (add_spacing == false) {
					// Initially no space character needs to be added.
					// From then on, a space character needs always to be added.
					add_spacing = true;
				}
				else {
					// Appends a space character to the destination string. 
					strcat_s(complete_string, (unsigned int)_countof(complete_string), " ");
				}

				// Appends a copy of the buffer string to the destination string.
				strcat_s(complete_string, (unsigned int)_countof(complete_string), buffer);

			} while (commas_found == true);

			const string *value = new string(complete_string);
			AddVariable(name, StringType, value);
		}
		else {
			// The variable has an unknown type.
			char *value = new char[strlen(buffer) + 1];
			fscanf_s(file, "%s", buffer, (unsigned int)_countof(buffer));
			strcpy_s(value, strlen(buffer) + 1, buffer);
			AddVariable(name, UnknownType, (void *)value);
		}

		return S_OK;
	}

	HRESULT VariableScript::ExportVariable(const Variable *variable, FILE *file) {
		char output[MAX_PATH];
		
		const char *name = variable->GetName().c_str();
		const void *raw_value = variable->GetValue();

		switch (variable->GetType()) {
		case BoolType: {
			const bool *value = (bool *)raw_value;
			if (*value) {
				sprintf_s(output, (unsigned int)_countof(output), "%s bool true", name);
			}
			else {
				sprintf_s(output, (unsigned int)_countof(output), "%s bool false", name);
			}
			break;
		}
		case IntType: {
			const int *value = (int *)raw_value;
			sprintf_s(output, (unsigned int)_countof(output), "%s int %d", name, *value);
			break;
		}
		case FloatType: {
			const float *value = (float *)raw_value;
			sprintf_s(output, (unsigned int)_countof(output), "%s float %f", name, *value);
			break;
		}
		case Float3Type: {
			const float3 *value = (float3 *)raw_value;
			sprintf_s(output, (unsigned int)_countof(output), "%s float3 %f %f %f", name, value->x, value->y, value->z);
			break;
		}
		case Float4Type: {
			const float4 *value = (float4 *)raw_value;
			sprintf_s(output, (unsigned int)_countof(output), "%s float4 %f %f %f %f", name, value->x, value->y, value->z, value->w);
			break;
		}
		case ColourType: {
			const colour *value = (colour *)raw_value;
			sprintf_s(output, (unsigned int)_countof(output), "%s colour %f %f %f %f", name, value->x, value->y, value->z, value->w);
			break;
		}
		case StringType: {
			const string *value = (string *)raw_value;
			sprintf_s(output, (unsigned int)_countof(output), "%s string \"%s\"", name, value->c_str());
			break;
		}
		case UnknownType: {
			const char *value = (char *)raw_value;
			sprintf_s(output, (unsigned int)_countof(output), "%s unknown %s", name, value);
			break;
		}
		default: {
			Error("Could not export variable: %s", name);
			return E_FAIL;
		}
		}

		fputs(output, file);
		fputs("\n", file);

		return S_OK;
	}

	/**
	 A struct of predicates matching variables based on their name.
	 In case of a match, the variable is destructed.
	 */
	struct DestructVariablePredicate {

	public:

		/**
		 Constructs a predicate with the given variable name to look for.

		 @param[in]		variable_name
						A reference to the variable name to look for.
		 */
		DestructVariablePredicate(const string &variable_name) 
			: m_variable_name(variable_name) {}

		/**
		 Checks if the given variable has the same name as the name stored in this predicate. 
		 If this is the case, the variable is destructed.

		 @param[in]		variable
						A pointer to the variable.
		 @return		@c true if the given variable has the same name as the name stored in this predicate.
						@c false otherwise.
		 */
		bool operator()(const Variable *variable) const {
			if (variable->GetName() == m_variable_name) {
				delete variable;
				return true;
			}
			return false;
		}

		/**
		 The variable name of this predicate.
		 */
		const string &m_variable_name;
	};

	void VariableScript::RemoveVariable(const string &name) {
		RemoveIf(m_variables, DestructVariablePredicate(name));
	}

	void VariableScript::RemoveAllVariables() {
		RemoveAndDestructAllElements(m_variables);
	}
}