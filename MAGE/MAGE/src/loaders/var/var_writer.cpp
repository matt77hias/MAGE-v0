//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\var\var_writer.hpp"
#include "loaders\var\var_tokens.hpp"
#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	VARWriter::VARWriter(const map< string, Value > &variable_buffer)
		: Writer(), 
		m_variable_buffer(variable_buffer) {}

	VARWriter::VARWriter(VARWriter &&writer) = default;

	VARWriter::~VARWriter() = default;

	void VARWriter::Write() {
		
		char output[MAX_PATH];
		_countof(output);

		for (const auto &[key, value] : m_variable_buffer) {
				
			// MAGE_VAR_TOKEN_BOOL
			{
				const bool *v = std::get_if< bool >(&value);
				if (nullptr != v) {
					if (*v) {
						sprintf_s(output, _countof(output), 
							"%s %s true",
							MAGE_VAR_TOKEN_BOOL, key.c_str());
					}
					else {
						sprintf_s(output, _countof(output), 
							"%s %s false",
							MAGE_VAR_TOKEN_BOOL, key.c_str());
					}
					WriteStringLine(output);
					continue;
				}
			}

			// MAGE_VAR_TOKEN_INT
			{
				const S32 *v = std::get_if< S32 >(&value);
				if (nullptr != v) {
					sprintf_s(output, _countof(output), 
						"%s %s %d",
						MAGE_VAR_TOKEN_INT, key.c_str(), 
						*v);
					WriteStringLine(output);
					continue;
				}
			}

			// MAGE_VAR_TOKEN_INT2
			{
				const S32x2 *v = std::get_if< S32x2 >(&value);
				if (nullptr != v) {
					sprintf_s(output, _countof(output),
						"%s %s %d %d",
						MAGE_VAR_TOKEN_INT2, key.c_str(), 
						v->m_x, v->m_y);
					WriteStringLine(output);
					continue;
				}
			}

			// MAGE_VAR_TOKEN_INT3
			{
				const S32x3 *v = std::get_if< S32x3 >(&value);
				if (nullptr != v) {
					sprintf_s(output, _countof(output),
						"%s %s %d %d %d",
						MAGE_VAR_TOKEN_INT3, key.c_str(), 
						v->m_x, v->m_y, v->m_z);
					WriteStringLine(output);
					continue;
				}
			}

			// MAGE_VAR_TOKEN_FLOAT
			{
				const F32 *v = std::get_if< F32 >(&value);
				if (nullptr != v) {
					sprintf_s(output, _countof(output),
						"%s %s %f",
						MAGE_VAR_TOKEN_FLOAT, key.c_str(),
						*v);
					WriteStringLine(output);
					continue;
				}
			}

			// MAGE_VAR_TOKEN_FLOAT2
			{
				const F32x2 *v = std::get_if< F32x2 >(&value);
				if (nullptr != v) {
					sprintf_s(output, _countof(output),
						"%s %s %f %f", 
						MAGE_VAR_TOKEN_FLOAT2, key.c_str(),
						v->m_x, v->m_y);
					WriteStringLine(output);
					continue;
				}
			}

			// MAGE_VAR_TOKEN_FLOAT3
			{
				const F32x3 *v = std::get_if< F32x3 >(&value);
				if (nullptr != v) {
					sprintf_s(output, _countof(output),
						"%s %s %f %f %f", 
						MAGE_VAR_TOKEN_FLOAT3, key.c_str(),
						v->m_x, v->m_y, v->m_z);
					WriteStringLine(output);
					continue;
				}
			}

			// MAGE_VAR_TOKEN_FLOAT4
			{
				const F32x4 *v = std::get_if< F32x4 >(&value);
				if (nullptr != v) {
					sprintf_s(output, _countof(output),
						"%s %s %f %f %f %f", 
						MAGE_VAR_TOKEN_FLOAT4, key.c_str(), 
						v->m_x, v->m_y, v->m_z, v->m_w);
					WriteStringLine(output);
					continue;
				}
			}

			// MAGE_VAR_TOKEN_STRING
			{
				const string *v = std::get_if< string >(&value);
				if (nullptr != v) {
					sprintf_s(output, _countof(output), "%s %s \"%s\"",
						MAGE_VAR_TOKEN_STRING, key.c_str(),
						v->c_str());
					WriteStringLine(output);
					continue;
				}
			}

			Warning("%ls: could not export variable: %s", 
				GetFilename().c_str(), key.c_str());
		}
	}
}