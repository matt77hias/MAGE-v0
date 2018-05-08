//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\var\var_writer.hpp"
#include "loaders\var\var_tokens.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	VARWriter::VARWriter(const std::map< string, Value >& variable_buffer)
		: Writer(), 
		m_variable_buffer(variable_buffer) {}

	VARWriter::VARWriter(VARWriter&& writer) noexcept = default;

	VARWriter::~VARWriter() = default;

	void VARWriter::Write() {
		
		char output[MAX_PATH];

		for (const auto& [key, value] : m_variable_buffer) {
				
			// bool
			{
				const auto v = std::get_if< bool >(&value);
				if (nullptr != v) {
					if (*v) {
						sprintf_s(output, std::size(output), 
							      "%s %s true",
							      g_var_token_bool, key.c_str());
					}
					else {
						sprintf_s(output, std::size(output),
							      "%s %s false",
							      g_var_token_bool, key.c_str());
					}
					WriteStringLine(output);
					continue;
				}
			}

			// int
			{
				const auto v = std::get_if< S32 >(&value);
				if (nullptr != v) {
					sprintf_s(output, std::size(output),
						      "%s %s %d",
						      g_var_token_int, key.c_str(), 
						      *v);
					WriteStringLine(output);
					continue;
				}
			}

			// int2
			{
				const auto v = std::get_if< S32x2 >(&value);
				if (nullptr != v) {
					sprintf_s(output, std::size(output),
						      "%s %s %d %d",
						      g_var_token_int2, key.c_str(), 
						      (*v)[0], (*v)[1]);
					WriteStringLine(output);
					continue;
				}
			}

			// int3
			{
				const auto v = std::get_if< S32x3 >(&value);
				if (nullptr != v) {
					sprintf_s(output, std::size(output),
						      "%s %s %d %d %d",
						      g_var_token_int3, key.c_str(), 
						      (*v)[0], (*v)[1], (*v)[2]);
					WriteStringLine(output);
					continue;
				}
			}

			// float
			{
				const auto v = std::get_if< F32 >(&value);
				if (nullptr != v) {
					sprintf_s(output, std::size(output),
						      "%s %s %f",
						      g_var_token_float, key.c_str(),
						      *v);
					WriteStringLine(output);
					continue;
				}
			}

			// float2
			{
				const auto v = std::get_if< F32x2 >(&value);
				if (nullptr != v) {
					sprintf_s(output, std::size(output),
						      "%s %s %f %f", 
						      g_var_token_float2, key.c_str(),
						      (*v)[0], (*v)[1]);
					WriteStringLine(output);
					continue;
				}
			}

			// float3
			{
				const auto v = std::get_if< F32x3 >(&value);
				if (nullptr != v) {
					sprintf_s(output, std::size(output),
						      "%s %s %f %f %f", 
						      g_var_token_float3, key.c_str(),
						      (*v)[0], (*v)[1], (*v)[2]);
					WriteStringLine(output);
					continue;
				}
			}

			// float4
			{
				const auto v = std::get_if< F32x4 >(&value);
				if (nullptr != v) {
					sprintf_s(output, std::size(output),
						      "%s %s %f %f %f %f", 
						      g_var_token_float4, key.c_str(), 
						      (*v)[0], (*v)[1], (*v)[2], (*v)[3]);
					WriteStringLine(output);
					continue;
				}
			}

			// string
			{
				const auto v = std::get_if< string >(&value);
				if (nullptr != v) {
					sprintf_s(output, std::size(output), 
						      "%s %s \"%s\"",
						      g_var_token_string, key.c_str(),
						      v->c_str());
					WriteStringLine(output);
					continue;
				}
			}

			Warning("%ls: could not export variable: %s", 
				    GetPath().c_str(), key.c_str());
		}
	}
}