#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include <string>
namespace mage {
	using std::string;
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	inline string GetFileExtension(const string &fname) {
		const size_t pos = fname.find_last_of(".");
		return fname.substr(pos + 1);
	}
}