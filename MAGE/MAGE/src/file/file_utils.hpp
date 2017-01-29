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

	/**
	 Returns the filename of the given file.

	 @param[in]		path
					A reference to the path of the file.
	 @param[in]		name
					A reference to the name of the file.
	 @return		The filename of the given file.
	 */
	inline string GetFilename(const string &path, const string &name) {
		return path + name;
	}

	/**
	 Returns the filename of the given file.

	 @param[in]		path
					A reference to the path of the file.
	 @param[in]		name
					A reference to the name of the file.
	 @return		The filename of the given file.
	 */
	inline wstring GetFilename(const wstring &path, const wstring &name) {
		return path + name;
	}

	/**
	 Returns the extension of the given file.

	 @param[in]		fname
					A reference to the filename of the file.
	 @return		The extension of the given file.
	 */
	inline string GetFileExtension(const string &fname) {
		const size_t begin_pos = fname.find_last_of(".");
		return fname.substr(begin_pos + 1);
	}

	/**
	 Returns the extension of the given file.

	 @param[in]		fname
					A reference to the filename of the file.
	 @return		The extension of the given file.
	 */
	inline wstring GetFileExtension(const wstring &fname) {
		const size_t begin_pos = fname.find_last_of(L".");
		return fname.substr(begin_pos + 1);
	}

	/**
	 Returns the name of the given file.

	 @param[in]		fname
					A reference to the filename of the file.
	 @return		The name of the given file.
	 */
	inline string GetFileName(const string &fname) {
		const size_t begin_pos = fname.find_last_of("/");
		return fname.substr(begin_pos + 1);
	}

	/**
	 Returns the name of the given file.

	 @param[in]		fname
					A reference to the filename of the file.
	 @return		The name of the given file.
	 */
	inline wstring GetFileName(const wstring &fname) {
		const size_t begin_pos = fname.find_last_of(L"/");
		return fname.substr(begin_pos + 1);
	}

	/**
	 Returns the path of the given file.

	 @param[in]		fname
					A reference to the filename of the file.
	 @return		The path of the given file.
	 */
	inline string GetPathName(const string &fname) {
		const size_t end_pos = fname.find_last_of("/");
		return fname.substr(0, end_pos + 1);
	}

	/**
	 Returns the path of the given file.

	 @param[in]		fname
					A reference to the filename of the file.
	 @return		The path of the given file.
	 */
	inline wstring GetPathName(const wstring &fname) {
		const size_t end_pos = fname.find_last_of(L"/");
		return fname.substr(0, end_pos + 1);
	}
}