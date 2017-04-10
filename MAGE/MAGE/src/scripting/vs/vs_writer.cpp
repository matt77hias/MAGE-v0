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

	HRESULT VSWriter::Write() {
		char output[MAX_PATH];

		for (vector< Variable * >::const_iterator it = m_variable_buffer.cbegin(); it != m_variable_buffer.cend(); ++it) {
			const Variable *variable = *it;
			const char *name = variable->GetName().c_str();
			const void *raw_value = variable->GetValue();

			switch (variable->GetType()) {
			case VariableType_Bool: {
				const bool *value = (bool *)raw_value;
				if (*value) {
					sprintf_s(output, (unsigned int)_countof(output), "%s %s true", MAGE_VS_TOKEN_BOOL, name);
				}
				else {
					sprintf_s(output, (unsigned int)_countof(output), "%s %s false", MAGE_VS_TOKEN_BOOL, name);
				}
				break;
			}
			case VariableType_Int: {
				const int *value = (int *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %d", MAGE_VS_TOKEN_INT, name, *value);
				break;
			}
			case VariableType_Int2: {
				const int2 *value = (int2 *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %d %d", MAGE_VS_TOKEN_INT2, name, value->x, value->y);
				break;
			}
			case VariableType_Int3: {
				const int3 *value = (int3 *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %d %d %d", MAGE_VS_TOKEN_INT3, name, value->x, value->y, value->z);
				break;
			}
			case VariableType_Float: {
				const float *value = (float *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %f", MAGE_VS_TOKEN_FLOAT, name, *value);
				break;
			}
			case VariableType_Float2: {
				const float2 *value = (float2 *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %f %f", MAGE_VS_TOKEN_FLOAT2, name, value->x, value->y);
				break;
			}
			case VariableType_Float3: {
				const float3 *value = (float3 *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %f %f %f", MAGE_VS_TOKEN_FLOAT3, name, value->x, value->y, value->z);
				break;
			}
			case VariableType_Float4: {
				const float4 *value = (float4 *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %f %f %f %f", MAGE_VS_TOKEN_FLOAT4, name, value->x, value->y, value->z, value->w);
				break;
			}
			case VariableType_Color: {
				const color *value = (color *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %f %f %f %f", MAGE_VS_TOKEN_COLOR, name, value->x, value->y, value->z, value->w);
				break;
			}
			case VariableType_String: {
				const string *value = (string *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s \"%s\"", MAGE_VS_TOKEN_STRING, name, value->c_str());
				break;
			}
			case VariableType_Unknown: {
				const char *value = (char *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %s", MAGE_VS_TOKEN_UNKNOWN, name, value);
				break;
			}
			default: {
				Error("%ls: could not export variable: %s", GetFilename().c_str(), name);
				return E_FAIL;
			}
			}

			WriteLine(output);
		}

		return S_OK;
	}
}