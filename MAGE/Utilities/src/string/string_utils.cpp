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

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	[[nodiscard]]
	const std::wstring StringToWString(const std::string& str) {
		return std::wstring(CA2WEX< 512 >(str.c_str()));
	}

	[[nodiscard]]
	const std::string WStringToString(const std::wstring& str) {
		return std::string(CW2AEX< 512 >(str.c_str()));
	}
}