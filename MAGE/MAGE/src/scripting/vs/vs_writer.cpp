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

	HRESULT VSWriter::Write() const {
		char output[MAX_PATH];

		for (vector< Variable * >::const_iterator it = m_variable_buffer.cbegin(); it != m_variable_buffer.cend(); ++it) {
			const Variable *variable = *it;
			const char *name = variable->GetName().c_str();
			const void *raw_value = variable->GetValue();

			switch (variable->GetType()) {
			case BoolType: {
				const bool *value = (bool *)raw_value;
				if (*value) {
					sprintf_s(output, (unsigned int)_countof(output), "%s %s true", MAGE_VS_TOKEN_BOOL, name);
				}
				else {
					sprintf_s(output, (unsigned int)_countof(output), "%s %s false", MAGE_VS_TOKEN_BOOL, name);
				}
				break;
			}
			case IntType: {
				const int *value = (int *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %d", MAGE_VS_TOKEN_INT, name, *value);
				break;
			}
			case Int2Type: {
				const int2 *value = (int2 *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %d %d", MAGE_VS_TOKEN_INT2, name, value->x, value->y);
				break;
			}
			case Int3Type: {
				const int3 *value = (int3 *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %d %d %d", MAGE_VS_TOKEN_INT3, name, value->x, value->y, value->z);
				break;
			}
			case FloatType: {
				const float *value = (float *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %f", MAGE_VS_TOKEN_FLOAT, name, *value);
				break;
			}
			case Float2Type: {
				const float2 *value = (float2 *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %f %f", MAGE_VS_TOKEN_FLOAT2, name, value->x, value->y);
				break;
			}
			case Float3Type: {
				const float3 *value = (float3 *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %f %f %f", MAGE_VS_TOKEN_FLOAT3, name, value->x, value->y, value->z);
				break;
			}
			case Float4Type: {
				const float4 *value = (float4 *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %f %f %f %f", MAGE_VS_TOKEN_FLOAT4, name, value->x, value->y, value->z, value->w);
				break;
			}
			case ColorType: {
				const color *value = (color *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s %f %f %f %f", MAGE_VS_TOKEN_COLOR, name, value->x, value->y, value->z, value->w);
				break;
			}
			case StringType: {
				const string *value = (string *)raw_value;
				sprintf_s(output, (unsigned int)_countof(output), "%s %s \"%s\"", MAGE_VS_TOKEN_STRING, name, value->c_str());
				break;
			}
			case UnknownType: {
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