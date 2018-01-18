#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Checks whether a file with the given filename exists.

	 @param[in]		fname
					A reference to the filename of the file.
	 @return		@c true if a file with the given filename exists. @c false 
					otherwise.
	 */
	[[nodiscard]] bool FileExists(const wstring &fname) noexcept;

	/**
	 Returns the filename of the given file.

	 @pre			@a path must end with a '/' character.
	 @tparam		StringT
					The string type.
	 @param[in]		path
					A reference to the path of the file.
	 @param[in]		name
					A reference to the name of the file.
	 @return		The filename of the given file.
	 */
	template< typename StringT >
	[[nodiscard]] const StringT 
		GetFilename(const StringT &path, const StringT &name);

	/**
	 Returns the extension of the given file.

	 @tparam		StringT
					The string type.
	 @param[in]		fname
					A reference to the filename of the file.
	 @return		The extension of the given file.
	 @throws		Exception
					The filename does not have a file extension.
	 */
	template< typename StringT >
	[[nodiscard]] const StringT GetFileExtension(const StringT &fname);

	/**
	 Returns the name of the given file.

	 @tparam		StringT
					The string type.
	 @param[in]		fname
					A reference to the filename of the file.
	 @return		The name of the given file.
	 @throws		Exception
					The filename does not have a file path.
	 */
	template< typename StringT >
	[[nodiscard]] const StringT GetFileName(const StringT &fname);

	/**
	 Returns the path of the given file.

	 @tparam		StringT
					The string type.
	 @param[in]		fname
					A reference to the filename of the file.
	 @return		The path of the given file.
	 @throws		Exception
					The filename does not have a file path.
	 */
	template< typename StringT >
	[[nodiscard]] const StringT GetPathName(const StringT &fname);

	/**
	 Returns the filename of the given file without its file extension.
	 
	 @tparam		StringT
					The string type.
	 @param[in]		fname
					A reference to the filename of the file.
	 @return		The filename of the given file without its file extension.
	 @throws		Exception
					The filename does not have a file extension.
	 */
	template< typename StringT >
	[[nodiscard]] const StringT
		GetFilenameWithoutFileExtension(const StringT &fname);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "file\file_utils.tpp"

#pragma endregion