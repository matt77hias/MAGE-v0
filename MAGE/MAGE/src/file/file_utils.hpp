#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <string>
namespace mage {
	using std::string;
	using std::wstring;
}

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	inline string GetFilename(const string &path, const string &name) {
		return path + name;
	}

	inline wstring GetFilename(const wstring &path, const wstring &name) {
		return path + name;
	}

	inline string GetFileExtension(const string &fname) {
		const size_t begin_pos = fname.find_last_of(".");
		return fname.substr(begin_pos + 1);
	}

	inline wstring GetFileExtension(const wstring &fname) {
		const size_t begin_pos = fname.find_last_of(L".");
		return fname.substr(begin_pos + 1);
	}

	inline string GetFileName(const string &fname) {
		const size_t begin_pos = fname.find_last_of("/");
		return fname.substr(begin_pos + 1);
	}

	inline wstring GetFileName(const wstring &fname) {
		const size_t begin_pos = fname.find_last_of(L"/");
		return fname.substr(begin_pos + 1);
	}

	inline string GetPathName(const string &fname) {
		const size_t end_pos = fname.find_last_of("/");
		return fname.substr(0, end_pos + 1);
	}

	inline wstring GetPathName(const wstring &fname) {
		const size_t end_pos = fname.find_last_of(L"/");
		return fname.substr(0, end_pos + 1);
	}
}