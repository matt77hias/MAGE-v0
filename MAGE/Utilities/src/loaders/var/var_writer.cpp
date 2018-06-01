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
		char buffer[MAX_PATH];
		const auto not_null_buffer = NotNull< const_zstring >(buffer);

		for (const auto& [key, value] : m_variable_buffer) {
				
			// bool
			{
				const auto v = std::get_if< bool >(&value);
				if (nullptr != v) {
					if (*v) {
						sprintf_s(buffer, std::size(buffer), 
							      "%s %s true",
							      g_var_token_bool, key.c_str());
					}
					else {
						sprintf_s(buffer, std::size(buffer),
							      "%s %s false",
							      g_var_token_bool, key.c_str());
					}
					WriteStringLine(not_null_buffer);
					continue;
				}
			}

			// F32
			{
				const auto v = std::get_if< F32 >(&value);
				if (nullptr != v) {
					sprintf_s(buffer, std::size(buffer),
							  "%s %s %f",
							  g_var_token_F32, key.c_str(),
							  *v);
					WriteStringLine(not_null_buffer);
					continue;
				}
			}

			// F32x2
			{
				const auto v = std::get_if< F32x2 >(&value);
				if (nullptr != v) {
					const auto [x, y] = *v;
					sprintf_s(buffer, std::size(buffer),
							  "%s %s %f %f",
							  g_var_token_F32x2, key.c_str(),
							  x, y);
					WriteStringLine(not_null_buffer);
					continue;
				}
			}

			// F32x3
			{
				const auto v = std::get_if< F32x3 >(&value);
				if (nullptr != v) {
					const auto [x, y, z] = *v;
					sprintf_s(buffer, std::size(buffer),
							  "%s %s %f %f %f",
							  g_var_token_F32x3, key.c_str(),
							  x, y, z);
					WriteStringLine(not_null_buffer);
					continue;
				}
			}

			// F32x4
			{
				const auto v = std::get_if< F32x4 >(&value);
				if (nullptr != v) {
					const auto [x, y, z, w] = *v;
					sprintf_s(buffer, std::size(buffer),
							  "%s %s %f %f %f %f",
							  g_var_token_F32x4, key.c_str(),
							  x, y, z, w);
					WriteStringLine(not_null_buffer);
					continue;
				}
			}

			// S32
			{
				const auto v = std::get_if< S32 >(&value);
				if (nullptr != v) {
					sprintf_s(buffer, std::size(buffer),
							  "%s %s %d",
							  g_var_token_S32, key.c_str(),
							  *v);
					WriteStringLine(not_null_buffer);
					continue;
				}
			}

			// S32x2
			{
				const auto v = std::get_if< S32x2 >(&value);
				if (nullptr != v) {
					const auto [x, y] = *v;
					sprintf_s(buffer, std::size(buffer),
							  "%s %s %d %d",
							  g_var_token_S32x2, key.c_str(),
							  x, y);
					WriteStringLine(not_null_buffer);
					continue;
				}
			}

			// S32x3
			{
				const auto v = std::get_if< S32x3 >(&value);
				if (nullptr != v) {
					const auto [x, y, z] = *v;
					sprintf_s(buffer, std::size(buffer),
							  "%s %s %d %d %d",
							  g_var_token_S32x3, key.c_str(),
							  x, y, z);
					WriteStringLine(not_null_buffer);
					continue;
				}
			}

			// S32x4
			{
				const auto v = std::get_if< S32x4 >(&value);
				if (nullptr != v) {
					const auto [x, y, z, w] = *v;
					sprintf_s(buffer, std::size(buffer),
							  "%s %s %d %d %d %d",
							  g_var_token_S32x4, key.c_str(),
							  x, y, z, w);
					WriteStringLine(not_null_buffer);
					continue;
				}
			}

			// U32
			{
				const auto v = std::get_if< U32 >(&value);
				if (nullptr != v) {
					sprintf_s(buffer, std::size(buffer),
							  "%s %s %u",
							  g_var_token_U32, key.c_str(),
							  *v);
					WriteStringLine(not_null_buffer);
					continue;
				}
			}

			// U32x2
			{
				const auto v = std::get_if< U32x2 >(&value);
				if (nullptr != v) {
					const auto [x, y] = *v;
					sprintf_s(buffer, std::size(buffer),
							  "%s %s %u %u",
							  g_var_token_U32x2, key.c_str(),
							  x, y);
					WriteStringLine(not_null_buffer);
					continue;
				}
			}

			// U32x3
			{
				const auto v = std::get_if< U32x3 >(&value);
				if (nullptr != v) {
					const auto [x, y, z] = *v;
					sprintf_s(buffer, std::size(buffer),
							  "%s %s %u %u %u",
							  g_var_token_U32x3, key.c_str(),
							  x, y, z);
					WriteStringLine(not_null_buffer);
					continue;
				}
			}

			// U32x4
			{
				const auto v = std::get_if< U32x4 >(&value);
				if (nullptr != v) {
					const auto [x, y, z, w] = *v;
					sprintf_s(buffer, std::size(buffer),
							  "%s %s %u %u %u %u",
							  g_var_token_U32x4, key.c_str(),
							  x, y, z, w);
					WriteStringLine(not_null_buffer);
					continue;
				}
			}

			// string
			{
				const auto v = std::get_if< string >(&value);
				if (nullptr != v) {
					sprintf_s(buffer, std::size(buffer), 
						      "%s %s \"%s\"",
						      g_var_token_string, key.c_str(),
						      v->c_str());
					WriteStringLine(not_null_buffer);
					continue;
				}
			}

			Warning("%ls: could not export variable: %s", 
				    GetPath().c_str(), key.c_str());
		}
	}
}