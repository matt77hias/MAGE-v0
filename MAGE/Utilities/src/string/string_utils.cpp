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
	const wstring StringToWString(const string& str) {
		return wstring(CA2W(str.c_str()));
	}

	[[nodiscard]]
	const string WStringToString(const wstring& str) {
		return string(CW2A(str.c_str()));
	}
}