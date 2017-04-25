#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Returns the filename of the given file.

	 @pre			The path must end with a '/' character.
	 @param[in]		path
					A reference to the path of the file.
	 @param[in]		name
					A reference to the name of the file.
	 @return		The filename of the given file.
	 */
	inline const string GetFilename(const string &path, const string &name) {
		return path + name;
	}

	/**
	 Returns the filename of the given file.

	 @pre			The path must end with a '/' character.
	 @param[in]		path
					A reference to the path of the file.
	 @param[in]		name
					A reference to the name of the file.
	 @return		The filename of the given file.
	 */
	inline const wstring GetFilename(const wstring &path, const wstring &name) {
		return path + name;
	}

	/**
	 Returns the extension of the given file.

	 @param[in]		fname
					A reference to the filename of the file.
	 @return		The extension of the given file.
	 @throws		FormattedException
					The filename does not have a file extension.
	 */
	inline const string GetFileExtension(const string &fname) {
		const size_t begin_pos = fname.find_last_of(".");
		if (begin_pos == string::npos) {
			throw FormattedException("The filename does not have a file extension.");
		}
		return fname.substr(begin_pos + 1);
	}

	/**
	 Returns the extension of the given file.

	 @param[in]		fname
					A reference to the filename of the file.
	 @return		The extension of the given file.
	 @throws		FormattedException
					The filename does not have a file extension.
	 */
	inline const wstring GetFileExtension(const wstring &fname) {
		const size_t begin_pos = fname.find_last_of(L".");
		if (begin_pos == string::npos) {
			throw FormattedException("The filename does not have a file extension.");
		}
		return fname.substr(begin_pos + 1);
	}

	/**
	 Returns the name of the given file.

	 @param[in]		fname
					A reference to the filename of the file.
	 @return		The name of the given file.
	 @throws		FormattedException
					The filename does not have a file path.
	 */
	inline const string GetFileName(const string &fname) {
		const size_t begin_pos = fname.find_last_of("/");
		if (begin_pos == string::npos) {
			throw FormattedException("The filename does not have a file path.");
		}
		return fname.substr(begin_pos + 1);
	}

	/**
	 Returns the name of the given file.

	 @param[in]		fname
					A reference to the filename of the file.
	 @return		The name of the given file.
	 @throws		FormattedException
					The filename does not have a file path.
	 */
	inline const wstring GetFileName(const wstring &fname) {
		const size_t begin_pos = fname.find_last_of(L"/");
		if (begin_pos == string::npos) {
			throw FormattedException("The filename does not have a file path.");
		}
		return fname.substr(begin_pos + 1);
	}

	/**
	 Returns the path of the given file.

	 @param[in]		fname
					A reference to the filename of the file.
	 @return		The path of the given file.
	 @throws		FormattedException
					The filename does not have a file path.
	 */
	inline const string GetPathName(const string &fname) {
		const size_t end_pos = fname.find_last_of("/");
		if (end_pos == string::npos) {
			throw FormattedException("The filename does not have a file path.");
		}
		return fname.substr(0, end_pos + 1);
	}

	/**
	 Returns the path of the given file.

	 @param[in]		fname
					A reference to the filename of the file.
	 @return		The path of the given file.
	 @throws		FormattedException
					The filename does not have a file path.
	 */
	inline const wstring GetPathName(const wstring &fname) {
		const size_t end_pos = fname.find_last_of(L"/");
		if (end_pos == string::npos) {
			throw FormattedException("The filename does not have a file path.");
		}
		return fname.substr(0, end_pos + 1);
	}

	/**
	 Returns the filename of the given file without its file extension.

	 @param[in]		fname
					A reference to the filename of the file.
	 @return		The filename of the given file without its file extension.
	 @throws		FormattedException
					The filename does not have a file path.
	 */
	inline const string GetFilenameWithoutFileExtension(const string &fname) {
		const size_t end_pos = fname.find_last_of(".");
		if (end_pos == string::npos) {
			throw FormattedException("The filename does not have a file extension.");
		}
		return fname.substr(0, end_pos);
	}

	/**
	 Returns the filename of the given file without its file extension.

	 @param[in]		fname
					A reference to the filename of the file.
	 @return		The filename of the given file without its file extension.
	 @throws		FormattedException
					The filename does not have a file path.
	 */
	inline const wstring GetFilenameWithoutFileExtension(const wstring &fname) {
		const size_t end_pos = fname.find_last_of(L".");
		if (end_pos == string::npos) {
			throw FormattedException("The filename does not have a file extension.");
		}
		return fname.substr(0, end_pos);
	}
}