//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <limits>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	DWORD UTF8toUTF16::Convert(std::string_view s) {
		if (static_cast< std::size_t >(std::numeric_limits< int >::max()) < s.size()) {
			return ERROR_INVALID_PARAMETER;
		}
		const auto s_size = static_cast< int >(s.size());

		if (0 == s_size) {
			m_buffer.resize(1u);
			return 0u;
		}

		const int required_size = MultiByteToWideChar(
			CP_UTF8, MB_ERR_INVALID_CHARS, s.data(), s_size, nullptr, 0);
		if (0 == required_size) {
			return GetLastError();
		}

		m_buffer.resize(static_cast< std::size_t >(required_size) + 1u);

		const int written_size = MultiByteToWideChar(
			CP_UTF8, MB_ERR_INVALID_CHARS, s.data(), s_size, m_buffer.data(), required_size);
		if (0 == written_size) {
			return GetLastError();
		}

		return 0u;
	}

	DWORD UTF16toUTF8::Convert(std::wstring_view s) {
		if (static_cast< std::size_t >(std::numeric_limits< int >::max()) < s.size()) {
			return ERROR_INVALID_PARAMETER;
		}
		const auto s_size = static_cast< int >(s.size());

		if (0 == s_size) {
			m_buffer.resize(1u);
			return 0u;
		}

		const int required_size = WideCharToMultiByte(
			CP_UTF8, 0u, s.data(), s_size, nullptr, 0, nullptr, nullptr);
		if (0 == required_size) {
			return GetLastError();
		}

		m_buffer.resize(static_cast< std::size_t >(required_size) + 1u);

		const int written_size = WideCharToMultiByte(
			CP_UTF8, 0u, s.data(), s_size, m_buffer.data(), required_size, nullptr, nullptr);
		if (0 == written_size) {
			return GetLastError();
		}

		return 0u;
	}
}