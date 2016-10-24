//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <typeinfo>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Script::Script(const string &name, const string &path) : Resource(name, path), m_variables(new LinkedList< Variable >()) {
		// Open the file whose name is specified by the given filename and
		// associate it with a returned stream.
		FILE *file;
		const errno_t result_fopen_s = fopen_s(&file, GetFilename().c_str(), "r");
		if (result_fopen_s) {
			Severe("Could not construct script: %s", GetFilename());
		}

		// format: s
		// Any number of non-whitespace characters, stopping at the first whitespace character found.
		// A terminating null character is automatically added at the end of the stored sequence.

		bool read = false;
		char buffer[MAX_PATH];
		// Read the first word.
		fscanf_s(file, "%s", buffer, (unsigned int)sizeof(buffer));
		// Continue reading from the file until the eof is reached.
		while (feof(file) == 0) {
			// Check if the file position indicator is between a #begin and #end
			// statement. If so then read the data into the variable linked list.
			if (read) {
				// Stop reading data if an #end statement has been reached.
				if (strcmp(buffer, "#end") == 0) {
					read = false;
				}
				else {
					ImportVariable(buffer, file);
				}
			}
			else if (strcmp(buffer, "#begin") == 0) {
				read = true;
			}

			// Read the next word.
			fscanf_s(file, "%s", buffer, (unsigned int)sizeof(buffer));
		}

		// Close the file associated with the stream and disassociates it.
		fclose(file);
	}

	void Script::SaveScript(const string &filename) {
		FILE *file = NULL;
		const string &fname = (filename != "") ? filename : GetFilename();
		const errno_t result_fopen_s = fopen_s(&file, fname.c_str(), "w");
		if (result_fopen_s) {
			Severe("Could not save script: %s", fname);
		}

		// Write the #begin statement to the file.
		fputs("#begin\n", file);

		char output[MAX_PATH];

		// Iterate the states looking for the specified variable.
		LinkedList< Variable >::LinkedListIterator it = m_variables->GetIterator();
		while (it.HasNext()) {
			const Variable *next = it.Next();
			const char *name = next->GetName().c_str();
			const void *raw_value = next->GetValue();
			const char *type_name = typeid(raw_value).name();

			if (strcmp(type_name, "Pb") == 0) {
				const bool *value = (bool *)raw_value;
				if (*value) {
					sprintf_s(output, sizeof(output), "%s bool true", name);
				}
				else {
					sprintf_s(output, sizeof(output), "%s bool false", name);
				}
			}
			else if (strcmp(type_name, "Pi") == 0) {
				const int *value = (int *)raw_value;
				sprintf_s(output, sizeof(output), "%s int %d", name, *value);
			}
			else if (strcmp(type_name, "Ff") == 0) {
				const float *value = (float *)raw_value;
				sprintf_s(output, sizeof(output), "%s float %f", name, *value);
			}
			else if (strcmp(type_name, typeid(float3 *).name()) == 0) {
				const float3 *value = (float3 *)raw_value;
				sprintf_s(output, sizeof(output), "%s float3 %f %f %f", name, value->x, value->y, value->z);
			}
			else if (strcmp(type_name, typeid(float4 *).name()) == 0) {
				const float4 *value = (float4 *)raw_value;
				sprintf_s(output, sizeof(output), "%s float4 %f %f %f %f", name, value->x, value->y, value->z, value->w);
			}
			else if (strcmp(type_name, typeid(colour *).name()) == 0) {
				const colour *value = (colour *)raw_value;
				sprintf_s(output, sizeof(output), "%s colour %f %f %f %f", name, value->x, value->y, value->z, value->w);
			}
			else if (strcmp(type_name, "PSs") == 0) {
				const string *value = (string *)raw_value;
				sprintf_s(output, sizeof(output), "%s string %s", name, value->c_str());
			}
			else if (strcmp(type_name, "Pv") == 0) {
				const char *value = (char *)raw_value;
				sprintf_s(output, sizeof(output), "%s unknown %s", name, value);
			}
			else {
				Warning("Could not export variable: %s", name);
				continue;
			}

			fputs(output, file);
			fputs("\n", file);
		}

		// Write the #end statement to the file.
		fputs("#end", file);
	}

	void Script::ImportVariable(const string &variable_name, FILE *file) {
		// Ensure the file pointer is valid.
		if (file == NULL) {
			Warning("Could not import variable: %s", variable_name);
			return;
		}

		// Read the variable's type.
		char buffer[MAX_PATH];
		// Read the first word containing the type.
		fscanf_s(file, "%s", buffer, (unsigned int)sizeof(buffer));

		if (strcmp(buffer, "bool") == 0) {
			// The variable is a bool.
			bool *value = new bool;
			fscanf_s(file, "%s", buffer, (unsigned int)sizeof(buffer));
			*value = (strcmp(buffer, "true") == 0) ? true : false;
			AddVariable(variable_name, value);
		}
		else if (strcmp(buffer, "int") == 0) {
			// The variable is an int.
			int *value = new int;
			fscanf_s(file, "%s", buffer, (unsigned int)sizeof(buffer));
			*value = atoi(buffer);
			AddVariable(variable_name, value);
		}
		else if (strcmp(buffer, "float") == 0) {
			// The variable is a float.
			float *value = new float;
			fscanf_s(file, "%s", buffer, (unsigned int)sizeof(buffer));
			*value = (float)atof(buffer);
			AddVariable(variable_name, value);
		}
		else if (strcmp(buffer, "float3") == 0) {
			// The variable is a float3.
			float3 *value = new float3();
			fscanf_s(file, "%s", buffer, (unsigned int)sizeof(buffer));
			value->x = (float)atof(buffer);
			fscanf_s(file, "%s", buffer, (unsigned int)sizeof(buffer));
			value->y = (float)atof(buffer);
			fscanf_s(file, "%s", buffer, (unsigned int)sizeof(buffer));
			value->z = (float)atof(buffer);
			AddVariable(variable_name, value);
		}
		else if (strcmp(buffer, "float4") == 0) {
			// The variable is a float4.
			float4 *value = new float4();
			fscanf_s(file, "%s", buffer, (unsigned int)sizeof(buffer));
			value->x = (float)atof(buffer);
			fscanf_s(file, "%s", buffer, (unsigned int)sizeof(buffer));
			value->y = (float)atof(buffer);
			fscanf_s(file, "%s", buffer, (unsigned int)sizeof(buffer));
			value->z = (float)atof(buffer);
			fscanf_s(file, "%s", buffer, (unsigned int)sizeof(buffer));
			value->w = (float)atof(buffer);
			AddVariable(variable_name, value);
		}
		else if (strcmp(buffer, "colour") == 0) {
			// The variable is a colour.
			colour *value = new colour();
			fscanf_s(file, "%s", buffer, (unsigned int)sizeof(buffer));
			value->x = (float)atof(buffer);
			fscanf_s(file, "%s", buffer, (unsigned int)sizeof(buffer));
			value->y = (float)atof(buffer);
			fscanf_s(file, "%s", buffer, (unsigned int)sizeof(buffer));
			value->z = (float)atof(buffer);
			fscanf_s(file, "%s", buffer, (unsigned int)sizeof(buffer));
			value->w = (float)atof(buffer);
			AddVariable(variable_name, value);
		}
		else if (strcmp(buffer, "string") == 0) {
			// The variable is a string.
			
			// format: c
			// 	The next character.

			// Find the opening inverted commas.
			ZeroMemory(buffer, MAX_PATH * sizeof(char));
			bool commas_found = false;
			fscanf_s(file, "%c", buffer, (unsigned int)sizeof(buffer));
			while (true) {
				if (strcmp(buffer, "\"") == 0) {
					commas_found = true;
					break;
				}

				if (strcmp(buffer, " ") != 0) {
					// Used to specify a position within a file.
					fpos_t pos;
					// Retrieves the current position in the stream.
					fgetpos(file, &pos);
					// Restores the current position in the stream to --pos.
					fsetpos(file, &--pos);
					break;
				}

				fscanf_s(file, "%c", buffer, (unsigned int)sizeof(buffer));
			}

			// Read the string.
			char complete_string[MAX_PATH];
			ZeroMemory(complete_string, MAX_PATH * (unsigned int)sizeof(char));
			bool add_spacing = false;
			do {
				fscanf_s(file, "%s", buffer, (unsigned int)sizeof(buffer));

				if (strcmp(&buffer[strlen(buffer) - 1], "\"") == 0) {
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
					strcat_s(complete_string, sizeof(complete_string), " ");
				}

				// Appends a copy of the buffer string to the destination string.
				strcat_s(complete_string, sizeof(complete_string), buffer);

			} while (commas_found == true);

			const string *value = new string(complete_string);
			AddVariable(variable_name, value);
		}
		else {
			// The variable has an unknown type.
			char *value = new char[strlen(buffer) + 1];
			fscanf_s(file, "%s", buffer, (unsigned int)sizeof(buffer));
			strcpy_s(value, sizeof(value), buffer);
			AddVariable(variable_name, (void *)value);
		}
	}

	bool Script::RemoveVariable(const string &variable_name) {
		Variable *target = NULL;

		// Iterate the states looking for the specified variable.
		LinkedList< Variable >::LinkedListIterator it = m_variables->GetIterator();
		while (it.HasNext()) {
			Variable *next = it.Next();
			if (next->GetName() == variable_name) {
				target = next;
				break;
			}
		}

		if (target == NULL) {
			return false;
		}

		// Remove the variable
		m_variables->Remove(&target);
		return true;
	}

	template < typename T >
	const T *Script::GetValueOfVariable(const string &variable_name) const {
		// Iterate the states looking for the specified variable.
		LinkedList< Variable >::LinkedListIterator it = m_variables->GetIterator();
		while (it.HasNext()) {
			const Variable *next = it.Next();
			if (next->GetName() == variable_name) {
				return (T *)next->GetValue();
			}
		}

		return NULL;
	}

	template < typename T >
	void Script::SetValueOfVariable(const string &variable_name, const T *value) {
		if (RemoveVariable(variable_name)) {
			// Readd the variable with a new value.
			AddVariable(variable_name, value);
		}
	}
}