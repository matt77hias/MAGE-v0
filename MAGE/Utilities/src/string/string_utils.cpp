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

#include <AtlBase.h>
#include <atlconv.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	[[nodiscard]]
	const std::wstring StringToWString(const std::string& str) {
		return std::wstring(CA2W(str.c_str()));
	}

	[[nodiscard]]
	const std::string WStringToString(const std::wstring& str) {
		return std::string(CW2A(str.c_str()));
	}
}