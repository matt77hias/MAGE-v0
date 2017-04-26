//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\vs\vs_writer.hpp"
#include "scripting\vs\vs_tokens.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void VSWriter::Write() {
		char output[MAX_PATH];

		for (vector< Variable >::const_iterator it = m_variable_buffer.cbegin(); it != m_variable_buffer.cend(); ++it) {
			const char *name = it->GetName().c_str();
			const void *raw_value = it->GetValue();

			switch (it->GetType()) {
			case VariableType_Bool: {
				const bool *value = (const bool *)raw_value;
				if (*value) {
					sprintf_s(output, (unsigned int)_countof(output), "%s %s true", MAGE_VS_TOKEN_BOOL, name);
				}
				else {
					sprintf_s(output, (unsigned int)_countof(output), "%s %s false", MAGE_VS_TOKEN_BOOL, name);
				}
				break;
			}
			case VariableType_Int: {
				const int *value = (const int *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %d", MAGE_VS_TOKEN_INT, name, *value);
				break;
			}
			case VariableType_Int2: {
				const int2 *value = (const int2 *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %d %d", MAGE_VS_TOKEN_INT2, name, value->x, value->y);
				break;
			}
			case VariableType_Int3: {
				const int3 *value = (const int3 *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %d %d %d", MAGE_VS_TOKEN_INT3, name, value->x, value->y, value->z);
				break;
			}
			case VariableType_Float: {
				const float *value = (const float *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %f", MAGE_VS_TOKEN_FLOAT, name, *value);
				break;
			}
			case VariableType_Float2: {
				const float2 *value = (const float2 *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %f %f", MAGE_VS_TOKEN_FLOAT2, name, value->x, value->y);
				break;
			}
			case VariableType_Float3: {
				const float3 *value = (const float3 *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %f %f %f", MAGE_VS_TOKEN_FLOAT3, name, value->x, value->y, value->z);
				break;
			}
			case VariableType_Float4: {
				const float4 *value = (const float4 *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %f %f %f %f", MAGE_VS_TOKEN_FLOAT4, name, value->x, value->y, value->z, value->w);
				break;
			}
			case VariableType_Color: {
				const color *value = (const color *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %f %f %f %f", MAGE_VS_TOKEN_COLOR, name, value->x, value->y, value->z, value->w);
				break;
			}
			case VariableType_String: {
				const string *value = (const string *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s \"%s\"", MAGE_VS_TOKEN_STRING, name, value->c_str());
				break;
			}
			default: {
				Warning("%ls: could not export variable: %s", GetFilename().c_str(), name);
				return;
			}
			}

			WriteStringLine(output);
		}
	}
}